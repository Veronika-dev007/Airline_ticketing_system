#include "Interface.h"

void addPassenger(HashTable* passengers) {
	string id, info, name, date;
	get_passenger(id, info, name, date);
	string passport_date = info.substr(info.find_last_of(' ') + 1);
	if (compare_dates(passport_date, date) > 0) {
		cout << "Пассажир добавлен.\n";
		insert_passenger(passengers, id, info, name, date);
	}
	else
		cout << "Ошибка! Введены некорректные данные, дата выдачи паспорта должна быть больше, чем дата рождения.\nПассажир не добавлен.\nВыберите пункт меню 1 ещё раз и повторите ввод.\n";
}

void deleteFlight(Node*& flights, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail) {
	string flight_id;
	flight_id = get_input(flight_id, check_flight_id, "Номер авиарейса: ", "Формат AAA-NNN, где A-заглавная латинская буква, N-цифра.\nВведите номер авиарейса: ");
	Node* delFlight = findFlightById(flights, flight_id);
	
	if (delFlight) {
		int countDelT = deleteTicketByFlightId(listHead, listTail, flight_id);
		deleteNode(&flights, delFlight);
		cout << "Количество билетов, купленных на авиарейс: "<< countDelT<<". Авиарейс удалён.\n";
	}
	else cout << "Такого авиарейса нет в системе!\n";
}

void findPassengerByPassportId(HashTable* passengers, ListOfFlightTickets* listHead) {
	string id; 
	id = get_input(id, check_passport_id, "Номер пастпорта: ", "Формат паспорта NNNN-NNNNNN, где N-цифра.\nВведите номер паспорта: ");
	Passenger* p = search_by_passport_id(passengers, id);
	if (!p) {
		cout << "\nПассажира с таким номером паспорта нет в таблице" << endl;
		return;
	}
	cout << "\nФИО: " << p->name << "\nДата рождения: " << p->date_birth << "\nНомер паспорта: " << p->passport_id << "\nМесто и дата выдачи паспорта: " << p->passport_info << endl;
	vector<string> passengerFlights = findAllFlightTicketsByPassportId(listHead, p->passport_id);
	if (!passengerFlights.empty()) {
		cout << "Пассажир купил билеты на авиарейсы:\n";
		for (auto i : passengerFlights)
			cout << i << endl;
	}
	else cout << "У пассажира нет купленных билетов\n";
}

void findPassengerByName(HashTable* passengers) {
	string name;
	cout << "Ведите ФИО: "; 
	getline(cin, name);
	cout << "|--------------------------------|----------------------|" << endl;
	cout << "|               ФИО              |     Номер паспорта   |" << endl;
	cout << "|--------------------------------|----------------------|" << endl;
	search_by_name(passengers, trim(name));
}

void deletePassenger(HashTable* passengers, Node* flights, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail) {
	string passport_id; 
	passport_id = get_input(passport_id, check_passport_id, "Номер пастпорта: ", "Формат паспорта NNNN-NNNNNN, где N-цифра.\nВведите номер паспорта: ");
	if (!search_by_passport_id(passengers, passport_id)) {
		cout << "\nПассажира с таким номером паспорта нет в системе!\n";
		return;
	}
	cout<<"Количество возвращённых билетов: "<<deleteTicketByPassportId(listHead, listTail, flights, passport_id)<<endl;
	delete_passenger(passengers, passport_id);
}

void deletePassengerTable(HashTable* passengers, Node* flights, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail) {
	clear_table(passengers);
	ListOfFlightTickets* ptr = listHead;
	ListOfFlightTickets* next;
	while (ptr != NULL) {
		next = ptr->next;
		increaseNumOfFreeSeats(flights, ptr->data.flight_id);
		deleteTicket(listHead, listTail, ptr);
		ptr = next;
	}
	listTail = NULL;
}

void addFlight(Node*& root) {
	string num, name, dep, arrival, d, t;
	unsigned int seats{}, free_seats{};
	get_flight(num, name, dep, arrival, d, t, seats, free_seats);
	if (compare_num_of_seats(seats, free_seats)) {
		Flight f{ num,name,dep,arrival,d,t,seats,free_seats };
		if (insertNode(&root, f))
			cout << "Авиарейс добавлен\n";
		else cout << "Ошибка! Авиарейс с таким номером уже есть в дереве!\n";
	}
	else cout << "Ошибка! Введены некорректные данные, количество свободных мест не должно превышать общее количество мест.\nАвиарейс не добавлен.\nВыберите пункт меню 7 ещё раз и повторите ввод.\n";

}

void printFlights(Node*& root) {
	if (root) {
		cout << "|---------|-----------------------|----------------------|--------------------|------------|-------------|------------|--------------|" << endl;
		cout << "|  Номер  | Название авиакомпании | Аэропорт отправления |  Аэропорт прибытия | Дата отпр. | Время отпр. | Мест всего | Мест свобод. |" << endl;
		cout << "|---------|-----------------------|----------------------|--------------------|------------|-------------|------------|--------------|" << endl;
		printPostorder(root);
		printTree(root, 10);
	}
	else cout << "В системе нет информации об авиарейсах\n";
}

