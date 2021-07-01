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
    //��ʼ��count
    count = 0;
    cout << "�����������ڴ������";
    cin >> PRO_MEMORY;
    ofs_CLOCK << "�����������ڴ������" << PRO_MEMORY << "\n";

    cout << "������ҳ����еĳ��ȣ�";
    cin >> length;

    cout << "������ҳ��ʹ���б��Կո�ֿ���";
    ofs_CLOCK << "������ҳ��ʹ���б��Կո�ֿ���";
    int da;
    for (int i = 0; i < length; i++)
    {
        cin >> da;
        usePageNumList_CLOCK.push_back(da);
        ofs_CLOCK << da << " ";
    }
    ofs_CLOCK << "\nҳ���û��������£�\n";

    for (int j = 0; j < PRO_MEMORY; j++)
    {
        Page* p = new Page(-1);
        p->setUsed(false);
        pages_CLOCK.push_back(*p);
    }
}

void CLOCK::display()
{
    cout << "��ǰ�ڴ汣����ҳ���ǣ�";
    ofs_CLOCK << "��ǰ�ڴ汣����ҳ�漰��ʹ��λΪ��";
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

    //�鿴�Ƿ�ȱҳ
    for (int i = 0; i < pages_CLOCK.size(); i++)
    {
        if (pages_CLOCK[i].getId() == pageId) {
            cout << "�ڴ�����IDΪ" << pageId << ",���ҳ�治���û�" << endl;
            ofs_CLOCK << "�ڴ�����IDΪ" << pageId << ",���ҳ�治���û�\n";
            return;
        }
    }
    //ȱҳ��
    while (true) {
        if (pages_CLOCK[cur].getUsed()) {
            pages_CLOCK[cur].setUsed(false);
            cur = (cur+1)% PRO_MEMORY;
        }
        else {
            pages_CLOCK[cur].setId(pageId);
            pages_CLOCK[cur].setUsed(true);
            if (count < PRO_MEMORY) {
                cout << "ҳ��ID:" << pageId << "���ڷ����ڴ�" << endl;
                ofs_CLOCK << "ҳ��ID:" << pageId << "���ڷ����ڴ�\n";
                count++;
                lackTime++;
            }
            else
            {
                cout << "ҳ��ID��" << pageId << "���ڷ����ڴ棬ҳ��ID��" << cur << "���滻��ȥ" << endl;
                ofs_CLOCK << "ҳ��ID��" << pageId << "���ڷ����ڴ棬ҳ��ID��" << cur << "���滻��ȥ\n";
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
            cout << "�밴enter��" << endl;
        }
    }

    cout << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float)lackTime / length  << endl;
    ofs_CLOCK << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float)lackTime / length  << "\n";
    ofs_CLOCK << "============================================================";
    ofs_CLOCK.close();
}