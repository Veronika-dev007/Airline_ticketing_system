#pragma once

#include<iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

struct Passenger {
	string passport_id;
	string passport_info;
	string name;
	string date_birth;
	bool state;
};

struct HashTable {
	Passenger** pss;
	const double rehash_size = 0.75; // коэффициент, при котором произойдет увеличение таблицы
	int count; 
};

Passenger* create_passenger(string id, string info, string name, string date);
HashTable* create_table();
void delete_table(HashTable* table);
int hash_function(string id);
void print_table(HashTable* table);
Passenger* search_by_passport_id(HashTable* table, string id);
void search_by_name(HashTable* table, string name);
void insert_passenger(HashTable* table, string id, string info, string name, string date);
void delete_passenger(HashTable* table, string id);
void clear_table(HashTable* table);
void resizeHt(HashTable* table);
