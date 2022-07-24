#include "libraryOfHuy.h"
/*
*  //-------------------------TASKS-------------------------//
*		1. Nhap / Xuat Danh Sach theo Them Cuoi
*		2. Loc Ra Danh Sach Nhan Vien Co Xep Hang Theo Option
*		3. In Ra Toan Bo Thong Tin Cua Nhan Vien Co Luong Thuc Linh Lon Nhat
*		4. Sap Xep Danh Sach Tang Dan Theo Luong Thuc Linh
*		5. Xoa 1 Nhan Vien Bang Ma
*		6. Xoa Tat Ca Nhan Vien Co Ngay Cong La 0
*		7. Luu Danh Sach Cuoi Cung Ra File
*/
struct Employee
{
	char id[10];
	char firstName[30];
	char lastName[20];
	char birthDay[13];
	int salary;
	int amoutOfWorkdays;
	int realSalary;
	char rank[12];
	/*
	* //------------------------DESCRIPTION OF RANK------------------------//
	*    IF The Number Of Workdays > 28		 --> VERY GOOD + 500000
	*	 ELSE IF The Number Of Workdays > 26 --> GOOD + 300000
	*    ELSE IF The Number Of Workdays > 24 --> NORMAL +0
	*    ELSE IF The Number Of Workdays < 24 --> BAD - 200000
	*  
	*/
};
struct Node
{
	Employee Data;
	Node* pNext;
};
typedef Node* List;
void createEmployee(Employee& employee)
{
	cout << "Nhap Ho Va Ten Dem Cua Nhan Vien: "; cin.getline(employee.firstName, 30);
	cout << "Nhap Ten Nhan Vien: "; cin.getline(employee.lastName, 20);
	cout << "Nhap Ngay Sinh Cua Nhan Vien (string): "; cin.getline(employee.birthDay, 13);
	cout << "Nhap Luong 1 Ngay Cua Nhan Vien: "; cin >> employee.salary;
	cout << "Nhap So Ngay Cong: "; cin >> employee.amoutOfWorkdays;
	employee.realSalary = employee.amoutOfWorkdays * employee.salary;
	if (employee.amoutOfWorkdays > 28)
	{
		strcpy(employee.rank, "Very Good");
		employee.realSalary += 500000;
	}
	else if (employee.amoutOfWorkdays > 26)
	{
		strcpy(employee.rank, "Good");
		employee.realSalary += 300000;
	}
	else if (employee.amoutOfWorkdays > 24)
	{
		strcpy(employee.rank, "Normal");
	}
	else 
	{
		strcpy(employee.rank, "Bad");
		employee.realSalary -= 200000;
	}
}
List createNode(Employee& employee)
{
	List newNode = new Node;
	newNode->pNext = NULL;
	newNode->Data = employee;
	return newNode;
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
void inputListEmployee(List& L, Employee& employee, int lenght)
{
	int index = 1;
	while (index <= lenght)
	{
		cout << setw(15) << left << "" << "Nhap Thong Tin Nhan Vien Thu " << index++ << "!" << endl;
		createEmployee(employee);
		strcpy(employee.id, employee.lastName);// line code 90 -> 93: Tạo Id tự động cho nó không trùng nhau. Tao đéo thích nhập đấy :))
		std::string s = std::to_string(100+index-1);
		char const* pchar = s.c_str();
		strcpy(employee.id + strlen(employee.id), pchar); 
		InsLast(L, employee);
		cin.ignore();
	}
}
void title()
{
	cout << setw(15) << left << "Ma Nhan Vien" << setw(30) << left << "Ho Va Ten Dem" << setw(10) << left << "Ten" << setw(18) << left << "Ngay Sinh" << setw(12) 
		<< left << "Luong CB" << setw(12) << left << "Ngay Cong" << setw(15) << left << "Thuc Linh" << setw(15) << right << "Xep Hang" << endl;
}
void printInforOfEmployee(Employee employee)
{
	cout << setw(15) << left <<employee.id << setw(30) << left << employee.firstName << setw(10) << left << employee.lastName << setw(18) << left << employee.birthDay << setw(12)
		<< left << employee.salary << setw(12) << left << employee.amoutOfWorkdays << setw(15) << left << employee.realSalary << setw(15) << right << employee.rank << endl;
}
void printListEmployee(List L)
{
	title();
	for (List Pointer = L; Pointer != NULL; Pointer = Pointer->pNext)
	{
		cout << setw(15) << left << Pointer->Data.id << setw(30) << left << Pointer->Data.firstName << setw(10) << left << Pointer->Data.lastName << setw(18) << left << Pointer->Data.birthDay << setw(12)
			<< left << Pointer->Data.salary << setw(12) << left << Pointer->Data.amoutOfWorkdays << setw(15) << left << Pointer->Data.realSalary << setw(15) << right << Pointer->Data.rank << endl;
	}
}
void plitRankOfEmpoyeeWithOption(List L, char option[13])
{
	for (List Pointer = L; Pointer != NULL; Pointer = Pointer->pNext)
	{
		if (strcmp(Pointer->Data.rank, option) == 0)
		{
			printInforOfEmployee(Pointer->Data);
		}
	}
}
void printInforOfEmployeeHasMaxRealSalary(List L)
{

	List Pointer = L;
	Employee DataOfMax = Pointer ->Data;
	auto max = DataOfMax.realSalary;
	for (Pointer; Pointer != NULL; Pointer = Pointer->pNext)
	{
		if (max < Pointer->Data.realSalary) // con trỏ trỏ đến con trỏ tiếp theo và trỏ đến data của lương thực lĩnh :)) lú cái đầu chưa :)))))) Con trỏ every where :v
		{
			DataOfMax = Pointer->Data;
			max = Pointer->Data.realSalary;
		}
	}
	printInforOfEmployee(DataOfMax);
	//return employee;
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
bool deletedEmployeeById(List& L,Employee &employee, char idOfEmployee[10])
{
	auto index = 1;
	for (List Pointer = L; Pointer != NULL; Pointer = Pointer->pNext)
	{
		if (strcmp(Pointer->Data.id, idOfEmployee) == 0)
		{
			DelPos<List, Employee>(L, employee, index);
			return true; // Trongg Hàm Có kiểu trả về thì sự khác biệt của return và break như sau: return sẽ trả về và thoát khỏi hàm luôn mà không quan tâm phía dưới còn câu lệnh hay không, 
						//  Còn break thì chỉ dùng vòng lặp ở đó nếu ngoài vòng lặp còn lệnh thì lệnh đó sẽ được thực thi. Không tin thì có thể kiểm chứng :))
		}
		index++;
	}
	return false;
}
auto findPositionOfAmoutOfWorkdaysEqualZero(List L)
{
	auto index = 1;
	for (List Pointer = L; Pointer != NULL; Pointer = Pointer->pNext)
	{
		if (Pointer->Data.amoutOfWorkdays == 0)
		{
			return index;
		}
		index++;
	}
	return -1;
}
void deletedAllEmployeesHaveAmoutOfWorkdaysEqualZero(List& L, Employee& employee)
{
	while (findPositionOfAmoutOfWorkdaysEqualZero(L) != -1)
	{
		DelPos<List, Employee>(L, employee, findPositionOfAmoutOfWorkdaysEqualZero(L));
	}
}
void savingListToFile(List L, fstream& fileOfList, string filePath)
{
	List Pointer = L;
	fileOfList.open(filePath, ios::out | ios::binary);
	while (Pointer != NULL)
	{
		fileOfList.write((char*)(&Pointer->Data), sizeof(Pointer->Data));
		Pointer = Pointer->pNext;
	}
	fileOfList.close();
}
void menu()
{
	cout << setw(10) << left << "" << "*********************************************************************\n";
	cout << setw(11) << right << "*" << setw(10) << left << "" << setw(57) << left << "1.Nhap Danh Sach Nhan Vien." << "*\n";
	cout << setw(11) << right << "*" << setw(68) << right << "*" << endl;
	cout << setw(11) << right << "*" << setw(10) << left << "" << setw(57) << left << "2.Xuat Danh Sach Nhan Vien." << "*\n";
	cout << setw(11) << right << "*" << setw(68) << right << "*" << endl;
	cout << setw(11) << right << "*" << setw(10) << left << "" << setw(57) << left << "3.Loc Danh Sach Nhan Vien Theo Xep Hang." << "*\n";
	cout << setw(11) << right << "*" << setw(68) << right << "*" << endl;
	cout << setw(11) << right << "*" << setw(10) << left << "" << setw(57) << left << "4.Thong Tin Cua Nhan Vien Luong Thuc Linh Cao Nhat." << "*\n";
	cout << setw(11) << right << "*" << setw(68) << right << "*" << endl;
	cout << setw(11) << right << "*" << setw(10) << left << "" << setw(57) << left << "5.Sap Xep Danh Sach Tang Dan Theo Luong Thuc Linh." << "*\n";
	cout << setw(11) << right << "*" << setw(68) << right << "*" << endl;
	cout << setw(11) << right << "*" << setw(10) << left << "" << setw(57) << left << "6.Xoa 1 Nhan Vien Bang Ma." << "*\n";
	cout << setw(11) << right << "*" << setw(68) << right << "*" << endl;
	cout << setw(11) << right << "*" << setw(10) << left << "" << setw(57) << left << "7.Xoa Tat Ca Nhan Vien Co Ngay Cong La 0." << "*\n";
	cout << setw(11) << right << "*" << setw(68) << right << "*" << endl;
	cout << setw(11) << right << "*" << setw(10) << left << "" << setw(57) << left << "8.Luu Danh Sach Ra File." << "*\n";
	cout << setw(11) << right << "*" << setw(68) << right << "*" << endl;
	cout << setw(10) << left << "" << "*********************************************************************\n\n";
}
void menuOfPlitting()
{
	cout << setw(10) << left << "" << "**************************************************************\n";
	cout << setw(11) << right << "*" << setw(10) << left << "" << setw(50) << left << "1.Nhung Nhan Vien Co Xep Hang Very Good." << "*\n";
	cout << setw(11) << right << "*" << setw(61) << right << "*" << endl;
	cout << setw(11) << right << "*" << setw(10) << left << "" << setw(50) << left << "2.Nhung Nhan Vien Co Xep Hang Good." << "*\n";
	cout << setw(11) << right << "*" << setw(61) << right << "*" << endl;
	cout << setw(11) << right << "*" << setw(10) << left << "" << setw(50) << left << "3.Nhung Nhan Vien Co Xep Hang Normal." << "*\n";
	cout << setw(11) << right << "*" << setw(61) << right << "*" << endl;
	cout << setw(11) << right << "*" << setw(10) << left << "" << setw(50) << left << "4.Nhung Nhan Vien Co Xep Hang Bad." << "*\n";
	cout << setw(11) << right << "*" << setw(61) << right << "*" << endl;
	cout << setw(10) << left << "" << "**************************************************************\n\n";
}
void plittedListByRank(List L)
{
	char option[13];
	char checkContinue;
	auto selection = 0;
	do
	{
		system("CLS");
		menuOfPlitting();
		cout << "Nhap  Lua Chon Cua Ban: "; cin >> selection; cin.ignore();
		switch (selection)
		{
		case 1:
			strcpy(option, "Very Good");
			plitRankOfEmpoyeeWithOption(L, option); break;
		case 2:
			strcpy(option, "Good");
			plitRankOfEmpoyeeWithOption(L, option); break;
		case 3:
			strcpy(option, "Normal");
			plitRankOfEmpoyeeWithOption(L, option); break;
		case 4:
			strcpy(option, "Bad");
			plitRankOfEmpoyeeWithOption(L, option); break;
		default:cout << setw(15) << left << "" << "Lua Chon Khong Hop Le!\n";
			break;
		}
		cout << setw(15) << left << "" << "Thay Tao Dep Trai Khong :))? Y/N -------> "; cin >> checkContinue; cin.ignore();
		if (!(checkContinue == 'Y' || checkContinue == 'y'))
		{
			cout << setw(15) << left << "" << "Ket Thuc Phan Loc Danh Sach!\n";
		}
	} while (checkContinue == 'Y' || checkContinue == 'y');
}
int main()
{
	List L = new Node[100];
	Employee employee;
	fstream fileOfList;
	string filePath;
	int lenght ;
	char idOfEmployee[10];
	char checkContinue;
	auto selection=0;
	InitList<List>(L);
	do
	{
		system("CLS");
		menu();
		cout << "Nhap  Lua Chon Cua Ban: "; cin >> selection; cin.ignore();
		switch (selection)
		{
		case 1:
			cout << "Nhap So Luong Nhan Vien: "; cin >> lenght; cin.ignore();
			inputListEmployee(L, employee, lenght);
			break;
		case 2:
			printListEmployee(L);
			break;
		case 3:
			plittedListByRank(L);
			break;
		case 4:
			printInforOfEmployeeHasMaxRealSalary(L);
			break;
		case 5: 
			sortedListByRealSalary(L);
			break;
		case 6:
			cout << "Nhap Ma Nhan Vien Can Xoa: "; cin.getline(idOfEmployee, 10);
			deletedEmployeeById(L, employee, idOfEmployee);
			break;
		case 7:
			deletedAllEmployeesHaveAmoutOfWorkdaysEqualZero(L, employee);
			break;
		case 8:
			cout << "Nhap Duong Dan Luu File -------> "; getline(cin, filePath);
			savingListToFile(L, fileOfList, filePath);
			break;
		default:cout << setw(15) << left << "" << "Lua Chon Khong Hop Le!\n";
			break;
		}
		cout << setw(15) << left << "" << "Thay Tao Dep Trai Khong :))? Y/N -------> "; cin >> checkContinue; cin.ignore();
		if (!(checkContinue == 'Y' || checkContinue == 'y'))
		{
			cout << setw(15) << left << "" << "Ket Thuc Chuong Trinh. Bye Cac Con Vo!\n";
		}
	} while (checkContinue == 'Y' || checkContinue == 'y');
	
	
	cout << endl;
	delete[] L;
	return 0;
}