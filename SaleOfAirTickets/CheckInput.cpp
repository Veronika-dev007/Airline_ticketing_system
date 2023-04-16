#include "CheckInput.h"

bool check_passport_id(string id) {
	const regex pattern("^\\d{4}-\\d{6}$");
	return regex_match(id, pattern);
}

bool check_passport_info(string info) {
	const regex pattern("^([А-ЯЁа-яё.\\s]{1,40})\\s([0]?[1-9]|[12][0-9]|3[01]).(0[1-9]|1[012]).(19\\d\\d|20[01]\\d|202[0123])$");
	return regex_match(info, pattern);
}

bool check_name(string name) {
	const regex pattern("^([А-ЯЁ][а-яё]{1,40})\\s([А-ЯЁ][а-яё]{1,40})\\s([А-ЯЁ][а-яё]{1,40})$");
	return regex_match(name, pattern);
}

bool isLeap(int year){//високосный год
	return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
}

bool check_date(string date) {
	const regex pattern("^([0]?[1-9]|[12][0-9]|3[01]).(0[1-9]|1[012]).(19\\d\\d|20[01]\\d|202[0123])$");
	if(!regex_match(date, pattern)) return false;
	int d, m, y;
	parse_string(date, y, m, d);
	if(!correct_numbers_of_days_in_month(y, m, d))
		return false;
	return true;
}

bool check_departure_date(string date) {
	const regex pattern("^([0]?[1-9]|[12][0-9]|3[01]).(0[1-9]|1[012]).(20\\d\\d)$");
	if (!regex_match(date, pattern)) return false;
	int d, m, y;
	parse_string(date, y, m, d);
	if (!correct_numbers_of_days_in_month(y, m, d))
		return false;
	return true;
}

bool correct_numbers_of_days_in_month(int y, int m, int d) {
	if (m == 2) {// Handle February month with leap year
		if (isLeap(y))
			return (d <= 29);
		else
			return (d <= 28);
	}
	if (m == 4 || m == 6 || m == 9 || m == 11)// Months of April, June, Sept and Nov must have number of days less than or equal to 30.
		return (d <= 30);
}

void parse_string(string date, int& y, int& m, int& d) {
	stringstream ss(date);
	char delimiter;
	ss >> d >> delimiter >> m >> delimiter >> y;
}

int compare_dates(string date1, string date2) {
	int y1, y2, m1, m2, d1, d2;
	parse_string(date1, y1, m1, d1);
	parse_string(date2, y2, m2, d2);
	return (y1 != y2) ? y1 - y2 : (m1 != m2) ? m1 - m2 : d1 - d2;
}

bool check_flight_id(string num) {
	const regex pattern("^[A-Z]{3}-\\d{3}$");
	return regex_match(num, pattern);
}

bool has_only_letters(string s) {
	const regex pattern("^[А-ЯЁа-яёa-zA-Z.\\s]+$");
	return regex_match(s, pattern);
}

bool check_time(string t) {
	const regex pattern("^([01]?[0-9]|2[0-3]):[0-5][0-9]$");
	return regex_match(t, pattern);
}

bool compare_num_of_seats(int seats, int free_seats) {
	return free_seats <= seats;
}

bool has_only_digits(const string s) {
	return s.find_first_not_of("0123456789") == string::npos;
}

bool check_ticket_id(string id) {
	const regex pattern("^\\d{9}$");
	return regex_match(id, pattern);
}



