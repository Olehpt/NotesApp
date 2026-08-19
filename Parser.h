#pragma once
#include <string>
#include <iostream>
#include "NoteManager.h"
#include "Note.h"
#include <sstream>

const enum action {
	add,
	rm,
	list,
	modify,
	unknown
};

class Parser {
	char** arguments;
	size_t arg_count;
	action act;
	NoteManager* manager;
	template <typename T>
	void suggest(T& var, const std::string& prompt);
	action parse();
	bool parse_date(const std::string& date_str, Date& date);
public:
	Parser(size_t argc, char** argv, NoteManager* nm);
	void Add();
	void Remove();
	void List();
	void Modify();
};