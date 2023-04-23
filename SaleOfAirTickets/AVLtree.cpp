#include "AVLtree.h"

Node* createNode(Flight f) {
    Node* node = new Node;
    node->f = f;
    node->left = NULL;
    node->right = NULL;
    node->prev = NULL;
    node->height = 0;//
    return node;
}

bool insertNode(Node** root, Flight f) {
    if (*root == NULL) {
        *root = createNode(f);
    }
    else {
        Node* parent = *root;
        Node* newNode = createNode(f);
        while (true) {
            if (newNode->f.flight_id < parent->f.flight_id) {
                if (parent->left)
                    parent = parent->left;
                else {
                    parent->left = newNode;
                    newNode->prev = parent;
                    break;
                }
            }
            else if (newNode->f.flight_id > parent->f.flight_id) {
                if (parent->right)
                    parent = parent->right;
                else {
                    parent->right = newNode;
                    newNode->prev = parent;
                    break;
                }
            }
            else {
                return false;
            }
        }
        balanceTree(root, &parent);
        return true;
    }
}

void balanceTree(Node** root, Node** p) {
    Node* parent = *p;
    while (true) {
        updateHeight(parent);
        int balance = getBalance(parent);
        if (balance == 2) {
            if (getBalance(parent->right) == 0)
                leftRotate(parent);
            else if (getBalance(parent->right) == 1)
                leftRotate(parent);
            else
                bigLeftRotate(parent);
        }
        else if (balance == -2) {
            if (getBalance(parent->left) == 0)
                rightRotate(parent);
            else if (getBalance(parent->left) == -1)
                rightRotate(parent);
            else
                bigRightRotate(parent);
        }
        if (parent->prev)
            parent = parent->prev;
        else {
            break;
        }
    }
    *root = parent;
}

void updateHeight(Node*& node) {
    node->height = max(getHeight(node->left),getHeight(node->right))+1;
}

int getHeight(Node* node) {
    return (node == NULL) ? -1 : node->height;
}

int getBalance(Node* node) {
    return (node == NULL) ? 0 : getHeight(node->right) - getHeight(node->left);
}

void rightRotate(Node*& root) {
    Node* parent = root->prev;
    Node* leftSub = root->left;
    root->left = leftSub->right;
    if (leftSub->right != NULL)
        leftSub->right->prev = root;
    leftSub->right = root;
    root->prev = leftSub;
    leftSub->prev = parent;
    if (parent != NULL) {
        if (parent->left == root)
            parent->left = leftSub;
        else parent->right = leftSub;
    }
    root = leftSub;
    updateHeight(root->right);
    updateHeight(root);
}

void leftRotate(Node*& root) {
    Node* parent = root->prev;
    Node* rightSub = root->right;
    root->right = rightSub->left;
    if (rightSub->left != NULL)
        rightSub->left->prev = root;
    rightSub->left = root;
    root->prev = rightSub;
    rightSub->prev = parent;
    if (parent != NULL) {
        if (parent->left == root)
            parent->left = rightSub;
        else parent->right = rightSub;
    }
    root = rightSub;
    updateHeight(root->left);
    updateHeight(root);
}

void bigRightRotate(Node*& root) {
    leftRotate(root->left);
    rightRotate(root);
}

void bigLeftRotate(Node*& root) {
    rightRotate(root->right);
    leftRotate(root);
}

void deleteNode(Node** root, Node* curr) {
    if (curr->right == NULL && curr->left == NULL) {
        if (curr == *root)
            *root = NULL;
        else {
            if (curr->prev->right == curr)
                curr->prev->right = NULL;
            else
                curr->prev->left = NULL;
            balanceTree(root, &(curr->prev));
        }
    }
    else if (curr->right == NULL) {
        if (curr == *root) {
            *root = curr->left;
            curr->left->prev = curr->prev;
            balanceTree(root, root);
        }
        else {
            if (curr->prev->right == curr)
                curr->prev->right = curr->left;
            else
                curr->prev->left = curr->left;
            curr->left->prev = curr->prev;
            balanceTree(root, &(curr->prev));
        }
    }
    else if (curr->left == NULL) {
        if (curr == *root) {
            *root = curr->right;
            curr->right->prev = curr->prev;
            balanceTree(root, root);
        }
        else {
            if (curr->prev->right == curr)
                curr->prev->right = curr->right;
            else
                curr->prev->left = curr->right;
            curr->right->prev = curr->prev;
            balanceTree(root, &(curr->prev));
        }
    }
    else {
        Node* successor = getSuccessor(curr);
        Node* node = successor;
        if (curr == *root)
            *root = successor;
        else if (curr->prev->right == curr)
            curr->prev->right = successor;
        else
            curr->prev->left = successor;
        successor->left = curr->left;
        successor->prev = curr->prev;
        curr->left->prev = successor;
        balanceTree(root, &node);
    }
    delete curr;
}

