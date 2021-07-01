#include "Page.h"
#include <iostream>
#include <vector>
#include<iostream>
#include "FIFO.h"
#include <fstream>
#include<conio.h>

using namespace std;

typedef vector<Page> LISTPAGE;
typedef vector<int> USEPAGE;
LISTPAGE pages;
USEPAGE usePageNumList;
ofstream ofs("record.txt",ios::app);

void FIFO::init()
{

    if(!ofs) return;
    //��ʼ��count
    count = 0;
    cout << "�����������ڴ������";
    cin >> PRO_MEMORY;
    ofs << "�����������ڴ������" << PRO_MEMORY << "\n";

    cout << "������ҳ����еĳ��ȣ�";
    cin >> length;

    cout << "������ҳ��ʹ���б��Կո�ֿ���";
    ofs << "������ҳ��ʹ���б��Կո�ֿ���";
    int da;
    for (int i = 0; i < length; i++)
    {
        cin >> da;
        usePageNumList.push_back(da);
        ofs << da << " ";
    }
    ofs << "\nҳ���û��������£�\n";

    for (int j = 0; j < PRO_MEMORY; j++)
    {
        Page *p = new Page(-1);
        pages.push_back(*p);
    }
}

/**
 * ��ʾ��ǰ�ڴ��б����ĵ�ҳ��
 */
void FIFO::display()
{

    cout << "��ǰ�ڴ汣����ҳ���ǣ�";
    ofs << "��ǰ�ڴ汣����ҳ���ǣ�";
    for (int i = 0; i < pages.size(); i++)
    {
        cout << pages[i].getId() << " ";
        ofs << pages[i].getId() << " ";

    }
    ofs << "\n";
    cout << endl;
}

bool FIFO::search(int pageId)
{
    for (int i = 0; i < pages.size(); i++)
    {
        if (pages[i].getId() == pageId)
            return true;
    }
    return false;
}

void FIFO::replace(int pageId)
{
    //�û����ڴ��д���ʱ����õ�ҳ��
    int outPageId = -1;
    outPageId = pages[countOldPoint].getId();
    pages[countOldPoint].setId(pageId);
    cout << "ҳ��ID��" << pageId << "���ڷ����ڴ棬ҳ��ID��" << outPageId << "���滻��ȥ" << endl;
    ofs << "ҳ��ID��" << pageId << "���ڷ����ڴ棬ҳ��ID��" << outPageId << "���滻��ȥ\n";
}

void FIFO::running()
{

    for (int i = 0; i < length; i++)
    {
        countOldPoint = countOldPoint % PRO_MEMORY;
        int inPageId = usePageNumList[i];
        int key = _getch();
        if(key==13){

        if (search(inPageId))
        {
            cout << "�ڴ�����IDΪ" << inPageId << ",���ҳ�治���û�" << endl;
            ofs << "�ڴ�����IDΪ" << inPageId << ",���ҳ�治���û�\n";
        }
        else if (count < PRO_MEMORY)    //�п����ڴ�ҳ
        {
            pages[count++].setId(inPageId);
            cout << "ҳ��ID��" << inPageId << "���ڷ����ڴ���" << endl;
            ofs << "ҳ��ID��" << inPageId << "���ڷ����ڴ���\n";
        }
        else    //�滻
        {
            replace(inPageId);
            lackTime++;
            countOldPoint++;
        }
        display();
    }else{
        i--;
        cout<<"�밴enter��"<<endl;
    }
    }
    cout << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float) lackTime / (length - PRO_MEMORY) << endl;
    ofs << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float) lackTime / (length - PRO_MEMORY) << "\n";
    ofs << "============================================================";
    ofs.close();


}
