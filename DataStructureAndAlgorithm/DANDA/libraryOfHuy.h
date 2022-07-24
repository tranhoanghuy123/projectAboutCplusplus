#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<string>
#include<iomanip>
using namespace std;
template<class T>
void InitList(T& L) {
	L = NULL;
}
template <class T>
int ListLen(T L) {
	T P = L;
	int i = 0; //biến đếm
	while (P != NULL) { //duyệt đến cuối d/s
		i++; //đếm số Node
		P = P->pNext; //cho P trỏ đến Node tiếp theo
	}
	return i; //trả về số Node của L
}
template <class T,class T2>
int Position(T L, T2 x) {
	T P = L; int i = 1;
	while (P != NULL && P->Data != x) {
		P = P->pNext;
		i++;
	}
	if (P != NULL)
		return i; //trả về vị tri tìm thấy
	else
		return 0; //trả về 0 nếu không tìm thấy
}
template <class T, class T2>
int DelFirst(T& L, T2 &x) {
	if (L == NULL) return 0; //Xóa thất bại
	T Q = L; //Cho Q trỏ đến Node đầu trong d/s
	x = L->Data; //Lấy dữ liệu để dùng (nếu cần)
	L = L->pNext; //Cho L trỏ đến Node thứ 2 trong d/s
	delete Q; //Giải phóng vùng nhớ
	return 1; //Xóa thành công
}
template <class T, class T2>
int DelLast(T& L, T2& x) {
	if (L == NULL) return 0;//Xóa thất bại
	if (L->pNext == NULL) {
		DelFirst<T,T2>(L, x); return 1;//Xóa thành công
	}
	T P = L,Q;
	while (P->pNext->pNext != NULL) P = P->pNext;
	Q = P->pNext; x = Q->Data; P->pNext = NULL;
	delete Q; //Giải phóng vùng nhớ
	return 1; //Xóa thành công
}
template <class T, class T2>
int DelPos(T& L, T2& x, int k) {
	if (k<1 || k>ListLen<T>(L)) return 0; //Xóa thất bại
	if (k == 1) DelFirst<T, T2>(L, x);
	else {
		T P = L,  Q; int i = 1;
		while (i != k - 1) { P = P->pNext; i++; }
		Q = P->pNext; P->pNext = Q->pNext;
		x = Q->Data; delete Q;
	}
	return 1; //Xóa thành công
}