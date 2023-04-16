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

vector<string> findAllFlightTicketsByPassportId(ListOfFlightTickets* head, string passport_id) {//возврашаем вектор flight_id всех пассажиров обнаруженных по passport_id
    //vector<unique_ptr<TicketInfo>> v;
    vector<string> v;
    ListOfFlightTickets* node = head;
    while (node != NULL) {
        if (node->data.passport_id == passport_id)
            v.push_back(node->data.flight_id);
        node = node->next;
    }
    return v;
}

vector<string> findAllPassportTicketsByFlightId(ListOfFlightTickets* head, string flight_id) {//возвращаем вектор passport_id всех пассажиров которые купили билеты на этот рейс flight_id
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
    //ListOfFlightTickets* delNode = findTicket(head, ticket_id);
    //if (!delNode)
    //    return false;// "No such element in the list"

    //if (head == delNode) {
    //    head = delNode->next;
    //    if (head)
    //        head->prev = NULL;
    //    else tail = NULL;
    //}
    //else {
    //    delNode->prev->next = delNode->next;
    //    if (delNode->next)
    //        delNode->next->prev = delNode->prev;
    //    else tail =NULL;//null delNode->prev
    //}
    //delete delNode;
   
    if (delNode == head)
        head = head->next;
    // If it was at the tail, advance the tail to the previous item
    if (delNode == tail)
        tail = tail->prev;

    // Remove from the list
    if (delNode->next)
        delNode->next->prev = delNode->prev;
    if (delNode->prev)
        delNode->prev->next = delNode->next;

    // Free the removed node
    delete delNode;
}

int deleteTicketByFlightId(ListOfFlightTickets*& head, ListOfFlightTickets*& tail, string flight_id) {
    ListOfFlightTickets* ptr = head;
    ListOfFlightTickets* next;
    int countT = 0;
    while (ptr != NULL) {
        next = ptr->next;
        if (ptr->data.flight_id == flight_id) {
            //increaseNumOfFreeSeats(tree, ptr->data.flight_id);
            deleteTicket(head, tail, ptr);
            countT++;
        }
        ptr = next;
    }
    return countT;
}

int deleteTicketByPassportId(ListOfFlightTickets*& head, ListOfFlightTickets*& tail, Node* tree, string passport_id) {//&&
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

//Временная сложность занимает O (n ^ 2) времени в худшем случае и O (nLogn) в среднем и лучшем случаях. 
//Наихудший случай возникает, когда связанный список уже отсортирован.
//O (n) Дополнительное пространство возникает из - за стека вызовов функций.

void quickSort(ListOfFlightTickets* head, ListOfFlightTickets* tail) {
    if (tail != NULL && head != tail && head != tail->next) {
        ListOfFlightTickets* p = partition(head, tail);
        quickSort(head, p->prev);
        quickSort(p->next, tail);
    }
}