#ifndef PAGE_H
#define PAGE_H


class Page
{
public:
    Page(int id);
    virtual ~Page();
    int getId() const;

    void setId(int id);

    int getCount() const;

    void inc();

    void setCount(int count);

private:
    int id;
    int count;
};

#endif // PAGE_H
