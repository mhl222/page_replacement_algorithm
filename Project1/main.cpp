#include <iostream>
#include "FIFO.h"
#include "LRU.h"
#include "OPT.h"

using namespace std;

int main() {

    int select;
    cout << "================ҳ���û��㷨================" << endl;
    cout <<"    "<< "1--->FIFO" << "    ";
    cout <<"    "<< "2--->LRU" << "    ";
    cout <<"    "<< "3--->OPT" << "    ";
    cout<<endl;
    cout << "=============��ѡ��ҳ���û��㷨=============" << endl;

    FIFO *repl = new FIFO();
    LRU *lru = new LRU();
    OPT *opt = new OPT();
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
        default:
            cout <<"��������ȷ��ѡ���ţ�" << endl;
            break;
    }

    return 0;
}

