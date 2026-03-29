#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;
class Node {
public:
    Node() {
        next = nullptr;
        key = -1;
        value = -1;
    }
    Node(int k, int v) {
        next = nullptr;
        key = k;
        value = v;
    }
    int key;
    int value;
    Node* next;
    Node* prev;
};
class LRUCache {
public:
    int cap;
    int size;
    Node* head, *tail;
    unordered_map<int, Node*>m;
    LRUCache(int capacity) {
        cap = capacity;
        size = 0;
        head = new Node(-1, -1);
        tail = new Node(-1, -1);

        head->next = tail;
        tail->prev = head;
    }
    void moveToHead(Node* now) {
        now->next = head->next;
        now->prev = head;

        head->next->prev = now;
        head->next = now;
    }

    void deleteNode(Node *now) {
        Node* prev = now->prev;
        Node* next = now->next;

        next->prev = prev;
        prev->next = next;
    }
    int get(int key) {
        if (m.find(key) != m.end()) {
            Node* node = m[key];
            deleteNode(node);
            moveToHead(node);
            return node->value;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if (m.find(key) != m.end()) {
            Node* node = m[key];
            node->value = value;
            deleteNode(node);
            moveToHead(node);
            return;
        } else {
            if (size == cap) {
                deleteNode(tail->prev),size--;
                m.erase(tail->prev->key);
            }
            size++;
            Node* now = new Node(key, value);
            moveToHead(now);
        }
    }
};
