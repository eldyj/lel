void
dup()
{
	spush(LelTmp::stack.back());
	//std::cout<<"dup was called"<<std::endl;
}

void
rm()
{
	LelTmp::stack.pop_back();
	//std::cout<<"rm was called"<<std::endl;
}

void
eq()
{
	spush(std::to_string(int(spop() == spop())));
	//std::cout<<"eq was called"<<std::endl;
}

void
gt()
{
	str s1 = spop();
	str s2 = spop();
	if (!is_float(s1)) {
		std::cerr << "first argument to gt must be number" << std::endl;
	} else if (!is_float(s2)) {
		std::cerr << "second argument to gt must be number" << std::endl;
	}	else {
		spush(std::to_string(int(std::stof(s1) > std::stof(s2))));
	}
	//std::cout<<"gt was called"<<std::endl;
}

void
lt()
{
	str s1 = spop();
	str s2 = spop();
	if (!is_float(s1)) {
		std::cerr << "first argument to lt must be number" << std::endl;
	} else if (!is_float(s2)) {
		std::cerr << "second argument to lt must be number" << std::endl;
	}	else {
		spush(std::to_string(int(std::stof(s1) < std::stof(s2))));
	}
	//std::cout<<"lt was called"<<std::endl;
}

void
no()
{
	str s1 = spop();
	if (!is_float(s1)) {
		std::cerr << "first argument to no must be number" << std::endl;
	} else {
		spush(std::to_string(int(!std::stof(s1))));
	}
	//std::cout<<"no was called"<<std::endl;
}

void
unl()
{
	str s1 = spop();
	if (!is_float(s1)) {
		std::cerr << "first argument to unl must be number" << std::endl;
	} else {
		LelTmp::skip_next = !!std::stof(s1);
	}
	//std::cout<<"unl was called"<<std::endl;
}

void
sum()
{
	str s1 = spop();
	str s2 = spop();

	if (!is_float(s1) || !is_float(s2)) {
		std::cerr << "mathematical operation with non-number" << std::endl;
	} else {
		spush(std::to_string(std::stof(s1) + std::stof(s2)));
	}
	//std::cout<<"sum was called"<<std::endl;
}

void
sub()
{
	str s1 = spop();
	str s2 = spop();

	if (!is_float(s1) || !is_float(s2)) {
		std::cerr << "mathematical operation with non-number" << std::endl;
	} else {
		spush(std::to_string(std::stof(s1) - std::stof(s2)));
	}
	//std::cout<<"sub was called"<<std::endl;
}

void
mul()
{
	str s1 = spop();
	str s2 = spop();

	if (!is_float(s1) || !is_float(s2)) {
		std::cerr << "mathematical operation with non-number" << std::endl;
	} else {
		spush(std::to_string(std::stof(s1) * std::stof(s2)));
	}
	//std::cout<<"mul was called"<<std::endl;
}

void
divn()
{
	str s1 = spop();
	str s2 = spop();

	if (!is_float(s1) || !is_float(s2)) {
		std::cerr << "mathematical operation with non-number" << std::endl;
	} else {
		spush(std::to_string(std::stof(s1) / std::stof(s2)));
	}
	//std::cout<<"div was called"<<std::endl;
}

void
poww()
{
	str s1 = spop();
	str s2 = spop();

	if (!is_float(s1) || !is_float(s2)) {
		std::cerr << "mathematical operation with non-number" << std::endl;
	} else {
		spush(std::to_string(pow(std::stof(s1), std::stof(s2))));
	}
	//std::cout<<"pow was called"<<std::endl;
}

void
swp()
{
	str s1 = spop();
	str s2 = spop();
	spush(s1);
	spush(s2);
	//std::cout<<"swp was called"<<std::endl;
}

void
pr()
{
	str s = spop();
	if (is_quoted(s))
		s = unquote(s);

	std::cout << s;
}

void
sj()
{
	str s1 = spop();
	str s2 = spop();

	if (is_quoted(s1)) {
		s1 = unquote(s1);
	}

	if (is_quoted(s2)) {
		s2 = unquote(s2);
	}

	spush(quote(s1 + s2));
}

void
rd()
{
	str s;
	std::cin >> s;
	spush(s);
}

void
load()
{
	str s = unquote(spop());
	std::cout << s << std::endl;
	load_file(s);
}

void
eval()
{
	str s = spop();
	if (!is_quoted(s)) {
		std::cerr << "non string argument passed to eval" << std::endl;
	} else {
		eval_string(unquote(s));
	}
}

void
fl()
{
	str s = spop();
	if (!is_float(s)) {
		std::cerr << "non number passed to fl" << std::endl;
	} else {
		spush(std::to_string((int)std::stof(s)));
	}
}
