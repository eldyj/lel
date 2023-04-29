/*std::vector<std::string>
lel_tokens(const std::string& text)
{
	std::vector<std::string> tokens;
	std::regex re(R"((\"[^\"]+\"|\S+))");
	std::sregex_iterator iter(text.begin(), text.end(), re);
	std::sregex_iterator end;

	while (iter != end)
		tokens.push_back(iter++->str());

	return tokens;
}*/

bool
is_space(char c)
{
	return c == '\t' || c == '\n' || c == ' ';
}

std::vector<std::string>
lel_tokens(const std::string& text)
{
	std::vector<std::string> tokens;
	std::string token = "";
	bool in_str = false;

	for (unsigned long i = 0; i < text.size(); ++i) {
		if (in_str) {
			token += text[i];
			if (text[i] == '"') {
				in_str = false;
			}
		} else if (is_space(text[i])) {
			if (token != "") {
				tokens.push_back(token);
				token = "";
			}
		} else {
			if (text[i] == '"') {
				in_str = true;
			}
			token += text[i];
		}
	}
	
	if (token != "") {
		tokens.push_back(token);
		token = "";
	}

	return tokens;
}