Node* getSuccessor(Node* node) {
    Node* successor = node;
    Node* curr = node->right;
    while (curr != NULL) {
        successor = curr;
        curr = curr->left;
    }
    if (successor != node->right) {
        successor->prev->left = successor->right;
        if(successor->right!=NULL) 
            successor->right->prev = successor->prev;
        successor->right = node->right;
    }
    return successor;
}

void printPostorder(Node* node){
    if (node == NULL) return;
    printPostorder(node->left);
    printPostorder(node->right);
    printFlight(node->f);
}

Node* deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
        return NULL;
    }
}

void findFlightByArrivalName(Node* node, const string& pat, bool& flag) {
    if (node == NULL) return;
    findFlightByArrivalName(node->left, pat,flag);
    findFlightByArrivalName(node->right, pat,flag);
    if (BMSearch(node->f.arrival, pat) >= 0) {
        cout << "| " << setw(7) << node->f.flight_id << " | "  << setw(18) << node->f.arrival << " | " << setw(10) << node->f.date << " | "<< setw(11) << node->f.time<<" | " << endl;
        cout << "|---------|--------------------|------------|-------------|" << endl;
        flag = true;
    }
}

Node* findFlightById(Node* root, string flight_id) {
    Node* curr = root;
    while (curr && curr->f.flight_id != flight_id) {
        if (flight_id < curr->f.flight_id) 
            curr = curr->left;
        else 
            curr = curr->right;
    }
    return curr;
}

void printFlight(Flight& f) {
    cout << "| " << setw(7) << f.flight_id << " | " << setw(21) << f.airline_name << " | "
        << setw(20) << f.departure << " | " << setw(18) << f.arrival << " | "<< setw(10) << f.date << " | " 
        << setw(11) << f.time << " | " << setw(10) << f.num_of_seats << " | "<< setw(12) << f.num_of_free_seats << " | " << endl;
    cout << "|---------|-----------------------|----------------------|--------------------|------------|-------------|------------|--------------|" << endl;
}


void badCharHeuristic(string str, int size, int* badchar)
{
    for (int i = 0; i < 256; i++)//по умолчание ни одной буквы в образе нет
        badchar[i] = -1;

    for (int i = 0; i < size; i++)//заполн€ем массив последним вхождением символа в образ 
        badchar[(unsigned char)str[i]] = i;
}

int BMSearch(string txt, string pat)
{
    int m = pat.size();
    int n = txt.size();

    if (n < m) // —равните длину
        return -1;//ƒлина строки меньше длины поискового запроса
    

    int* badChar = new int[256];//таблица смещений 

    badCharHeuristic(pat, m, badChar);

    int s = 0; //сдвиг образца относительно текста
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && pat[j] == txt[s + j])// уменьшаем j пока символы образца и текста совпадают при данном сдвиге s
            j--;

        //≈сли образец есть в тексте полностью, то j будет равен -1 после предыдущего цикла
        if (j < 0)
        {
            delete[] badChar;
            return s;
        }
        else
            //смещаем образец так, чтобы badChar в тексте выравнилс€ по последнему его вхождению в образец.
            //‘ункци€ max используетс€ дл€ того, чтобы убедитьс€, что мы получаем положительный сдвиг.
            //ћы можем получить отрицательный сдвиг, если последний по€вление badChar в образце находитс€ с правой стороны от текущего символа в тексте.
            s += max(1, j - badChar[(unsigned char)txt[s + j]]);
    }
    delete[] badChar;
    return -1;
}

bool hasFreeSeats(Node* node) {
    return node->f.num_of_free_seats;
}

void increaseNumOfFreeSeats(Node* node, string flight_id) {
    Node* curr = findFlightById(node, flight_id);
    curr->f.num_of_free_seats++;
}
void decreaseNumOfFreeSeats(Node* node, string  flight_id) {
    Node* curr = findFlightById(node, flight_id);
    curr->f.num_of_free_seats--;
}


void printTree(Node* root, int space_size ) {
    deque<Node*> q = { root };
    int height = getHeight(root);
    int cur_level_nodes = 1, next_level_nodes = 0, level = 0;
    int padding = space_size * (pow(2, height - level) - 1);
    cout << endl << setw(padding / 2) << "";
    while (level <= height) {
        cout << setw(space_size);
        if (q.front()) {
            cout << q.front()->f.flight_id;
            q.push_back(q.front()->left);
            q.push_back(q.front()->right);
        }
        else {
            cout << " ";
            q.push_back(nullptr);
            q.push_back(nullptr);
        }
        next_level_nodes += 2;
        cout << setw(padding) << "";
        q.pop_front();

        if (--cur_level_nodes == 0) {
            cur_level_nodes = next_level_nodes;
            next_level_nodes = 0;
            ++level;
            padding = space_size * (pow(2, height - level) - 1);
            cout << endl << setw(padding / 2) << "";
        }
    }
    cout << endl;
}