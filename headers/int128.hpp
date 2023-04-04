typedef __int128_t int128_t;

std::string i128tos(int128_t n) {
  if (n == 0)
    return "0";
    
	std::string s = "";
  bool negative = n < 0;
    
  if (negative)
		n = -n;
    
  while (n > 0){
    s += (char)(n % 10 + '0');
		n /= 10;
	}
    
	if (negative)
	  s += "-";
    
	reverse(s.begin(), s.end());
	return s;
	//return std::to_string((long long)n);
}

int128_t stoi128(const std::string& s) {
  if (s.empty())
    return 0;
    
  int128_t n = 0;
  int i = 0;
  bool negative = s[0] == '-';
    
  if (negative)
    i = 1;
    
  for (; i < s.length(); i++)
    n = n * 10 + (s[i] - '0');
    
  if (negative)
    n = -n;
    
  return n;
	//return (int128_t)std::stoll(s);
}

bool is_int128(const std::string& s) {
  if (s.empty())
    return false;
    
  int i = 0;
  bool negative = false;
    
  if (s[0] == '-') {
    negative = true;
    i = 1;
  }
    
  if (i == s.length())
    return false;
    
  for (; i < s.length(); i++) {
    if (!isdigit(s[i]))
      return false;
    
  if (negative && s.length() == 1)
    return false;
    
  if (!negative && s.length() > 1 && s[0] == '0')
    return false;

  return s.length() <= 39;
}
