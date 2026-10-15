#include<cstring>
#include<iostream>
using namespace std;


class GameCharacter {

private:
    string name;
    int hp;
    int level;
    // Constructor

public:

    GameCharacter() {};

    GameCharacter(string n, int& h, int& l) :name(n), hp(h), level(l) {};
    // 受到傷害
    void damage(int value);
    // 回復生命值
    void heal(int value);
    // 升級
    void levelUp();
    // 顯示角色資料
    void show();

    ~GameCharacter() {};
};



void GameCharacter::damage(int value) {

    GameCharacter::hp -= value;

    if (hp < 0)
        hp = 0;


}

void GameCharacter::heal(int value) {

    GameCharacter::hp += value;

    if (hp > 100)
        hp = 100;

}

void GameCharacter::levelUp() {

    level++;
    hp = 100;

}

void GameCharacter::show() {

    cout << "名稱: " << name << "\n";
    cout << "血量: " << hp << "\n";
    cout << "等級: " << level << "\n";

}



int main(void) {

    int p;//角色設定人數
    cout << "請輸入創建角色人數:";
    cin >> p;

    string name;
    int hp;
    int le;
    int f = 1;
    int d;
    GameCharacter* a = new GameCharacter[p];




    for (int i = 0; i < p; i++) {

        cout << "==請輸入角色" << i + 1 << "==" << "\n";

        cout << "角色名稱:";
        cin >> name;
        cout << "角色血量:";
        cin >> hp;
        cout << "角色等級:";
        cin >> le;

        cout << "===============" << "\n";

        a[i] = GameCharacter(name, hp, le);
    }



    while (f > 0) {

        cout << "======選單======" << "\n";
        cout << "1.扣血" << "\n";
        cout << "2.回血" << "\n";
        cout << "3.升級" << "\n";
        cout << "4.Show角色資料:" << "\n";
        cout << "0.結束" << "\n";
        cout << "請選擇:";
        cin >> d;

        if (d == 1) {
            int num;
            int dm;
            cout << "==============" << "\n";
            cout << "選擇角色號(1" << "~" << p << "):";
            cin >> num;
            cout << "請輸入傷害值:";
            cin >> dm;
            a[num - 1].damage(dm);
            f = d;
            cout << "==============" << "\n";
            continue;

        }


        if (d == 2) {
            int num;
            int H;
            cout << "==============" << "\n";
            cout << "選擇角色號(1" << "~" << p << "):";
            cin >> num;
            cout << "請輸入回血量:";
            cin >> H;

            a[num - 1].heal(H);
            f = d;
            cout << "==============" << "\n";
            continue;

        }



        if (d == 3) {
            int num;
            cout << "==============" << "\n";
            cout << "選擇角色號(1" << "~" << p << "):";
            cin >> num;
            cout << "升級成功!\n";

            a[num - 1].levelUp();
            f = d;
            cout << "==============" << "\n";
            continue;

        }


        if (d == 4) {
            int num;
            cout << "==============" << "\n";
            cout << "選擇角色號(1" << "~" << p << "):";
            cin >> num;
            a[num - 1].show();

            f = d;
            cout << "==============" << "\n";
            continue;

        }

        if (d == 0) {
            break;
        }


    }


    delete[] a;



}