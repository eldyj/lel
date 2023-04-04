#include<iostream>
#include<vector>
#include<regex>
#include<algorithm>
#include<map>
#include<functional>
#include<cmath>
#include<fstream>
#include"headers/int128.hpp"
#include"headers/dir.hpp"
typedef std::vector<std::string> str_vec;
typedef std::string str;

void rm();

namespace LelTmp {
	str_vec stack = {};
	std::map<str,std::function<void()>> fns;
	str include_dir;
	str current_dir;
	bool comment = false;
	bool skip_next = false;
	bool get_macro_name = false;
	str current_macro = "";
	std::map<str,str> macros;
}

void
spush(const str& s)
{
	try {
		LelTmp::stack.push_back(s);
	} catch (std::bad_alloc) {
		S_ERROR("stack overflow");
	}
}

const str&
spop(void)
{
	if (LelTmp::stack.size() == 0) {
		S_ERROR("stack underflow");
	}
	str& s = LelTmp::stack.back();
	rm();
	return s;
}

bool
is_float(const str& s) {
	try {
		std::stof(s);
		return true;
	} catch (std::invalid_argument e) {
		return is_int128(s);
	}
}

bool
non_int(const str& s) {
	return s.find('.') != std::string::npos;
}

bool
is_quoted(const str& s)
{
	return s.front() == '"' && s.back() == '"';
}

str
quote(const str& s)
{
	return "\"" + s + "\"";
}

str
unquote(const str& s)
{
	str r = s;
	r.erase(r.length()-1,1);
	r.erase(0,1);
	//std::cout << "unquote log: '" << s << "' '" << r << "'" << std::endl;
	return r;
}

str
to_lelstr(const str& s)
{
	return is_quoted(s) ? s : quote(s);
}

str
to_cppstr(const str& s)
{
	return is_quoted(s) ? unquote(s) : s;
}

str
lelstr_join(const str& s1, const str& s2)
{
	return to_lelstr(to_cppstr(s1) + to_cppstr(s2));
}

bool
macros_exists(const str& s)
{
	return LelTmp::macros.find(s) != LelTmp::macros.end();
}

bool
fn_exists(const str& s)
{
	return LelTmp::fns.find(s) != LelTmp::fns.end();
}

str_vec
split(const str& text)
{
	str_vec tokens;
	std::regex re(R"((\"[^\"]+\"|\S+))");
	std::sregex_iterator iter(text.begin(), text.end(), re);
	std::sregex_iterator end;

	while (iter != end)
		tokens.push_back(iter++->str());

	return tokens;
}

void eval_string(const str&);

void
eval_op(const str& op)
{
	if (op == "")
		return;

	if (op == "/*") {
		LelTmp::comment = true;
		return;
	}

	if (op == "*/") {
		LelTmp::comment = false;
		return;
	}

	if (LelTmp::comment)
		return;

	if (LelTmp::skip_next) {
		LelTmp::skip_next = false;
		return;
	}

	if (op == "=") {
		LelTmp::get_macro_name = true;
		return;
	}

	if (op == ".") {
		LelTmp::current_macro = "";
		return;
	}

	if (LelTmp::current_macro != "") {
		LelTmp::macros[LelTmp::current_macro] += " " + op;
		return;
	}

	if (macros_exists(op)) {
		eval_string(LelTmp::macros[op]);
		return;
	}

	if (is_float(op)) {
		spush(op);
		return;
	}

	if (LelTmp::get_macro_name) {
		LelTmp::current_macro = op;
		LelTmp::macros[op] = "";
		LelTmp::get_macro_name = false;
		return;
	}

	if (fn_exists(op)) {
		LelTmp::fns[op]();
		return;
	}

	if (is_quoted(op)) {
		spush(op);
		return;
	}

	V_ERROR("wtf is `" << op << "`?");
}

void
eval_string(const str& s)
{
	str_vec v = split(s);

	for (const str& op: v)
		eval_op(op);
}

void
load_file(str s)
{
	std::ifstream file(s);
	if (!file)
		V_ERROR("file '" << s << "' not exists");

	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	eval_string(content);
}

void
use_file(str s)
{
	load_file(LelTmp::include_dir + s + ".lel");
}

#include"fns.cpp"

int
main(int argc, char* argv[])
{
	LelTmp::include_dir = dirname(std::string(argv[0]))+"/std/";
#include"fnlist.cpp"
	use_file("stdop");
	use_file("stdfn");
	use_file("stdmath");
	load_file(std::string(argv[1]));
	return 0;
}
