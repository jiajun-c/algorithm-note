#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    Node *prev;
    Node *next;
    int val;
    Node(int _val)
    {
        prev = NULL;
        next = NULL;
        val = _val;
    }
};


class MyCircularDeque {
public:
    int cap;
    int size;
    Node *head;
    Node *tail;
    MyCircularDeque(int k) {
        cap = k;
        size = 0;
        head = new Node(-1);
        head->next = tail;
        tail = new Node(-1);
        tail->prev = head;
    }
    
    bool insertFront(int value) {
        Node *node = new Node(value);
        if (size == cap) return false;
        node->next = head->next;
        node->prev = head;
        head->next = node;
        size++;
        return true;
    }
    
    bool insertLast(int value) {
        Node *node = new Node(value);
        if (size == cap) return false;
        node->prev = tail->prev;
        tail->prev = node;
        node->next = tail;
        size++;
        return true;
    }
    
    bool deleteFront() {
        if (head->next == tail) return false;
        Node* node = head->next;
        head->next = node->prev;
        node->next->prev = head;
        size--;
        return true;
    }
    
    bool deleteLast() {
        if (tail->prev == head) return false;
        Node* node = tail->prev;
        node->prev->next = tail;
        tail->prev = node->prev;
        size--;
        return true;
    }
    
    int getFront() {
        return head->next->val;
    }
    
    int getRear() {
        return tail->prev->val;
    }
    
    bool isEmpty() {
        return size == 0;
    }
    
    bool isFull() {
        return size == cap;
    }
};

/**
 * Your MyCircularDeque object will be instantiated and called as such:
 * MyCircularDeque* obj = new MyCircularDeque(k);
 * bool param_1 = obj->insertFront(value);
 * bool param_2 = obj->insertLast(value);
 * bool param_3 = obj->deleteFront();
 * bool param_4 = obj->deleteLast();
 * int param_5 = obj->getFront();
 * int param_6 = obj->getRear();
 * bool param_7 = obj->isEmpty();
 * bool param_8 = obj->isFull();
 */