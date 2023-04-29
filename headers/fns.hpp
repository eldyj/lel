#define stoi128(s) std::stoll(s)
#define i128tos(s) std::to_string(s)

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
		spush(std::to_string(int(stoi128(s1) < stoi128(s2))));;
}

void
no()
{
	std::string s1 = spop();
	if (!is_float(s1))
		T_ERROR("non number argument passed to no");

	spush(std::to_string(int(!std::stod(s1))));
}

void
unl()
{
	std::string s1 = spop();
	if (!is_float(s1))
		T_ERROR("non number argument passed to unl");

	LelTmp::skip_next = !!std::stod(s1);
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
	else {
		long long s2i = stoi128(s2);
		double r = powl(stoi128(s1),s2i);

		if (s2i < 0) 
			spush(std::to_string(r));
		else
			spush(std::to_string((long long) r));
	}
}

void
swp()
{
	std::string s1 = spop();
	std::string s2 = spop();
	spush(s1);
	spush(s2);
}

void
pr()
{
	//std::cout << to_cppstr(to_lelstr(spop()));
	fputs(to_cppstr(to_lelstr(spop())).c_str(), stdout);
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

void
done()
{
	std::string s = spop();
	if (!is_float(s))
		T_ERROR("non number argument passed to exit")
	if (!non_int(s))
		T_ERROR("non int passed to exit");

	exit(std::stoi(s));
}

void
ge()
{
	std::string s = spop();
	if (!is_quoted(s))
		T_ERROR("non string argument passed to ge");
	
	spush(quote(std::string(std::getenv(to_cppstr(s).c_str()))));
}

void
ga()
{
	std::string s = spop();

	if (!is_float(s))
		T_ERROR("non number argument passed to ga");

	if (non_int(s))
		T_ERROR("non int argument passed to ga");

	long long n = stoi128(s);

	if (n < 0)
		V_ERROR("negative int passed to ga");

	if (n >= LelTmp::argc)
		V_ERROR("index too large for ga");

	spush(quote(std::string(LelTmp::argv[n])));
}

void
rf()
{
	std::string s = spop();
	std::cout << "rflog: " << s << std::endl;

	if (!is_quoted(s))
		T_ERROR("non string argument passed to rf");

	spush(quote(read_file(to_cppstr(s))));
}

void
wf()
{
	std::string s1 = spop();
	std::string s2 = spop();

	if (!is_quoted(s1) || !is_quoted(s2))
		T_ERROR("non string argument passed to wf");

	write_file(to_cppstr(s1),to_cppstr(s2));
}

#undef stoi128
//#undef i128tos
