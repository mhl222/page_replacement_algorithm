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
    
    bool getUsed();

    void setUsed(bool flag);

private:
    int id;
    int count;//LRU--¡·timeRefresh()
    bool used;//CLOCK ->>used_flag
};

#endif 
