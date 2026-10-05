#include <iostream>

using namespace std;

// 遞迴版本的 Ackermann 函數
int ackermannRecursive(int m, int n) {
    // 情況 1: m == 0
    if (m == 0) {
        return n + 1;
    } 
    // 情況 2: m > 0 且 n == 0
    else if (n == 0) {
        return ackermannRecursive(m - 1, 1);
    } 
    // 情況 3: m > 0 且 n > 0
    else {
        return ackermannRecursive(m - 1, ackermannRecursive(m, n - 1));
    }
}

int main() {
    int m = 2, n = 2; // 可根據需要修改測試數值
    
    cout << "=== Problem 1: Ackermann Function (Recursive) ===" << endl;
    cout << "Calculating A(" << m << ", " << n << ")...\n" << endl;
    
    int result = ackermannRecursive(m, n);
    cout << "Result: A(" << m << ", " << n << ") = " << result << endl;
    
    return 0;
}