#include <iostream>
using namespace std;

// 自己簡單實作的 Stack
class CustomStack {
private:
    int arr[100000]; // 直接開一個夠大的陣列，省去擴容的麻煩
    int topIndex;

public:
    CustomStack() {
        topIndex = -1;
    }

    void push(int value) {
        if (topIndex < 99999) {
            arr[++topIndex] = value;
        }
    }

    void pop() {
        if (topIndex >= 0) {
            topIndex--;
        }
    }

    int top() {
        if (topIndex >= 0) {
            return arr[topIndex];
        }
        return -1; 
    }

    bool empty() {
        return topIndex == -1;
    }
};

// 非遞迴 Ackermann 函式 
int ackermannNonRecursive(int m, int n) {
    CustomStack s;
    s.push(m);

    while (!s.empty()) {
        m = s.top();
        s.pop();

        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            s.push(m - 1);
            n = 1;
        } else {
            // A(m, n) = A(m - 1, A(m, n - 1))
            s.push(m - 1); // 存外層
            s.push(m);     // 存內層
            n = n - 1;
        }
    }
    return n;
}

int main() {
    int m = 2, n = 2;
    cout << "=== 第一題: Ackermann Function (非遞迴手刻 Stack) ===" << endl;
    cout << "結果 A(" << m << ", " << n << ") = " << ackermannNonRecursive(m, n) << endl;
    return 0;
}