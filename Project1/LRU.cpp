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
    //��ʼ��count
    count = 0;
    cout << "�����������ڴ������";
    cin >> PRO_MEMORY;
    ofs_LRU << "�����������ڴ������" << PRO_MEMORY << "\n";

    cout << "������ҳ����еĳ��ȣ�";
    cin >> length;

    cout << "������ҳ��ʹ���б��Կո�ֿ���";
    ofs_LRU << "������ҳ��ʹ���б��Կո�ֿ���";
    int da;
    for (int i = 0; i < length; i++)
    {
        cin >> da;
        usePageNumList_LRU.push_back(da);
        ofs_LRU << da << " ";
    }
    ofs_LRU << "\nҳ���û��������£�\n";

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
    cout << "��ǰ�ڴ汣����ҳ���ǣ�";
    ofs_LRU << "��ǰ�ڴ汣����ҳ���ǣ�";
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
    //max ���time��cur���time��pageId,perCount ����ָ�룬outPageId�滻ҳ��
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
    reSet(cur);//time���㣬ʱ������
    pages_LRU[cur].setId(pageId);

    cout << "ҳ��ID��" << pageId << "���ڷ����ڴ棬ҳ��ID��" << outPageId << "���滻��ȥ" << endl;
    ofs_LRU << "ҳ��ID��" << pageId << "���ڷ����ڴ棬ҳ��ID��" << outPageId << "���滻��ȥ\n";
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
                cout << "�ڴ�����IDΪ" << pageId << ",���ҳ�治���û�" << endl;
                ofs_LRU << "�ڴ�����IDΪ" << pageId << ",���ҳ�治���û�\n";
            }
            else if (count < PRO_MEMORY)    //�п���ҳ
            {
                pages_LRU[count].setId(pageId);
                cout<<"ҳ��ID:"<<pageId<<"���ڷ����ڴ�"<<endl;
                ofs_LRU<<"ҳ��ID:"<<pageId<<"���ڷ����ڴ�\n";
                timeRefresh();
                reSet(count);
                count++;
                lackTime++;
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
            cout<<"�밴enter��"<<endl;
        }
    }

    cout << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float) lackTime / length  << endl;
    ofs_LRU << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float) lackTime / length  << "\n";
    ofs_LRU << "============================================================";
    ofs_LRU.close();
}
