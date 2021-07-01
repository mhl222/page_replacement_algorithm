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
    int PRO_MEMORY;
    int countOldPoint;
    int count;
    int lackTime;
    int length;
};

#endif // FIFO_H
