#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
struct City
{
	int id;
	char name[100];
	float area;
};
void dosomething(City* c)
{
	float max = c[0].area;
	int i_max = 0;
	for (int i=1; i < 10; i++)
	{
		if (max < c[i].area)
		{
			max = c[i].area;
			i_max = i;
		}
	}
	cout << c[i_max].area << "\t" << c[i_max].id << "\n";
}
int main()
{
	City *c=new City [11];
	c[0].area = 0.1;
	c[1].area = 0.2;
	c[2].area = 0.3;
	c[3].area = 0.11;
	c[4].area = 0.14;
	c[5].area = 0.15;
	c[6].area = 0.331;
	c[7].area = 0.41;
	c[8].area = 0.1;
	c[9].area = 0.21;
	dosomething(c);
	cout << endl;
	delete[11]c;
	return 0;
}