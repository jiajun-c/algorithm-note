#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class Node
{
public:
    Node* prev;
    Node* next;
    list<string>values;
    int count;
    Node(int count)
    {
        this->count = count;
        this->prev = nullptr;
        this->next = nullptr;
    }
};


class AllOne {


    public:
        Node *head, *tail;
        unordered_map<string, Node*> NodeMap;
        AllOne() {
            head = nullptr;
            tail = nullptr;
        }
        Node* addNode(Node* prevNode, int count) {
            Node* node = new Node(count);
            if (prevNode->next) {
                prevNode->next->prev = node;
                node->next = prevNode->next;
            } else {
                prevNode->next = node;
            }
            if (!tail) tail = node;
            node->prev = prevNode;
            return node;    
        }

        void removeNode(Node* node) { 
            if (node->prev) {
                node->prev->next = node->next;
            }

            if (node->next) {
                node->next->prev = node->prev;
            }
            if (tail == node) {
                tail = node->prev;
            }
        }
        void inc(string key) {
            if (NodeMap.find(key) == NodeMap.end()) {
                if (head->next == nullptr || head->next->count != 1) {
                    addNode(head, 1);
                }
                head->next->values.push_front(key);
                NodeMap[key] = head->next;
            } else {
                Node* node = NodeMap[key];
                int count = NodeMap[key]->count;
                if (node->next == nullptr || node->next->count != count + 1) {
                    addNode(node, count + 1);
                    
                }
                node->next->values.push_front(key);
                NodeMap[key] = node->next;
                node->values.remove(key);
                if (node->values.empty()) {
                    removeNode(node);
                }
            }
        }
        
        void dec(string key) {
            Node* node = NodeMap[key];
            int count = node->count-1;
            if (count) {
                if (!node->prev || node->prev->count != count){
                    addNode(node, count);
                } 
                node->prev->values.push_front(key);
                NodeMap[key] = node->next;
            }
            node->values.remove(key);
            if (node->values.empty()) removeNode(node);
        }
        
        string getMaxKey() {
            return head->next ? head->next->values.front() : "";
        }
        
        string getMinKey() {
            return tail ? tail->values.front() : "";
        }
    };
    
    /**
     * Your AllOne object will be instantiated and called as such:
     * AllOne* obj = new AllOne();
     * obj->inc(key);
     * obj->dec(key);
     * string param_3 = obj->getMaxKey();
     * string param_4 = obj->getMinKey();
     */