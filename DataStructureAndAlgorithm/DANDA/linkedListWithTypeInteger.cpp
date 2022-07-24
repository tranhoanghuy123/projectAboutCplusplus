#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
struct Node
{
	int Data;
	Node* pNext;
};
typedef Node* List;
void initList(List& L)
{
	L = NULL;
}
List createNode(int data)
{
	List newNode = new Node;
	newNode->pNext = NULL;
	newNode->Data = data;
	return newNode;
}
void InsLast(List& L, int x) {
	Node* P = createNode(x);//tạo 1 Node P
	if (L != NULL) { //trường hợp d/s không rỗng
		Node* Q = L; //tạo Q để duyệt d/s
		while (Q->pNext != NULL)
			Q = Q->pNext; //đến node cuối
		Q->pNext = P; //cho node cuối trỏ về P
	}
	else //trường hợp d/s rỗng
		L = P;
}
void inputList(List& L, int& data,int lenght)
{
	int index = 0;
	while (index < lenght)
	{
		cout << "Nhap So Nguyen Thu " << ++index << ": "; cin >> data;
		InsLast(L, data);
	}
}
void outputList(List L)
{
	cout << "Danh Sach Cac So Nguyen: ";
	for (List P = L; P != NULL; P = P->pNext)
	{
		cout << setw(5) << left << P->Data;
	}
	cout << endl;
}
int ListLen(List L) {
	Node* P = L;
	int i = 0; //biến đếm
	while (P != NULL) { //duyệt đến cuối d/s
		i++; //đếm số Node
		P = P->pNext; //cho P trỏ đến Node tiếp theo
	}
	return i; //trả về số Node của L
}
void sortedList(List L)
{
	for (List P = L; P != NULL; P = P->pNext)
	{
		for (List Q = P->pNext; Q != NULL; Q = Q->pNext)
		{
			if (P->Data > Q->Data)
			{
				swap(P->Data, Q->Data);
			}
		}
	}
}
void mergeSort(List &L1, List &L2)
{
	auto size = ListLen(L1) + ListLen(L2);
	List C = new Node[size];
	int data;
	Node * P = L1;
	Node * Q = L2;
	initList(C);
	for (int i = 0; i < size; i++)
	{
		if (P != NULL && Q != NULL)
		{
			if (P->Data <= Q->Data)
			{
				data = P->Data;
				InsLast(C, data);
				P = P->pNext;
			}
			else
			{
				data = Q->Data;
				InsLast(C, data);
				Q = Q->pNext;
			}
			
		}
		else
		{
			if (P == NULL)
			{
				data = Q->Data;
				InsLast(C, data);
				Q = Q->pNext;
			}
			else
			{
				data = P->Data;
				InsLast(C, data);
				P = P->pNext;
			}
			
		}
	}
	outputList(C);
}
int main()
{
	int lenght1,lenght2,data1,data2;
	cout << "Nhap So Luong PT Cua Ds 1: "; cin >> lenght1;
	List L1 = new Node[lenght1];
	cout << "Nhap So Luong PT Cua Ds 1: "; cin >> lenght2;
	List L2 = new Node[lenght2];
	initList(L1);
	initList(L2);
	inputList(L1, data1,lenght1);
	inputList(L2, data2,lenght2);
	sortedList(L1);
	sortedList(L2);
	outputList(L1);
	outputList(L2);
	mergeSort(L1, L2);
	delete[lenght1]L1;
	delete[lenght2]L2;
	cout << endl;
	return 0;
}