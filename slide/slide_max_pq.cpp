#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class StreamingMaxPqFixed {
private:
    // pair<int, int> 存储 {数值, 时间戳}
    // C++ pair 默认比较 first，所以这会形成一个按数值排序的大顶堆
    priority_queue<pair<int, int>> pq;
    int winsize;
    int64_t now; // 当前元素的逻辑下标
public:
    StreamingMaxPqFixed(int _winSize) {
        this->winsize = _winSize;
        now = 0;
    }
    
    void push(int x) {        
        // 修正 1: 将数值 x 放在 first，时间戳 now 放在 second
        pq.push({x, (int)now}); 
        
        // 修正 2: 检查堆顶元素的时间戳(second)是否在窗口左边界(now - winsize)及左边
        // 当前窗口范围是 [now - winsize + 1, now]
        // 所以如果 index <= now - winsize，说明它已经滑出去了
        while (!pq.empty() && pq.top().second <= now - winsize) {
            pq.pop();
        }
        now++;
    }
    
    int currentMax() {
        if (pq.empty()) return -1;
        return pq.top().first; // 修正 3: 返回 first (数值)
    }
};
void runTest(string testName, vector<int> inputs, int k, vector<int> expected) {
    cout << "=== Test: " << testName << " (Window Size: " << k << ") ===" << endl;
    StreamingMaxPqFixed s(k);
    bool passed = true;
    
    printf("%-10s %-10s %-10s %-10s\n", "Input", "Expected", "Actual", "Status");
    
    for (size_t i = 0; i < inputs.size(); i++) {
        s.push(inputs[i]);
        int actual = s.currentMax();
        int exp = expected[i];
        
        string status = (actual == exp) ? "OK" : "FAIL";
        if (actual != exp) passed = false;
        
        printf("%-10d %-10d %-10d %-10s\n", inputs[i], exp, actual, status.c_str());
    }
    cout << "Result: " << (passed ? "PASSED" : "FAILED") << "\n" << endl;
}
int main() {
    // 测试用例 1: 降序数组 (最能暴露你的 Bug)
    // 你的代码会输出 5, 4, 3, 2, 1 (因为总是返回最新值)
    // 正确应该是 5, 5, 5, 4, 3
    runTest("Decreasing", {5, 4, 3, 2, 1}, 3, {5, 5, 5, 4, 3});

    // 测试用例 2: 升序数组 (你的代码会侥幸通过，因为最新值刚好是最大值)
    runTest("Increasing", {1, 2, 3, 4, 5}, 3, {1, 2, 3, 4, 5});

    // 测试用例 3: 波峰滑出 (验证延迟删除逻辑)
    // 窗口大小 3。输入: 1, 10, 1, 2, 3
    // 10 进入后，最大值应锁定 10，直到 10 滑出窗口
    runTest("Peak Exit", {1, 10, 1, 2, 3}, 3, {1, 10, 10, 10, 3});

    // 测试用例 4: 震荡数据
    runTest("Wavy", {2, 1, 5, 1, 2}, 3, {2, 2, 5, 5, 5});

    return 0;
}