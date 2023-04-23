#pragma once

#include "CheckInput.h"
#include "GetInput.h"
#include "HashTable.h"
#include "AVLtree.h"
#include "DoubleList.h"
#include <iostream>
using namespace std;

void addPassenger(HashTable* passengers);
void deleteFlight(Node*& flights, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail);
void findPassengerByPassportId(HashTable* passengers, ListOfFlightTickets* listHead);
void findPassengerByName(HashTable* passengers);
void deletePassenger(HashTable* passengers, Node* flights, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail);
void deletePassengerTable(HashTable* passengers, Node* flights, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail);
void addFlight(Node*& root);
void printFlights(Node*& root);
void deleteFlightsTree(Node*& root, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail);
void findFlightByFlightId(HashTable* passengers, Node* flights, ListOfFlightTickets* listHead);
void findFlightByFragmentOfArrivalName(Node* flights);
void buyTicket(HashTable* passengers, Node* flights, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail);
void returnTicket(Node* flights, ListOfFlightTickets*& listHead, ListOfFlightTickets*& listTail);
void printTickets(ListOfFlightTickets* listHead);


