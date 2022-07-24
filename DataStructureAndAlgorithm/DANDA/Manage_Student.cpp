#include "libraryOfHuy.h"
//Câu 4: (4, 0 điểm) Cho cấu trúc của một sinh viên như sau :
//-Mã sinh viên : chuỗi ký tự. (Lưu ý : các mã không trùng nhau)
//- Họ tên sinh viên : chuỗi ký tự.
//- Điểm trung bình : số thực.
//- Xếp loại : ký tự(X : xuất sắc, G : giỏi, K : khá, T : trung bình, Y : yếu) Sử dụng danh sách liên kết đơn, thực hiện các công việc sau :
//a.Khai báo cấu trúc dữ liệu lưu trữ thông tin nhân viên theo mô tả trên.
//b.Viết hàm nhập danh sách nhân viên bằng thao tác thêm nhân viên vào cuối danh sách.
//c.Việt hàm xếp loại cho sinh viên.
//Loại X : Điểm trung bình > 9.0 Loại G : 8.0 < Điểm trung bình < 9.0 Loại K : 7.0 < Điểm trung bình < 8.0 Loại T : 5, 0 < Điểm trung bình 7.0
//	Loại Y : Điểm trung bình < 5.0 
// d.Xóa tất cả các sinh viên có xếp loại Y.
//--------------------------------------Gét Gô--------------------------------------//
struct Student 
{
	char id[10];
	char fullName[40];
	float averageOfPoint;
	char rank;
};
struct Node 
{
	Student Data;
	Node* pNext;
};
typedef Node* List;
List createNode(Student& student)
{
	List newNode = new Node;
	newNode->pNext = NULL;
	newNode->Data = student;
	return newNode;
}
void createStudent(Student& student)
{
	cout << "Nhap Ten Sinh Vien: "; cin.getline(student.fullName,40);
	cout << "Nhap Diem Trung Binh: "; cin >> student.averageOfPoint;
	if (student.averageOfPoint > 9.0)
	{
		student.rank = 'X';
	}
	else if (student.averageOfPoint > 8.0)
	{
		student.rank = 'G';
	}
	else if (student.averageOfPoint > 7.0)
	{
		student.rank = 'K';
	}
	else if (student.averageOfPoint > 5.0)
	{
		student.rank = 'T';
	}
	else
	{
		student.rank = 'Y';
	}
}
int checkIdOfList(List L, char idNeedToCheck[10])
{
	int index = 1;
	for (List Pointer = L; Pointer != NULL; Pointer = Pointer->pNext)
	{
		if (strcmp(idNeedToCheck, Pointer->Data.id) == 0)
		{
			return index;
		}
		index++;
	}
	return -1;
}
void InsLast(List& L, Student &x) {
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
void inputListStudent(List& L, Student& student, int lenght)
{
	int index = 1;
	int position;
	char idTemp[10];
	while (index <= lenght)
	{
		cout << setw(15) << left << "" << "Nhap Sinh Vien Thu " << index++ << endl;
		do
		{
			cout << "Nhap Ma Sinh Vien: "; cin.getline(idTemp, 10);
			position = checkIdOfList(L, idTemp);
			if (position != -1)
			{
				cout << setw(15) << left << "" << "Ma Bi Trung! Nhap Lai." << endl;
			}
		} while (position != -1);
		strcpy(student.id, idTemp);
		createStudent(student);
		InsLast(L, student);
		cin.ignore();
	}
}
void title()
{
	cout << setw(15) << left << "Ma Sinh Vien" << setw(35) << left << "Ho Va Ten" << setw(12) << left << "Diem TB" << setw(15) << left << "Xep Loai"<< endl;
}
void printOneStudent(Student student)
{
	cout << setw(15) << left << student.id << setw(35) << left << student.fullName << setw(12) << left << student.averageOfPoint << setw(15) << left << student.rank << endl;
}
void printListStudent(List L)
{
	title();
	for (List Pointer = L; Pointer != NULL; Pointer = Pointer->pNext)
	{
		cout << setw(15) << left << Pointer->Data.id << setw(35) << left << Pointer->Data.fullName << setw(12) << left << Pointer->Data.averageOfPoint << setw(15) << left << Pointer->Data.rank << endl;
	}
}
//void plitRankOfStudent(List L,char option) 
//{
// // Nếu đề yêu cầu là lọc danh sách ra theo xếp loại thì uncoment ra còn không thì xếp loại trong createStudent()  rồi. Nếu chỉ yêu cầu viết hàm riêng xếp loại thì copy phần xếp loại ra hàm mới
//	title();
//	for (List Pointer = L; Pointer != NULL; Pointer = Pointer->pNext)
//	{
//		if (option == Pointer->Data.rank)
//		{
//			switch (option)
//			{
//			case 'Y':
//				printOneStudent(Pointer->Data); break;
//			case 'T':
//				printOneStudent(Pointer->Data); break;
//			case 'K':
//				printOneStudent(Pointer->Data); break;
//			case 'G':
//				printOneStudent(Pointer->Data); break;
//			case 'X':
//				printOneStudent(Pointer->Data); break;
//			default:cout << setw(15) << left << "" << "Rank Is Invalid!" << endl;
//				break;
//			}
//		}
//	}
//}
int checkRankOfList(List L)
{
	int index = 1;
	for (List Pointer = L; Pointer != NULL; Pointer = Pointer->pNext)
	{
		if (Pointer->Data.rank == 'Y')
		{
			return index;
		}
		index++;
	}
	return -1;
}
void deletedAllStudentsHaveRankY(List& L, Student& student)
{
	while (checkRankOfList(L) != -1)
	{
		DelPos<List, Student>(L, student, checkRankOfList(L));
	}
}
int main()
{
	List L = new Node[100];
	Student student;
	int lenght;
	cout << setw(15) << left << "" << "Nhap So Luong Sinh Vien: "; cin >> lenght; cin.ignore();
	InitList<List>(L);
	inputListStudent(L, student, lenght);
	deletedAllStudentsHaveRankY(L, student);
	//plitRankOfStudent(L, 'K'); // Uncomment hàm trước khi Uncomment cái này!
	printListStudent(L);
	cout << endl;
	delete[] L;
	return 0;
}