void deleteFlightsTree(Node*& root, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail) {
	root = deleteTree(root);
	deleteList(listHead, listTail);
	cout << "Иформация об авиарейсах удалена\n";
}

void findFlightByFlightId(HashTable* passengers, Node* flights, ListOfFlightTickets* listHead) {
	string flight_id;
	get_input(flight_id, check_flight_id, "Номер авиарейса: ", "Формат AAA-NNN, где A-заглавная латинская буква, N-цифра.\nВведите номер авиарейса: ");

	Node* curr = findFlightById(flights, flight_id);
	if (curr) {
		cout << "|---------|-----------------------|----------------------|--------------------|------------|-------------|------------|--------------|" << endl;
		cout << "|  Номер  | Название авиакомпании | Аэропорт отправления |  Аэропорт прибытия | Дата отпр. | Время отпр. | Мест всего | Мест свобод. |" << endl;
		cout << "|---------|-----------------------|----------------------|--------------------|------------|-------------|------------|--------------|" << endl;
		printFlight(curr->f);
		vector<string> passengerPassports = findAllPassportTicketsByFlightId(listHead, flight_id);
		if (!passengerPassports.empty()) {
			cout << setw(5) << "\nПассажиры, которые купили билеты на этот авиарейс:\n\n";
			cout << "|--------------------------------|----------------------|" << endl;
			cout << "|               ФИО              |     Номер паспорта   |" << endl;
			cout << "|--------------------------------|----------------------|" << endl;
			for (auto i : passengerPassports) {
				cout << "|" << setw(32) << search_by_passport_id(passengers, i)->name << "|" << setw(22) << i << "|" << endl;
				cout << "|--------------------------------|----------------------|" << endl;
			}
		}
		else cout << "Пассажирв не купили билеты на этот авиарейс\n";
	}
	else cout << "Авиарейса с таким номером в системе нет\n";
}

void findFlightByFragmentOfArrivalName(Node* flights) {
	string arrival;
	bool flag = false;
	arrival = get_input(arrival, has_only_letters, "Введите фрагмет аэропорта прибытия: ", "\nВведите фрагмент аэропорта прибытия: ");
	cout << "|---------|--------------------|------------|-------------|" << endl;
	cout << "|  Номер  |  Аэропорт прибытия | Дата отпр. | Время отпр. |" << endl;
	cout << "|---------|--------------------|------------|-------------|" << endl;
	findFlightByArrivalName(flights, arrival, flag);
	if (!flag) {
		cout << "|                   Совпадений не найдено                 |" << endl;
		cout << "|---------------------------------------------------------|" << endl;
	}
}

void buyTicket(HashTable* passengers, Node* flights, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail) {
	string passport_id, flight_id, ticket_id;

	if (!flights) {
		cout << "\nВ системе нет авиарейсов!\n" << endl;
		return;
	}

	passport_id = get_input(passport_id, check_passport_id, "Номер пастпорта: ", "Формат паспорта NNNN-NNNNNN, где N-цифра.\nВведите номер паспорта: ");
	if(!search_by_passport_id(passengers,passport_id)){
		cout << "\nПассажира с таким номером паспорта нет в системе!\n";
		return;
	}
	
	flight_id = get_input(flight_id, check_flight_id, "Номер авиарейса: ", "Формат AAA-NNN, где A-заглавная латинская буква, N-цифра.\nВведите номер авиарейса: ");
	Node* currFlight = findFlightById(flights, flight_id);
	if (!currFlight) {
		cout << "\nАвиарейса с таким номером нет в системе!\n";
		return;
	}
	if (!hasFreeSeats(currFlight)) {
		cout << "\nНа этом авиарейсе все места проданы!\n";
		return;
	}

	ticket_id = getTicketId();

	TicketInfo t{ passport_id, flight_id, ticket_id };
	insertTicket(listHead, listTail, t);
	quickSort(listHead, listTail);
	decreaseNumOfFreeSeats(flights,flight_id);

	cout << "Авиабилет продан\n";
}

void returnTicket(Node* flights, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail) {
	string ticket_id;

	if (!flights) {
		cout << "\nВ системе нет авиарейсов!\n" << endl;
		return;
	}
	if (!listHead) {
		cout << "\nВ системе нет проданных авиабилетов!\n" << endl;
		return;
	}

	ticket_id = get_input(ticket_id, check_ticket_id, "Номер авиабилета: ", "Формат NNNNNNNNN, где N-цифра.\nВведите номер авиабилета: ");
	ListOfFlightTickets* currTicket = findTicket(listHead, ticket_id);
	if (!currTicket) {
		cout << "\nВ системе нет такого авиабилета!\n" << endl;
		return;
	}
	increaseNumOfFreeSeats(flights, currTicket->data.flight_id);
	deleteTicket(listHead, listTail, currTicket);
	cout << "Авиабилет возвращён\n";
}

void printTickets(ListOfFlightTickets* listHead) {
	if (listHead) {
		cout << "|--------------------|-------------------|-------------------|" << endl;
		cout << "|  Номер авиабилета  |   Номер паспорта  |  Номер авиарейса  |" << endl;
		cout << "|--------------------|-------------------|-------------------|" << endl;
		printList(listHead);
	}
	else cout << "Список авиабилетов пуст\n";
}