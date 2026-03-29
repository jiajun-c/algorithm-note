#include <iostream>
#include <deque>
#include <vector>
#include <queue>
using namespace std;
class StreamingMax {
private:
    std::deque<int>q;
    vector<int>maxv;
    queue<int>toDel;
    int winsize; // 窗口的大小
    int64_t now;
public:
    StreamingMax(int _winSize) {
        this->winsize = _winSize;
    }
    void push(int x) {
        while (q.size() && q.back() < x) q.pop_back();
        q.push_back(x);
        if (toDel.size() < winsize) {
            toDel.push(x);
            return;
        } 
        while (!q.empty() && q.front() == toDel.front()) q.pop_front();
        toDel.pop();
        toDel.push(x);
        maxv.push_back(q.front());
    }
    int currentMax() {
        return q.front();
    }
};
int main() {
    StreamingMax s(3);
    for (int i = 9; i >= 0; i--) {
        s.push(i);
        printf("%d\n", s.currentMax());
    }
}