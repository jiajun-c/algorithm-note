#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

template<typename T>
class Deque {
private:
    T* buffer;
    int start;      // 指向队头元素
    int end;        // 指向队尾元素的下一个位置 (左闭右开区间 [start, end))
    int size;
    int capacity;

public:
    // 【修正1】 正确初始化 capacity 和 buffer
    Deque(int cap) {
        capacity = cap;
        buffer = new T[capacity]; 
        start = 0;
        end = 0;
        size = 0;
    }

    // 析构函数 (防止内存泄漏)
    ~Deque() {
        delete[] buffer;
    }

    bool is_full() {
        return size == capacity;
    }

    bool is_empty() {
        return size == 0;
    }

    // 【修正逻辑】 Front 向左生长：先减索引，再存值
    void put_front(T x) {
        if (is_full()) {
            cout << "Deque is full!" << endl;
            return;
        }
        start = (start - 1 + capacity) % capacity;
        buffer[start] = x;
        size++;
    }

    // 【修正逻辑】 Back 向右生长：先存值，再加索引
    void put_back(T x) {
        if (is_full()) {
            cout << "Deque is full!" << endl;
            return;
        }
        buffer[end] = x;
        end = (end + 1) % capacity;
        size++;
    }

    T get_front() {
        if (is_empty()) throw runtime_error("Deque is empty");
        return buffer[start];
    }

    // 【修正逻辑】 End 指向的是下一个空位，所以取值要取 end-1
    T get_end() {
        if (is_empty()) throw runtime_error("Deque is empty");
        return buffer[(end - 1 + capacity) % capacity];
    }

    void pop_front() {
        if (is_empty()) return;
        start = (start + 1) % capacity;
        size--; // 【修正2】 记得减少 size
    }

    void pop_back() {
        if (is_empty()) return;
        end = (end - 1 + capacity) % capacity;
        size--; // 【修正2】 记得减少 size
    }
    
    int get_size() {
        return size;
    }
};

// --- 测试代码 ---
int main() {
    cout << "=== 开始测试 Deque ===" << endl;

    // 1. 初始化容量为 5
    Deque<int> dq(5);

    // 2. 测试 put_back
    dq.put_back(10);
    dq.put_back(20);
    // 当前队列: [10, 20]
    assert(dq.get_front() == 10);
    assert(dq.get_end() == 20);
    assert(dq.get_size() == 2);
    cout << "Test 1 (Put Back): Pass" << endl;

    // 3. 测试 put_front
    dq.put_front(5);
    // 当前队列: [5, 10, 20]
    assert(dq.get_front() == 5);
    assert(dq.get_end() == 20);
    assert(dq.get_size() == 3);
    cout << "Test 2 (Put Front): Pass" << endl;

    // 4. 测试混合操作
    dq.pop_back(); // 弹出 20, 剩余 [5, 10]
    assert(dq.get_end() == 10);
    
    dq.pop_front(); // 弹出 5, 剩余 [10]
    assert(dq.get_front() == 10);
    cout << "Test 3 (Pop Mixed): Pass" << endl;

    // 5. 测试环形覆盖 (Circular Buffer)
    // 当前剩余 [10] (size=1)
    // 容量是5，我们再加 4 个，填满它
    dq.put_back(100);
    dq.put_back(200);
    dq.put_back(300);
    dq.put_front(1); 
    // 此时 size 应该为 5
    assert(dq.get_size() == 5);
    assert(dq.is_full() == true);
    
    // 再加应该报错（或者被忽略，取决于实现，这里测试不崩溃即可）
    dq.put_back(999); 
    assert(dq.get_size() == 5); // size 不应增加
    cout << "Test 4 (Full/Circular): Pass" << endl;

    // 6. 测试清空
    while(!dq.is_empty()) {
        dq.pop_front();
    }
    assert(dq.get_size() == 0);
    cout << "Test 5 (Empty): Pass" << endl;

    cout << "=== 所有测试通过 ===" << endl;
    return 0;
}