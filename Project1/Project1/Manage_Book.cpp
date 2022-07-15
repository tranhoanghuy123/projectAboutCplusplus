#define _CRT_SECURE_NO_WARNINGS
#include "Methods.h"
#pragma execution_character_set( "utf-8" )

/*
*	TASK:
* + Khai báo Struct Book gồm:
*	+ Mã sách : string ---> 2 hướng: 1 là tự động 2 lại nhập( không được trùng nhau)
*	+ Tên Sách: string
*	+ Thể loại
*	+ Ngày xuất bản: Date 
*	+ Ngày Nhập Sách: Date
*	+ Ngày Bán Sách: Date
*	+ Gía  Sách NHẬP: kiểu số nguyên dương
*	+ Gía  Sách Bán ra: kiểu số nguyên dương
*	+ số lượng sách Nhập vào: kiểu short
*	+ số lượng sách bán ra: kiểu short
*	+ Lợi Nhuận = Số lượng từng sách *( giá bán - giá nhập)
*	+ Số lượng sách tồn kho = Nếu ngày hiện tại > ngày nhập = 365 ---> tìm số lượng sách còn tồn
* + Nhập / Xuất Danh Sách có trong cửa hàng ( chia ra 2 đối tượng dùng: nếu là admin ( phải login bằng username Password của admin) --> show tất cả; 
	nếu là khách (kg đăng nhập) thì không show Lợi nhuận + sl sách nhập vào + giá sách nhập + ngày nhập sách + các chức năng thêm xóa sửa của 1 sách và người dùng có chức năng mua sách
* + Tìm sách theo: 
*		+ Mã
*		+ Tên
*		+ Thể Loại
*		+ ngày xuất bản
*		+ Gía sách bán
*		+ giá sách nhập
*  + Thêm 1 sách vào danh sách (admin)
*  + Xóa 1 quyển sách bằng mã (admin)
*  + Sắp xếp danh sách tăng dần theo:
*		+ Mã
*		+ Tên
*		+ Ngày xuất bản
*		+ Gía sách bán 
*  + Mua sách
*  + Sửa thông tin của sách (admin)
*  + Lưu danh sách cuối cùng ra file (admin)
* 
*/	
string userAdmin[2] =
{
	"admindeptrai",
	"123456"
}; // tài khoản admin
struct IdOfBook
{
	string header; // có thể thêm thành phần body 
	string footer;
};
struct Book
{
	IdOfBook id;
	char name[50];
	char category[20];
	string IdOfcategory;
	int costSoldOut{};
	int theNumberOfBooksRemaining{};
	Date publishing{};
	Date dateSell{};
	Date dateImport{};
	int costImport{};
	int profit{};
	int theNumberOfBooksImports{};
	int theNumberOfBooksSoldOut{};
	int inventoryNumber{};
};
Book pushInforOfOneBook(Book& book)
{
	SetConsoleOutputCP(65001);
	//setvbuf(stdout, nullptr, _IOFBF, 1000);
	short temp;
	cout << setw(8) << "" << "Nhập Tên Sách: "; cin.getline( book.name,50); 
	cout << setw(8) << "" << "Nhập Thể Loại: "; cin.getline(book.category,40);
	cout << setw(8) << "" << "Nhập Mã Thể Loại: "; getline(cin,book.IdOfcategory); 
	cout << setw(8) << "" << "Nhập Giá Sách Bán Ra: "; cin>>book.costSoldOut; cin.ignore();
	cout << setw(8) << "" << "Nhập Ngày Xuất Bản!\n"; input_date(book.publishing); //book.customer.publishing.day = book.publishing.day; book.customer.publishing.month = book.publishing.month; book.customer.publishing.year = book.publishing.year; cin.ignore();
	cout << setw(8) << "" << "Nhập Ngày Bán Ra! \n"; input_date(book.dateSell); 
	cout << setw(8) << "" << "Nhập Ngày Nhập Vào! \n"; input_date(book.dateImport); 
	cout << setw(8) << "" << "Nhập Giá Nhập Vào: "; cin >> book.costImport;
	cout << setw(8) << "" << "Nhập Số Lượng Sách Nhập Vào: "; cin >> book.theNumberOfBooksImports;
	book.theNumberOfBooksSoldOut = 0;
	book.profit = (book.costSoldOut - book.costImport) * book.theNumberOfBooksSoldOut;
	temp = book.theNumberOfBooksImports - book.theNumberOfBooksSoldOut;
	book.theNumberOfBooksRemaining = temp;
	if (distance_two_date(book.dateImport, book.dateSell) > 365 && temp > 0)
	{
		book.inventoryNumber = temp;
	}
	else
	{
		if (temp < 0)
		{
			book.theNumberOfBooksRemaining = 0;
		}
		book.inventoryNumber = 0;
	}
	cin.ignore();
	return book;
}
void pushInforOfBooks(fstream &f1, int lenght)
{
	SetConsoleOutputCP(65001);
	//setvbuf(stdout, nullptr, _IOFBF, 1000);
	Book book;
	f1.open("listBook.txt", ios::out | ios::binary);
	for (int i = 0; i < lenght; i++)
	{
		cout << "Nhập Sách Thứ " << i + 1 << endl;
		book = pushInforOfOneBook(book);
		book.id.header = book.IdOfcategory;
		book.id.footer = to_string(10+i);
		f1.write((char*)(&book), sizeof(book));
	}
	f1.close();
}
bool readFileToListBooks(fstream& f1, Book list[],  int& lenght)
{
	SetConsoleOutputCP(65001);
	//setvbuf(stdout, nullptr, _IOFBF, 1000);
	lenght = 0;
	f1.open("listBook.txt", ios::in | ios::binary);
	if (!f1)
	{
		cout << "ERROR: Undefined File!\n";
	}
	else
	{
		while (f1.read((char*)(&list[lenght]), sizeof(list[lenght])))
		{
			lenght++;
			//cout << "Doc Thanh Cong!\n";
		}
		return true;
	}
	f1.close();
	return false;
}
void titleOfCustomer()
{
	SetConsoleOutputCP(65001);
	cout << setw(15) << left << "Mã Sách" << setw(40) << left << "Tên Sách" << setw(20) << left << "Thể Loại" << setw(20) << left << "Ngày Xuất Bản" << setw(15) << left << "Giá Sách" << setw(12)
		<< left << "Số Lượng";
}
void printOneBookForCustomer(Book book)
{
	SetConsoleOutputCP(65001);
	cout << setw(15) << left << book.id.header + book.id.footer << setw(40) << left << book.name << setw(20) << left << book.category << setw(20);
	output_date(book.publishing); cout << setw(15) << left << book.costSoldOut << setw(12) << left << book.theNumberOfBooksRemaining;
}
void printListBooksForCustomer(Book list[], int lenght)
{
	titleOfCustomer();
	cout << endl << endl;
	for (int i = 0; i < lenght; i++)
	{
		printOneBookForCustomer(list[i]);
		cout << endl << endl;
	}
}
void titleOfAdmin()
{
	SetConsoleOutputCP(65001);
	titleOfCustomer();
	cout << setw(20) << left << "Ngày Nhập Vào" << setw(20) << left << "Ngày Bán Ra" << setw(12) << left << "Giá Nhập" << setw(12) << left << "Lợi Nhuận" << setw(12) << left << "SL Nhập"
		<< setw(12) << left << "SL Bán" << setw(12) << left << "Tồn Kho";
}
void printOneBooksForAdmin(Book book)
{
	printOneBookForCustomer(book);
	cout << setw(20) ; output_date(book.dateImport);
	cout << setw(20) ; output_date(book.dateSell);
	cout << left << book.costImport << setw(12) << left << book.profit << setw(12) << left << book.theNumberOfBooksImports << setw(12) << left << book.theNumberOfBooksSoldOut
		<< setw(12) << left << book.inventoryNumber;
}
void printListBooksForAdmin(Book list[],int lenght)
{
	titleOfAdmin();
	cout << endl;
	for (int i = 0; i < lenght; i++)
	{
		printOneBooksForAdmin(list[i]);
		cout << endl;
	}

}
//+ Tìm sách theo :
//*+Mã
//* +Tên
//* +Thể Loại
//* +ngày xuất bản
//* +Gía sách bán
//* +giá sách nhập // admin
//* +Thêm 1 sách vào danh sách(admin)
//* +Xóa 1 quyển sách bằng mã(admin)
//* +Sắp xếp danh sách tăng dần theo :
//*		+Mã
//*		+Tên
//*		+Ngày xuất bản
//*		+Gía sách bán
//* +Mua sách
//* +Sửa thông tin của sách(admin)
//* +Lưu danh sách cuối cùng ra file(admin)
int searchedBookById(Book list[], int lenght, string idSearching)
{
	string idOfBook;
	for (int i = 0; i < lenght; i++)
	{
		idOfBook = list[i].id.footer + list[i].id.header;
		if (idOfBook.compare(idSearching) == 0)
		{
			return i;
		}
	}
	return -1; // Not Found
}
int searchedBookByName(Book list[], int lenght, char nameSearching[50])
{
	for (int i = 0; i < lenght; i++)
	{
		if (_stricmp(list[i].name,nameSearching) == 0)
		{
			return i;
		}
	}
	return -1; // Not Found
}
bool searchedBookByPublishing(Book list[], int lenght, Date dateNeedToSearch)
{
	titleOfCustomer();
	bool flag = false;
	for (int i = 0; i < lenght; i++)
	{
		if (list[i].publishing.day == dateNeedToSearch.day && list[i].publishing.month == dateNeedToSearch.month && list[i].publishing.year == dateNeedToSearch.year)
		{
			printOneBookForCustomer(list[i]);
			flag = true;
		}
	}
	return flag;
}
void searchedBookByCostExport(Book list[], int lenght, int costExport)
{
	titleOfCustomer();
	for (int i = 0; i < lenght; i++)
	{
		if (list[i].costSoldOut == costExport)
		{
			printOneBookForCustomer(list[i]);
		}
	}
}
void searchedBookByCostImport(Book list[], int lenght, int costImport)
{
	titleOfCustomer();
	for (int i = 0; i < lenght; i++)
	{
		if (list[i].costImport == costImport)
		{
			printOneBooksForAdmin(list[i]);
		}
	}
}
void addItem(Book list[], int &lenght, Book value,int position)
{
	insert<Book>(list, lenght, position, value);
}
bool deletedItemById(Book list[], int& lenght, string idNeedToDelete)
{
	int position = searchedBookById(list, lenght, idNeedToDelete);
	if (position != -1)
	{
		del<Book>(list, position, lenght);
		return true;
	}
	return false;
}
bool buyItem(Book list[], int lenght, int amout,string idOfBookNeedToBuy)
{
	int position = searchedBookById(list, lenght, idOfBookNeedToBuy);
	if (position != -1 && amout < list[position].theNumberOfBooksRemaining)
	{
		list[position].theNumberOfBooksSoldOut += amout;
		list[position].theNumberOfBooksRemaining -= amout;
		return true;
	}
	return false;
}
void menuOfSorting()
{
	SetConsoleOutputCP(65001);
	cout << setw(10) << left << "" << "********************************************************************\n";
	cout << setw(11) << right << "*" << setw(11) << left << "" << setw(55) << left << "Danh Mục Sắp Xếp" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(46) << left << " 1.Sắp Xếp Tăng Dần Theo Mã" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(46) << left << " 2.Sắp Xếp Tăng Dần Theo Tên" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(46) << left << " 3.Sắp Xếp Tăng Dần Theo Ngày Xuất Bản" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(46) << left << " 4.Sắp Xếp Tăng Dần Theo Gía Bán" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(46) << left << " 5.Sắp Xếp Giảm Dần Theo Gía Bán" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(10) << left << "" << "********************************************************************\n";
}
void sortedListBooks(Book list[], int lenght,int &methods)
{
	SetConsoleOutputCP(65001);
	/*
	* 1 : SX theo mã
	* 2 : SX theo tên
	* 3 : SX theo Ngày Xuất Bản
	* 4 : SX theo Gía
	* 5:  SX GIẢM DẦN theo giá 
	*/
	string idOfBook;
	system("CLS");
	menuOfSorting();
	cout << setw(15) << left << "" << "Nhập Lựa Chọn Của Bạn: "; cin >> methods;
	cin.ignore();
	switch (methods)
	{
	case 1:
		for (int i = 0; i < lenght - 1; i++)
		{
			idOfBook = list[i].id.header + list[i].id.footer;
			for (int j = i + 1; j < lenght; j++)
			{
				if (idOfBook > (list[j].id.header + list[j].id.footer))
				{
					swap(list[i], list[j]);
				}
			}
		}
		system("CLS");
		printListBooksForCustomer(list, lenght);
		break;
	case 2:
		for (int i = 0; i < lenght -1; i++)
		{
			for (int j = i + 1; j < lenght; j++)
			{
				if (strcmp(list[i].name, list[j].name) > 0)
				{
					swap(list[i], list[j]);
				}
			}
		}
		system("CLS");
		printListBooksForCustomer(list, lenght);
		break;
	case 3:
		for (int i = 0; i < lenght - 1; i++)
		{
			for (int j = i + 1; j < lenght; j++)
			{
				if (index_of_day_ver2(list[i].publishing) > index_of_day_ver2(list[j].publishing))
				{
					swap(list[i], list[j]);
				}
			}
		}
		system("CLS");
		printListBooksForCustomer(list, lenght);
		break;
	case 4: 
		for (int i = 0; i < lenght - 1; i++)
		{
			for (int j = i + 1; j < lenght; j++)
			{
				if (list[i].costSoldOut > list[j].costSoldOut)
				{
					swap(list[i], list[j]);
				}
			}
		}
		system("CLS");
		printListBooksForCustomer(list, lenght);
		break;
	case 5:
		for (int i = 0; i < lenght - 1; i++)
		{
			for (int j = i + 1; j < lenght; j++)
			{
				if (list[i].costSoldOut < list[j].costSoldOut)
				{
					swap(list[i], list[j]);
				}
			}
		}
		system("CLS");
		printListBooksForCustomer(list, lenght);
		break;
	default: cout << setw(8) << left << "" << "Phương Thức Sắp Xếp Không Hợp Lệ! \n";
		break;
	}
}
bool saveListBooksToFile(fstream& fileSave, Book list[], int lenght,string filePath)
{
	fileSave.open(filePath, ios::out | ios::binary);
	if (!fileSave)
	{
		return false;
	}
	for (int i = 0; i < lenght; i++)
	{
		fileSave.write((char*)(&list[i]), sizeof(list[i]));
	}
	fileSave.close();
	return true;
}
void menuOfCustomer()
{
	SetConsoleOutputCP(65001);
	cout << setw(10) << left << "" << "********************************************************************\n";
	cout << setw(11) << right << "*" <<setw(11)<<left<<""<<setw(70)<<left<< "Chào Mừng Quý Khách Đến Với Cửa Hàng Bán Sách" <<"*"<< endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(51) << left << " 1.Xem Danh Sách Các Loại Sách" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(47) << left << " 2.Mua Sách" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(51) << left << " 3.Sắp Xếp Sách" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(49) << left << " 4.Tìm Sách Theo Mã" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(10) << left << "" << "********************************************************************\n";
}

