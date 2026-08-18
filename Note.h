#pragma once
#include <ctime>
#include "nlohmann/json.hpp"
#include <string>
#include <iostream>

class Note {
	size_t id;
	std::string title;
	std::tm* creation_date;
	std::tm* target_date;
public:
	Note();
	Note(const std::string& t, const std::time_t& td);
	void print();
	std::string to_string();
};