void
dup()
{
	spush(LelTmp::stack.back());
}

void
rm()
{
	LelTmp::stack.pop_back();
}

void
eq()
{
	spush(std::to_string(int(spop() == spop())));
}

void
gt()
{
	std::string s1 = spop();
	std::string s2 = spop();
	if (!is_float(s1) || !is_float(s2))
		T_ERROR("non number argument passed to gt");

	if (non_int(s1) || non_int(s2))
		spush(std::to_string(int(std::stod(s1) > std::stod(s2))));
	else
		spush(std::to_string(int(stoi128(s1) > stoi(s2))));
}

void
lt()
{
	std::string s1 = spop();
	std::string s2 = spop();
	if (!is_float(s1) || !is_float(s2))
		T_ERROR("non number argument passed to lt");

	if (non_int(s1) || non_int(s2))
		spush(std::to_string(int(std::stod(s1) < std::stod(s2))));
	else
		spush(std::to_string(int(stoi128(s1) < stoi128(s2))));
	//std::cout<<"lt was called"<<std::endl;
}

void
no()
{
	std::string s1 = spop();
	if (!is_float(s1))
		T_ERROR("non number argument passed to no");

	spush(std::to_string(int(!std::stod(s1))));
	//std::cout<<"no was called"<<std::endl;
}

void
unl()
{
	std::string s1 = spop();
	if (!is_float(s1))
		T_ERROR("non number argument passed to unl");

	LelTmp::skip_next = !!std::stod(s1);
	//std::cout<<"unl was called"<<std::endl;
}

void
sum()
{
	std::string s1 = spop();
	std::string s2 = spop();

	if (!is_float(s1) || !is_float(s2))
		T_ERROR("mathematical operation with non-number");

	if (non_int(s1) || non_int(s2))
		spush(std::to_string(std::stod(s1) + std::stod(s2)));
	else
		spush(i128tos(stoi128(s1) + stoi128(s2)));
	//std::cout<<"sum was called"<<std::endl;
}

void
sub()
{
	std::string s1 = spop();
	std::string s2 = spop();

	if (!is_float(s1) || !is_float(s2))
		T_ERROR("mathematical operation with non-number");

	if (non_int(s1) || non_int(s2))
		spush(std::to_string(std::stod(s1) - std::stod(s2)));
	else
		spush(i128tos(stoi128(s1) - stoi128(s2)));
	//std::cout<<"sub was called"<<std::endl;
}

void
mul()
{
	std::string s1 = spop();
	std::string s2 = spop();

	if (!is_float(s1) || !is_float(s2))
		T_ERROR("mathematical operation with non-number");

	if (non_int(s1) || non_int(s2))
		spush(std::to_string(std::stod(s1) * std::stod(s2)));
	else
		spush(i128tos(stoi128(s1) * stoi128(s2)));
	//std::cout<<"mul was called"<<std::endl;
}

void
divn()
{
	std::string s1 = spop();
	std::string s2 = spop();

	if (!is_float(s1) || !is_float(s2))
		T_ERROR("mathematical operation with non-number");

	if (non_int(s1) || non_int(s2))
		spush(std::to_string(std::stod(s1) / std::stod(s2)));
	else
		spush(i128tos(stoi128(s1) / stoi128(s2)));
	//std::cout<<"div was called"<<std::endl;
}

void
poww()
{
	std::string s1 = spop();
	std::string s2 = spop();

	if (!is_float(s1) || !is_float(s2))
		T_ERROR("mathematical operation with non-number");

	if (non_int(s1) || non_int(s2))
		spush(std::to_string(pow(std::stod(s1), std::stod(s2))));
	else
		spush(std::to_string(pow(stoi128(s1), stoi128(s2))));
	//std::cout<<"pow was called"<<std::endl;
}

void
swp()
{
	std::string s1 = spop();
	std::string s2 = spop();
	spush(s1);
	spush(s2);
	//std::cout<<"swp was called"<<std::endl;
}

void
pr()
{
	std::cout << to_cppstr(to_lelstr(spop()));
	//printf((is_quoted(s)?unquote(s):s).c_str());
}

void
sj()
{
	spush(lelstr_join(spop(),spop()));
}

void
rd()
{
	std::string s;
	std::cin >> s;
	spush(quote(s));
}

void
load()
{
	std::string s = spop();
	if (!is_quoted(s))
		T_ERROR("non string argument passed to load");

	load_file(to_cppstr(s));
}

void
eval()
{
	std::string s = spop();
	if (!is_quoted(s))
		T_ERROR("non string argument passed to eval");

	eval_string(to_cppstr(s));
}

void
fl()
{
	std::string s = spop();
	if (!is_float(s))
		T_ERROR("non number passed to fl");

	spush(std::to_string((int)std::stod(s)));
}

void
nl()
{
	spush("\"\n\"");
}

void
use()
{
	std::string s = spop();
	if (!is_quoted(s))
		T_ERROR("non string argument passed to use");

	use_file(to_cppstr(s));
}
