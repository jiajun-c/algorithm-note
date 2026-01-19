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
    ListNode* reverseEvenLengthGroups(ListNode* head) {
        int len = 2;
        ListNode* prev = head;
        while (prev->next)
        {
            ListNode* curr = prev;
            int actualLen = 0;
            for (int i = 0; i < len&&curr->next; i++) {
                curr = curr->next;
                actualLen++;
            }
            len++;
            if (actualLen % 2 == 0) {
                ListNode* currGroupHead = prev->next;
                ListNode* nextGroupHead = curr->next;
                ListNode *p = currGroupHead, *q = nullptr;
                while (p != nextGroupHead)
                {
                    ListNode* next = p->next;
                    p->next = q;
                    q = p;
                    p = next;
                }
                prev->next = q;
                currGroupHead->next = nextGroupHead;

                prev = currGroupHead;
            } else {
                prev = curr;
            }
        }
        return head;
    }
};