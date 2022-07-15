#define _CRT_SECURE_NO_WARNINGS
#define MAX_INPUT_LENGTH 255
#include<iostream>
#include<cmath>
#include<cstring>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>
#include<ctime>
#include <windows.h>
#include <cstdio>
#include<conio.h>
#pragma execution_character_set( "utf-8" )
using namespace std;
struct Date
{
	int day, month, year;
};
const short int dateOfYear = 365;
bool check_year(int year)
{
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
	{
		return true;
	}
	return false;
}
short int date[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
short int date_of_month(Date d)
{
	if (check_year(d.year))
	{
		date[2] = 29;
	}
	return date[d.month];
}
Date input_date(Date& d)
{
	SetConsoleOutputCP(65001);
	do
	{
		cout <<setw(15)<<left<<""<< "Nhập Tháng : "; cin >> d.month;
		if (d.month < 1 || d.month > 12)
		{
			cout << setw(15) << right << "" << "Tháng Không Hợp Lệ. Nhập Lại!\n";
		}

	} while (d.month < 1 || d.month > 12);
	cout << setw(15) << right << "" << "----------------------------------------\n";
	do
	{
		cout << setw(15) << left << "" << "Nhập Năm : "; cin >> d.year;
		if (d.year < 1)
		{
			cout << setw(15) << right << "" << "Năm Không Hợp Lệ. Nhập Lại!\n";
		}
	} while (d.year < 1);
	cout << setw(15) << right << "" << "----------------------------------------\n";
	do
	{
		cout << setw(15) << left << "" << "Nhập Ngày : "; cin >> d.day;
		if (d.day > date_of_month(d) || d.day <= 0)
		{
			cout << setw(15) << right << "" << "Ngày Không Hợp Lệ. Nhập Lại!\n";
		}
	} while (d.day > date_of_month(d) || d.day <= 0);
	cin.ignore();
	return d;
}
void output_date(Date d)
{
	cout << setw(3) << left << d.day << setw(2) << left << "/" << setw(3) << left << d.month
		<< setw(2) << left << "/" << setw(10) << left << d.year;
}
int countLeapYears(Date d)
{
	int years = d.year;
	// Check if the current year needs to be
	//  considered for the count of leap years
	// or not
	if (d.month <= 2)
		years--;
	// An year is a leap year if it
	// is a multiple of 4,
	// multiple of 400 and not a
	 // multiple of 100.
	return years / 4 - years / 100 + years / 400;
}
int index_of_day(Date d)
{
	int index = d.day;
	if (check_year(d.year))
		date[2] = 29;
	for (int i = 1; i < d.month; i++)
	{
		index += date[i];
	}
	return index;
}
int index_of_day_ver2(Date d) // Tính số thứ tự ngày kể từ ngày 1/1/1
{
	d.year--;
	int temp = d.year * 365 + index_of_day(d);
	return temp + countLeapYears(d);
}
int distance_two_date(Date d1, Date d2)
{
	//Mô tả: lấy giá trị dương của (số thứ tự ngày 1  - số thứ tự ngày 2) ( tính từ 1/1/1)
	return abs(index_of_day_ver2(d1) - index_of_day_ver2(d2));
}

void interSort(int a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i +1; j < n; j++)
		{
			if (a[i] > a[j])
			{
				swap(a[i], a[j]);
			}
		}
	}
}
template<class T>
void swap_test(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
void input(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "Nhap phan thu " << i + 1 << ": ";
		cin >> a[i];
	}
}
void output(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << "\t" << a[i];
	}
	cout << endl;
}
char upper(char ch)
{
	//đổi ký tự chữ ra chữ hoa, các ký tự khác giữ nguyên
	if (ch >= 'a' && ch <= 'z')
	{
		ch -= 32;
	}
	return ch;
}
char lower(char ch)
{
	if (ch >= 'a' && ch <= 'z')
	{
		ch += 32;
	}
	return ch;
}
void standard_string(char s[])
{
	// chuẩn chuỗi --> vd có chuỗi "   TrAn    hOaNg   hUy    " --> "Tran Hoang Huy"
	size_t len = strlen(s);
	while (s[0] == ' ')//  xóa ký tự thừa ở đầu chuỗi
	{
		strcpy(s, s + 1);
	}
	while (s[len - 1] == ' ') // xóa ký tự thừa ở cuối
	{
		len--;
		s[len] = '\0';
	}
	for (int i = 0; i < len; ++i)// xóa giữa
	{

		if (s[i] == ' ' && s[i + 1] == ' ')
		{
			for (int j = i; j < len; ++j)
			{
				s[j] = s[j + 1];
			}
			--i;
		}
	}
	_strlwr(s);
	s[0] = upper(s[0]);
	for (int i = 1; i < len; ++i)
	{
		if (s[i] == ' ')
		{
			s[i + 1] = upper(s[i + 1]);
		}
	}
	//cout << s;
}
string inputStringWithUTF8()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	wchar_t wstr[MAX_INPUT_LENGTH];
	char mb_str[MAX_INPUT_LENGTH * 3 + 1];

	unsigned long read;
	void* con = GetStdHandle(STD_INPUT_HANDLE);

	ReadConsole(con, wstr, MAX_INPUT_LENGTH, &read, NULL);

	int size = WideCharToMultiByte(CP_UTF8, 0, wstr, read, mb_str, sizeof(mb_str), NULL, NULL);
	mb_str[size - 1] = 0;
	//cout << strlen(mb_str) << endl;;
	return mb_str;
}
template<class T>
int search(T a[], int n, T key)
{
	int i = 0;
	while (a[i] != key)
	{
		i++;
	}
	if (i > n)
		return -1;
	return i;
}
void sort_row_up(int a[][6], int m, int n)
{
	for (int k = 0; k < m; k++)
		for (int i = 0; i < n - 1; i++)
			for (int j = n - 1; j > i; --j)
				if (a[k][j] < a[k][j - 1])
				{
					swap(a[k][j], a[k][j - 1]);
				}
}
int reverse_num(int n)
{
	int mod, res = 0;
	while (n > 0)
	{
		mod = n % 10;
		res = res * 10 + mod;
		n /= 10;
	}
	return res;
}
int symmetry(int n)
{
	//kiểm tra n có phải là số đối xứng hay ko?
	// số nguyên n gọi là số đối xứng nếu đọc từ trái qua phải, hay từ phải qua trái đều được số giống nhau.ví dụ : 11, 121, 101 là các số đối xứng.
	int sum = 0, mod, temp;
	for (temp = n; n != 0; n = n / 10)
	{
		mod = n % 10;
		sum = sum * 10 + mod;
	}
	if (sum == temp)
		return 1;
	return 0;
}
bool perfect_num(int n)
{
	//kiểm tra 1 số có phải là số hoàn chỉnh hay không?
	 /* +số hoàn chỉnh là một số nguyên dương mà tổng các ước nguyên dương chính thức của nó (số nguyên dương bị nó chia hết ngoại trừ nó) bằng chính nó.
		+nghĩa là 1 số nguyên dương khi tổng các ước của nó (trừ số đó) = chính số đó
		+ quy ước 0: sai; 1: đúng */
	int sum = 0;
	if (n < 0)
		return false;
	for (int i = 1; i <= n / 2; i++)  // giới hạn số lần lặp của 1 vòng lặp vì khi n/i luôn luôn nhỏ hơn hoặc bằng n/2!
	{
		if (n % i == 0)
			sum += i;
	}
	if (sum == n)
		return true;
	return false;
}
int lenght_num(int n)
{
	//trả về chiều dài của một số nguyên.
	int i = 1; // i là biến đếm số n gồm bao nhiêu số !
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return i;
}
bool check_prime(int n)
{
	for (int i = 2; i < sqrt(n); i++)
	{
		if (n % i == 0)
		{
			return false;
		}
	}
	return n > 1;
}
bool check_square_number(int n)
{
	int a = (int)sqrt(n); //biến a lấy kq của căn bậc 2 của n
	if (n < 0)
		return false;
	if (n == a * a)
		return true;
	return false;
}
int times_appear_array(int a[], int n, int key)
{
	int count = 0;
	for (int i = 0; i < n; ++i)
	{
		if (a[i] == key)
			count++;
	}
	return count;
}
int fibo(int n)
{
	if (n == 1 || n == 2)
		return 1;
	return fibo(n - 1) + fibo(n - 2);
}
template<class T>
int locate_final_x(T a[], int n, T key)
{
	for (int i = n - 1; i >= 0; --i)
	{
		if (key == a[i])
			return i;
	}
	return -1;
}
template<class T>
void del(T a[], int index, int& n)
{
	for (int i = index; i < n - 1; ++i)
	{
		a[i] = a[i + 1];
	}
	n--;
}
template<class T>
void insert(T a[], int& n, int pos, T val)
{
	for (int i = n - 1; i > pos; --i)
	{
		a[i] = a[i - 1];
	}
	a[pos] = val;
	//output_array(a, n);
}
template<class T>
void del_all_x(T a[], int n, T x)
{
	for (int i = 0; i < n; ++i)
	{
		if (a[i] == x)
		{
			del(a, i, n);
			--i;
		}
	}
	//output_array(a, n);
}
int gcd(int a, int b)
{
	a=abs(a);
	b=abs(b);
	if (a == 0 || b == 0)
		return a + b;
	while (a != b)
	{
		if (a > b)
		{
			a = a - b;
		}
		else
			b = b - a;
	}
	return a;
	/*
    return b == 0 ? a : gcd(b, a % b); */ // dùng đệ quy tìm ước chung lớn nhất chom tren mang :))
}
int lcm(int a, int b)
{
	a = abs(a);
	b = abs(b);
	return (a / gcd(a, b)) * b;
}
