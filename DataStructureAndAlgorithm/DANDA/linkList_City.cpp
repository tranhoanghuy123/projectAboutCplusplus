#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
using namespace std;
//Câu 2: sử dụng danh sách liên kết đơn để cài đặt biểu diễn thông tin cho n thành phố.
//Thông tin các thành phố gồm :
//Tên(chuỗi 30 ký tự).
//Diện tích(số nguyên).
//Dân số(số nguyên).
//a) Khai báo và khởi tạo DSLK
//b) Nhập dữ liệu n thành phố vào danh sách(n nhập từ bàn phím).
//c) In thông tin chi tiết của thành phố có diện tích lớn nhất.
//d) Sắp xếp DSLK theo thứ tự tăng dần của diện tích.
//e) Xóa khỏi DSLK thành phố có tên nhập từ bàn phím
//f) Lưu DSLK vào file nhị phâ
struct City
{
	char nameOfCity[30];
	int area, population;
};
struct Node
{
	City Data;
	Node* pNext; // chơi 1 con trỏ cho nó khổ dâm :))
};
typedef Node* List;
void initList(List& L)
{
	L = NULL;
}
List createNode(City& c)
{
	List newNode = new Node;
	newNode->pNext = NULL;
	newNode->Data = c;
	return newNode;
}
void createCity(City& c)
{
	cout << "Nhap ten thanh pho: "; cin.getline(c.nameOfCity, 30);
	do
	{
		cout << "Nhap dien tich: "; cin >> c.area;
		if (c.area < 0)
		{
			cout << "Dien tich khong hop le! Nhap lai.\n";
		}
	} while (c.area < 0);
	do
	{
		cout << "Nhap dan so: "; cin >> c.population;
		if (c.population < 0)
		{
			cout << "Dan so khong hop le! Nhap lai. \n";
		}
	} while (c.population < 0);
	cin.ignore();
	//return c;
}
List InsFirst(List& L, City &C) {
	Node* P = new Node;
	P =	createNode(C);
	P->pNext = L;
	L = P;
	return L;
}
void insertCity(fstream &f, int n)
{
	City C;
	f.open("listCity1.txt", ios::out | ios::binary);
	int index = 0;
	while (n > index)
	{
		cout << "Thanh pho thu " << ++index << " can them:\n";
		createCity(C);
		f.write((char*)(&C), sizeof(C));
	}
	cout << "Ghi file Thanh cong! \n";
	f.close();
}
void readFile(fstream& f, List& L,City &C,int &n)
{
	n = 0;
	f.open("listCity1.txt", ios::in | ios::binary);
	while (f.read((char*)(&C), sizeof(C)))
	{
		L = InsFirst(L, C);
		n++;
	}
}
void title()
{
	cout << setw(10) << left << "STT" << setw(35) << left << "Ten Thanh Pho" << setw(20) << left << "Dien Tich (Km2)" << setw(17) << left << "Dan So" << endl;
}
void printOneCity(City C)
{
	int index = 1;
	cout << setw(10) << left << index++ << setw(35) << left << C.nameOfCity << setw(20) << left << C.area << setw(17) << left << C.population << endl;
}
void printListCity(List L)
{
	int index = 1;
	title();
	for (Node* P = L; P != NULL; P = P->pNext)
	{
		cout << setw(10) << left << index++ << setw(35) << left << P->Data.nameOfCity << setw(20) << left << P->Data.area << setw(17) << left << P->Data.population << endl;
	}
}
void printCityHasMaxArea(List L)
{
	Node* P = L;
	City DataOfMax=P->Data;
	int max = P->Data.area;
	for (P; P != NULL; P = P->pNext)
	{
		if (P->Data.area > max)
		{
			max = P->Data.area;
			DataOfMax = P->Data;
		}
	}
	title();
	printOneCity(DataOfMax);
}
void SortedByArea(List L) // Using Algorithm: Interchange Sort	
{
	//Dùng	quickSort chắc phải dùng 2 con trỏ, pHead và pTail; mình nghĩ là vậy :))
	/*
	* DESCRIPTION: 
	* Dùng 2 vòng lặp lồng nhau: Độ phức tạp: O(n^2); ---> danh sách quản lý thành phố chắc ít nên nếu dùng quickSort sẽ nhanh hơn lúc này Big O() = O(nlog(n)) --> tốc độ sẽ nhanh hơn
	* B1: Khởi tạo 1 con trỏ P trỏ đến phần tử đầu; điều kiện dừng là P == NULL  hoặc P->pNext == NULL
	* B2: Tiếp theo là tạo thêm 1 con trỏ Q nữa; Q bắt đầu sau con trỏ thứ nhất 
	* vd: có linkedList 9 8 7 6 5 4 3 2 1
	*  lúc này P -> vị trí của pt 9; Q-> vị trí của phần tử 8; So sánh 9 > 8 ==> swap(9,8); tiếp theo con trỏ Q -> vị trí của pt 7; P->trỏ đến pt đầu (lúc này giá trị là 8) ==> cứ lặp như thế khi Q->NULL 
	* thi P-> pt thứ 2;
	* LIST = NODE * 
	*/
	for (List P = L; P != NULL; P = P->pNext)
	{
		for (List Q = P->pNext; Q != NULL; Q = Q->pNext)
		{
			if (P->Data.area > Q->Data.area)
			{
				swap(P->Data, Q->Data);
			}
		}
	}
}
int searchedByNameOfCity(List L, char nameOfCity[30]) {
	Node* P = L; int i = 1;
	while (P != NULL && strcmp(P->Data.nameOfCity,nameOfCity) !=0) 
	{
		P = P->pNext;
		i++;
	}
	if (P != NULL)
		return i; //trả về vị tri tìm thấy
	else
		return 0; //trả về 0 nếu không tìm thấy
}
int DelFirst(List& L, City &x) {
	if (L == NULL) return 0; //Xóa thất bại
	Node* Q = L; //Cho Q trỏ đến Node đầu trong d/s
	x = L->Data; //Lấy dữ liệu để dùng (nếu cần)
	L = L->pNext; //Cho L trỏ đến Node thứ 2 trong d/s
	delete Q; //Giải phóng vùng nhớ
	return 1; //Xóa thành công
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
int DelPos(List& L, City& x, int index) 
{
	if (index<1 || index>ListLen(L)) return 0; //Xóa thất bại
	if (index == 1) DelFirst(L, x);
	else {
		Node* P = L, * Q; int i = 1;
		while (i !=index - 1) { P = P->pNext; i++; }
		Q = P->pNext; P->pNext = Q->pNext;
		x = Q->Data; delete Q;
	}
	return 1; //Xóa thành công
}
int DelLast(List& L, City &x) {
	if (L == NULL) return 0;//Xóa thất bại
	if (L->pNext == NULL) {
		DelFirst(L, x); return 1;//Xóa thành công
	}
	Node* P = L, * Q;
	while (P->pNext->pNext != NULL) P = P->pNext;
	Q = P->pNext; x = Q->Data; P->pNext = NULL;
	delete Q; //Giải phóng vùng nhớ
	return 1; //Xóa thành công
}
void deletedByNameOfCity(List& L, City& x, char nameOfCity[30])
{
	int position = searchedByNameOfCity(L, nameOfCity);
	if (position != 0)
	{
		DelPos(L, x, position);
		cout << setw(20) << left << "" << "Xoa Thanh Cong!\n";
	}
	else
	{
		cout << setw(20) << left << "" << "Xoa That Bai!\n";
	}
}
void savingFile(fstream& f1, List L,string filePath)
{
	f1.open(filePath, ios::out | ios::binary);
	for (List P = L; P != NULL; P = P->pNext)
	{
		f1.write((char*)(&P->Data), sizeof(P->Data));
		//cout << "Luu thanh cong! \n";// dòng này chỉ test xem có chạy không thôi :))
	}
	f1.close();
}
void menu()
{
	cout << endl << endl;
	cout << setw(10) << right << "*" << "********************************************************\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "1.Ghi/Nhap Danh Sach Thanh Pho Vao File    " << setw(8) << right << "*\n";
	cout << setw(10) << "*" << setw(57) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "2.Doc File                                 " << setw(8) << right << "*\n";
	cout << setw(10) << "*" << setw(57) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "3.In Danh Sach Thanh Pho                   " << setw(8) << right << "*\n";
	cout << setw(10) << "*" << setw(57) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "4.Thong Tin Thanh Pho Co Dien Tich Lon Nhat" << setw(8) << right << "*\n";
	cout << setw(10) << "*" << setw(57) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "5.Sap Xep Tang Dan Theo Dien Tich          " << setw(8) << right << "*\n";
	cout << setw(10) << "*" << setw(57) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "6.Xoa Thanh Pho Theo Ten                   " << setw(8) << right << "*\n";
	cout << setw(10) << "*" << setw(57) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "7.Luu Danh Sach Thanh Pho Ra File          " << setw(8) << right << "*\n";
	cout << setw(10) << "*" << setw(57) << "*\n";
	cout << setw(10) << right << "*" << "********************************************************\n\n";
}
int main()
{
	int selection;
	char checkContinue;
	fstream f,f1;
	int n ;
	Node* L = new Node[100];
	City C;
	char nameOfCity[30];
	string filePath;
	initList(L);
	do
	{
		system("CLS");
		menu();
		cout << "Nhap Lua Chon Cua Ban: "; cin >> selection; cin.ignore();
		switch (selection)
		{
		case 1:
			cout << "Nhap so luong thanh pho: "; cin >> n; cin.ignore();
			insertCity(f, n); break;
		case 2: 
			readFile(f, L, C, n); 
			cout << setw(20) << left << "" << "Doc File Thanh Cong!\n"; break;
		case 3:
			printListCity(L); break;
		case 5:
			SortedByArea(L); 
			cout << setw(20) << left << "" << "Sap Xep Thanh Cong!\n";break;
		case 4: 
			printCityHasMaxArea(L); break;
		case 6:
			cout << "Nhap ten Thanh pho can xoa: "; cin.getline(nameOfCity, 30);
			deletedByNameOfCity(L, C, nameOfCity); break;
		case 7:	
			cout << "Nhap duong dan luu file: "; cin >> filePath; cin.ignore();
			savingFile(f1, L, filePath); 
			cout << setw(20) << left << "" << "Luu File Thanh Cong!\n"; break;
		default: cout << setw(20) << left << "" << "Lua Chon Khong Hop Le!\n";
			break;
		}
		cout << setw(20) << left <<""<< "Ban Muon Tiep Tuc? Y/N --------> "; cin >> checkContinue;
		if (checkContinue != 'y' && checkContinue != 'Y')
		{
			cout << setw(20) << left << "" << "Ket Thuc Chuong Trinh!" << endl;
		}
	} while (!(checkContinue != 'y' && checkContinue != 'Y'));
	cout << endl;
	delete[]L;
	return 0;
}