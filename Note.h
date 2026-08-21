#pragma once
#include "nlohmann/json.hpp"
#include <ctime>
#include <string>
#include <iostream>

struct Date {
	size_t day, mon, year;
	Date();
	Date(size_t d, size_t m, size_t y);
	std::string to_string() const;
	static Date today();
	bool valid() const;
};

class Note {
	size_t id;
	std::string title;
	Date creation_date, target_date;
public:
	Note();
	Note(const std::string& t, const Date& td);
	Note(size_t i, const std::string& t, const Date& td, const Date& cd);
	Date get_date() const;
	std::string get_title() const;
};