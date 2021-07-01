#ifndef CLOCK_H
#define CLOCK_H

class CLOCK
{
public:
	void init();

	void running();

	bool search(int pageId);

	void replace(int pageId);

	void display();
private:
	int PRO_MEMORY;//分配内存块
	int count;//当前内存占用
	int lackTime;//缺页率
	int length;//页面队列长度
	int cur = 0;//内存块循环指针
};




#endif // !CLOCK_H