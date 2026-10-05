# 程式作業報告 (Homework Report)

**姓名 (Name)：** 金廷臻

**學號 (Student ID)：** 41443124

---

## 1. 程式一：遞迴版 Ackermann 函數 (`Recursive_ackermann.cpp`)

### 程式說明與邏輯架構

本程式使用 **遞迴 (Recursion)** 的方式來實作數學上著名的 Ackermann 函數。Ackermann 函數是一個非原始遞迴函數 (non-primitive recursive function)，其特色為數值成長速度極快，且遞迴深度極深，常用於測試編譯器優化與系統堆疊 (Call Stack) 的極限。

程式嚴格依照數學定義，將邏輯拆分為三種基本情況進行遞迴呼叫：

1. **情況 1 (`m == 0`)：** 達到基礎條件，直接回傳 `n + 1`。
2. **情況 2 (`m > 0` 且 `n == 0`)：** 遞迴呼叫 `ackermannRecursive(m - 1, 1)`。
3. **情況 3 (`m > 0` 且 `n > 0`)：** 進行雙重遞迴。先遞迴計算內層 `ackermannRecursive(m, n - 1)`，將其結果作為新參數 `n`，再帶入外層 `ackermannRecursive(m - 1, 新的n)` 中計算。

### 程式碼片段

```cpp
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
```

---

## 2. 程式二：非遞迴版 Ackermann 函數 (`NonRecursive_ackermann.cpp`)

### 程式說明與邏輯架構

為了解決遞迴版本在參數稍大時容易引發「堆疊溢位 (Stack Overflow)」的問題，本程式將原本依賴系統的遞迴呼叫，改寫為依賴 **自訂堆疊 (Custom Stack)** 的 **非遞迴 (Iterative)** 版本。

1. **自訂堆疊 `CustomStack` 類別：**
   * 使用動態陣列 (`int* arr`) 進行實作，預設提供 10000 的容量。
   * 實作了**自動擴容機制**：當堆疊滿載 (`topIndex == capacity - 1`) 時，會自動建立兩倍大的新陣列，並將舊資料複製過去，避免頻繁配置記憶體造成效能低落。
   * 提供基礎的 `push`、`pop`、`top`、`empty` 介面供演算法呼叫。

2. **非遞迴演算法 (`ackermannNonRecursive`)：**
   * 利用堆疊來保存並追蹤外層的 `m` 值。
   * 使用 `while` 迴圈反覆執行直到堆疊清空。每次取出堆疊頂端的 `m`：
     * 若 `m == 0`：將 $n$ 遞增 (`n = n + 1`)。
     * 若 `n == 0`：將 `m - 1` 推入堆疊，並將 $n$ 設為 1。
     * 其他情況：推入 `m - 1` (代表外層狀態) 與 `m` (代表內層繼續運算的狀態)，並將 $n$ 遞減。
   * 當堆疊為空時，所留下的 $n$ 變數即為最終答案。

### 程式碼片段

```cpp
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
```

---

## 3. 程式三：產生冪集 Powerset (`powerset.cpp`)

### 程式說明與邏輯架構

本程式旨在計算並印出給定集合 (例如 `{a, b, c}`) 的所有可能子集，也就是**冪集 (Powerset)**。程式運用了 **遞迴與回溯演算法 (Backtracking)** 的技巧來窮舉所有組合。

演算法核心概念如下：

1. **狀態定義：** 透過遞迴函式 `getPowerset` 傳遞目前處理到的元素索引 (`index`) 以及目前選取的元素集合 (`current`)。
2. **終止條件 (Base Case)：** 當 `index == S.size()` 時，代表對於集合中的每一個元素都已經做過「選」或「不選」的決定。此時直接印出 `current` 內的元素陣列。
3. **狀態分支：**
   * **情況 1 (不選擇)：** 不將 `S[index]` 加入子集，直接進入下一層遞迴 (`index + 1`)。
   * **情況 2 (選擇)：** 將 `S[index]` 加入 `current` 陣列 (`push_back`)，接著進入下一層遞迴。
4. **回溯 (Backtracking)：** 在「選擇」的分支遞迴結束後，必須將剛剛加入的元素從 `current` 中移除 (`pop_back`)，讓狀態還原到進入該層遞迴前的模樣，以便後續返回上層繼續正確地嘗試其他組合。

### 程式碼片段

```cpp
#include <iostream>
#include <vector>

using namespace std;

// 遞迴產生 Powerset (冪集)
void getPowerset(const vector<char>& S, size_t index, vector<char>& current) {
    // 終止條件：當索引等於集合大小，代表所有元素都決定過「選或不選」
    if (index == S.size()) {
        cout << "(";
        for (size_t i = 0; i < current.size(); ++i) {
            cout << current[i];
            if (i + 1 < current.size()) {
                cout << ", ";
            }
        }
        cout << ")" << endl;
        return;
    }

    // 情況 1：不選擇當前元素 S[index]
    getPowerset(S, index + 1, current);

    // 情況 2：選擇當前元素 S[index] 加入子集合
    current.push_back(S[index]);
    getPowerset(S, index + 1, current);

    // 回溯（Backtrack）：將剛加入的元素移除，以便回到上一層嘗試其他組合
    current.pop_back();
}

int main() {
    vector<char> S = {'a', 'b', 'c'};
    vector<char> current;

    cout << "=== Problem 2: Powerset of {a, b, c} ===" << endl;
    getPowerset(S, 0, current);

    return 0;
}
```

---

## 4. 總結 (Summary)

這三個程式分別展示了資料結構中幾個非常重要的核心觀念：

* **遞迴函式的直觀性：** 如程式一，演算法邏輯與數學定義幾乎完全一致。
* **遞迴與迭代的轉換：** 如程式二，展示了如何透過維護「自訂堆疊」來將複雜的雙層遞迴攤平，以空間換取執行穩定度。
* **狀態樹的遍歷：** 如程式三，透過回溯法 (Backtracking) 完美示範了如何在決策樹 (選與不選) 中進行深度優先搜尋 (DFS) 以取得所有子集合。