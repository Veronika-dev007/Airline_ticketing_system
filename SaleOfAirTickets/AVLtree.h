#pragma once

#include <string>
#include <iostream>
#include <deque>
#include <iomanip>
using namespace std;

struct Flight {
    string flight_id;
    string airline_name;
    string departure;
    string arrival;
    string date;
    string time;
    unsigned int num_of_seats;
    unsigned int num_of_free_seats;
};

struct Node {
    Flight f;
    int height;
    Node* left;
    Node* right;
    Node* prev;
};

Node* createNode(Flight f);
bool insertNode(Node** root, Flight f);
void balanceTree(Node** root, Node** p);
int getHeight(Node* node);
void rightRotate(Node*& root);
void leftRotate(Node*& root);
void bigRightRotate(Node*& root);
void bigLeftRotate(Node*& root);
void updateHeight(Node*& node);
int getBalance(Node* node);
void printTree(Node* root, int space_size = 4);
void deleteNode(Node** root, Node* curr);
Node* getSuccessor(Node* node);
void printPostorder(Node* node);
Node* deleteTree(Node* node);
Node* findFlightById(Node* root, string flight_id);
void printFlight(Flight& f);

bool hasFreeSeats(Node* node);
void increaseNumOfFreeSeats(Node* node, string  flight_id);
void decreaseNumOfFreeSeats(Node* node, string  flight_id);

void badCharHeuristic(string str, int size, int* badchar);
int BMSearch(string txt, string pat);
void findFlightByArrivalName(Node* node, const string& pat, bool& falg);



