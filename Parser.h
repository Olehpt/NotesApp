#pragma once
#include <string>
#include <iostream>

const enum action {
	add,
	rm,
	list,
	modify
};

class Parser {
	char** arguments;
	size_t arg_count;
public:
	Parser(size_t argc, char* argv[]);
	action parse();
};