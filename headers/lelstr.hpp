bool
is_quoted(const std::string& s)
{
	return s.front() == '"' && s.back() == '"';
}

std::string
quote(const std::string& s)
{
	return "\"" + s + "\"";
}

std::string
unquote(const std::string& s)
{
	std::string r = s;
	r.erase(r.length()-1,1);
	r.erase(0,1);
	return r;
}

std::string
to_lelstr(const std::string& s)
{
	return is_quoted(s) ? s : quote(s);
}

std::string
to_cppstr(const std::string& s)
{
	return is_quoted(s) ? unquote(s) : s;
}

std::string
lelstr_join(const std::string& s1, const std::string& s2)
{
	return to_lelstr(to_cppstr(s1) + to_cppstr(s2));
}
