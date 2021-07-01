#include "Page.h"
#include <iostream>
#include <vector>
#include "FIFO.h"
#include <fstream>
#include<conio.h>

using namespace std;

typedef vector<Page> LISTPAGE;
typedef vector<int> USEPAGE;
LISTPAGE pages;//内存页面
USEPAGE usePageNumList;//待使用页面列表
ofstream ofs("record.txt",ios::app);//记录内容保存

void FIFO::init()
{

    if(!ofs) return;
    //初始化count
    count = 0;
    cout << "请输入分配的内存块数：";
    cin >> PRO_MEMORY;
    ofs << "请输入分配的内存块数：" << PRO_MEMORY << "\n";

    cout << "请输入页面队列的长度：";
    cin >> length;

    cout << "请输入页面使用列表，以空格分开：";
    ofs << "请输入页面使用列表，以空格分开：";
    int da;
    for (int i = 0; i < length; i++)
    {
        cin >> da;
        usePageNumList.push_back(da);
        ofs << da << " ";
    }
    ofs << "\n页面置换过程如下：\n";

    for (int j = 0; j < PRO_MEMORY; j++)
    {
        Page *p = new Page(-1);
        pages.push_back(*p);
    }
}

/**
 * 显示当前内存中保留的的页面
 */
void FIFO::display()
{

    cout << "当前内存保留的页面是：";
    ofs << "当前内存保留的页面是：";
    for (int i = 0; i < pages.size(); i++)
    {
        cout << pages[i].getId() << " ";
        ofs << pages[i].getId() << " ";

    }
    ofs << "\n";
    cout << endl;
}
/**
 * 搜素pageId是否已在内存
 */
bool FIFO::search(int pageId)
{
    for (int i = 0; i < pages.size(); i++)
    {
        if (pages[i].getId() == pageId)
            return true;
    }
    return false;
}
/**
 * 将pageId替换入countOldPoint（最久位置指针）
 */
void FIFO::replace(int pageId)
{
    //置换在内存中呆的时间最久的页面
    int outPageId = -1;
    outPageId = pages[countOldPoint].getId();
    pages[countOldPoint].setId(pageId);
    cout << "页号ID：" << pageId << "正在放入内存，页号ID：" << outPageId << "被替换出去" << endl;
    ofs << "页号ID：" << pageId << "正在放入内存，页号ID：" << outPageId << "被替换出去\n";
}

void FIFO::running()
{

    for (int i = 0; i < length; i++)
    {
        countOldPoint = countOldPoint % PRO_MEMORY;
        int inPageId = usePageNumList[i];
        int key = _getch();//等待回车
        if(key==13){

        if (search(inPageId))
        {
            cout << "内存中有ID为" << inPageId << ",这个页面不能置换" << endl;
            ofs << "内存中有ID为" << inPageId << ",这个页面不能置换\n";
        }
        else if (count < PRO_MEMORY)    //有空闲内存页
        {
            pages[count++].setId(inPageId);
            cout << "页号ID：" << inPageId << "正在放入内存中" << endl;
            ofs << "页号ID：" << inPageId << "正在放入内存中\n";
            lackTime++;
        }
        else    //替换
        {
            replace(inPageId);
            lackTime++;
            countOldPoint++;
        }
        display();
    }else{
        i--;
        cout<<"请按enter键"<<endl;
    }
    }
    cout << "缺页次数为：" << lackTime << ",缺页率为：" << (float) lackTime / length  << endl;
    ofs << "缺页次数为：" << lackTime << ",缺页率为：" << (float) lackTime / length  << "\n";
    ofs << "============================================================";
    ofs.close();


}
