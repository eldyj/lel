void
load_file(const std::string& s)
{
	std::ifstream file(s);

	if (!file)
		V_ERROR("file '" << s << "' not exists");

	std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	eval_string(content);
}

void
use_file(const std::string& s)
{
	load_file(LelTmp::include_dir + s + ".lel");
}

