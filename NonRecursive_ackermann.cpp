#include <iostream>

// 自己實作的 Stack 類別 (使用動態陣列)
class CustomStack {
private:
    int* arr;
    int capacity;
    int topIndex;

public:
    // 預設給大一點的空間，避免頻繁擴充
    CustomStack(int size = 10000) {  
        capacity = size;
        arr = new int[capacity];
        topIndex = -1;
    }

    ~CustomStack() {
        delete[] arr;
    }

    void push(int value) {
        if (topIndex == capacity - 1) {
            // 當空間不夠時，自動將陣列容量加倍
            capacity *= 2;
            int* newArr = new int[capacity];
            for (int i = 0; i <= topIndex; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
        }
        arr[++topIndex] = value;
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

// 非遞迴 Ackermann 函式 (使用自訂 CustomStack)
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
            s.push(m - 1); // 外層
            s.push(m);     // 內層
            n = n - 1;
        }
    }
    return n;
}

int main() {
    int m = 2, n = 2;
    std::cout << "Problem 1: Non-recursive Ackermann using Custom Stack\n";
    std::cout << "A(" << m << ", " << n << ") = " << ackermannNonRecursive(m, n) << std::endl;
    return 0;
}