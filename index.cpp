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
#define A_ERROR(category, message) {std::cerr << category << "Error: " << message << std::endl;exit(1);}
#define T_ERROR(message) A_ERROR("Type",message)
#define S_ERROR(message) A_ERROR("Stack",message)
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
is_float(const str s) {
	try {
		std::stof(s);
		return true;
	} catch (std::invalid_argument e) {
		return is_int128(s);
	}
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

	std::cerr << "wtf is " << op << "?" << std::endl;
#if 0
	if (op == "*/")
		LelTmp::comment = false;
	else if (LelTmp::comment || LelTmp::skip_next)
		LelTmp::skip_next = false;
	else if (op == "/*")
		LelTmp::comment = true;
	else if (op == "=") {
		std::cout << "macro start" << std::endl;
		LelTmp::get_macro_name = true;
	}
	else if (op == ".") {
		std::cout << LelTmp::macros[LelTmp::current_macro] << std::endl;
		std::cout << "endmacro " << LelTmp::current_macro << std::endl; 
		LelTmp::current_macro = "";
	}
	else if (LelTmp::current_macro != "") {
		LelTmp::macros[LelTmp::current_macro] += ((LelTmp::macros[LelTmp::current_macro] == "") ?  "" : " ") + op;
	}
	else if (macros_exists(op)) {
		str s = LelTmp::macros[op];
		std::cout << "macro " << op << ": " << s << std::endl;
		eval_string(s);
	}
	else if (is_float(op) || is_quoted(op))
		LelTmp::stack.push_back(op);
	else if (LelTmp::get_macro_name) {
		LelTmp::current_macro = op;
		LelTmp::macros[op] = "";
	}
	else if (fn_exists(op)) {
		LelTmp::fns[op]();
	}
	else {
		std::cerr << "wtf is " << op << "?" << std::endl;
	}
#endif
}

void
eval_string(const str& s)
{
	//std::cout << "eval-str log: " << s << std::endl;
	str_vec v = split(s);
	for (const str& op: v) {
		//std::cout << "eval-op log: " << op << std::endl;
		eval_op(op);
	}
}

void
load_file(str s)
{
	std::ifstream file(s);
	if (!file)
		return;

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
#include"fns.list"
	use_file("stdop");
	use_file("stdfn");
	use_file("stdmath");
	load_file(std::string(argv[1]));
	return 0;
}
