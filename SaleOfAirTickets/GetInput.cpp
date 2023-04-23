#include "GetInput.h"

string& trim(string& str, string const& whitespace) {
	str.erase(str.find_last_not_of(whitespace) + 1);
	str.erase(0, str.find_first_not_of(whitespace));
	return str;
}

string& get_input(string& param, bool (*check)(string), const string& basic_info, const string& error_info ) {
	cout << basic_info;
	getline(cin, param);
	trim(param);
	while (!check(param)) {
		cout <<"Некорректный ввод. "<<error_info;
		getline(cin, param);
		trim(param);
	}
	return param;
}

void get_passenger(string& id, string& info, string& name, string& date) {
	cout << "Введите данные о пассажире\n";
	get_input(id, check_passport_id, "Номер пастпорта: ", "Формат паспорта NNNN-NNNNNN, где N-цифра.\nВведите номер паспорта: ");
	get_input(info, check_passport_info, "Место и дата выдачи паспорта: ", "\nВведите место и дату выдачи паспорта: ");
	get_input(name, check_name, "ФИО: ", "\nВведите ФИО: ");
	get_input(date, check_date, "Дата рождения: ", "Формат даты рождения дд.мм.гггг\nВведите дату рождения: ");
}

void get_passengers_from_file(HashTable* table) {
	ifstream f("passengers.csv");
	string line;
	char delimiter = ';';
	if (!f.is_open())
		cout << "\nФайл с данными о пассажирах не может быть открыт!\n\n";
	else {
		while (getline(f, line))
		{
			stringstream stream(line);
			string id, info, name, date;
			getline(stream, id, delimiter);
			getline(stream, info, delimiter);
			getline(stream, name, delimiter);
			getline(stream, date, delimiter);
			if(check_passport_id(id) && check_passport_info(info) && check_name(name) && check_date(date) && compare_dates(info.substr(info.find_last_of(' ') + 1),date)>0)
				insert_passenger(table, id, info, name, date);
		}
	}
	f.close();
}

int getIntNum(const string& basic_info, const string& error_info) {
	int ans;
	cout << basic_info;
	cin >> ans;
	while (cin.fail() || cin.get() != '\n' || ans < 0) {
		cin.clear();
		cin.ignore(cin.rdbuf()->in_avail());
		cout << error_info;
		cin >> ans;
	}
	return ans;
}

void get_flight(string& num, string& name, string& departure, string& arrival, string& date, string& time, unsigned int& seats, unsigned int& free_seats) {
	cout << "Введите данные об авиарейсе\n";
	get_input(num, check_flight_id, "Номер авиарейса: ", "Формат AAA-NNN, где A-заглавная латинская буква, N-цифра.\nВведите номер авиарейса: ");
	get_input(name, has_only_letters, "Название авиакомпании: ", "\nВведите название авиакомпании: ");
	get_input(departure, has_only_letters, "Аэропорт отправления: ", "\nВведите аэропорт отправления: ");
	get_input(arrival, has_only_letters, "Аэропорт прибытия: ", "\nВведите аэропорт прибытия: ");
	get_input(date, check_departure_date, "Дату отправления: ", "Формат даты дд.мм.гггг\nВведите дату отправления: ");
	get_input(time, check_time, "Время отправления: ", "Формат чч:мм\nВведите время отправления: ");
	seats = getIntNum("Количество мест всего: ", "\nВведите количество мест всего: ");
	free_seats = getIntNum("Количество свободных мест: ", "\nВведите количество свободных: ");
}

void get_flights_from_file(Node*& root) {
	ifstream f("flights.csv");
	string line;
	char delimiter = ';';
	if (!f.is_open())
		cout << "\nФайл с данными о авиарейсах не может быть открыт!\n\n";
	else {
		while (getline(f, line))
		{
			stringstream stream(line);
			string num, name, dep, arrival, d, t, seats, free_seats;
			getline(stream, num, delimiter);
			getline(stream, name, delimiter);
			getline(stream, dep, delimiter);
			getline(stream, arrival, delimiter);
			getline(stream, d, delimiter);
			getline(stream, t, delimiter);
			getline(stream, seats, delimiter);
			getline(stream, free_seats, delimiter);
			
			if (check_flight_id(num) && has_only_letters(name) && has_only_letters(dep) && has_only_letters(arrival) && check_date(d)
				&& check_time(t) && has_only_digits(seats) &&has_only_digits(free_seats)) {
				if (compare_num_of_seats(stoi(seats), stoi(free_seats))) {
					Flight f{ num, name, dep, arrival, d, t, stoi(seats),  stoi(free_seats) };
					insertNode(&root, f);
				}
			}
		}
	}
	f.close();
}

void get_tickets_from_file(ListOfFlightTickets*& head, ListOfFlightTickets*& tail, Node* flights) {
	ifstream f("tickets.csv");
	string line;
	char delimiter = ';';
	if (!f.is_open())
		cout << "\nФайл с данными о билетах не может быть открыт!\n\n";
	else {
		while (getline(f, line))
		{
			stringstream stream(line);
			string passport_id, flight_id, ticket_id;
			getline(stream, ticket_id, delimiter);
			getline(stream, passport_id, delimiter);
			getline(stream, flight_id, delimiter);

			if (check_flight_id(flight_id) && check_passport_id(passport_id) && check_ticket_id(ticket_id)) {
					TicketInfo t{ passport_id,flight_id,ticket_id };
					insertTicket(head,tail, t);
					decreaseNumOfFreeSeats(flights, flight_id);
			}
		}
		quickSort(head, tail);
	}
	f.close();
}

string& getTicketId(){
	static string str = "000000000";
	for (int i = str.length() - 1; i >= 0; i--)
	{
		int n = str[i] - 48;
		n++;
		if (n < 10)
		{
			str[i] = n + 48;
			break;
		}
		else str[i] = 48;
	}
	return str;
}