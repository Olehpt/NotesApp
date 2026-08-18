#pragma once
#include <string>
#include <iostream>
#include "NoteManager.h"
#include "Note.h"

const enum action {
	add,
	rm,
	list,
	modify
};

class Parser {
	char** arguments;
	size_t arg_count;
	action act;
	NoteManager* manager;

	action parse();
public:
	Parser(size_t argc, char** argv, NoteManager* nm);
	void Add();
	void Remove();
	void List();
	void Modify();
};