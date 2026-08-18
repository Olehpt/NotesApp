#include "Parser.h"

Parser::Parser(size_t argc, char** argv, NoteManager* nm) : arg_count(argc), arguments(argv), manager(nm) {
	act = parse();
	switch (act) {
	case add:
		Add();
		break;
	case rm:
		Remove();
		break;
	case list:
		List();
		break;
	case modify:
		Modify();
		break;
	default:
		std::cout << "Unknown command\n";
		break;
	}
}

action Parser::parse() {
	if (arg_count == 1) return list;
	if (arguments[1] == std::string("add")) return add;
	if (arguments[1] == std::string("rm")) return rm;
	if (arguments[1] == std::string("mod")) return modify;
}

void Parser::Add() {
	
}

void Parser::Remove() {
	
}

void Parser::List() {
	manager->ListNotes();
}

void Parser::Modify() {
	
}