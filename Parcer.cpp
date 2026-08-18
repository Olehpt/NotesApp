#include "Parser.h"

Parser::Parser(size_t argc, char* argv[]) : arg_count(argc), arguments(argv) {}

action Parser::parse() {
	if (arg_count == 1) return list;
	if (arguments[1] == std::string("add")) return add;
	if (arguments[1] == std::string("rm")) return rm;
	if (arguments[1] == std::string("mod")) return modify;
}