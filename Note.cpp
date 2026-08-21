#include "Note.h"

Date::Date() : day(0), mon(0), year(0) {}

Date::Date(size_t d, size_t m, size_t y) : day(d), mon(m), year(y) {}

std::string Date::to_string() const {
	return std::to_string(day) + "/" + std::to_string(mon) + "/" + std::to_string(year);
}

Date Date::today() {
	std::time_t now = std::time(nullptr);
	std::tm* local_time = std::localtime(&now);
	return Date(local_time->tm_mday, local_time->tm_mon + 1, local_time->tm_year + 1900);
}

bool Date::valid() const //todo?
{
    if (year < 1 || mon < 1 || mon > 12 || day < 1)
        return false;
    int days_in_month;
    switch (mon)
    {
    case 2:
        days_in_month = 28;
        break;

    case 4:
    case 6:
    case 9:
    case 11:
        days_in_month = 30;
        break;

    default:
        days_in_month = 31;
    }

    if (day > days_in_month)
        return false;
    Date today = Date::today();
    if (year < today.year)
        return false;
    if (year == today.year && mon < today.mon)
        return false;
    if (year == today.year && mon == today.mon && day < today.day)
        return false;
    return true;
}

Note::Note() {
    id = 0;
	title = "null";
	std::time_t now = std::time(nullptr);
	creation_date = Date::today();
	target_date = creation_date;
}

Note::Note(const std::string& t, const Date& td) {
    id = 0;
	title = t;
	creation_date = Date::today();
	target_date = td;
}

Note::Note(size_t i, const std::string& t, const Date& td, const Date& cd) {
	id = i;
	title = t;
	creation_date = cd;
	target_date = td;
}

Date Note::get_date() const{
	return target_date;
}

std::string Note::get_title() const {
	return title;
}