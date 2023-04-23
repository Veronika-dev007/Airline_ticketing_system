#include "DoubleList.h"

ListOfFlightTickets* createTicket(TicketInfo n) {
    ListOfFlightTickets* node = new ListOfFlightTickets;
    node->data = n;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void insertTicket(ListOfFlightTickets*& head, ListOfFlightTickets*& tail, TicketInfo n) {
    ListOfFlightTickets* newNode = createTicket(n);
    newNode->prev = tail;
    newNode->next = NULL;
    if (tail) tail->next = newNode;
    tail = newNode;
    if (!head) head = tail;
}

ListOfFlightTickets* findTicket(ListOfFlightTickets* head, string ticket) {
    ListOfFlightTickets* node = head;
    while (node != NULL) {
        if (node->data.ticket_id == ticket)
            return node;
        node = node->next;
    }
    return NULL;
}

vector<string> findAllFlightTicketsByPassportId(ListOfFlightTickets* head, string passport_id) {
    vector<string> v;
    ListOfFlightTickets* node = head;
    while (node != NULL) {
        if (node->data.passport_id == passport_id)
            v.push_back(node->data.flight_id);
        node = node->next;
    }
    return v;
}

vector<string> findAllPassportTicketsByFlightId(ListOfFlightTickets* head, string flight_id) {
    vector<string> v;
    ListOfFlightTickets* node = head;
    while (node != NULL) {
        if (node->data.flight_id == flight_id)
            v.push_back(node->data.passport_id);
        node = node->next;
    }
    return v;
}

void deleteTicket(ListOfFlightTickets*& head, ListOfFlightTickets*& tail, ListOfFlightTickets* delNode) {
    if (delNode == head)
        head = head->next;
  
    if (delNode == tail)
        tail = tail->prev;

    if (delNode->next)
        delNode->next->prev = delNode->prev;
    if (delNode->prev)
        delNode->prev->next = delNode->next;

    delete delNode;
}

int deleteTicketByFlightId(ListOfFlightTickets*& head, ListOfFlightTickets*& tail, string flight_id) {
    ListOfFlightTickets* ptr = head;
    ListOfFlightTickets* next;
    int countT = 0;
    while (ptr != NULL) {
        next = ptr->next;
        if (ptr->data.flight_id == flight_id) {
            deleteTicket(head, tail, ptr);
            countT++;
        }
        ptr = next;
    }
    return countT;
}

int deleteTicketByPassportId(ListOfFlightTickets*& head, ListOfFlightTickets*& tail, Node* tree, string passport_id) {
    ListOfFlightTickets* ptr = head;
    ListOfFlightTickets* next;
    int countT = 0;
    while (ptr != NULL) {
        next = ptr->next;
        if (ptr->data.passport_id == passport_id) {
            increaseNumOfFreeSeats(tree, ptr->data.flight_id);
            deleteTicket(head, tail,ptr);
            countT++;
        }
        ptr = next;
    }
    return countT;
}

void deleteList(ListOfFlightTickets*& head, ListOfFlightTickets*& tail) {
    ListOfFlightTickets* tmp;
    while (head) {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = NULL;
}

void printList(ListOfFlightTickets* head) {
    ListOfFlightTickets* node = head;
    while (node != NULL)
    {
        cout << "| " << setw(18) << node->data.ticket_id << " | " << setw(17) << node->data.passport_id << " | " << setw(17) << node->data.flight_id << " | " << endl;
        cout << "|--------------------|-------------------|-------------------|" << endl;
        node = node->next;
    }
}

void swap(TicketInfo* a, TicketInfo* b) {
    TicketInfo t = *a;
    *a = *b;
    *b = t;
}

ListOfFlightTickets* partition(ListOfFlightTickets* head, ListOfFlightTickets* tail) {
    int pivot = stoi(tail->data.ticket_id);// set pivot as last element
    ListOfFlightTickets* i = head->prev;
    for (ListOfFlightTickets* j = head; j != tail; j = j->next)
    {
        if (stoi(j->data.ticket_id) <= pivot) {
            i = (i == NULL) ? head : i->next;//i++
            swap(&(i->data), &(j->data));
        }
    }
    i = (i == NULL) ? head : i->next;
    swap(&(i->data), &(tail->data));
    return i;
}

//��������� ��������� �������� O (n ^ 2) ������� � ������ ������ � O (nLogn) � ������� � ������ �������. 
//��������� ������ ���������, ����� ��������� ������ ��� ������������.
//O (n) �������������� ������������ ��������� �� - �� ����� ������� �������.

void quickSort(ListOfFlightTickets* head, ListOfFlightTickets* tail) {
    if (tail != NULL && head != tail && head != tail->next) {
        ListOfFlightTickets* p = partition(head, tail);
        quickSort(head, p->prev);
        quickSort(p->next, tail);
    }
}