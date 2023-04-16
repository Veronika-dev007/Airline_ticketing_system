#include "HashTable.h"

static int SIZE = 8;

Passenger* create_passenger(string id, string info, string name, string date) {
	Passenger* ps = new Passenger;
	ps->passport_id = id;
	ps->passport_info = info;
	ps->name = name;
	ps->date_birth = date;
	ps->state = true;
	return ps;
}

HashTable* create_table() {
	HashTable* table = new HashTable;
	table->count = 0;    
	table->pss = new Passenger * [SIZE];//память под массив указателей на структуру!
	for (int i = 0; i < SIZE; i++)
		table->pss[i] = NULL;
	return table;
}

void delete_table(HashTable* table) {
	for (int i = 0; i < SIZE; i++)
		if (table->pss[i] != NULL)
			delete table->pss[i];
	delete[] table->pss;
	delete table;
}

int hash_function(string id) {
	unsigned int sum = 0;
	for (int i = 0; i < id.size(); i++)
		sum += pow((int)id[i], 2);
	return sum % SIZE;
}

void print_table(HashTable* table) {
	if (table->count != 0) {
		cout << "|--------------------|---------------------------------|---------------------------------|--------------------|" << endl;
		cout << "|   Номер паспорта   |   Место и дата выдачи паспорт   |               ФИО               |    Дата рождения   |" << endl;
		cout << "|--------------------|---------------------------------|---------------------------------|--------------------|" << endl;
		for (int i = 0; i < SIZE; i++) {
			if (table->pss[i] && table->pss[i]->state) {
				cout << "|" <<left<< setw(20) << table->pss[i]->passport_id << "|" << setw(33) << table->pss[i]->passport_info << "|" << setw(33) << table->pss[i]->name << "|" << setw(20) << table->pss[i]->date_birth << "|" << endl;
				cout << "|--------------------|---------------------------------|---------------------------------|--------------------|" << endl;
			}
		}
	}
	else cout << "В системе нет зарегистрированных пассажиров!" << endl;
}


void insert_passenger(HashTable* table, string id, string info, string name, string date) {
	double loadFactor = (1.0 * (table->count+1)) / SIZE;
	if (loadFactor > table->rehash_size) {
		 resizeHt(table);//Производим  рехеширование таблицы
	}
	Passenger* ps = create_passenger(id, info,name,date);
	int index = hash_function(id);

	if (table->pss[index] == NULL || table->pss[index]->state == false) {
		table->pss[index] = ps;
		table->count++;
	}
	else {
		int i = 0;
		do {
			if (table->pss[index]->passport_id == id && table->pss[index]->state) {
				table->pss[index]->passport_info = info;
				table->pss[index]->name = name;
				table->pss[index]->date_birth = date;
				return;
			}
			i++;
			index = (hash_function(id) + i * i) % SIZE;
		} while (table->pss[index] != NULL && table->pss[index]->state != false);

		if (table->pss[index] == NULL || table->pss[index]->state == false) {
			table->pss[index] = ps;
			table->count++;
		}
	}
}

void delete_passenger(HashTable* table, string id) {
	int index = hash_function(id);
	int i = 0;
	while (table->pss[index] != NULL) {
		if (table->pss[index]->passport_id == id && table->pss[index]->state) {
			table->pss[index]->state = false;
			table->count--;
			cout << "Пассажир " << table->pss[index]->name << " с номером паспорта " << table->pss[index]->passport_id << " удален из таблицы\n";
			return;
		}
		i++;
		index = (hash_function(id) + i * i) % SIZE;
	}
	cout << "Пассажира с таким номером паспорта нет в таблице" << endl;
}

Passenger* search_by_passport_id(HashTable* table, string id) {
	int index = hash_function(id);
	int i = 0;
	while (table->pss[index] != NULL && i < SIZE) {
		if (table->pss[index]->state && table->pss[index]->passport_id == id) {
			return table->pss[index];
		}
		i++;
		index = (hash_function(id) + i * i) % SIZE;
	}
	return NULL;
}

void search_by_name(HashTable* table, string name) {
	int count = 0;
	for (size_t i = 0; i < SIZE; i++)
	{
		if (table->pss[i] != NULL && table->pss[i]->state && table->pss[i]->name.size() >= name.size() && table->pss[i]->name.compare(0, name.size(), name) == 0) {
			cout << "| "<< setw(30) << table->pss[i]->name << " | " << setw(20) << table->pss[i]->passport_id << " |" << endl;
			cout << "|--------------------------------|----------------------|" << endl;
			count++;
		}
	}
	if (!count) {
		cout << "|           Пассажира с таким ФИО нет в таблице         |" << endl;
		cout << "|-------------------------------------------------------|" << endl;

	}
}

void clear_table(HashTable* table) {
	for (size_t i = 0; i < SIZE; i++) {
		if (table->pss[i] != NULL && table->pss[i]->state) {
			table->pss[i]->state = false;
		}
	}
	table->count = 0;
	cout << "Информация о пассажирах удалена" << endl;
}

void resizeHt(HashTable* table) {
	int past_size = SIZE;
	SIZE *= 2;
	Passenger** pss2 = new Passenger * [SIZE];
	for (int i = 0; i < SIZE; ++i)
		pss2[i] = NULL;
	swap(table->pss, pss2);
	for (int i = 0; i < past_size; ++i){
		if (pss2[i] && pss2[i]->state)
			insert_passenger(table, pss2[i]->passport_id, pss2[i]->passport_info, pss2[i]->name, pss2[i]->date_birth);
	}
	
	for (int i = 0; i < past_size; ++i)
		if (pss2[i])
			delete pss2[i];
	delete[] pss2;
}

