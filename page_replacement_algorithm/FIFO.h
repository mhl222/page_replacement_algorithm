#ifndef FIFO_H
#define FIFO_H


class FIFO
{
public:
    void init();

    void running();

    bool search(int pageId);

    void replace(int pageId);

    void display();


private:
    int PRO_MEMORY;//�����ڴ��
    int countOldPoint;//���λ��ָ��
    int count;//��ǰ�ڴ�ռ����
    int lackTime;//ȱҳ��
    int length;//ҳ����г���
};

#endif // FIFO_H