void menuOfAdmin()
{
	SetConsoleOutputCP(65001);
	cout << setw(10) << left << "" << "********************************************************************\n";
	cout << setw(11) << right << "*" << setw(15) << left << "" << setw(55) << left << "Đây Là Trang Dành Cho Administrator!" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(53) << left << " 1.Nhập Danh Sách Các Loại Sách" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(52) << left << " 2.Đọc Danh Sách Từ File" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(49) << left << " 3.Xem Thông Tin Sách Có Trong Kho" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(51) << left << " 4.Thêm 1 loại Sách Vào Kho" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(53) << left << " 5.Xoá 1 Loại Sách Trong Kho Bằng Mã" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(52) << left << " 6.Sửa Thông Tin Của Sách" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(48) << left << " 7.Lưu Danh Sách Ra File" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(10) << left << "" << "********************************************************************\n";
}
void menuHome()
{
	SetConsoleOutputCP(65001);
	cout << setw(10) << left << "" << "********************************************************************\n";
	cout << setw(11) << right << "*" << setw(10) << left << "" << setw(56) << left << "CHÀO MỪNG BẠN ĐẾN VỚI TRANG CHỦ CỦA HỆ THỐNG!           " << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(51) << left << " 1.Bạn Là Khách Hàng" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(11) << right << "*" << setw(20) << left << "" << setw(49) << left << " 2.Bạn Là Administrator" << "*" << endl;
	cout << setw(11) << right << "*" << setw(66) << "" << "*" << endl;
	cout << setw(10) << left << "" << "********************************************************************\n\n";
}
void formRegister(string& username, string &password)
{
	string confirmPassword;
	auto captcha =0;
	SetConsoleOutputCP(65001);
	cout << endl;
again:	cout << setw(15) << right << "" << "----------------------------------------\n";
	cout << setw(16) << right << "|"<<""<< setw(11) << left << "" << "Đăng Ký Tài Khoản"<<setw(11)<<right<<"|" << endl;
	cout << setw(15) << right << "" << "----------------------------------------\n";
	cout << setw(15) << right << "" <<setw(23)<<left<< "Tên Tài Khoản: "; cin >> username;
	cout << setw(15) << right << "" << "----------------------------------------\n";
	cout << setw(15) << right << "" << setw(23) << left << "Mật Khẩu: "; cin >> password;
	cout << setw(15) << right << "" << "----------------------------------------\n";
	cout << setw(15) << right << "" << setw(25) << left << "Xác Nhận Mật Khẩu: "; cin >> confirmPassword;
	cout << setw(15) << right << "" << "----------------------------------------\n";
	captcha = rand() % 90000 + 10000;
	cout << setw(15) << right << "" <<setw(23)<< left << "Mã Xác Nhận: " << captcha << endl;
	if (password != confirmPassword)
	{
		cout << setw(15) << right << "" << setw(25) << left << "Mật Khẩu Không Trùng Khớp! Đăng Ký Lại \n";
		Sleep(2000);
		system("CLS");
		goto  again;
	}
	cout << setw(15) << right << "" << "----------------------------------------\n";
}
void formLogin(string &username,string &password)
{
	SetConsoleOutputCP(65001);
	cout << setw(15) << right << "" << "----------------------------\n";
	cout << setw(25) << left << "" << "Đăng Nhập" << endl;
	cout << endl;
	cout << setw(15) << right << "" << "Username: "; cin >> username;
	cout << endl;
	cout << setw(15) << right << "" << "Password: "; cin >> password;
	cout << setw(15) << right << "" << "----------------------------\n";
	system("CLS");
}
void ClearScrollback()
{
	cout << "\x1B[3J\x1B[H";
}
void loading()
{
	cout << setw(20) << left << "" << "Chờ Một Chút Nhé!\n\n";
	cout << setw(26) << setfill(' ') << "" << "Loading ";
	for (int i = 0; i < 3; i++)
	{
		Sleep(1000);
		cout << ".";
	}
}
bool loginAdmin(string &username, string &password)
{
	SetConsoleOutputCP(65001);
	auto  countFailLogin = 0;
	auto waitTimes = 0;
		do
		{
			formLogin(username, password);
			if (username != userAdmin[0] || password != userAdmin[1])
			{
				cout << setw(15) << left << "" << "Sai Tài Khoản Hoặc Mật Khẩu! Đăng Nhập Lại." << endl << endl;
				countFailLogin++;
				cout << setw(15) << left << "" << "Bạn Còn " << 5 - countFailLogin << " Lượt Đăng Nhập Nữa" << endl << endl;
			}
			if (countFailLogin == 5)
			{ 
				cout << setw(15) << left << "" << "Đăng Nhập Thất Bại Quá Nhiều! Chờ 15s Để Tiếp Tục.\n\n";
				Sleep(1000);
				system("CLS");
				waitTimes++;
				if (waitTimes == 3)
				{
					cout << endl;
					cout << setw(15) << left << "" << "Bạn Đã Đăng Nhập Thất Bại Qúa Nhiều! Bạn Không Thể Đăng Nhập Nữa. Bạn Sẽ Là Khách Hàng!\n";
					Sleep(5000);
					return false;
				}
				for (int i = 0; i < 15; i++)
				{

					Sleep(1000);
					cout << setw(10) << left << "" << setw(20) << right << "Thời Gian Còn " << setw(2) << 15 - i << "s Nữa";
					ClearScrollback();
				}
				countFailLogin = 0;	
			}
		} while (username != userAdmin[0] || password != userAdmin[1]);
		return true;
}

