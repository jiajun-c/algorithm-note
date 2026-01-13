#include <iostream>
#include <vector>
#include <random>
#include <climits>

using namespace std;

class Skiplist {
private:
    struct Node
    {
        int val;
        vector<Node*> forward;
        Node(int v, int level): val(v), forward(level, nullptr) {}
    };
    static const int MAX_LEVEL = 32;
    // 晋升概率 (通常取 0.25 或 0.5)
    static constexpr float P_FACTOR = 0.25;
    Node* head; // 头节点（哨兵），不存实际数据，层数最高
    int level;  // 当前跳表的有效最大层数
    mt19937 gen; // 随机数生成器
    uniform_real_distribution<float> dis; // 0-1 分布
    int randomLevel() {
        int lv = 1;
        while (dis(gen) < P_FACTOR && lv < MAX_LEVEL) {
            lv++;
        }
        return lv;
    }
public:
    Skiplist() {
        head = new Node(-1, MAX_LEVEL);
        level = 0;
        random_device rd;
        dis = uniform_real_distribution<float>(0, 1);
    }
    
    bool search(int target) {
        Node* curr = head;
        // 1. 从最高层开始向下遍历
        for (int i = level - 1; i >= 0; i--) {
            // 2. 如果当前层的下一个节点值小于 target，就向右走
            while (curr->forward[i] && curr->forward[i]->val < target) {
                curr = curr->forward[i];
            }
        }
        // 3. 此时 curr 是小于 target 的最大节点。
        // 检查第 0 层（最底层）的下一个节点是不是 target
        curr = curr->forward[0];
        return curr && curr->val == target;
    }
    
    void add(int num) {
        vector<Node*> update(MAX_LEVEL, nullptr);
        Node* curr = head;
        for (int i = level - 1; i >= 0; i--) {
            // 2. 如果当前层的下一个节点值小于 target，就向右走
            while (curr->forward[i] && curr->forward[i]->val < target) {
                curr = curr->forward[i];
            }
            update[i] = curr;
        }
        int lv = randomLevel();

        // 如果新层数超过了当前跳表的最大层数，需要更新头节点作为前驱
        if (lv > level) {
            for (int i = level; i < lv; i++) {
                update[i] = head;
            }
            level = lv; // 更新跳表层数
        }

        // 3. 创建新节点并插入
        Node* newNode = new Node(num, lv);
        for (int i = 0; i < lv; i++) {
            // 标准的链表插入操作：newNode->next = prev->next; prev->next = newNode;
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
    
    bool erase(int num) {
        vector<Node*> update(MAX_LEVEL, nullptr);
        Node* curr = head;

        // 1. 寻找要删除的节点的前驱
        for (int i = level - 1; i >= 0; i--) {
            while (curr->forward[i] && curr->forward[i]->val < num) {
                curr = curr->forward[i];
            }
            update[i] = curr;
        }

        // curr 指向目标节点
        curr = curr->forward[0];

        // 2. 如果没找到，返回 false
        if (!curr || curr->val != num) {
            return false;
        }
        for (int i = 0; i < level; i++) {
            // 如果这一层的前驱并没有指向 curr，说明 curr 在这一层不存在（或更高层），循环结束
            if (update[i]->forward[i] != curr) {
                break;
            }
            // 断开连接：prev->next = curr->next
            update[i]->forward[i] = curr->forward[i];
        }
        delete curr;

        // 5. 如果删除了最高层的节点，可能导致跳表有效层数降低
        while (level > 0 && head->forward[level - 1] == nullptr) {
            level--;
        }

        return true;
    }
};

/**
 * Your Skiplist object will be instantiated and called as such:
 * Skiplist* obj = new Skiplist();
 * bool param_1 = obj->search(target);
 * obj->add(num);
 * bool param_3 = obj->erase(num);
 */