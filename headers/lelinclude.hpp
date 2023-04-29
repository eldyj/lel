void
load_file(const std::string& s)
{
	eval_string(read_file(s));
}

void
use_file(const std::string& s)
{
	load_file(LelTmp::include_dir + s + ".lel");
}

