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
	cout << "1.  Зарегистрировать пассажира" << endl;
	cout << "2.  Удалить данные о пассажире " << endl;
	cout << "3.  Посмотреть всех зарегистрированных пассажиров" << endl;
	cout << "4.  Очистить данные о пассажирах" << endl;
	cout << "5.  Поиск пассажира по «номеру паспорта»" << endl;
	cout << "6.  Поиск пассажира по ФИО" << endl;
	cout << endl;
	cout << "7.  Добавить новый авиарейса" << endl;
	cout << "8.  Удалить сведения о авиарейсе" << endl;
	cout << "9.  Посмотреть все авиарейсы" << endl;
	cout << "10. Очистить данные об авиарейсах" << endl;
	cout << "11. Поиск авиарейса по «номеру авиарейса»" << endl;
	cout << "12. Поиск авиарейса по фрагментам названия аэропорта прибытия" << endl;
	cout << endl;
	cout << "13. Зарегистрировать продажу авиабилета" << endl;
	cout << "14. Зарегистрировать возврат авиабилета" << endl;
	cout << "15. Посмотреть список купленных билетов" << endl;

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
		ch = getIntNum("\nВведите номер опции: ", "Некорректный ввод. Введите число: ");
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
