void
spush(const std::string& s)
{
	try {
		LelTmp::stack.push_back(s);
	} catch (std::bad_alloc) {
		S_ERROR("stack overflow");
	}
}

const std::string&
spop(void)
{
	if (LelTmp::stack.size() == 0) {
		S_ERROR("stack underflow");
	}
	const std::string& s = LelTmp::stack.back();
	rm();
	return s;
}
