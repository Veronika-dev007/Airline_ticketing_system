#pragma once

#include <regex>
#include <sstream>
using namespace std;

bool check_passport_id(string id);
bool isLeap(int year);
bool check_date(string date);
bool check_name(string name);
bool check_passport_info(string info);
int compare_dates(string date1, string date2);
void parse_string(string date, int& y, int& m, int& d);
bool check_flight_id(string num);
bool has_only_letters(string s);
bool check_time(string t);
bool compare_num_of_seats(int seats, int free_seats);
bool has_only_digits(const string s);
bool correct_numbers_of_days_in_month(int y, int m, int d);
bool check_departure_date(string date);
bool check_ticket_id(string id);
