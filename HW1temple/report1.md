# 資料結構作業報告

**姓名：** 金廷臻  
**學號：** 41443124  

---

## 程式一：遞迴版 Ackermann 函數 (Recursive_ackermann.cpp)

### 解題說明
這題是要我們實作數學上的 Ackermann 函數。這個函數的特色是它的數值成長速度超級快，通常是用來測試編譯器跟系統 Call Stack 遞迴深度的極限。

### 解題策略
因為題目已經給了明確的數學定義，所以最直覺的解法就是直接照著公式用遞迴寫。把邏輯分成三種情況：m=0、m>0且n=0、還有m>0且n>0。用 if-else 判斷式把這三條路徑寫出來呼叫自己就好。

### 程式實作
```cpp
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
```

### 效能分析
時間跟空間複雜度都很難用簡單的 Big-O 表示，因為它成長得比指數還快。只要參數稍微給大一點，遞迴呼叫的次數就會暴增，空間上會消耗掉系統極大量的 Call Stack，很容易發生 Stack Overflow。

### 測試與驗證
設定 m = 2, n = 2 下去跑，終端機印出來的結果是 7，跟自己慢慢手推算出來的結果一樣，邏輯上沒問題。

---

## 程式二：非遞迴版 Ackermann 函數 (NonRecursive_ackermann.cpp)

### 解題說明
因為遞迴版只要數字大一點就很容易發生堆疊溢位，所以這題要求我們不用系統遞迴，改成自己寫一個 Stack 來模擬遞迴的過程。

### 解題策略
不能用系統的遞迴，我就手刻一個 Stack 類別。為了避免寫動態陣列擴容那種麻煩又容易出錯的邏輯，我直接開了一個容量十萬的固定陣列來當作 Stack 的底層。接著用 while 迴圈去跑，把原本要遞迴的參數 push 進去，每次從頂端拿出來檢查，按照規則把拆解後的狀態再丟回 Stack，直到 Stack 空了為止。

### 程式實作
```cpp
#include <iostream>
using namespace std;

// 自己簡單實作的 Stack
class CustomStack {
private:
    int arr[100000]; // 宣告數字大的陣列，省去擴容的麻煩
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

    // 程式一開始，先把最初的任務 m 丟進 Stack 排隊

    CustomStack s;    //宣告物件
    s.push(m);
   

   // 只要 Stack 裡面還有待辦事項沒清空，就繼續跑
    while (!s.empty()) {
        m = s.top();   //紀錄stack 的頂端元素
        s.pop();     // 每次都從最上面拿出一個任務 m 來處理，拿出來後要記得 pop 掉

        if (m == 0) {
            n = n + 1;   //對應：A(0, n) = n + 1
        } else if (n == 0) {
            s.push(m - 1);
            n = 1;        //對應:A(m-1,1);
        } else {
            // 對應A(m, n) = A(m - 1, A(m, n - 1))
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
```

### 效能分析
時間複雜度一樣很高，但空間複雜度從吃系統的 Stack 變成了吃我們自己宣告的陣列記憶體。好處是只要我們陣列開得夠大，就不會像遞迴版那樣隨便就當掉，穩定度提高很多。

### 測試與驗證
一樣用 m = 2, n = 2 測試，印出來也是 7。證明非遞迴的拆解順序與原本的數學定義是一致的。

---

## 程式三：產生冪集 Powerset (powerset.cpp)

### 解題說明
這題給我們一個集合，例如 {a, b, c}，要求我們把所有可能的子集合 (也就是冪集) 全部印出來，包含空集合。

### 解題策略
這是一個很經典的窮舉問題。針對集合裡的每一個元素，我們都只有兩種決定：選它或不選它。所以我寫了一個遞迴函式，每次遞迴往下走的時候分兩條岔路，一條是把元素塞進目前的陣列，另一條是什麼都不做直接往下一格走。有選的那條路走完之後，要記得把元素 pop 出來做回溯 (Backtrack)，這樣狀態才會乾淨，才能繼續找下一個組合。

### 程式實作
```cpp
#include <iostream>
#include <vector>
using namespace std;

// 遞迴產生冪集
void getPowerset(const vector<char>& S, int index, vector<char>& current) {
    // 終止條件：所有的元素都決定過選或不選了
    if (index == S.size()) {
        cout << "(";
        for (int i = 0; i < current.size(); ++i) {
            cout << current[i];
            if (i + 1 < current.size()) {
                cout << ", ";
            }
        }
        cout << ")" << endl;
        return;
    }

    // 選擇 1：不要把現在這個元素加進去
    getPowerset(S, index + 1, current);

    // 選擇 2：把這個元素加進去
    current.push_back(S[index]);
    getPowerset(S, index + 1, current);

    // 回溯 (Backtrack)：把剛剛加進去的元素拔掉，還原狀態
    current.pop_back();
}

int main() {
    vector<char> S = {'a', 'b', 'c'};
    vector<char> current;

    cout << "=== 第二題: Powerset of {a, b, c} ===" << endl;
    getPowerset(S, 0, current);

    return 0;
}
```

### 效能分析
因為每個元素都有選跟不選兩種狀態，如果有 N 個元素就會產生 2 的 N 次方種結果。所以時間複雜度是 O(2^N)。空間複雜度的話，主要是遞迴呼叫的深度，最多也就是 N 層，所以是 O(N)。

### 測試與驗證
設定初始集合為 {a, b, c}。跑出來的結果確實印出了 8 種組合，也有正確把空集合 () 印出來，格式完全符合預期。

---

## 編譯與執行指令

如果在一般終端機底下要編譯跟執行這三支程式，可以輸入以下指令：

```bash
# 程式一
g++ Recursive_ackermann.cpp -o p1_rec
./p1_rec

# 程式二
g++ NonRecursive_ackermann.cpp -o p1_nonrec
./p1_nonrec

# 程式三
g++ powerset.cpp -o p2
./p2
```

---

## 結論

這次作業主要是在練習遞迴跟非遞迴的思維轉換。遞迴雖然很好寫，程式碼看起來也很乾淨，但遇到 Ackermann 這種深度的計算，系統根本扛不住。自己刻 Stack 來模擬雖然稍微麻煩一點，但確實是解決 Stack Overflow 的實用方法。然後在寫 Powerset 的時候，也複習到了 DFS 跟 Backtracking 的技巧，了解什麼時候要把狀態還原真的很重要。

---

## 申論及開發報告

分享一下寫這份作業的過程。剛開始寫第一題的遞迴版覺得滿簡單的，就是帶入遞迴的式子打完就好了。結果稍微改大一點的數字測試，程式就跑不步了，用了非遞迴才能跑

在寫非遞迴版的時候其實卡了一陣子，主要是不懂要放進stack的要是m還是n 或是兩者都要?，內層跟外層要誰先丟進去、誰後丟進去，想了滿久才弄懂。為了不要在作業裡處理煩人的動態記憶體配置 (怕寫錯指標導致 memory leak)，我直接用空間換時間，宣告了一個大小為十萬的陣列來當作 Stack。這算是一個寫 code 的折衷辦法，至少不會有容量不夠的問題，除錯起來也比較直覺。

最後的 Powerset 就比較順利了，因為以前有寫過類似用 vector 去跑窮舉的題目，只要記得在遞迴回來的下一行加上 `pop_back()` 做好回溯，結果就順利印出來了。整體來說這幾支程式幫助我對 Call Stack 的運作原理有更具體的感覺。