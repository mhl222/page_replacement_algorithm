#include <iostream>
#include "FIFO.h"
#include "LRU.h"
#include "OPT.h"

using namespace std;

//test

int main() {

    int select;
    cout << "================页面置换算法================" << endl;
    cout <<"    "<< "1--->FIFO" << "    ";
    cout <<"    "<< "2--->LRU" << "    ";
    cout <<"    "<< "3--->OPT" << "    ";
    cout<<endl;
    cout << "=============请选择页面置换算法=============" << endl;

    FIFO *repl = new FIFO();
    LRU *lru = new LRU();
    OPT *opt = new OPT();
    cin >> select;
    switch (select) {
        case 1:
            cout << "-----先进先出算法（FIFO）-----" << endl;

            repl->init();
            repl->running();
            break;
        case 2:
            cout << "-----最近最久未使用算法（LRU）-----" << endl;

            lru->init();
            lru->running();
            break;
        case 3:
            cout << "-----最佳置换算法（OPT）-----" << endl;

            opt->init();
            opt->running();
            break;
        default:
            cout <<"请输入正确的选项标号！" << endl;
            break;
    }

    return 0;
}

