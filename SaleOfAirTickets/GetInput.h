#pragma once

#include "CheckInput.h"
#include "HashTable.h"
#include "AVLtree.h"
#include "DoubleList.h"
#include <string>
#include <algorithm>

void get_passenger(string& id, string& info, string& name, string& date);
string& trim(string& str, string const& whitespace= " \r\n\t\v\f");
string& get_input(string& param, bool(*check)(string), const string& basic_info, const string& error_info);
void get_passengers_from_file(HashTable* table);
int getIntNum(const string& basic_info, const string& error_info);
void get_flight(string& num, string& name, string& departure, string& arrival, string& date, string& time, unsigned int& seats, unsigned int& free_seats);
void get_flights_from_file(Node*& root);
void get_tickets_from_file(ListOfFlightTickets*& head, ListOfFlightTickets*& tail, Node* flights);
string& getTicketId();