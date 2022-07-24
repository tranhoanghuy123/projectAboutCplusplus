#include "libraryOfHuy.h"
//Câu 4: (4, 0 điểm) Cho cấu trúc của một nhân viên như sau :
//-Mã nhân viên : chuỗi ký tự. (Lưu ý : các mã không trùng nhau)
//- Họ tên nhân viên : chuỗi ký tự. -
//Tiền lương một ngày : số thực.
//- Số ngày công : số nguyên.
//- Thực lĩnh : số thực(Thực lĩnh = Tiền lương một ngày x số ngày công).
//Sử dụng danh sách liên kết đơn, thực hiện các công việc sau :
//a.Khai báo cấu trúc dữ liệu lưu trữ thông tin nhân viên theo mô tả trên.
//b.Viết hàm nhập danh sách nhân viên bằng thao tác thêm nhân viên vào cuối danh sách.
//c.Viết hàm sắp xếp thực lĩnh tăng dần.
//d.Xóa một nhân viên theo mã nhân viên bất kỳ.
struct Employee
{
	char id[10];
	char fullName[40];
	int salary;
	int amoutOfWorkdays;
	int realSalary;
};
struct Node
{
	Employee Data;
	Node* pNext;
};
typedef Node* List;
List createNode(Employee& employee)
{
	List newNode = new Node;
	newNode->pNext = NULL;
	newNode->Data = employee;
	return newNode;
}
void createEmployee(Employee& employee)
{
	//cout << "Nhap Ma Nhan Vien: "; cin.getline(employee.id, 10);
	cout << "Nhap Ten Nhan Vien: "; cin.getline(employee.fullName, 40);
	cout << "Nhap Luong 1 Ngay: "; cin >> employee.salary;
	cout << "Nhap Luong So Ngay Cong: "; cin >> employee.amoutOfWorkdays;
	employee.realSalary = employee.amoutOfWorkdays * employee.salary * 1.0;
	//cin.ignore();
}
int checkIdOfList(List L,char idTemp[10])
{
	int index = 1;
	for (List P = L; P != NULL; P = P->pNext)
	{
		if (strcmp(P->Data.id, idTemp) == 0)
		{
			return index;//Valid
		}
		index++;
	}
	return -1; // InValid
}
void InsLast(List& L, Employee x) {
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
void inputListEmployee(List& L, Employee& employee,int lenght)
{
	char idTemp[10];
	int index = 0;
	int position ;
	while (index < lenght)
	{
		
		cout <<setw(15)<<left<<""<< "Nhap Nhan Vien Thu " << ++index << endl;
		do
		{
			cout << "Nhap Ma Nhan Vien: "; cin.getline(idTemp, 10);
			position = checkIdOfList(L, idTemp);
			if (position != -1)
			{
				cout << setw(15) << left << "" << "Ma Nhan Vien Bi Trung! Nhap Lai. \n";
			}
		} while (position != -1);
		strcpy(employee.id, idTemp);
		createEmployee(employee);
		InsLast(L, employee);
		cin.ignore();
	}
}
void title()
{
	cout << setw(15) << left << "Ma Nhan Vien" << setw(35) << left << "Ho Va Ten" << setw(12) << left << "Luong" << setw(15) << left << "Ngay Cong" <<setw(20)<<left<< "Luong Thuc Lanh" << endl;
}
void printListEmployee(List L)
{
	title();
		for (List P = L; P != NULL; P = P->pNext)
		{
			cout << setw(15) << left << P->Data.id << setw(35) << left << P->Data.fullName << setw(12) << left << P->Data.salary << setw(15) << left << P->Data.amoutOfWorkdays <<setw(20)<<left<< P->Data.realSalary << endl;
		}
}
void sortedListByRealSalary(List L)
{
	for (List P = L; P != NULL; P = P->pNext)
	{
		for (List Q = P->pNext; Q != NULL; Q = Q->pNext)
		{
			if (P->Data.realSalary > Q->Data.realSalary)
			{
				swap(P->Data, Q->Data);
			}
		}
	}
}
bool deletedEmployeeById(List& L,Employee &x, char idNeedToDelete[10])
{
	int position = checkIdOfList(L, idNeedToDelete);
	if (position != -1)
	{
		DelPos < List, Employee >(L, x, position);
		return true;
	}
	return false;
}
int main()
{
	List L = new Node[100];
	int lenght;
	cout << "Nhap So Luong Nhan Vien: "; cin >> lenght; cin.ignore();
	char idNeedToDelete[10];
	Employee employee;
	InitList<List>(L);
	inputListEmployee(L, employee, lenght);
	sortedListByRealSalary(L);
	cout <<setw(15)<<left<<""<< "Nhap Ma Nhan Vien Can Xoa: "; cin.getline(idNeedToDelete, 10);
	if (deletedEmployeeById(L, employee, idNeedToDelete))
	{
		cout << setw(15) << left << "" << " Xoa Thanh Cong! \n";
		printListEmployee(L);
	}
	else
	{
		cout << setw(15) << left << "" << " Xoa That Bai! \n";
	}
	cout << endl;
	delete[] L;
	return 0;
}