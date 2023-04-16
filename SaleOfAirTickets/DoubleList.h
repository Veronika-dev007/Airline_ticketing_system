#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "AVLtree.h"
using namespace std;

struct TicketInfo {
    string passport_id = "NNNN-NNNNNN";// 4 - 6 цифр
    string flight_id = "AAA-NNN";// 3 заглавные буквы - 3 цифры
    string ticket_id = "NNNNNNNNN";// 9 цифр
};

struct ListOfFlightTickets {
    TicketInfo data;
    ListOfFlightTickets* next, * prev;
};

ListOfFlightTickets* createTicket(TicketInfo n);
void insertTicket(ListOfFlightTickets*& head, ListOfFlightTickets*& tail, TicketInfo n);
ListOfFlightTickets* findTicket(ListOfFlightTickets* head, string ticket);
void deleteTicket(ListOfFlightTickets*& head, ListOfFlightTickets*& tail, ListOfFlightTickets* delTicket);
int deleteTicketByFlightId(ListOfFlightTickets*& head, ListOfFlightTickets*& tail, string flight_id);
int deleteTicketByPassportId(ListOfFlightTickets*& head, ListOfFlightTickets*& tail, Node* tree, string passport_id);//&&+
void deleteList(ListOfFlightTickets*& head, ListOfFlightTickets*& tail);
void printList(ListOfFlightTickets* head);
vector<string> findAllFlightTicketsByPassportId(ListOfFlightTickets* head, string passport_id);
vector<string> findAllPassportTicketsByFlightId(ListOfFlightTickets* head, string flight_id);

void swap(TicketInfo* a, TicketInfo* b);
ListOfFlightTickets* partition(ListOfFlightTickets* head, ListOfFlightTickets* tail);
void quickSort(ListOfFlightTickets* head, ListOfFlightTickets* tail);