int main()
{
	SetConsoleOutputCP(65001);
	//setvbuf(stdout, nullptr, _IOFBF, 1000);
	Book list[20];
	Book value;
	fstream f1;
	int lenght = 0,optionHome,optionAdmin,OptionCustomer;
	int amoutOfNeedingToBuy;
	int position;
	int  method;
	int pos;
	char checkContinueMain{};
	char checkContinueCustomer{};
	char checkContinueAdmin{};
	string username, password;
	string idOfBookNeedToBuy;
	string idNeedToDelete;
	do
	{
		system("CLS");
		menuHome();
		cout << setw(10) << left << "" << "Lựa Chọn Của Bạn ---------> "; cin >> optionHome; cin.ignore();
		system("CLS");
		switch (optionHome)
		{
		jump:	case 1: 
			do
			{
				system("CLS");
				menuOfCustomer();
				cout << setw(10) << left << "" << "Lựa Chọn Của Bạn ---------> "; cin >> OptionCustomer; cin.ignore();
				switch (OptionCustomer)
				{
				case 1:
					if (lenght == 0)
					{
						cout << setw(15) << left << "" << "Danh Sách Đang Trống! Chờ Admin Thêm Sách.\n";
					}
					else
					{
						printListBooksForCustomer(list, lenght);
					}
					break;
				case 2:
					printListBooksForCustomer(list, lenght);
					cout << endl;
					cout << setw(15) << left << "" << "Nhập Mã Sách Cần Mua: "; cin >> idOfBookNeedToBuy; cin.ignore();
					if (searchedBookById(list, lenght, idOfBookNeedToBuy) == -1)
					{
						cout << setw(15) << left << "" << "Không Tồn Tại Sách Cần Mua!\n\n";
					}
					else
					{
						cout << setw(15) << left << "" << "Nhập Số Lượng Sách Cần Mua: "; cin >> amoutOfNeedingToBuy; cin.ignore();
						if (buyItem(list, lenght, amoutOfNeedingToBuy, idOfBookNeedToBuy))
						{
							cout << setw(15) << left << "" << "Đã Mua Sách Thành Công!\n";
						}
						else
						{
							cout << setw(15) << left << "" << "Mua Sách Thất Bại!\n";
						}
					}
					break;
				case 3:
					sortedListBooks(list, lenght, method); break;
				case 4:
					cout << setw(15) << left << "" << "Nhập Mã Sách Cần Tìm: "; cin >> idOfBookNeedToBuy; cin.ignore();
					pos = searchedBookById(list, lenght, idOfBookNeedToBuy);
					if (pos != -1)
					{
						titleOfCustomer();
						printOneBookForCustomer(list[pos]);
					}
					else
					{
						cout << setw(15) << left << "" << "Không Tồn Tại Sách Cần Tìm!\n\n";
					}
					break;
				default:cout << setw(15) << left << "" << "Lựa Chọn Không Hợp Lệ!\n\n";
					break;
				}
					cout << setw(10) << left << "" << "Quý Khách Muốn Tiếp Tục? Y/N ---------> "; cin >> checkContinueCustomer; cin.ignore();
					if (checkContinueCustomer != 'Y' && checkContinueCustomer != 'y')
					{
						cout << endl;
						cout << setw(10) << left << "" << "TẠM BIỆT QUÝ KHÁCH. CẢM ƠN ĐÃ ỦNG HỘ SHOP!" << endl;
					}
			} while (checkContinueCustomer == 'Y' || checkContinueCustomer == 'y');
			break;
		case 2: 
			if (loginAdmin(username, password))
			{
				system("CLS");
				cout << endl;
				cout << setw(25) << left << "" << "Chào Mừng Bạn Đến Với Trang Dành Cho Administrator!\n\n";
				Sleep(1000);
				loading();
				cout << endl;
				do
				{
					system("CLS");
					menuOfAdmin();
					cout << setw(15) << left << "" << "Nhập Lựa Chọn Của Bạn: "; cin >> optionAdmin; cin.ignore();
					switch (optionAdmin)
					{
					case 1:
						cout << setw(15) << left << "" << "Nhập Số Lượng Cần Thêm Vào: "; cin >> lenght; cin.ignore();
						pushInforOfBooks(f1, lenght);
						break;
					case 2:
						if (readFileToListBooks(f1, list, lenght))
						{
							cout << setw(20) << left << "" << "Đọc File Thành Công!\n\n";
						}
						else
						{
							cout << setw(20) << left << "" << "Đọc File Thật Bại!\n\n";
						}
						break;
					case 3:
						printListBooksForAdmin(list, lenght);
						break;
					case 4:
						value = pushInforOfOneBook(value);
						cout << setw(15) << left << "" << "Nhập Vị Trí Cần Thêm: "; cin >> position; cin.ignore();
						addItem(list, lenght, value, position);
						break;
					case 5:

						cout << setw(15) << left << "" << "Nhập Mã Sách Cần Xoá: "; cin >> idNeedToDelete; cin.ignore();
						deletedItemById(list, lenght, idNeedToDelete);
						break;
					default:cout << setw(15) << left << "" << "Lựa Chọn Không Hợp Lệ!\n\n";
						break;
					}
						cout << setw(10) << left << "" << "Bạn Muốn Tiếp Tục Phần Của Admin? Y/N ---------> "; cin >> checkContinueAdmin; cin.ignore();
						if (checkContinueAdmin != 'Y' && checkContinueAdmin != 'y')
						{
							cout << endl;
							cout << setw(10) << left << "" << "KẾT THÚC PHIÊN LÀM VIỆC CỦA ADMIN!" << endl;
						}
				} while (checkContinueAdmin == 'Y' || checkContinueAdmin == 'y');	
			} 
			else
			{
				goto jump;
			}
			break;
		default:cout << setw(15) << left << "" << "Lựa Chọn Không Hợp Lệ!\n\n";
			break;
		}
		cout << setw(10) << left << "" << "Bạn Muốn Tiếp Tục Chương Trình Chính? Y/N ---------> "; cin >> checkContinueMain; cin.ignore();
		if (checkContinueMain!= 'Y' && checkContinueMain != 'y')
		{
			cout << endl;
			cout << setw(10) << left << "" << "KẾT THÚC CHƯƠNG TRÌNH!" << endl;
		}
	} while (checkContinueMain == 'Y' || checkContinueMain == 'y');
	
	
	//cout << "Đây Là Tiếng Việt \n";
	/*string username;
	string password;
	formRegister(username, password);*/
//for (int i = 0; i < 10; i++)
//{
//	cout << rand() % 90000 + 10000 << endl;
//	
//}
	//loading();
	cout << endl;
	return 0;
}