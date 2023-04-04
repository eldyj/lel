bool
is_float(const std::string& s) {
	try {
		std::stof(s);
		return true;
	} catch (std::invalid_argument e) {
		return is_int128(s);
	}
}

bool
non_int(const std::string& s) {
	return s.find('.') != std::string::npos;
}

bool
macros_exists(const std::string& s)
{
	return LelTmp::macros.find(s) != LelTmp::macros.end();
}

bool
fn_exists(const std::string& s)
{
	return LelTmp::fns.find(s) != LelTmp::fns.end();
}
