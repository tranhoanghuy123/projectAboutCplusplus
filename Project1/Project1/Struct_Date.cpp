#define  _CRT_SECURE_NO_WARNINGS
#include"Methods.h"
//COMMENT 1 ĐOẠN CODE: BÔI ĐEN ĐOẠN CODE --> ẤN CTRL + K + C
//UNCOMMENT 1 ĐOẠN CODE: BÔI ĐEN ĐOẠN CODE --> ẤN CTRL + K + U
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
short int date[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
short int date_of_month(Date d)
{
	if (check_year(d.year))
	{
		date[2] = 29;
	}
	return date[d.month];
}
void input_date(Date& d)
{
	do
	{
		cout << "Nhap thang: "; cin >> d.month;

	} while (d.month < 1 || d.month > 12);
	do
	{
		cout << "Nhap nam: "; cin >> d.year;
	} while (d.year < 1);
	do
	{
		cout << "Nhap ngay: "; cin >> d.day;
	} while (d.day > date_of_month(d) || d.day <= 0);
}
void output_date(Date d)
{
	cout << d.day << "/" << d.month << "/" << d.year << endl;
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
int indexOfDayLoop(Date a)
{
	int index = 0;
	for (int i = 1; i < a.year; i++)
	{
		if (check_year(i))
			index += 366;
		else
			index += 365;
	}
	return index + index_of_day(a);
}
 int index_of_day_ver2(Date d) // Tính số thứ tự ngày kể từ ngày 1/1/1
{
	 d.year--;
	 int temp = d.year * 365 + index_of_day(d);
	 return temp + countLeapYears(d);
}
//int find_day(Date d, int index) //. Tìm ngày khi biết năm và số thứ tự của ngày trong năm
// {
//	int temp = 0;
//	int i = 1;
//	if (check_year(d.year))
//	{
//		date[2] = 29;
//	}
//	while (temp < index)
//	{
//		temp += date[i];
//		i++;
//	}
//	return date[i-1] - (temp - index);
// }
Date findDay(int year, int index)
{
	Date find;
	int temp = 0,i=1;
	find.year = year;
	if (check_year(year))
	{
		date[2] = 29;
	}
	while (temp < index)
	{
		temp += date[i];
		++i;
	}
	--i;
	find.month = i;
	find.day = date[i] - (temp - index);
	return find;
}
Date find_day_ver2(int &index) // Tìm ngày khi biết số thứ tự ngày kể từ ngày 1/1/1
{
	Date find2;
	int i = 1;
	while (index > 365)
	{
		if (check_year(i))
		{
			index -= 366;
		}
		else
		{
			index -= 365;
		}
		i++;
	}
	find2 = findDay(i, index);
	return find2;
}
Date next_day(Date d)
{
	Date nextDay;
	nextDay.day = d.day + 1;
	nextDay.month = d.month;
	nextDay.year = d.year;
	if (nextDay.day  > date_of_month(d))
	{
		nextDay.day = 1;
		nextDay.month = d.month + 1;
		nextDay.year = d.year + 1;
		if (nextDay.month > 12)
		{
			nextDay.month = 1;
			nextDay.year = d.year + 1;
		}
	}
	output_date(nextDay);
	return nextDay;
}
Date previous_day(Date d)
{
	Date preDay;
	preDay.day = d.day - 1;
	preDay.month = d.month;
	preDay.year = d.year;
	if (preDay.day == 0)
	{
		preDay.month -= 1;
		if (preDay.month == 0)
		{
			preDay.day = 31;
			preDay.month = 12;
			preDay.year -= 1;
		}
		else
		{
			preDay.day = date_of_month(preDay);
		}
	}
	output_date(preDay);
	return preDay;
}
Date next_k_day(Date d, int k)
{
	Date nextKDay;
	nextKDay.day = d.day + k;
	nextKDay.month = d.month;
	nextKDay.year = d.year;
	while (nextKDay.day > date_of_month(nextKDay))
	{
		nextKDay.day -= date_of_month(nextKDay);
		++nextKDay.month;
		if (nextKDay.month > 12)
		{
			nextKDay.month = 1;
			nextKDay.year++;
		}
	}
	output_date(nextKDay);
	return nextKDay;
}
Date previous_k_day(Date d, int k)
{
	Date preKDay;
	preKDay.day = d.day - k;
	preKDay.month = d.month;
	preKDay.year = d.year;
	while (preKDay.day <= 0)
	{
		preKDay.day += date_of_month(preKDay);
		--preKDay.month;
		if (preKDay.month <= 0)
		{
			preKDay.month = 12;
			preKDay.year--;
		}
	}
	output_date(preKDay);
	return preKDay;
}
int distance_two_date(Date d1, Date d2)
{
	//Mô tả: lấy giá trị dương của (số thứ tự ngày 1  - số thứ tự ngày 2) ( tính từ 1/1/1)
	return abs(index_of_day_ver2(d1)-index_of_day_ver2(d2));
}
int calcDayNumFromDate(Date &d)
{
	d.month = (d.month + 9) % 12;
	d.year -= d.month / 10;
	return 365 * d.year + d.year / 4 - d.year / 100 + d.year / 400 + (d.month * 306 + 5) / 10 + (d.day - 1);
	/* m = (m + 9) % 12;
	 y -= m / 10;
	 ul dn = 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (d - 1);

	 return dn;*/
}
string  day_of_week(Date d)
{
	int temp = calcDayNumFromDate(d);
	string dayOfWeek [7] = {
		"Thu Tu",
		"Thu Nam",
		"Thu Sau",
		"Thu Bay",
		"Chu Nhat",
		"Thu Hai",
		"Thu Ba",
	};
	return dayOfWeek[temp%7];
}
void print_menu()
{
	cout << setw(114) << setfill('-') << "" << "\n\n";
	cout << setw(114/2-4) << setfill(' ') << "" << "MENU \n\n";
	cout << setw(55) << left << "1.Nhap/Xuat" << "2.Kiem tra nam nhuan\n";
	cout << setw(55) << left << "3.Tinh so thu tu ngay trong nam" << "4.Tinh so thu tu ngay trong nam tu 1/1/1\n";
	cout << setw(55) << left << "5.Tim ngay  khi biet nam va so thu tu trong nam" << "6.Tim ngay  khi biet nam va so thu tu trong nam tu 1/1/1\n";
	cout << setw(55) << left << "7.Tim ngay ke tiep" << "8.Tim ngay hom qua\n";
	cout << setw(55) << left << "9.Tim ngay ke do k ngay" << "10.Tim ngay truoc do k ngay\n";
	cout << setw(55) << left << "11.Khoang cach giua 2 ngay" << "12.Tinh thu cua ngay\n";
	cout << setw(55) << left << "13.Nhap lai ngay" << "14.EXIT\n";
	cout << setw(114) << setfill('-') << "" << "\n\n";
}
int main()
{
	Date d,d1;
	char checkCont;
	short int select,k,year;
	int index;
	input_date(d);
	do
	{
		system("CLS");
		print_menu();
		do
		{
			cout << "Nhap lua chon cua ban: "; cin >> select;
			if (select < 1 || select > 14)
			{
				cout << "Lua chon khong phu hop. Nhap Lai!\n";
			}
		} while (select < 1 || select > 14);
		switch (select)
		{
		case 1:output_date(d); break;
		case 2:
			if (check_year(d.year))
			{
				cout << "La nam nhuan!\n";
			}
			else
				cout << "Khong la nam nhuan!\n"; break;
		case 3:cout << "So thu tu ngay trong nam: " << index_of_day(d)<<endl; break;
		case 4:cout << "So thu tu ngay : " << index_of_day_ver2(d) << endl; break;
		case 5:
			do
		{
			cout << "Nhap nam can tim: "; cin >> year;
		} while (year < 1);
		if (check_year(year))
		{
			do
			{
				cout << "Nhap so thu tu trong nam: "; cin >> index;
			} while (index < 1 || index > 366);
		}
		else
		{
			do
			{
				cout << "Nhap so thu tu trong nam: "; cin >> index;
			} while (index < 1 || index > 365);
		}
			cout << "Ngay can tim la: "; output_date(findDay(year, index));
			/*cout << "Nhap so thu tu cua ngay: "; cin >> index;
			cout << "Ngay can tim la: " << find_day(d, index) << endl;*/ break;
		case 6:
			do
			{
				cout << "Nhap so thu tu cua ngay: "; cin >> index;
				if (index < 1)
				{
					cout << "Nhap sai. Moi nhap lai!\n";
				}
			} while (index < 1); 
			cout << "Ngay can tim la: ";output_date(find_day_ver2(index)) ; break;
		case 7:cout << "Ngay hien tai: "; output_date(d);
			cout << "Ngay ke tiep la: "; next_day(d); break;
		case 8:cout << "Ngay hien tai: "; output_date(d);
			cout << "Ngay hom qua la: "; previous_day(d); break;
		case 9:  cout << "Nhap so ngay ke tiep: "; cin >> k;
			cout << "Ngay hien tai: "; output_date(d);
			cout << "Ngay ke do k ngay la: "; next_k_day(d, k); break;
		case 10: cout << "Nhap so ngay truoc do: "; cin >> k;
			cout << "Ngay hien tai: "; output_date(d);
			cout << "Ngay truoc do k ngay la: "; previous_k_day(d, k); break;
		case 11:input_date(d1);
			cout << "Ngay thu nhat: "; output_date(d);
			cout << "Ngay thu hai: "; output_date(d1);
			cout << "Khoang cach giua 2 ngay la: " << distance_two_date(d, d1) << endl; break;
		case 12: cout << day_of_week(d) << ", Ngay "; output_date(d); break;
		case 13: input_date(d);
			cout << "Nhap lai thanh cong!\n"; break;
		case 14: exit(0); break;
		}
		cout << "Ban muon tiep tuc? Y/N ------> "; cin >> checkCont;
		if (checkCont != 'y' && checkCont != 'Y')
		{
			cout << endl;
			cout << setw(114 / 2 -8) << setfill(' ') << "" << "Chuong trinh ket thuc!\n";
		}
	} while (checkCont == 'y' || checkCont == 'Y');
	return 0;
}
