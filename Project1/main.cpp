#include <iostream>
#include "FIFO.h"
#include "LRU.h"
#include "OPT.h"
#include "CLOCK.h"

using namespace std;


int main() {
    while (true) {
        system("cls");
        int select;
        cout << "================ҳ���û��㷨================" << endl;
        cout << "    " << "1--->FIFO" << "    ";
        cout << "    " << "2--->LRU" << "    ";
        cout << "    " << "3--->OPT" << "    ";
        cout << "    " << "4--->CLOCK" << "    ";
        cout << endl;
        cout << "=============��ѡ��ҳ���û��㷨=============" << endl;

        FIFO* repl = new FIFO();
        LRU* lru = new LRU();
        OPT* opt = new OPT();
        CLOCK* clock = new CLOCK();

        cin >> select;
        switch (select) {
        case 1:
            cout << "-----�Ƚ��ȳ��㷨��FIFO��-----" << endl;

            repl->init();
            repl->running();
            break;
        case 2:
            cout << "-----������δʹ���㷨��LRU��-----" << endl;

            lru->init();
            lru->running();
            break;
        case 3:
            cout << "-----����û��㷨��OPT��-----" << endl;

            opt->init();
            opt->running();
            break;
        case 4:
            cout << "-----����û��㷨��CLOCK��-----" << endl;

            clock->init();
            clock->running();
            break;
        default:
            cout << "��������ȷ��ѡ���ţ�" << endl;
            break;

        }
        system("pause");
    }
    

    return 0;
}

