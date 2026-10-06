#include <iostream>
using namespace std;

// 遞迴版本的 Ackermann 函數
int ackermannRecursive(int m, int n) {
    // 情況 1: 到底了，直接回傳
    if (m == 0) {
        return n + 1;
    } 
    // 情況 2: m > 0 但 n 歸零
    else if (n == 0) {
        return ackermannRecursive(m - 1, 1);
    } 
    // 情況 3: m 跟 n 都大於 0，要跑雙重遞迴
    else {
        return ackermannRecursive(m - 1, ackermannRecursive(m, n - 1));
    }
}

int main() {
    int m = 2, n = 2; // 測試用的數字
    cout << "=== 第一題: Ackermann Function (遞迴版) ===" << endl;
    cout << "計算 A(" << m << ", " << n << ") 中..." << endl;
    
    int result = ackermannRecursive(m, n);
    cout << "結果: A(" << m << ", " << n << ") = " << result << endl;
    
    return 0;
}