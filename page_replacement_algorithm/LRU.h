#ifndef LRU_H
#define LRU_H


class LRU
{
public:
    void init();

    bool search(int pageId);

    void reSet(int cur);

    void timeRefresh();

    void replace(int pageId);

    void display();

    void running();

private:
    int PRO_MEMORY;
    int count;//当前内存占用数
    int lackTime;
    int length;

};

#endif // LRU_H
