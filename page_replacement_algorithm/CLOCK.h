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
	int PRO_MEMORY;//�����ڴ��
	int count;//��ǰ�ڴ�ռ��
	int lackTime;//ȱҳ��
	int length;//ҳ����г���
	int cur = 0;//�ڴ��ѭ��ָ��
};




#endif // !CLOCK_H