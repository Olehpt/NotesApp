#include "Note.h"

Note::Note() {
	id = 0;
	title = "null";
	std::time_t now = std::time(nullptr);
	creation_date = std::localtime(&now);
	target_date = creation_date;
}

Note::Note(const std::string& t, const std::time_t& td) {
	id = 0;
	title = t;
	std::time_t now = std::time(nullptr);
	creation_date = std::localtime(&now);
	target_date = std::localtime(&td);
}

void Note::print() {
	std::string result = to_string();
	std::cout << result;
}

std::string Note::to_string() {
	std::string result = "id: " + std::to_string(id) + "; title: " + title + "; creation date: " +
		std::to_string(creation_date->tm_mday) + "." + std::to_string(creation_date->tm_mon) + "." +
		std::to_string(creation_date->tm_year) + "; target date: " + std::to_string(target_date->tm_mday) +
		"." + std::to_string(target_date->tm_mon) + "." + std::to_string(target_date->tm_year) + ";\n";
	return result;
}