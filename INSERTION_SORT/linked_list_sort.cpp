#include <iostream>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v): val(v), next(nullptr) {}
};

// inserta node en la lista ordenada cuyo head es 'sortedHead'
void sortedInsert(Node*& sortedHead, Node* node) {
    if (!sortedHead || node->val <= sortedHead->val) {
        node->next = sortedHead;
        sortedHead = node;
        return;
    }
    Node* cur = sortedHead;
    while (cur->next && cur->next->val < node->val) cur = cur->next;
    node->next = cur->next;
    cur->next = node;
}

Node* insertionSortList(Node* head) {
    Node* sorted = nullptr;
    Node* cur = head;
    while (cur) {
        Node* next = cur->next;
        cur->next = nullptr;
        sortedInsert(sorted, cur);
        cur = next;
    }
    return sorted;
}

// helpers para demo
void printList(Node* h) {
    for (; h; h = h->next) cout << h->val << " ";
    cout << "\n";
}

int main() {
    Node* head = new Node(4);
    head->next = new Node(3);
    head->next->next = new Node(5);
    head->next->next->next = new Node(1);

    head = insertionSortList(head);
    printList(head);
}

