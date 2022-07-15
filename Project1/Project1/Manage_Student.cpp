#define _CRT_SECURE_NO_WARNINGS
#include "Methods.h"
/*	Cấu trúc sinh vien:
* Mã 10 Ký tự
* Tên 50 ký tự
* Ngày Sinh kiểu Ngay
* Điểm kiểu float
*	TASK:
* + Khai báo cấu trúc
* + Nhập n sinh viên từ bàn phím và ghi ra file "SINHVIEN.DAT"
* + Đọc danh sách sinh viên từ file trên và thực hiện các TASK sau:
*		+ Sắp xếp danh sách sinh viên tăng dần và ghi ra file "DSSV_TANGDAN.DAT"
*		+ Tìm theo mã, theo tên	
*		+ Xóa 1 SV theo mã	
*		+ Sủa thông tin 1 sinh viên
*		+  Kết quả cuối cùng lưu ra file "listStudentFinal.DAT"
* 
*/
struct Student
{
	char id[10], fullName[50];
	Date birthDay;
	float point;
};
int searchingIdOfStudent(Student a[], int n, char id[10])
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(a[i].id, id) == 0)
		{
			return i;
		}
	}
	return - 1;
}
void writeListStudentToFile(fstream& f, int n)
{
	Student temp[100];
	char tempId[10];
	f.open("SINHVIEN.DAT", ios::out | ios::binary);
	for (int i = 0; i < n; i++)
	{
		do
		{
			cout << "Nhap Ma cua sinh vien: "; cin.getline(tempId, 10);
			if (searchingIdOfStudent(temp, n, tempId) != -1)
			{
				cout << setw(20) << right << "" << "Ma da bi trung! Nhap lai.\n";
			}
		} while (searchingIdOfStudent(temp, n, tempId) != -1);
		strcpy(temp[i].id, tempId);
		cout << "Nhap ten cua sinh vien: "; cin.getline(temp[i].fullName, 50); standard_string(temp[i].fullName);
		input_date(temp[i].birthDay);
		do
		{
			cout << "Nhap diem cua sinh vien: "; cin >> temp[i].point;
			if (temp[i].point < 0 || temp[i].point > 10)
			{
				cout << setw(20) << right << "" << "Diem khong hop le! Nhap lai.\n";
			}
		} while (temp[i].point < 0 || temp[i].point > 10);
		cin.ignore();
		f.write((char*)(&temp[i]), sizeof(temp[i]));
	}
	f.close();
}
void readListStudentFromFile(fstream& f, Student a[], int& n)
{
	n = 0;
	f.open("SINHVIEN.DAT", ios::in | ios::binary);
	while (f.read((char*)(&a[n]), sizeof(a[n])))
	{
		n++;
	}
	f.close();
}
void title()
{
	cout << setw(15) << left << "Ma SV" << setw(35) << left << "Ten Sinh Vien" << setw(26) << left << "Ngay Sinh" << setw(10) << left << "Diem" << endl;
}
void printOneStudent(Student s)
{
	cout  << setw(15) << left << s.id << setw(35) << left << s.fullName << setw(3) << left << s.birthDay.day << setw(2) << left << "/" << setw(3) << left << s.birthDay.month
		<< setw(2) << left << "/" << setw(16) << left << s.birthDay.year << s.point << endl;
}
void printListStudent(Student a[], int n)
{
	title();
	for (int i = 0; i < n; i++)
	{
		printOneStudent(a[i]);
	}
}
void sortedListStudentByPoint(Student a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i].point > a[j].point)
				swap(a[i], a[j]);
		}
	}
}
void searchingFullNameOfStudent(Student a[], int n,char fullName[50])
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(a[i].fullName, fullName) == 0)
		{
			printOneStudent(a[i]);
		}
	}
}
void deletedOneStudentById(Student a[], int& n, char id[10])
{
	int position = searchingIdOfStudent(a, n, id);
	if (position != -1)
	{
		del<Student>(a, position, n);
		cout << setw(20) << right << "" << "Xoa Thanh Cong!\n";
	}
	else
	{
		cout <<setw(20)<<right<<""<< "Khong Ton Tai Sinh Vien Can Xoa!\n";
	}
}
void fixingIdOfStudent(Student a[], int n, int pos)
{
	char tempId[10];
	do
	{
		cout << "Nhap Ma Sinh Vien Can Sua: "; cin.getline(tempId, 10);
		if (searchingIdOfStudent(a, n, tempId) != -1)
		{
			cout << setw(20) << right << "" << "Ma da bi trung! Nhap lai.\n";
		}
	} while (searchingIdOfStudent(a, n, tempId) != -1);
	strcpy(a[pos].id, tempId);
	cout << setw(20) << right << "" << "Sua Ma Sinh Vien Thanh Cong!\n";
}
void fixingFullNameOfStudent(Student a[], int pos)
{
	char fullName[50];
	cout << "Nhap Ten Sinh Vien Sua Lai: "; cin.getline(fullName, 50); standard_string(fullName);
	strcpy(a[pos].fullName, fullName);
	cout << setw(20) << right << "" << "Sua Ten Sinh Vien Thanh Cong!\n";
}
void menuFixingBirtDay()
{
	cout << endl << endl;
	cout << setw(10) << right << "*" << "************************************\n";
	cout << setw(10) << "*" << setw(37) << "*\n";
	cout << setw(10) << right << "*" << setw(10) << "" << "1.Sua Ngay Sinh " << setw(11) << right << "*\n";
	cout << setw(10) << "*" << setw(37) << "*\n";
	cout << setw(10) << right << "*" << setw(10) << "" << "2.Sua Thang Sinh" << setw(11) << right << "*\n";
	cout << setw(10) << "*" << setw(37) << "*\n";
	cout << setw(10) << right << "*" << setw(10) << "" << "3.Sua Nam Sinh  " << setw(11) << right << "*\n";
	cout << setw(10) << "*" << setw(37) << "*\n";
	cout << setw(10) << right << "*" << "************************************\n\n";
}
void fixingPointOfStudent(Student a[], int pos)
{
	do
	{
		cout << "Nhap Diem Sua Lai: "; cin >> a[pos].point;
		if (a[pos].point < 0 || a[pos].point > 10)
		{
			cout << setw(20) << right << "" << "Diem khong hop le! Nhap lai.\n";
		}
	} while (a[pos].point < 0 || a[pos].point > 10);
	cin.ignore();
}
void fixingBirthDayOfStudent(Student a[], int pos)
{
	int selection;
	bool checkError = true; // kiểm tra lỗi khi sửa lại
	char checkContinue;
	do
	{
		system("CLS");
		menuFixingBirtDay();
		cout << "Nhap lua chon cua ban: "; cin >> selection; cin.ignore();
		switch (selection)
		{
		case 1: do
		{
			cout << "Nhap ngay: "; cin >> a[pos].birthDay.day;
			if (a[pos].birthDay.day > date_of_month(a[pos].birthDay) || a[pos].birthDay.day <= 0)
			{
				cout << "Ngay khong hop le! Nhap lai Hoac Sua Thang/Nam truoc.\n";
				cout << setw(10) << right << "*" << "*************************\n";
				cout << setw(10) << right << "*" << "  0.Nhap Lai!           *\n";
				cout << setw(10) << right << "*" << "                        *\n";
				cout << setw(10) << right << "*" << "  1.Sua Thang Hoac Nam! *\n";
				cout << setw(10) << right << "*" << "*************************\n\n";
				cout << "Nhap lua chon cua ban: "; cin >> checkError;
			}
			else
			{
				cout << endl;
				cout << setw(20) << right << "" << "Sua Ngay Sinh Thanh Cong!\n";
			}
		} while ((a[pos].birthDay.day > date_of_month(a[pos].birthDay) || a[pos].birthDay.day <= 0) && !checkError); break;
		case 2:
			do
			{
				cout << "Nhap Thang: "; cin >> a[pos].birthDay.month;
				if (a[pos].birthDay.day > date_of_month(a[pos].birthDay))
				{
					cout << "Thang khong hop le! Nhap lai Hoac Sua Ngay truoc.\n";
					cout << setw(10) << right << "*" << "*************************\n";
					cout << setw(10) << right << "*" << "  0.Nhap Lai!           *\n";
					cout << setw(10) << right << "*" << "                        *\n";
					cout << setw(10) << right << "*" << "  1.Sua Ngay!           *\n";
					cout << setw(10) << right << "*" << "*************************\n\n";
					cout << "Nhap lua chon cua ban: "; cin >> checkError;
				}
				else
				{
					cout << endl;
					cout << setw(20) << right << "" << "Sua Thang Sinh Thanh Cong!\n";
				}
			} while (a[pos].birthDay.day > date_of_month(a[pos].birthDay) && !checkError); break;
		case 3: do
		{
			cout << "Nhap nam: "; cin >> a[pos].birthDay.year;
			if (a[pos].birthDay.year < 1)
				cout << setw(20) << right << "" << "Nam khong hop le! Nhap lai \n";
			else
			{
				cout << endl;
				cout << setw(20) << right << "" << "Sua Nam Sinh Thanh Cong!\n";
			}
		} while (a[pos].birthDay.year < 1); break;
		default: cout << setw(20) << right << "" << "Lua Chon Khong Hop Le!\n";
			break;
		}
		cout << endl;
		cout << "Ban Muon Tiep Tuc Sua Ngay sinh? Y/N -----> "; cin >> checkContinue;
		if (checkContinue != 'Y' && checkContinue != 'y')
		{
			cout << endl;
			cout << setw(20) << "" << "Ket Thuc Phan Sua Ngay sinh! \n";
		}
	} while (checkContinue == 'y' || checkContinue == 'Y');
}
void menuFixingInfor()
{
	cout << endl << endl;
	cout << setw(10) << right << "*" << "*************************************\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "1.Sua Ma Sinh Vien        " << setw(6) << right << "*\n";
	cout << setw(10) << "*" << setw(38) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "2.Sua Ho Ten Sinh Vien    " << setw(6) << right << "*\n";
	cout << setw(10) << "*" << setw(38) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "3.Sua Diem Sinh Vien      " << setw(6) << right << "*\n";
	cout << setw(10) << "*" << setw(38) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "4.Sua Ngay Sinh Sinh Vien " << setw(6) << right << "*\n";
	cout << setw(10) << "*" << setw(38) << "*\n";
	cout << setw(10) << right << "*" << "*************************************\n\n";
}
void fixingInforOfStudent(Student a[], int n, int pos)
{
	int selection;
	char checkContinue;
	do
	{
		system("CLS");
		menuFixingInfor();
		cout << "Nhap Lua Chon Cua Ban: "; cin >> selection; cin.ignore();
		switch (selection)
		{
		case 1: fixingIdOfStudent(a, n, pos); break;
		case 2: fixingFullNameOfStudent(a, pos); break;
		case 3: fixingPointOfStudent(a, pos); break;
		case 4: fixingBirthDayOfStudent(a, pos); break;
		default: cout << setw(20) << "" << "Lua Chon Khong Hop Le! \n";
			break;
		}
		cout << endl;
		cout << "Ban Muon Tiep Tuc Sua Thong Tin? Y/N -----> "; cin >> checkContinue;
		if (checkContinue != 'Y' && checkContinue != 'y')
		{
			cout << endl;
			cout << setw(20) << "" << "Ket Thuc Phan Sua Thong Tin! \n";
		}
	} while (checkContinue == 'y' || checkContinue == 'Y');
}
void writeFinalListStudentToFile(fstream& f, Student a[], int n)
{
	string filePath;
	cout << "Nhap Duong Dan Can Luu: "; cin >> filePath;
	f.open(filePath, ios::out | ios::binary);
	for (int i = 0; i < n; i++)
	{
		f.write((char*)(&a[i]), sizeof(a[i]));
	}
	cout << setw(20) << right << "" << "Luu Danh Sach Vao File Thanh Cong!\n";
	f.close();
}
void mainMenu()
{
	cout << endl << endl;
	cout << setw(10) << right << "*" << "*****************************************************\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "1.Ghi Danh Sach Sinh Vien Vao File     " << setw(9) << right << "*\n";
	cout << setw(10) << "*" << setw(54) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "2.Doc File & In Danh Sach Sinh Vien    " << setw(9) << right << "*\n";
	cout << setw(10) << "*" << setw(54) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "3.Tim Sinh Vien Bang Ma                " << setw(9) << right << "*\n";
	cout << setw(10) << "*" << setw(54) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "4.Tim Sinh Vien Bang Ho Ten            " << setw(9) << right << "*\n";
	cout << setw(10) << "*" << setw(54) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "5.Sap Xep Danh Sach Sinh Vien Theo Diem" << setw(9) << right << "*\n";
	cout << setw(10) << "*" << setw(54) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "6.Xoa Sinh Vien Bang Ma                " << setw(9) << right << "*\n";
	cout << setw(10) << "*" << setw(54) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "7.Sua Thong Tin Sinh Vien              " << setw(9) << right << "*\n";
	cout << setw(10) << "*" << setw(54) << "*\n";
	cout << setw(10) << right << "*" << setw(6) << "" << "8.Luu Danh Sach Sinh Vien Ra File      " << setw(9) << right << "*\n";
	cout << setw(10) << "*" << setw(54) << "*\n";
	cout << setw(10) << right << "*" << "*****************************************************\n\n";
}
int main()
{
	Student a[100];
	fstream f;
	int n,selectionMain,temp,pos;
	char checkContinue;
	char id[10], fullName[50];
	do
	{
		system("CLS");
		mainMenu();
		cout << "Nhap Lua Chon Cua Ban: "; cin >> selectionMain; cin.ignore();
		switch (selectionMain)
		{
		case 1:
			cout << "Nhap So Luong Sinh Vien: "; cin >> n; cin.ignore();
			writeListStudentToFile(f, n); break;
		case 2: 
			readListStudentFromFile(f, a, n);
			printListStudent(a, n);
			break;
		case 3:
			cout << "Nhap Ma Sinh Vien Can Tim: "; cin.getline(id, 10);
			temp = searchingIdOfStudent(a, n, id);
			if (temp != -1)
			{
				title();
				printOneStudent(a[temp]);
			}
			else
			{
				cout << setw(20) << right << "" << "Khong Ton Tai Sinh Vien Can Tim!\n";
			} break;
		case 4: 
			cout << "Nhap Ten Sinh Vien Can Tim: "; cin.getline(fullName, 50); standard_string(fullName);
			title();
			searchingFullNameOfStudent(a, n, fullName); break;
		case 5: 
			sortedListStudentByPoint(a, n);
			cout << setw(20) << right << "" << "Danh Sach Sau Khi Sap Xep!\n";
			printListStudent(a, n); break;
		case 6: 
			cout << "Nhap Ma Sinh Vien Can Xoa: "; cin.getline(id, 10);
			deletedOneStudentById(a, n, id); break;
		case 7: 
			cout << "Nhap Vi Tri Cua Sinh Vien Can Sua Thong Tin: "; cin >> pos; cin.ignore();
			fixingInforOfStudent(a, n, pos); break;
		case 8: writeFinalListStudentToFile(f, a, n); break;
		default:cout << setw(20) << "" << "Lua Chon Khong Hop Le! \n";
			break;
		}
		cout << endl;
		cout << "Ban Muon Tiep Tuc Chuong Trinh? Y/N -----> "; cin >> checkContinue;
		if (checkContinue != 'Y' && checkContinue != 'y')
		{
			cout << endl;
			cout << setw(20) << "" << "Ket Thuc Chuong Trinh! \n";
		}
	} while (checkContinue == 'y' || checkContinue == 'Y');
	cout << endl;
	return 0;
}