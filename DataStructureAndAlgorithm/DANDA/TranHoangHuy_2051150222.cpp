#include <iostream>
using namespace std;

// phan danh cho STACK
//
//struct STACK {
//	int Top;
//	int Data[100];
//};
//int IsEmptyStack(STACK s)
//{
//	if (s.Top == -1)
//		return 1;
//	return 0;
//}
//
//int IsFullStack(STACK s)
//{
//	if (s.Top == 99)
//		return 1;
//	return 0;
//}
//void CreateStack(STACK s) 
//{
//	s.Top = -1;
//}
//
//void Push(STACK s, int x) 
//{
//	if (IsFullStack(s)==0)
//	{
//		s.Top++;
//		s.Data[s.Top] = x;
//	}
//}
//
//int Pop(STACK s) 
//{
//	int x;
//	if (!IsEmptyStack(s))
//	{
//		x = s.Data[s.Top];
//		s.Top--;
//	}
//	return x;
//}
//int DaoSo(int n)
//{
//	STACK s;
//	int res=0;
//	int i = 1;
//	while (n!= 0)
//	{
//		Push(s,n%10);
//		n /= 10;
//	}
//	while (!IsEmptyStack(s))
//	{
//		res = res + (s.Data[s.Top] * i);
//		Pop(s);
//		i *= 10;
//	}
//	return res;
//}

//Double link list
struct Node {
    int Data;
    struct Node* Next;
    struct Node* prev;
};
Node* head, * tail = NULL;
typedef Node* List;
void InitList(List& L) {
    L = NULL;
}
void PrintList(List L) {
    Node* temp = head;
    cout << "\n[ ";
    while (temp != NULL) {//Duyệt từ đầu đến cuối d/s
        cout << temp->Data << ", ";//In thành phàn dữ liệu
        temp = temp->Next;
    }
    cout << " ] ";
}
Node* MakeNode(int x) {
    Node* newNode = new Node; //Cấp phát vùng nhớ cho newNode
    newNode->Data = x;
   newNode->prev = NULL; 
   newNode->Next = NULL; 
    return newNode;
}
void InsertFirst(int x) {
    Node* newNode = MakeNode(x);
    if (head == NULL) {
        head = newNode;
        tail = newNode;
        return;
    }
    head->prev = newNode;
    newNode->Next = head;
    head = newNode;
}
void InsertLast(int x) {
  Node* newNode = MakeNode(x);
    if (head == NULL) {
        head = newNode;
        tail = newNode;
        return;
    }
    tail->Next = newNode;
    newNode->prev = tail;
    tail = newNode;
}
void DelFirst() {
    if (head == NULL) {
        return;
    }
    head = head->Next;
    head->prev = NULL;
}
void DelLast() {
    if (head == NULL) {
        return;
    }
    tail = tail->prev;
    tail->Next = NULL;
}