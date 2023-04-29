std::string
read_file(const std::string& s)
{
	std::ifstream file(s);

	if (!file)
		V_ERROR("file '" << s << "' not exists");

	return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

void
write_file(const std::string& n, const std::string& s)
{
	std::ofstream file(n);
	file << s;
	file.close();
}
