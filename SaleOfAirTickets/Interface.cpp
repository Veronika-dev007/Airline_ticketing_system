#include "Interface.h"

void addPassenger(HashTable* passengers) {
	string id, info, name, date;
	get_passenger(id, info, name, date);
	string passport_date = info.substr(info.find_last_of(' ') + 1);
	if (compare_dates(passport_date, date) > 0) {
		cout << "�������� ��������.\n";
		insert_passenger(passengers, id, info, name, date);
	}
	else
		cout << "������! ������� ������������ ������, ���� ������ �������� ������ ���� ������, ��� ���� ��������.\n�������� �� ��������.\n�������� ����� ���� 1 ��� ��� � ��������� ����.\n";
}

void deleteFlight(Node*& flights, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail) {
	string flight_id;
	flight_id = get_input(flight_id, check_flight_id, "����� ���������: ", "������ AAA-NNN, ��� A-��������� ��������� �����, N-�����.\n������� ����� ���������: ");
	Node* delFlight = findFlightById(flights, flight_id);
	
	if (delFlight) {
		int countDelT = deleteTicketByFlightId(listHead, listTail, flight_id);
		deleteNode(&flights, delFlight);
		cout << "���������� �������, ��������� �� ��������: "<< countDelT<<". �������� �����.\n";
	}
	else cout << "������ ��������� ��� � �������!\n";
}

void findPassengerByPassportId(HashTable* passengers, ListOfFlightTickets* listHead) {
	string id; 
	id = get_input(id, check_passport_id, "����� ���������: ", "������ �������� NNNN-NNNNNN, ��� N-�����.\n������� ����� ��������: ");
	Passenger* p = search_by_passport_id(passengers, id);
	if (!p) {
		cout << "\n��������� � ����� ������� �������� ��� � �������" << endl;
		return;
	}
	cout << "\n���: " << p->name << "\n���� ��������: " << p->date_birth << "\n����� ��������: " << p->passport_id << "\n����� � ���� ������ ��������: " << p->passport_info << endl;
	vector<string> passengerFlights = findAllFlightTicketsByPassportId(listHead, p->passport_id);
	if (!passengerFlights.empty()) {
		cout << "�������� ����� ������ �� ���������:\n";
		for (auto i : passengerFlights)
			cout << i << endl;
	}
	else cout << "� ��������� ��� ��������� �������\n";
}

void findPassengerByName(HashTable* passengers) {
	string name;
	cout << "������ ���: "; 
	getline(cin, name);
	cout << "|--------------------------------|----------------------|" << endl;
	cout << "|               ���              |     ����� ��������   |" << endl;
	cout << "|--------------------------------|----------------------|" << endl;
	search_by_name(passengers, trim(name));
}

void deletePassenger(HashTable* passengers, Node* flights, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail) {
	string passport_id; 
	passport_id = get_input(passport_id, check_passport_id, "����� ���������: ", "������ �������� NNNN-NNNNNN, ��� N-�����.\n������� ����� ��������: ");
	if (!search_by_passport_id(passengers, passport_id)) {
		cout << "\n��������� � ����� ������� �������� ��� � �������!\n";
		return;
	}
	cout<<"���������� ������������ �������: "<<deleteTicketByPassportId(listHead, listTail, flights, passport_id)<<endl;
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
			cout << "�������� ��������\n";
		else cout << "������! �������� � ����� ������� ��� ���� � ������!\n";
	}
	else cout << "������! ������� ������������ ������, ���������� ��������� ���� �� ������ ��������� ����� ���������� ����.\n�������� �� ��������.\n�������� ����� ���� 7 ��� ��� � ��������� ����.\n";

}

void printFlights(Node*& root) {
	if (root) {
		cout << "|---------|-----------------------|----------------------|--------------------|------------|-------------|------------|--------------|" << endl;
		cout << "|  �����  | �������� ������������ | �������� ����������� |  �������� �������� | ���� ����. | ����� ����. | ���� ����� | ���� ������. |" << endl;
		cout << "|---------|-----------------------|----------------------|--------------------|------------|-------------|------------|--------------|" << endl;
		printPostorder(root);
		printTree(root, 10);
	}
	else cout << "� ������� ��� ���������� �� ����������\n";
}

void deleteFlightsTree(Node*& root, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail) {
	root = deleteTree(root);
	deleteList(listHead, listTail);
	cout << "��������� �� ���������� �������\n";
}

