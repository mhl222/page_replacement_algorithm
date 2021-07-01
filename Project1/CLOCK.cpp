#include <iostream>
#include <fstream>
#include <vector>
#include<conio.h>
#include "Page.h"
#include"CLOCK.h"

using namespace std;

typedef vector<Page> LISTPAGE_CLOCK;
typedef vector<int> USEPAGE_CLOCK;
LISTPAGE_CLOCK pages_CLOCK;
USEPAGE_CLOCK usePageNumList_CLOCK;
ofstream ofs_CLOCK("record_CLOCK.txt", ios::app);



void CLOCK::init()
{
    if (!ofs_CLOCK) return;
    //初始化count
    count = 0;
    cout << "请输入分配的内存块数：";
    cin >> PRO_MEMORY;
    ofs_CLOCK << "请输入分配的内存块数：" << PRO_MEMORY << "\n";

    cout << "请输入页面队列的长度：";
    cin >> length;

    cout << "请输入页面使用列表，以空格分开：";
    ofs_CLOCK << "请输入页面使用列表，以空格分开：";
    int da;
    for (int i = 0; i < length; i++)
    {
        cin >> da;
        usePageNumList_CLOCK.push_back(da);
        ofs_CLOCK << da << " ";
    }
    ofs_CLOCK << "\n页面置换过程如下：\n";

    for (int j = 0; j < PRO_MEMORY; j++)
    {
        Page* p = new Page(-1);
        p->setUsed(false);
        pages_CLOCK.push_back(*p);
    }
}

void CLOCK::display()
{
    cout << "当前内存保留的页面是：";
    ofs_CLOCK << "当前内存保留的页面及其使用位为：";
    for (int i = 0; i < pages_CLOCK.size(); i++)
    {
        if (pages_CLOCK[i].getUsed())
        {
            cout << pages_CLOCK[i].getId() << ":1 ";
            ofs_CLOCK << pages_CLOCK[i].getId() << ":1 ";
        }else{
            cout << pages_CLOCK[i].getId() << ":0 ";
            ofs_CLOCK << pages_CLOCK[i].getId() << ":0 ";
        }
        

    }
    ofs_CLOCK << "\n";
    cout << endl;
}



void CLOCK::replace(int pageId){

    //查看是否缺页
    for (int i = 0; i < pages_CLOCK.size(); i++)
    {
        if (pages_CLOCK[i].getId() == pageId) {
            cout << "内存中有ID为" << pageId << ",这个页面不能置换" << endl;
            ofs_CLOCK << "内存中有ID为" << pageId << ",这个页面不能置换\n";
            return;
        }
    }
    //缺页：
    while (true) {
        if (pages_CLOCK[cur].getUsed()) {
            pages_CLOCK[cur].setUsed(false);
            cur = (cur+1)% PRO_MEMORY;
        }
        else {
            pages_CLOCK[cur].setId(pageId);
            pages_CLOCK[cur].setUsed(true);
            if (count < PRO_MEMORY) {
                cout << "页号ID:" << pageId << "正在放入内存" << endl;
                ofs_CLOCK << "页号ID:" << pageId << "正在放入内存\n";
                count++;
                lackTime++;
            }
            else
            {
                cout << "页号ID：" << pageId << "正在放入内存，页号ID：" << cur << "被替换出去" << endl;
                ofs_CLOCK << "页号ID：" << pageId << "正在放入内存，页号ID：" << cur << "被替换出去\n";
                lackTime++;
            }
            cur = (cur + 1) % PRO_MEMORY;
            return;
        }
       

    }

}

void CLOCK::running()
{

    for (int i = 0; i < length; ++i)
    {
        int pageId = usePageNumList_CLOCK[i];
        
        int key = _getch();
        if (key == 13)
        {
            replace(pageId);
            display();
        }
        else
        {
            i--;
            cout << "请按enter键" << endl;
        }
    }

    cout << "缺页次数为：" << lackTime << ",缺页率为：" << (float)lackTime / length  << endl;
    ofs_CLOCK << "缺页次数为：" << lackTime << ",缺页率为：" << (float)lackTime / length  << "\n";
    ofs_CLOCK << "============================================================";
    ofs_CLOCK.close();
}