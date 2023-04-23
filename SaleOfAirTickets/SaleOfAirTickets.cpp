#ifdef _DEBUG
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)										
#define new DEBUG_NEW																		
#endif

#include <iostream>
#include <windows.h>

#include "CheckInput.h"
#include "GetInput.h"
#include "HashTable.h"
#include "AVLtree.h"
#include "DoubleList.h"
#include "Interface.h"
using namespace std;

void menu() {
	cout << "1.  ���������������� ���������" << endl;
	cout << "2.  ������� ������ � ��������� " << endl;
	cout << "3.  ���������� ���� ������������������ ����������" << endl;
	cout << "4.  �������� ������ � ����������" << endl;
	cout << "5.  ����� ��������� �� ������� ��������" << endl;
	cout << "6.  ����� ��������� �� ���" << endl;
	cout << endl;
	cout << "7.  �������� ����� ���������" << endl;
	cout << "8.  ������� �������� � ���������" << endl;
	cout << "9.  ���������� ��� ���������" << endl;
	cout << "10. �������� ������ �� ����������" << endl;
	cout << "11. ����� ��������� �� ������� ���������" << endl;
	cout << "12. ����� ��������� �� ���������� �������� ��������� ��������" << endl;
	cout << endl;
	cout << "13. ���������������� ������� ����������" << endl;
	cout << "14. ���������������� ������� ����������" << endl;
	cout << "15. ���������� ������ ��������� �������" << endl;

}

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	menu();

	HashTable* ht = create_table();
	get_passengers_from_file(ht);

	Node* root = NULL;
	get_flights_from_file(root);

	ListOfFlightTickets* head = NULL, * tail = NULL;
	get_tickets_from_file(head, tail,root);

	int ch;

	do {
		ch = getIntNum("\n������� ����� �����: ", "������������ ����. ������� �����: ");
		switch (ch) {
		case 1: addPassenger(ht); break;
		case 2: deletePassenger(ht, root, head, tail); break;
		case 3: print_table(ht); break;
		case 4: deletePassengerTable(ht, root, head, tail); break;
		case 5: findPassengerByPassportId(ht, head); break;
		case 6: findPassengerByName(ht); break;
		case 7: addFlight(root); break;
		case 8: deleteFlight(root, head, tail); break;
		case 9: printFlights(root); break;
		case 10: deleteFlightsTree(root, head, tail); break;
		case 11: findFlightByFlightId(ht, root, head); break;
		case 12: findFlightByFragmentOfArrivalName(root); break;
		case 13: buyTicket(ht, root, head, tail); break;
		case 14: returnTicket(root, head, tail); break;
		case 15: printTickets(head); break;
		case 16: system("cls"); menu(); break;
		}
	} while (ch != 0);

	delete_table(ht);
	deleteTree(root);
	deleteList(head, tail);

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();
}
