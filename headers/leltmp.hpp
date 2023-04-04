namespace LelTmp {
	std::vector<std::string> stack = {};
	std::map<std::string,std::function<void()>> fns;
	std::string include_dir;
	std::string current_dir;
	bool comment = false;
	bool skip_next = false;
	bool get_macro_name = false;
	std::string current_macro = "";
	std::map<std::string,std::string> macros;
	char **argv;
	int argc;
}
