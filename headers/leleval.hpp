void eval_string(const std::string&);

void
eval_op(const std::string& op)
{
	if (op == "")
		return;

	if (op == "/*") {
		LelTmp::comment = true;
		return;
	}

	if (op == "*/") {
		LelTmp::comment = false;
		return;
	}

	if (LelTmp::comment)
		return;

	if (LelTmp::skip_next) {
		LelTmp::skip_next = false;
		return;
	}

	if (op == "=") {
		LelTmp::get_macro_name = true;
		return;
	}

	if (op == ".") {
		LelTmp::current_macro = "";
		return;
	}

	if (LelTmp::current_macro != "") {
		LelTmp::macros[LelTmp::current_macro] += " " + op;
		return;
	}

	if (macros_exists(op)) {
		eval_string(LelTmp::macros[op]);
		return;
	}

	if (is_float(op)) {
		spush(op);
		return;
	}

	if (LelTmp::get_macro_name) {
		LelTmp::current_macro = op;
		LelTmp::macros[op] = "";
		LelTmp::get_macro_name = false;
		return;
	}

	if (fn_exists(op)) {
		LelTmp::fns[op]();
		return;
	}

	if (is_quoted(op)) {
		spush(op);
		return;
	}

	V_ERROR("wtf is `" << op << "`?");
}

void
eval_string(const std::string& s)
{
	std::vector<std::string> v = lel_tokens(s);

	for (const std::string& op: v)
		eval_op(op);
}
