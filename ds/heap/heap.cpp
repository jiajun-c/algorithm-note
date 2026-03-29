#include <iostream>
#include <vector>
#include <functional> // for std::less, std::greater
#include <algorithm>  // for std::swap
#include <stdexcept>  //
using namespace std;

template<typename T, typename Compare=std::less<T>>
class PriorityQueue {
private:
    std::vector<T>heap;
    Compare comp;
public:
    void shift_up(int index) {
        while (index > 0) {
            int parent = (index - 1)/2;
            if (comp(heap[parent], heap[index])) {
                std::swap(heap[parent], heap[index]);
                index = parent;
            } else {
                break;
            }
        }
    }
    void shift_down(int index) {
        while(true) {
            int left = index*2 +1;
            int right = index*2+2;
            int target = index;
            if (left < heap.size() && comp(heap[target], heap[left])) {
                target = left;
            }

            if (right < heap.size() && comp(heap[target], heap[right])) {
                target = right;
            }
            if (target == index) break;
            swap(heap[target], heap[index]);
            index = target;
        }
    }

    void push(T x) {
        heap.push_back(x);
        shift_up(heap.size()-1);
    }

    void pop() {
        std::swap(heap[heap.size()-1], heap[0]);
        heap.pop_back();
        if (heap.size()) shift_down(0);
    }

    bool empty() {
        return !heap.size();
    }

    T top() {
        return heap[0];
    }
};


int main() {
    // 1. 测试大顶堆 (默认)
    cout << "=== Max Heap Test ===" << endl;
    PriorityQueue<int> max_pq;
    vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};
    
    for (int x : nums) max_pq.push(x);
    
    while (!max_pq.empty()) {
        cout << max_pq.top() << " "; // 应该输出: 9 6 5 4 3 2 1 1
        max_pq.pop();
    }
    cout << endl;

    // 2. 测试小顶堆 (使用 greater)
    cout << "\n=== Min Heap Test ===" << endl;
    PriorityQueue<int, std::greater<int>> min_pq;
    
    for (int x : nums) min_pq.push(x);
    
    while (!min_pq.empty()) {
        cout << min_pq.top() << " "; // 应该输出: 1 1 2 3 4 5 6 9
        min_pq.pop();
    }
    cout << endl;

    return 0;
}