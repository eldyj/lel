std::string
dirname(const std::string& s) {
  return s.substr(0,s.find_last_of("/\\"));
}
