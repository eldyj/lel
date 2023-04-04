#include<iostream>
#include<vector>
#include<regex>
#include<algorithm>
#include<map>
#include<functional>
#include<cmath>
#include<fstream>
#include"headers/int128.hpp"
#include"headers/dir.hpp"
#include"headers/error.hpp"
#include"headers/fns.def.hpp"
#include"headers/leltmp.hpp"
#include"headers/lelchecks.hpp"
#include"headers/lelstack.hpp"
#include"headers/lelstr.hpp"
#include"headers/lelparse.hpp"
#include"headers/leleval.hpp"
#include"headers/lelinclude.hpp"
#include"headers/fns.hpp"

int
main(int argc, char** argv)
{
	LelTmp::include_dir = dirname(std::string(argv[0]))+"/std/";
#include"headers/fnlist.hpp"
	use_file("stdop");
	use_file("stdfn");
	use_file("stdmath");
	load_file(std::string(argv[1]));
	return 0;
}
