#ifndef OPT_H
#define OPT_H


class OPT
{
public:
    void init();

    bool search(int pageId);

    void replace(int pageId,int currentPoint);

    void display();

    void running();

private:
    int PRO_MEMORY;
    int count;
    int lackTime;
    int length;
};

#endif // OPT_H
