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
    int PRO_MEMORY;//分配内存块
    int countOldPoint;//最久位置指针
    int count;//当前内存占用数
    int lackTime;//缺页率
    int length;//页面队列长度
};

#endif // FIFO_H
