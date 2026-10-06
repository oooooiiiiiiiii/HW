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