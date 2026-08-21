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
	default:
		std::cout << "Unknown command\n";
		break;
	}
}

template <typename T>
void Parser::suggest(T& var, const std::string& prompt) {
	std::cout << prompt;
	std::getline(std::cin, var);
}

action Parser::parse() {
	if (arg_count == 1) return list;
	if (arguments[1] == std::string("add")) return add;
	if (arguments[1] == std::string("rm")) return rm;
	return unknown;
}

bool Parser::parse_date(const std::string& date_str, Date& date) {
	std::stringstream ss(date_str);
	int d, m, y;
	if (!(ss >> d >> m >> y)) {
		std::cout << "Invalid date format\n";
		return false;
	}
	Date target_date(d, m, y);
	if (!target_date.valid()) {
		std::cout << "Invalid date\n";
		return false;
	}
	date = target_date;
	return true;
	return false;
}

void Parser::Add() {
	std::string title, date_str;
	Date target_date = Date::today();
	if (arg_count == 2) {
		suggest(title, "Enter title: ");
		suggest(date_str, "Enter valid target date (dd mm yyyy):");
		if (!parse_date(date_str, target_date)) return;
	}
	else {
		std::cout << "Unknown signature\n";
		return;
	}
	Note n = Note(title, target_date);
	manager->AddNote(n);
}

void Parser::Remove() {
	std::string id_str;
	if (arg_count == 2) {
		suggest(id_str, "Enter ID: ");
	}
	else if (arg_count == 3) {
		id_str = arguments[2];
	}
	else {
		std::cout << "Unknown signature\n";
		return;
	}
	size_t id;
	try {
		id = std::stoul(id_str);
	}
	catch (const std::exception& e) {
		std::cout << "Invalid ID format\n";
		return;
	}
	manager->RemoveNote(id);
}

void Parser::List() {
	manager->ListNotes();
}
