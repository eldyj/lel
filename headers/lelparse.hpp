std::vector<std::string>
lel_tokens(const std::string& text)
{
	std::vector<std::string> tokens;
	std::regex re(R"((\"[^\"]+\"|\S+))");
	std::sregex_iterator iter(text.begin(), text.end(), re);
	std::sregex_iterator end;

	while (iter != end)
		tokens.push_back(iter++->str());

	return tokens;
}
