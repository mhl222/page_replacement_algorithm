#include <iostream>

#include "Page.h"
#include <fstream>
#include "LRU.h"
#include <vector>
#include<conio.h>


using namespace std;

typedef vector<Page> LISTPAGE_LRU;
typedef vector<int> USEPAGE_LRU;
LISTPAGE_LRU pages_LRU;
USEPAGE_LRU usePageNumList_LRU;
ofstream ofs_LRU("record_LRU.txt",ios::app);

void LRU::init()
{
    if (!ofs_LRU) return;
    //初始化count
    count = 0;
    cout << "请输入分配的内存块数：";
    cin >> PRO_MEMORY;
    ofs_LRU << "请输入分配的内存块数：" << PRO_MEMORY << "\n";

    cout << "请输入页面队列的长度：";
    cin >> length;

    cout << "请输入页面使用列表，以空格分开：";
    ofs_LRU << "请输入页面使用列表，以空格分开：";
    int da;
    for (int i = 0; i < length; i++)
    {
        cin >> da;
        usePageNumList_LRU.push_back(da);
        ofs_LRU << da << " ";
    }
    ofs_LRU << "\n页面置换过程如下：\n";

    for (int j = 0; j < PRO_MEMORY; j++)
    {
        Page *p = new Page(-1);
        pages_LRU.push_back(*p);
    }
}

void LRU::reSet(int cur)
{
    pages_LRU[cur].setCount(0);
}

void LRU::timeRefresh()
{
    for (int i = 0; i < pages_LRU.size(); ++i)
    {
        pages_LRU[i].inc();
    }
}

void LRU::display()
{
    cout << "当前内存保留的页面是：";
    ofs_LRU << "当前内存保留的页面是：";
    for (int i = 0; i < pages_LRU.size(); i++)
    {
        cout << pages_LRU[i].getId() << " ";
        ofs_LRU << pages_LRU[i].getId() << " ";

    }
    ofs_LRU << "\n";
    cout << endl;
}

bool LRU::search(int pageId)
{
    for (int i = 0; i < pages_LRU.size(); ++i)
    {
        if (pages_LRU[i].getId() == pageId)
        {
            timeRefresh();
            reSet(i);
            return true;
        }
    }
    return false;
}

void LRU::replace(int pageId)
{
    int max = 0, perCount, outPageId = -1, cur = 0;
    for (int i = 0; i < pages_LRU.size(); ++i)
    {
        perCount = pages_LRU[i].getCount();
        if (max < perCount)
        {
            max = perCount;
            cur = i;
        }
    }
    outPageId = pages_LRU[cur].getId();
    timeRefresh();
    reSet(cur);
    pages_LRU[cur].setId(pageId);

    cout << "页号ID：" << pageId << "正在放入内存，页号ID：" << outPageId << "被替换出去" << endl;
    ofs_LRU << "页号ID：" << pageId << "正在放入内存，页号ID：" << outPageId << "被替换出去\n";
}

void LRU::running()
{

    for (int i = 0; i < length; ++i)
    {
        int pageId = usePageNumList_LRU[i];

        int key = _getch();
        if(key==13)
        {


            if (search(pageId))
            {
                cout << "内存中有ID为" << pageId << ",这个页面不能置换" << endl;
                ofs_LRU << "内存中有ID为" << pageId << ",这个页面不能置换\n";
            }
            else if (count < PRO_MEMORY)    //有空闲页
            {
                pages_LRU[count].setId(pageId);
                cout<<"页号ID:"<<pageId<<"正在放入内存"<<endl;
                ofs_LRU<<"页号ID:"<<pageId<<"正在放入内存\n";
                timeRefresh();
                reSet(count);
                count++;

            }
            else
            {
                replace(pageId);

                lackTime++;
            }
            display();
        }
        else
        {
            i--;
            cout<<"请按enter键"<<endl;
        }
    }

    cout << "缺页次数为：" << lackTime << ",缺页率为：" << (float) lackTime / (length - PRO_MEMORY) << endl;
    ofs_LRU << "缺页次数为：" << lackTime << ",缺页率为：" << (float) lackTime / (length - PRO_MEMORY) << "\n";
    ofs_LRU << "============================================================";
    ofs_LRU.close();
}