void findFlightByFlightId(HashTable* passengers, Node* flights, ListOfFlightTickets* listHead) {
	string flight_id;
	get_input(flight_id, check_flight_id, "����� ���������: ", "������ AAA-NNN, ��� A-��������� ��������� �����, N-�����.\n������� ����� ���������: ");

	Node* curr = findFlightById(flights, flight_id);
	if (curr) {
		cout << "|---------|-----------------------|----------------------|--------------------|------------|-------------|------------|--------------|" << endl;
		cout << "|  �����  | �������� ������������ | �������� ����������� |  �������� �������� | ���� ����. | ����� ����. | ���� ����� | ���� ������. |" << endl;
		cout << "|---------|-----------------------|----------------------|--------------------|------------|-------------|------------|--------------|" << endl;
		printFlight(curr->f);
		vector<string> passengerPassports = findAllPassportTicketsByFlightId(listHead, flight_id);
		if (!passengerPassports.empty()) {
			cout << setw(5) << "\n���������, ������� ������ ������ �� ���� ��������:\n\n";
			cout << "|--------------------------------|----------------------|" << endl;
			cout << "|               ���              |     ����� ��������   |" << endl;
			cout << "|--------------------------------|----------------------|" << endl;
			for (auto i : passengerPassports) {
				cout << "|" << setw(32) << search_by_passport_id(passengers, i)->name << "|" << setw(22) << i << "|" << endl;
				cout << "|--------------------------------|----------------------|" << endl;
			}
		}
		else cout << "��������� �� ������ ������ �� ���� ��������\n";
	}
	else cout << "��������� � ����� ������� � ������� ���\n";
}

void findFlightByFragmentOfArrivalName(Node* flights) {
	string arrival;
	bool flag = false;
	arrival = get_input(arrival, has_only_letters, "������� ������� ��������� ��������: ", "\n������� �������� ��������� ��������: ");
	cout << "|---------|--------------------|------------|-------------|" << endl;
	cout << "|  �����  |  �������� �������� | ���� ����. | ����� ����. |" << endl;
	cout << "|---------|--------------------|------------|-------------|" << endl;
	findFlightByArrivalName(flights, arrival, flag);
	if (!flag) {
		cout << "|                   ���������� �� �������                 |" << endl;
		cout << "|---------------------------------------------------------|" << endl;
	}
}

void buyTicket(HashTable* passengers, Node* flights, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail) {
	string passport_id, flight_id, ticket_id;

	if (!flights) {
		cout << "\n� ������� ��� ����������!\n" << endl;
		return;
	}

	passport_id = get_input(passport_id, check_passport_id, "����� ���������: ", "������ �������� NNNN-NNNNNN, ��� N-�����.\n������� ����� ��������: ");
	if(!search_by_passport_id(passengers,passport_id)){
		cout << "\n��������� � ����� ������� �������� ��� � �������!\n";
		return;
	}
	
	flight_id = get_input(flight_id, check_flight_id, "����� ���������: ", "������ AAA-NNN, ��� A-��������� ��������� �����, N-�����.\n������� ����� ���������: ");
	Node* currFlight = findFlightById(flights, flight_id);
	if (!currFlight) {
		cout << "\n��������� � ����� ������� ��� � �������!\n";
		return;
	}
	if (!hasFreeSeats(currFlight)) {
		cout << "\n�� ���� ��������� ��� ����� �������!\n";
		return;
	}

	ticket_id = getTicketId();

	TicketInfo t{ passport_id, flight_id, ticket_id };
	insertTicket(listHead, listTail, t);
	quickSort(listHead, listTail);
	decreaseNumOfFreeSeats(flights,flight_id);

	cout << "��������� ������\n";
}

void returnTicket(Node* flights, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail) {
	string ticket_id;

	if (!flights) {
		cout << "\n� ������� ��� ����������!\n" << endl;
		return;
	}
	if (!listHead) {
		cout << "\n� ������� ��� ��������� �����������!\n" << endl;
		return;
	}

	ticket_id = get_input(ticket_id, check_ticket_id, "����� ����������: ", "������ NNNNNNNNN, ��� N-�����.\n������� ����� ����������: ");
	ListOfFlightTickets* currTicket = findTicket(listHead, ticket_id);
	if (!currTicket) {
		cout << "\n� ������� ��� ������ ����������!\n" << endl;
		return;
	}
	increaseNumOfFreeSeats(flights, currTicket->data.flight_id);
	deleteTicket(listHead, listTail, currTicket);
	cout << "��������� ���������\n";
}

void printTickets(ListOfFlightTickets* listHead) {
	if (listHead) {
		cout << "|--------------------|-------------------|-------------------|" << endl;
		cout << "|  ����� ����������  |   ����� ��������  |  ����� ���������  |" << endl;
		cout << "|--------------------|-------------------|-------------------|" << endl;
		printList(listHead);
	}
	else cout << "������ ����������� ����\n";
}