#include <iostream>
#include <vector>

using namespace std;
 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
class Solution {
public:

    int back(ListNode* now) {
        if (now == nullptr) {
            return 0;
        }
        int backValue = back(now->next);
        now->val = (now->val + backValue)*2;
        backValue = now->val/10;
        now->val = now->val%10;
        return backValue;
    }
    ListNode* doubleIt(ListNode* head) {
        int v = back(head);
        if (v) {
            ListNode* newHead = new ListNode(1);
            newHead->next = v;
            return newHead;
        }
        return head;
    }
};