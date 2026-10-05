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