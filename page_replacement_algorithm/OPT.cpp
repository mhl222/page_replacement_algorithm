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
    //��ʼ��count
    count = 0;
    cout << "�����������ڴ������";
    cin >> PRO_MEMORY;
    ofs_OPT << "�����������ڴ������" << PRO_MEMORY << "\n";

    cout << "������ҳ����еĳ��ȣ�";
    cin >> length;

    cout << "������ҳ��ʹ���б��Կո�ֿ���";
    ofs_OPT << "������ҳ��ʹ���б��Կո�ֿ���";
    int da;
    for (int i = 0; i < length; i++)
    {
        cin >> da;
        usePageNumList_OPT.push_back(da);
        ofs_OPT << da << " ";
    }
    ofs_OPT << "\nҳ���û��������£�\n";

    for (int j = 0; j < PRO_MEMORY; j++)
    {
        Page *p = new Page(-1);
        pages_OPT.push_back(*p);
    }
}


void OPT::display()
{
    cout << "��ǰ�ڴ汣����ҳ���ǣ�";
    ofs_OPT << "��ǰ�ڴ汣����ҳ���ǣ�";
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
    //curΪ�ڴ���±�,searchCounter��¼�Ƿ��ڴ���������
    //ѭ�������Ϊʹ�õ�ҳ��
    int max = 0, perCount, outPageId = -1, cur = 0;
    /*int search_count[PRO_MEMORY];*/
	vector<int> search_count(PRO_MEMORY);

    //��ѯ��һ���滻��ʱ�����
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
    cout << "ҳ��ID��" << pageId << "���ڷ����ڴ棬ҳ��ID��" << outPageId << "���滻��ȥ" << endl;
    ofs_OPT << "ҳ��ID��" << pageId << "���ڷ����ڴ棬ҳ��ID��" << outPageId << "���滻��ȥ\n";
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
                cout << "�ڴ�����IDΪ" << pageId << ",���ҳ�治���û�" << endl;
                ofs_OPT << "�ڴ�����IDΪ" << pageId << ",���ҳ�治���û�\n";
            }
            else if (count < PRO_MEMORY)
            {
                pages_OPT[count].setId(pageId);
                cout << "ҳ��ID:" << pageId << "���ڷ����ڴ�" << endl;
                ofs_OPT << "ҳ��ID:" << pageId << "���ڷ����ڴ�\n";
                count++;
                lackTime++;
            }
            else
            {
                replace(pageId, currentPoint);//���뵱ǰ�±�ȷ����Ҫ������δ�������б�
                lackTime++;
            }
            currentPoint++;
            display();
        }
        else
        {
            i--;
            cout<<"�밴enter��"<<endl;
        }
    }

    cout << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float) lackTime / length  << endl;
    ofs_OPT << "ȱҳ����Ϊ��" << lackTime << ",ȱҳ��Ϊ��" << (float) lackTime / length << "\n";
    ofs_OPT << "============================================================";
    ofs_OPT.close();
}
