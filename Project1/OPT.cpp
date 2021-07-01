//
// Created by fxr on 16-9-1.
//

#include <iostream>
#include<conio.h>

#include "OPT.h"
#include "Page.h"
#include <fstream>
#include "LRU.h"
#include <vector>

using namespace std;

typedef vector<Page> LISTPAGE_OPT;
typedef vector<int> USEPAGE_OPT;
LISTPAGE_OPT pages_OPT;
USEPAGE_OPT usePageNumList_OPT;
ofstream ofs_OPT("record_OPT.txt", ios::app);

void OPT::init()
{
    if (!ofs_OPT) return;
    //初始化count
    count = 0;
    cout << "请输入分配的内存块数：";
    cin >> PRO_MEMORY;
    ofs_OPT << "请输入分配的内存块数：" << PRO_MEMORY << "\n";

    cout << "请输入页面队列的长度：";
    cin >> length;

    cout << "请输入页面使用列表，以空格分开：";
    ofs_OPT << "请输入页面使用列表，以空格分开：";
    int da;
    for (int i = 0; i < length; i++)
    {
        cin >> da;
        usePageNumList_OPT.push_back(da);
        ofs_OPT << da << " ";
    }
    ofs_OPT << "\n页面置换过程如下：\n";

    for (int j = 0; j < PRO_MEMORY; j++)
    {
        Page *p = new Page(-1);
        pages_OPT.push_back(*p);
    }
}


void OPT::display()
{
    cout << "当前内存保留的页面是：";
    ofs_OPT << "当前内存保留的页面是：";
    for (int i = 0; i < pages_OPT.size(); i++)
    {
        cout << pages_OPT[i].getId() << " ";
        ofs_OPT << pages_OPT[i].getId() << " ";

    }
    ofs_OPT << "\n";
    cout << endl;
}

bool OPT::search(int pageId)
{
    for (int i = 0; i < PRO_MEMORY; ++i)
    {
        if (pages_OPT[i].getId() == pageId)
        {
            return true;
        }
    }
    return false;
}

void OPT::replace(int pageId, int currentPoint)
{
    //cur为内存块下标,searchCounter纪录是否内存块搜索完毕
    //循环爆出最长为使用的页面
    int max = 0, perCount, outPageId = -1, cur = 0;
    /*int search_count[PRO_MEMORY];*/
	vector<int> search_count(PRO_MEMORY);

    //查询下一次替换的时间距离
    for (int i = 0; i < PRO_MEMORY; i++)
    {
        for (int j = currentPoint + 1; j < length; j++)
        {
            if (pages_OPT[i].getId() == usePageNumList_OPT[j])
            {
                search_count[i] = j;
                break;
            }
        }
        if (search_count[i] == 0)
        {
            search_count[i] = length;
        }
    }

    for (int k = 0; k < PRO_MEMORY; ++k)
    {
        perCount = search_count[k];
        if (max < perCount)
        {
            max = perCount;
            cur = k;
        }
    }

    outPageId = pages_OPT[cur].getId();

    pages_OPT[cur].setId(pageId);
    cout << "页号ID：" << pageId << "正在放入内存，页号ID：" << outPageId << "被替换出去" << endl;
    ofs_OPT << "页号ID：" << pageId << "正在放入内存，页号ID：" << outPageId << "被替换出去\n";
}

void OPT::running()
{
    int currentPoint = 0;
    for (int i = 0; i < length; ++i)
    {
        int pageId = usePageNumList_OPT[i];

        int key = _getch();
        if(key==13)
        {

            if (search(pageId))
            {
                cout << "内存中有ID为" << pageId << ",这个页面不能置换" << endl;
                ofs_OPT << "内存中有ID为" << pageId << ",这个页面不能置换\n";
            }
            else if (count < PRO_MEMORY)
            {
                pages_OPT[count].setId(pageId);
                cout << "页号ID:" << pageId << "正在放入内存" << endl;
                ofs_OPT << "页号ID:" << pageId << "正在放入内存\n";
                count++;
                lackTime++;
            }
            else
            {
                replace(pageId, currentPoint);//传入当前下标确定需要遍历的未来输入列表
                lackTime++;
            }
            currentPoint++;
            display();
        }
        else
        {
            i--;
            cout<<"请按enter键"<<endl;
        }
    }

    cout << "缺页次数为：" << lackTime << ",缺页率为：" << (float) lackTime / length  << endl;
    ofs_OPT << "缺页次数为：" << lackTime << ",缺页率为：" << (float) lackTime / length << "\n";
    ofs_OPT << "============================================================";
    ofs_OPT.close();
}
