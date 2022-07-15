#define  _CRT_SECURE_NO_WARNINGS
#include "Methods.h"
struct Student
{
	char id[11];
	char fullName[30];// có thể tách ra 2 thành phần: họ tên đệm + tên hoặc 3 thành phần là: Họ + tên đệm + tên (để có sort theo tên hoặc xử lý các việc khác cũng dễ hơn)
	Date birthDay;
	float chemistry, physics, math,total;
	// có thể thêm các thành phần như gender/sex(giới tính), address(địa chỉ), telephone number (số điện thoại) v.v
};
// Những hàm + biến dưới đây sử dụng kỹ thuật đặt tên theo kiểu lạc đà (camelCase) rất phổ biến trong lập trình
// Vừa học Code vừa học luôn tiếng Anh :))
int searchId(Student a[], int &n, char idTemp[11])
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(a[i].id, idTemp)==0)
			return i;
	}
	return -1;
}
void writeFileStudent(fstream& f,int &n)
{
	Student temp[100];
	char tempId[11];
	f.open("E://Studies/kyThuatLapTrinh/listStudent.txt", ios::out|ios::binary);
	for (int i = 0; i < n; i++)
	{
		do
		{
			cout << "Nhap Ma: "; cin.getline(tempId, 11);
			if (searchId(temp, n, tempId) != -1)
			{
				cout << "Ma da bi trung!\n";
			}
		} while (searchId(temp, n, tempId) != -1);
		strcpy(temp[i].id, tempId);
		cout << "Nhap ten: "; cin.getline(temp[i].fullName, 30); standard_string(temp[i].fullName);
		input_date(temp[i].birthDay);
		cout << "Nhap diem mon Hoa: "; cin >> temp[i].chemistry;
		cout << "Nhap diem mon Ly: "; cin >> temp[i].physics;
		cout << "Nhap diem mon Toan: "; cin >> temp[i].math;
		temp[i].total = temp[i].math + temp[i].chemistry + temp[i].physics;
		cin.ignore();
		f.write((char*)(&temp[i]), sizeof(temp[i]));
	}
	f.close();
}
void readFileStudent(fstream& f, Student a[], int& n)
{
	n = 0;
	f.open("E://Studies/kyThuatLapTrinh/listStudent.txt", ios::in | ios::binary);
	while (f.read((char*)(&a[n]), sizeof(a[n])))
	{
		n++;
	}
	f.close();
}
void title()
{
	cout << setw(15) << left << "Ma Sinh Vien" << setw(35) << left << "Ho Va Ten Sinh Vien" << setw(18) << left << "Ngay Sinh" << setw(10) << left << "Toan" << setw(10) 
		<< left << "Ly" << setw(10) << left << "Hoa" << right << "Tong";
	cout << endl;
}
void printOneStudent(Student s)
{
	cout << setw(15) << left << s.id << setw(35) << left << s.fullName << setw(2) << left << s.birthDay.day << setw(2) << left << "/" << setw(2) << left << s.birthDay.month
		<< setw(2) << left << "/" << setw(10) << left << s.birthDay.year << setw(10) << left << s.math
		<< setw(10) << left << s.physics << setw(10) << left << s.chemistry << setw(10) << left << s.total << endl;
}
void printListStudent(Student a[], int &n)
{
	title();
	for (int i = 0; i < n; i++)
	{
		printOneStudent(a[i]);
	}
}
void sortedByTotalPoint(Student a[], int n) // sắp xếp danh sách học sinh theo điểm tổng tăng dần
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (a[i].total > a[j].total)
				swap(a[i], a[j]);
		}
	}
}
void filterOutTheListStudentPassUniversity(Student a[], int n, float benchMark) // lọc ra danh sách các học sinh đậu đại học
{
	int numberStudent = 0;
	Student b[100];
	for (int i = 0; i < n; i++)
	{
		if (a[i].total >= benchMark)
		{
			b[numberStudent++] = a[i];
		}
	}
	printListStudent(b, numberStudent);
}
int searchedByFullName(Student a[], int n,char fullNameNeedSearching[30])
{
	for (int i = 0; i < n ; i++)
	{
		if (strcmp(a[i].fullName, fullNameNeedSearching) == 0)
		{
			title();
			printOneStudent(a[i]);
			return i;
		}
	}
	cout << "Khong tim thay sinh vien\n";
	return -1;
}
void delStudentWithId(Student a[], int &n, char idNeedDel[11]) // xóa 1 học sinh bằng mã
{
	short searchingId = searchId(a, n, idNeedDel);
	if (searchingId != -1)
	{
		del<Student>(a, searchingId, n); // viết theo kiểu hướng đối tượng sử dụng Template. Có thể bỏ qua và viết 1 hàm xóa 1 PT ở phía trên
	}
	else
	{
		cout << "Khong ton tai sinh vien can xoa!\n";
	}
}
int findStudentByName(Student a[], int n, char name[10])
{
	char nameTemp[10]; int index;
	for (int i = 0; i < n; i++)
	{
		index = 0;
		auto size = strlen(a[i].fullName);
		for (auto j = size - 1; a[i].fullName[j] != ' '; j--)
		{
			index++;
		}
		strncpy(nameTemp, a[i].fullName + (strlen(a[i].fullName) - index), index);
		nameTemp[index] = '\0';
		if (strcmp(nameTemp, name) == 0)
		{
			return i;
		}
	}
	return -1;
}
void insertStudentIntoPos(Student a[], int &n, int pos)
{
	char tempId[11];
	n++;
	for (int i = n-1; i > pos; i--)
	{
		a[i] = a[i - 1];
	}
	do
	{
		cout << "Nhap Ma: "; cin.getline(tempId, 11);
		if (searchId(a, n,tempId ) != -1)
		{
			cout << "Ma da bi trung!\n";
		}
	} while (searchId(a, n, tempId) != -1);
	strcpy(a[pos].id, tempId);
	cout << "Nhap ten: "; cin.getline(a[pos].fullName, 30); standard_string(a[pos].fullName);
	input_date(a[pos].birthDay);
	cout << "Nhap diem mon Hoa: "; cin >> a[pos].chemistry;
	cout << "Nhap diem mon Ly: "; cin >> a[pos].physics;
	cout << "Nhap diem mon Toan: "; cin >> a[pos].math;
	a[pos].total = a[pos].math + a[pos].chemistry + a[pos].physics;
	cin.ignore();
}
void fixedIdOfStudent(Student a[],int n, int pos)
{
	char idFixed[11];
	do
	{
		cout << "Nhap Ma Can sua: "; cin.getline(idFixed, 11);
		if (searchId(a, n, idFixed) != -1)
		{
			cout << "Ma da bi trung!\n";
		}
	} while (searchId(a, n, idFixed) != -1);
	strcpy(a[pos].id, idFixed);
}
void fixedFullNameOfStudent(Student a[], int pos,char fullNameFixed[30])
{
	strcpy(a[pos].fullName, fullNameFixed);
}
void fixedBirthDayOfStudent(Student a[], int pos)
{
	short selection;
	char checkContinue;
	cout << setw(40) << setfill('-') << "";cout << endl;
	cout << setw(20) << left << "1.Sua Ngay Sinh" << "2.Sua Thang Sinh" << endl;
	cout << setw(20) << left << "3.Sua Nam Sinh" << "4.Khong Sua!" << endl;
	cout << setw(40) << setfill('-') << "";cout << endl;
	do
	{
		cout << "Nhap lua chon cua ban: "; cin >> selection;
		switch (selection)
		{
		case 1: 
			do
		{
				cout << "Nhap Ngay Sinh: "; cin >> a[pos].birthDay.day; 
				if (a[pos].birthDay.day <= 0 || a[pos].birthDay.day > date_of_month(a[pos].birthDay))
					cout << setw(20) << "" << "Ngay sinh kh hop le!\n";
		} while (a[pos].birthDay.day <= 0 || a[pos].birthDay.day > date_of_month(a[pos].birthDay)); break;
		case 2: 
			do
			{ // Có Bug: sửa lại tháng nhưng tháng đó không tồn tại ngày hiện tại. Ví dụ: đang là 31/12/2001 --> sửa thành 31/11/2001 là sai
				// Có thể ràng buộc điều kiện: khi chúng ta sửa lại tháng thì so sánh ngày hiện tại với số ngày trong tháng vừa sửa. Nếu ngày hiện tại > số ngày trong tháng
				// lúc này sẽ xảy ra 2TH: 1 là sẽ sửa lại tháng, 2 là sửa lại ngày
				cout << "Nhap Thang Sinh: "; cin >> a[pos].birthDay.month;
				if (a[pos].birthDay.month <= 0 || a[pos].birthDay.month > 12)
					cout << setw(20) << "" << "Thang khong hop le!\n";
			} while (a[pos].birthDay.month<=0 || a[pos].birthDay.month > 12);
			break;
		case 3:
			do
			{ // thêm 1 Bug nữa nếu hiện tại là 29/2/2000 --> sửa thành 29/2/2001 là sai
				// Tương tự như trường hợp trên
				cout << "Nhap Nam Sinh: "; cin >> a[pos].birthDay.year;
				if (a[pos].birthDay.year <= 0)
					cout << setw(20) << "" << "Nam khong hop le!\n";
			} while (a[pos].birthDay.year <=0);
			 break;
			default: cout << setw(20) << ""<<"Thong tin kh bi thay doi!\n";
			break;
		}
		cout << "Ban muon tiep tuc? An Y/N ---------> "; cin >> checkContinue;
		if (checkContinue != 'Y' && checkContinue != 'y')
		{
			cout <<setw(20)<<""<< "Ket thuc phan sua ngay sinh!\n";
		}
	} while (checkContinue == 'Y'|| checkContinue == 'y');
}
void fixedPointOfStudent(Student a[], int pos)
{
	int selectFix;
	char check;
	cout << "=========================================\n\n"; // có thể viết cout<< setw(<so luong ky tu can in>) << setfill('<ky tu can in>') << "" <<endl; IMPORTANT: phải thêm (<< "")
	cout << setw(20) << left << "1.Sua diem Toan" << "2.Sua diem Ly\n\n";
	cout << setw(20) << left << "3.Sua diem Hoa" << "4.Thoat chuong trinh\n\n";
	cout << "=========================================\n\n";
	do
	{
		cout << "Nhap lua chon cua ban: "; cin >> selectFix;
		switch (selectFix)
		{
		case 1:
			do
			{
				cout << "Nhap diem toan: "; cin >> a[pos].math;
			} while ((a[pos].math < 0 || a[pos].math >10)); break;
		case 2:
			do
			{
				cout << "Nhap diem ly: "; cin >> a[pos].physics;
			} while ((a[pos].physics < 0 || a[pos].physics >10)); break;
		case 3:
			do
			{
				cout << "Nhap diem hoa: "; cin >> a[pos].chemistry;
			} while ((a[pos].chemistry < 0 || a[pos].chemistry >10)); break;
		case 4: exit(0); break;
		default:cout << "Du lieu khong bi sua! \n";
			break;
		}
		cout << "Ban muon sua diem tiep? Y/N ---> "; cin >> check;
		if (check != 'y' && check != 'Y')
		{
			cout << setw(20) << setfill(' ') << "" << "Ket thuc phan sua diem!" << endl;
		}
		cin.ignore();
	} while (check == 'Y' || check == 'y');

	a[pos].total = a[pos].math + a[pos].physics + a[pos].chemistry; //IMPORTANT: cập nhật lại điểm tổng
}
void FixedInforOfStudent(Student a[], int n)
{
	int select, pos;
	char checkFix;
	char fullNameFixed[30];
	cout << "=========================================\n\n";
	cout << setw(20) << left << "1.Sua Ma sinh vien" << "2.Sua Ten Sinh vien \n\n";
	cout << setw(20) << left << "3.Sua Ngay Sinh" << "4.Sua Diem" << "\n\n";
	cout << "=========================================\n\n";
	do
	{
		cout << "Nhap vi tri sinh vien can sua: "; cin >> pos;
		if (pos >= n || pos < 0)
			cout << "Vi tri sua khong hop le. Moi ban nhap lai!\n";
	} while (pos >= n || pos < 0);
	do
	{
		cout << "Nhap Lua chon cua ban: "; cin >> select; cin.ignore();
		switch (select)
		{
		case 1:
			fixedIdOfStudent(a, n, pos); break;
		case 2:cout << "Nhap ten can sua: "; cin.getline(fullNameFixed, 30);
			fixedFullNameOfStudent(a, pos,fullNameFixed); break;
		case 3:fixedBirthDayOfStudent(a, pos); break;
		case 4:fixedPointOfStudent(a, pos); break;
		default:cout << "Chuong trinh khong thay doi!\n";
			break;
		}
		cout << "Ban muon sua tiep? Y/N ---> "; cin >> checkFix;
		if (checkFix != 'y' && checkFix != 'Y')
		{
			cout << setw(20) << setfill(' ') << "" << "Ket thuc phan sua thong tin!" << endl;
		}
		cin.ignore();
	} while (checkFix == 'Y' || checkFix == 'y');
	printOneStudent(a[pos]);
}
string nameOfNum[10] =
{
	"Khong",
	"Mot",
	"Hai",
	"Ba",
	"Bon",
	"Nam",
	"Sau",
	"Bay",
	"Tam",
	"Chin",
};
void doSomething(int n)
{
	string s = to_string(n);
	for (int i = 0; i < s.length(); i++)
	{
		cout << nameOfNum[s[i] - 48]<<" ";
	}
}
int main()
{
	/*fstream f,f1;
	Student a[100];
	int n;*/
	//char fullNameNeedSearching[30];
	//cout << "Nhap ho va ten sinh vien can tim: "; cin.getline(fullNameNeedSearching, 30); standard_string(fullNameNeedSearching);
	//char idNeedDel[11];
	//cout << "Nhap ma can xoa: "; cin.getline(idNeedDel, 11);
	/*cout << "Nhap so luong sinh vien: "; cin >> n; cin.ignore();
	writeFileStudent(f, n);*/
	//readFileStudent(f, a, n);
	//delStudentWithId(a, n, idNeedDel);
	//sortedByTotalPoint(a, n);
	//filterOutTheListStudentPassUniversity(a, n, 25.25);
	//searchedByFullName(a, n, fullNameNeedSearching);
	//insertStudentIntoPos(a, n, 12);
	//FixedInforOfStudent(a, n);
	/*char name[10];
	strcpy(name, "Huy");
	int pos = findStudentByName(a, n, name);
	printListStudent(a, n);
	cout << endl;
	cout <<pos << endl;
	printOneStudent(a[pos]);*/
	//printOneStudent(a[findStudentByName(a, n, name)]);
	/*f1.open("E://Studies/kyThuatLapTrinh/listStudentFinal.txt", ios::out);
	for (int i = 0; i < n; i++)
	{
		f1 << a[i].id << "," << a[i].fullName << "," << a[i].birthDay.day << "/" << a[i].birthDay.month << "/" << a[i].birthDay.year << "," << a[i].math << "," << a[i].physics 
			<< "," << a[i].chemistry << "," << a[i].total << "\n";
	}
	f1.close();*/
	doSomething(185617);
	cout << endl;
	return 0;
}