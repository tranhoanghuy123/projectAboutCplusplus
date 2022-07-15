#pragma once
#include "Methods.h"
void displayPassword(string& pass)
{
	pass = "";
	char ch;
	ch = _getch();
	while (ch != 13) {//character 13 is enter
		pass.push_back(ch);
		cout << '*';
		ch = _getch();
	}
	cout << endl;
}
void ClearScrollback()
{
	cout << "\x1B[3J\x1B[H";
}
void loading()
{
	cout << endl;
	cout << setw(20) << left << "" << "Chờ Một Chút Nhé!\n\n";
	cout << setw(26) << setfill(' ') << "" << "Loading ";
	for (int i = 0; i < 3; i++)
	{
		Sleep(1000);
		cout << ".";
	}
}
auto getCaptcha()
{
	auto captcha = rand() % 90000 + 10000;
	return captcha;
}

bool checkLogin(string user[], string username, string password, int lenght)
{
	for (int index = 0; index < lenght; index++)
	{
		if (username == user[index] && password == user[index + 1])
		{
			return true;
		}
	}
	return false;
}
bool checkUsername(string user[], string username, int lenght)
{
	for (int i = 0; i < lenght; i += 2)
	{
		if (user[i] == username)
		{
			return true;
		}
	}
	return false;
}
void readFile(fstream& fileOfUser, string user[], int& lenght)
{
	lenght = 0;
	fileOfUser.open("Accounts.txt", ios::in);
	while (fileOfUser >> user[lenght])
	{
		lenght++;
	}
	fileOfUser.close();
}
void formRegister(fstream& user, string& username, string& password)
{

	user.open("Accounts.txt", ios::app);
	fstream temp;
	string tempUser[100];
	auto index = 0;
	readFile(temp, tempUser, index);
	string confirmPassword;
	auto inputCaptcha = 0;
	SetConsoleOutputCP(65001);
	cout << endl;
again:	cout << setw(15) << right << "" << "----------------------------------------\n";
	cout << setw(16) << right << "|" << "" << setw(11) << left << "" << "Đăng Ký Tài Khoản" << setw(11) << right << "|" << endl;
	cout << setw(15) << right << "" << "----------------------------------------\n";
	cout << setw(15) << right << "" << setw(23) << left << "Tên Tài Khoản: "; cin >> username;
	cout << setw(15) << right << "" << "----------------------------------------\n";
	if (checkUsername(tempUser, username, index))
	{
		cout << setw(15) << left << "" << "Tài Khoản Đã Tồn Tại! Đăng Ký Lại" << endl;
		loading();
		system("CLS");
		goto again;
	}
	cout << setw(15) << right << "" << setw(23) << left << "Mật Khẩu: "; displayPassword(password);
	cout << setw(15) << right << "" << "----------------------------------------\n";
	cout << setw(15) << right << "" << setw(25) << left << "Xác Nhận Mật Khẩu: "; displayPassword(confirmPassword);
	if (password != confirmPassword)
	{
		cout << setw(15) << right << "" << setw(25) << left << "Mật Khẩu Không Trùng Khớp! Đăng Ký Lại \n";
		cout << endl;
		loading();
		//Sleep(2000);
		system("CLS");
		goto  again;
	}
captcha:	cout << setw(15) << right << "" << "----------------------------------------\n";
	int  captcha = getCaptcha();
	cout << setw(15) << right << "" << setw(23) << left << "Mã Xác Nhận: " << captcha << endl;
	cout << setw(15) << right << "" << "----------------------------------------\n";
	cout << setw(15) << right << "" << setw(23) << left << "Nhập Mã Xác Nhận: "; cin >> inputCaptcha;
	cout << setw(15) << right << "" << "----------------------------------------\n";

	if (captcha != inputCaptcha)
	{
		cout << endl;
		cout << setw(15) << right << "" << setw(23) << left << "Mã Xác Nhận Không Đúng! Nhập Lại.\n";
		//ClearScrollback();
		goto captcha;
	}
	user << username << " " << password << " ";
	user.close();
}
void formLogin(string& username, string& password)
{
	SetConsoleOutputCP(65001);
	cout << setw(15) << right << "" << "----------------------------\n";
	cout << setw(25) << left << "" << "Đăng Nhập" << endl;
	cout << endl;
	cout << setw(15) << right << "" << "Username: "; cin >> username;
	cout << setw(15) << right << "" << "----------------------------\n";
	cout << setw(15) << right << "" << "Password: "; displayPassword(password);
	cout << setw(15) << right << "" << "----------------------------\n";
	system("CLS");
}

bool login(string user[], string& username, string& password, int lenght)
{
	SetConsoleOutputCP(65001);
	auto  countFailLogin = 0;
	auto waitTimes = 0;
	do
	{
		formLogin(username, password);
		if (!checkLogin(user, username, password, lenght))
		{
			loading();
			system("CLS");
			cout << endl << endl;
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
				//cout << endl;
				cout << setw(15) << left << "" << "Bạn Đã Đăng Nhập Thất Bại Qúa Nhiều! Bạn Không Thể Đăng Nhập Nữa.\n";
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
	} while (!checkLogin(user, username, password, lenght));
	return true;
}

void menu()
{
	SetConsoleOutputCP(65001);
	cout << setw(15) << left << "" << "***************************************\n";
	cout << setw(16) << right << "*" << setw(37) << left << "" << "*" << endl;
	cout << setw(16) << right << "*" << setw(25) << left << "      1.Đăng Ký " << setw(19) << left << "2.Đăng Nhập" << "*" << endl;
	cout << setw(16) << right << "*" << setw(37) << left << "" << "*" << endl;
	cout << setw(16) << right << "*" << setw(37) << left << "" << "*" << endl;
	cout << setw(15) << left << "" << "***************************************\n\n";
}