#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
using namespace std;

bool kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if (ch != EOF) {
        ungetc(ch, stdin);
        return true;
    }
    return false;
}

char getch_nonblock() {
    return getchar();
}

void screen1(string head, string ehead, string body, string legs, string hp, string ehp, string prost, int HP, int EHP, string hod1, string road, string hpehp, string hpprost){
    cout << "\n\n\n\n\n\n" << hpprost << HP << " HP [" << hp << "]" << "  YOU" << hpehp << "MONSTER  " << "[" << ehp << "] " << EHP << " HP" << "\n\n\n";
    cout << hod1 << head << prost << ehead << "\n";
    cout << hod1 << body << prost << body << "\n";
    cout << hod1 << legs << prost << " " << legs << "\n" << road << "\n";
}

void screenedamage(string head, string ehead2, string body, string legs, string hp, string ehp, string prost, int HP, int EHP, string hod1, string road, string hpehp, string hpprost){
    cout << "\n\n\n\n\n\n" << hpprost << HP << " HP [" << hp << "]" << "  YOU" << hpehp << "MONSTER  " << "[" << ehp << "] " << EHP << " HP" << "\n\n\n";
    cout << hod1 << head << prost << ehead2 << "\n";
    cout << hod1 << body << prost << body << "\n";
    cout << hod1 << legs << prost << " " << legs << "\n" << road << "\n";
}

void screenydamage(string head2, string ehead, string body, string legs, string hp, string ehp, string prost, int HP, int EHP, string hod1, string road, string hpehp, string hpprost){
    cout << "\n\n\n\n\n\n" << hpprost << HP << " HP [" << hp << "]" << "  YOU" << hpehp << "MONSTER  " << "[" << ehp << "] " << EHP << " HP" << "\n\n\n";
    cout << hod1 << head2 << prost << ehead << "\n";
    cout << hod1 << body << prost << body << "\n";
    cout << hod1 << legs << prost << " " << legs << "\n" << road << "\n";
}

void firstscreen(string head, string ehead, string body, string legs, string hp, string ehp, string prost, int HP, int EHP, string hod1, string road, string hpehp, string hpprost){
    cout << "\n     Choose an action:\n     [1] - Attack\n     [2] - Drink Health Potion\n     [q] - Exit\n\n" << hpprost << HP << " HP [" << hp << "]" << "  YOU" << hpehp << "MONSTER  " << "[" << ehp << "] " << EHP << " HP" << "\n\n\n";
    cout << hod1 << head << prost << ehead << "\n";
    cout << hod1 << body << prost << body << "\n";
    cout << hod1 << legs << prost << " " << legs << "\n" << road << "\n";
}

int main() {
    string hpehp = "                                                      ";
    string hpprost = "     ";
    string head = " O_O", head2 = " X_X", ehead = "O_O", ehead2 = "X_X";
    string body = "/||\\", legs = " /\\", prost = "                                                      ", hod1 = "                                   ";
    string hp = "####################", ehp = "####################";
    int HP = 100, EHP = 100;
    bool stop = false;
    srand(time(0));
    int damage;
    string road = "¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯";
    int sizehod1 = hod1.size();
    bool flag = false;
    int sizeprost = prost.size();
    int k = 0;
    int heal;
    firstscreen(head, ehead, body, legs, hp, ehp, prost, HP, EHP, hod1, road, hpehp, hpprost);
    while(stop == false){
        if(kbhit() == true){
        char key = getch_nonblock();
        if(key == 'q'){
            stop = true;
        }
        if(key == '1'){
            for(int i = prost.size(); i > 0; i--){
                cout << "\033[2J\033[H" << flush;
                prost.pop_back();
                hod1.push_back(' ');
                screen1(head, ehead, body, legs, hp, ehp, prost, HP, EHP, hod1, road, hpehp, hpprost);
                std::this_thread::sleep_for(std::chrono::milliseconds(75));
            }
            damage = rand() % 3;
            if(damage == 0){
                EHP -= 20;
                ehp.pop_back();
                ehp.pop_back();
                ehp.pop_back();
                ehp.pop_back();
            }
            else {
                EHP -= 10;
                ehp.pop_back();
                ehp.pop_back();
            }
            while(hod1.size() > sizehod1){
                cout << "\033[2J\033[H" << flush;
                prost.push_back(' ');
                hod1.pop_back();
                screenedamage(head, ehead2, body, legs, hp, ehp, prost, HP, EHP, hod1, road, hpehp, hpprost);
                std::this_thread::sleep_for(std::chrono::milliseconds(75));
            }
            cout << "\033[2J\033[H" << flush;
            screen1(head, ehead, body, legs, hp, ehp, prost, HP, EHP, hod1, road, hpehp, hpprost);
            flag = true;
        }
        if(key == '2'){
            heal = rand() % 4;
            if(heal == 0){
                    HP += 5;
                    hp.push_back('#');
                    hpprost.pop_back();
            }
            if(heal == 1){
                    HP += 10;
                    hp.push_back('#');
                    hp.push_back('#');
                    hpprost.pop_back();
                    hpprost.pop_back();
            }
            if(heal == 2){
                    HP += 15;
                    hp.push_back('#');
                    hp.push_back('#');
                    hp.push_back('#');
                    hpprost.pop_back();
                    hpprost.pop_back();
                    hpprost.pop_back();
            }
            if(heal == 3){
                    HP += 20;
                    hp.push_back('#');
                    hp.push_back('#');
                    hp.push_back('#');
                    hp.push_back('#');
                    hpprost.pop_back();
                    hpprost.pop_back();
                    hpprost.pop_back();
                    hpprost.pop_back();
            }
            flag = true;
        }
    }
    if(flag == true){
        while(prost.size() > 0){
            cout << "\033[2J\033[H" << flush;
            prost.pop_back();
            screen1(head, ehead, body, legs, hp, ehp, prost, HP, EHP, hod1, road, hpehp, hpprost);
            std::this_thread::sleep_for(std::chrono::milliseconds(75));
        }
        damage = rand() % 3;
            if(damage == 0){
                HP -= 20;
                hp.pop_back();
                hp.pop_back();
                hp.pop_back();
                hp.pop_back();
                if(k == 0){
                    hpprost.push_back(' ');
                    hpprost.push_back(' ');
                    hpprost.push_back(' ');
                    hpprost.push_back(' ');
                    hpprost.push_back(' ');
                    k++;
                }
                else{
                    hpprost.push_back(' ');
                    hpprost.push_back(' ');
                    hpprost.push_back(' ');
                    hpprost.push_back(' ');
                }
            }
            else {
                HP -= 10;
                hp.pop_back();
                hp.pop_back();
                if(k == 0){
                    hpprost.push_back(' ');
                    hpprost.push_back(' ');
                    hpprost.push_back(' ');
                    k++;
                }
                else{
                    hpprost.push_back(' ');
                    hpprost.push_back(' ');
                }
            }
            while(prost.size() < sizeprost){
                cout << "\033[2J\033[H" << flush;
                prost.push_back(' ');
                screenydamage(head2, ehead, body, legs, hp, ehp, prost, HP, EHP, hod1, road, hpehp, hpprost);
                std::this_thread::sleep_for(std::chrono::milliseconds(75));
            }
            cout << "\033[2J\033[H" << flush;
            firstscreen(head, ehead, body, legs, hp, ehp, prost, HP, EHP, hod1, road, hpehp, hpprost);
            flag = false;
    }
    }
    return 0;
}
