
#include <iostream>
using namespace std;
struct NODE
{
    int data;
    NODE *next;
};

void push(NODE **head, int data) {
    NODE* node = new NODE();
    node->data = data;
    node->next = (*head);
    (*head) = node;
}

void reverse1(NODE* &head) {

  NODE* current = head, *next = nullptr, *prev = nullptr;

  while (current != nullptr) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  head = prev;
}

void printnodes(NODE *head) {
    while(head != NULL) {
        cout<<head->data<<" ";
        head = head->next;
    }
}

int main() {

  NODE* head = new NODE();
  push(&head, 1);
  push(&head, 2);
  push(&head, 3);
  push(&head, 4);

  cout << "Linked List Before Reversing" << endl;
  printnodes(head);
  reverse1(head);
  cout << endl;
  cout << "Linked List After Reversing"<<endl;
  printnodes(head);

  return 0;
}