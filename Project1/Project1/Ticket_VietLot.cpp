#include "LoginAccount.h"
const int freeToken = 100000;
const int costTicket = 10000;
// //------------------------Tỷ Lệ Thắng Giải Thưởng------------------------//
// 
//			JACKPOT			  : THƯỞNG 50 TRIỆU TOKEN --> TRÚNG 6 CẶP SỐ
//			GIẢI NHẤT		  : THƯỞNG 10 TRIỆU TOKEN --> TRÚNG 5 CẶP SỐ
//			GIẢI NHÌ		  : THƯỞNG 3 TRIỆU TOKEN  --> TRÚNG 4 CẶP SỐ
//			GIẢI BA			  : THƯỞNG 500 NGÀN TOKEN --> TRÚNG 3 CẶP SỐ
//			GIẢI KHUYẾN KHÍCH : THƯỞNG 30 NGÀN TOKEN  --> TRÚNG 2 CẶP SỐ
//		
// //------------------------Tỷ Lệ Thắng Giải Thưởng------------------------//
const int jackpot = 50000000;
const int top1 = 10000000;
const int top2 = 3000000;
const int top3 = 500000;
const int top4 = 30000;
struct Player
{
	string id{};
	string fullName{};
	string gender{};
	string username{};
	string password{};
	Date birthday{};
	long long token{};
};
Player setInforAdmin()
{
	Player admin;
	admin.fullName = "ADMIN ĐẸP TRAI";
	admin.id = "000000000";
	admin.birthday.day = 9;
	admin.birthday.month = 9;
	admin.birthday.year = 9999;
	admin.gender = "ADMIN";
	admin.username = "admindeptrai";
	admin.password = "123456";
	admin.token = 9999999999;
	return admin;
}
void clear()
{
	cout << "\x1b[1F\x1B[B";

}
void setResult(int result[6])
{
	auto random = 0;
	for (int i = 0; i < 6; i++)
	{
		cout << setw(15) << left << "" << "Số May Mắn Thứ " << i + 1 << " Là: \n";
		 srand((unsigned int)time(0));
		for (int j = 0; j < 100; j++)
		{
			random = rand() % 55;
			cout << setw(35) << left << "" <<setw(2)<<left<< random;
			clear();
			Sleep(50);
		}
		cout << endl;
		result[i]=	random;
	}
	interSort(result, 6);
}
void setPlayer(Player& player,fstream &fileAccount)
{
	
	cout << setw(15) << right << "" << "----------------------------------------\n";
	cout << setw(16) << right << "|" << "" << setw(11) << left << "" << "Thông Tin Tài Khoản" << setw(10) << right << "|" << endl;
	cout << setw(15) << right << "" << "----------------------------------------\n";
	cout << setw(15) << left << "" << "Nhập Họ và Tên Của Bạn: "; player.fullName = inputStringWithUTF8();
	cout << setw(15) << right << "" << "----------------------------------------\n";
	cout << setw(15) << left << "" << "Nhập Giới Tính Của Bạn: ";player.gender = inputStringWithUTF8();
	cout << setw(15) << right << "" << "----------------------------------------\n";
	cout << setw(15) << left << "" << "Nhập Ngày Sinh! \n";
	cout << setw(15) << right << "" << "----------------------------------------\n";
	input_date(player.birthday);
	formRegister(fileAccount, player.username, player.password);
	cout << setw(15) << right << "" << "    Đăng Ký Thành Công. Bạn Được Tặng \n\n";
	cout << setw(15) << right << "" << "   100 Ngàn Token Để Tham Gia Trò Chơi!\n";
	cout << setw(15) << right << "" << "----------------------------------------\n";
	player.token = freeToken;
	srand((unsigned int)time(0));
	auto random = rand() % 9000 + 1000;
	player.id = to_string(random) + to_string(player.birthday.day) + to_string(player.birthday.month)+ to_string(player.birthday.year);
	
}
bool addUserToList(vector<Player> &list,  fstream& fileAccount,Player &player)
{
	SetConsoleOutputCP(65001);
	auto sizeBegin = list.size();
	list.push_back(player);
	auto  sizeFinish = list.size();
	if (sizeBegin == sizeFinish)
		return false;
	return true;
}
bool saveDataToFile(fstream& inforOfUser, vector<Player> list, fstream& fileAccount)
{
	bool flag = false;
	inforOfUser.open("Infor_User.txt", ios::app);
	for (Player player : list)
	{
		inforOfUser << player.id << "," << player.fullName << "," << player.gender << "," << player.username << "," << player.password << "," << player.birthday.day 
			<< "/" << player.birthday.month << "/"
			<< player.birthday.year << "," << player.token;
		inforOfUser << "\n";
		flag = true;
	}
	inforOfUser.close();
	return flag;
}
void titleBuyTicket()
{
	cout << endl << endl << endl;
	cout << setw(15) << left << "" << "----------------------------------------------\n";
	cout << setw(16) << right << "|" << setw(8) << left << "" << setw(46) << left << "ĐÂY LÀ CỬA HÀNG BÁN VÉ SỐ ^_^" << "|\n";
	cout << setw(15) << left << "" << "----------------------------------------------\n\n";
}
bool buyTicket(Player &player,int ticket[][6], int amoutOfTicket)
{
	SetConsoleOutputCP(65001);
	bool flag = false;
	system("CLS");
	titleBuyTicket();
	if (player.token < amoutOfTicket * costTicket)
	{
		return false;
	}
	else
	{
		player.token -= (amoutOfTicket * costTicket);
	}
	for (int i = 0; i < amoutOfTicket; i++)
	{
		cout << setw(15) << left << "" << "Vé Thứ " << i + 1 << " : ";
		for (int j = 0; j < 6; j++)
		{
			cin >> ticket[i][j];
			flag = true;
		}
	}
	sort_row_up(ticket, amoutOfTicket, 6);
	return flag;
}

void printTicket(Player player, int ticket[][6],int amoutOfTicket)
{
	SetConsoleOutputCP(65001);
	//sort_row_up(ticket, amoutOfTicket, 6);
	cout << endl << endl << endl;
	cout << setw(15) << left << "" << "|----------------------------------------------------------------|\n";
	cout << setw(16) << right << "|" << setw(15) << left << "" << setw(58) << left << "VÉ SỐ VIETLOT TRÚNG CÁI NỊT ĐÂY :))" << "|" << endl;
	cout << setw(15) << left << "" << "|----------------------------------------------------------------|\n";
	cout << setw(16) << right << "|" << setw(8) << left << "" << setw(30) << left << "Họ Và Tên Khách Hàng: " << setw(35) << left << player.fullName << "|" << endl;
	cout << setw(15) << left << "" << "|----------------------------------------------------------------|\n";
	cout << setw(16) << right << "|" << setw(2) << left << "" << setw(10) << left << "STT" << setw(35) << left << "Thông Tin Của Vé" << setw(23) << left << "Giá Vé" << "|" << endl;
	cout << setw(15) << left << "" << "|----------------------------------------------------------------|\n";
	for (int i = 0; i < amoutOfTicket; i++)
	{
		cout << setw(16) << right << "|" << setw(3) << left << "" << setw(9) << left << i + 1;
		for (int j = 0; j < 6; j++)
		{
			if (ticket[i][j] >= 0 && ticket[i][j] <= 9)
			{
				cout << "0" << ticket[i][j] << " ";
			}
			else
			{
				cout << ticket[i][j] << " ";
			}
		}
		cout << setw(13) << left << "";
		cout << setw(21) << left << "10.000" << "|" << endl;
		cout << setw(15) << left << "" << "|----------------------------------------------------------------|\n";
	}
	
}
bool checkTicketWinRize(int result[6],int number)
{
	for (int i = 0; i < 6; i++)
	{
		if (number == result[i])
			return true;
	}
	return false;
}


bool checkResultOficket(Player &player, int result[6], int ticket[][6], int amoutOfTicket)
{
	SetConsoleOutputCP(65001);
	loading();
	system("CLS");
	cout << endl << endl;
	cout << setw(25) << left << "" << "CHƯƠNG TRÌNH XỔ SỐ BẮT ĐẦU. XIN ĐỪNG NHẢY LẦU ^_^ \n\n";
	setResult(result);
	system("CLS");
	printTicket(player, ticket, amoutOfTicket);
	cout << endl << endl;
	cout << setw(15) << left << "" << "Dãy Số May Mắn Kỳ Này Là: ";
	output(result, 6);
	auto countEqual = 0;
	auto countSuccess = 0;
	for (int i = 0; i < amoutOfTicket; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (checkTicketWinRize(result, ticket[i][j]))
			{
				countEqual++;
			}
		}
		switch (countEqual)
		{
		case 2:
			player.token += top4;
			cout << setw(15) << left << "" << " Xin Chúc Mừng Bạn Đã Trúng Giải Khuyến Khích!\n\n";
			cout << setw(20) << left << "" << " Bạn Đã Nhận Được 30 Ngàn Token!\n\n";
			countSuccess++;
			break;
		case 3:
			player.token += top3;
			cout << setw(15) << left << "" << " Xin Chúc Mừng Bạn Đã Trúng Giải Ba!\n\n";
			cout << setw(20) << left << "" << " Bạn Đã Nhận Được 500 Ngàn Token!\n\n";
			countSuccess++;
			break;
		case 4:
			player.token += top2;
			cout << setw(15) << left << "" << " Xin Chúc Mừng Bạn Đã Trúng Giải Nhì!\n\n";
			cout << setw(20) << left << "" << " Bạn Đã Nhận Được 3 Triệu Token!\n\n";
			break;
		case 5:
			player.token += top1;
			cout << setw(15) << left << "" << " Xin Chúc Mừng Bạn Đã Trúng Giải Nhất!\n\n";
			cout << setw(20) << left << "" << " Bạn Đã Nhận Được 10 Triệu Token!\n\n";
			countSuccess++;
			break;
		case 6:
			player.token += jackpot;
			cout << setw(15) << left << "" << " NỔ HỦ! NỔ HỦ! NỔ HỦ! NỔ HỦ x 3.14 ^_^\n\n";
			cout << setw(20) << left << "" << " Bạn Đã Nhận Được 50 Triệu Token!\n\n";
			countSuccess++;
			break;
		}
		if (countSuccess > 0)
		{
			Sleep(3000);
		}
		countEqual = 0;
	}
	if (countSuccess == 0)
	{
		cout << endl;
		cout << setw(20) << left << "" << " Chúc Mừng Bạn Nhận Được Cái Nịt T_T\n\n";
		cout << setw(15) << left << "" << " Không Sao Còn Thở Là Còn Gỡ. Dừng Lại Là Thất Bại ^_^\n\n";
	}
	return true;
}
void mainMenu()
{
	SetConsoleOutputCP(65001);
	cout << endl << endl << endl;
	cout << setw(35) << left << "" << "---------------------------------------\n";
	cout << setw(36) << right << "*" << setw(8) << left << "" << setw(35) << "1. Đăng Ký Tài Khoản" << "*" << endl;
	cout << setw(35) << left << "" << "---------------------------------------\n";
	cout << setw(36) << right << "*" << setw(8) << left << "" << setw(33) << "2. Đăng Nhập" << "*" << endl;
	cout << setw(35) << left << "" << "---------------------------------------\n";
	cout << setw(36) << right << "*" << setw(8) << left << "" << setw(32) << "3. Mua Vé Số" << "*" << endl;
	cout << setw(35) << left << "" << "---------------------------------------\n";
	cout << setw(36) << right << "*" << setw(8) << left << "" << setw(32) << "4. In Vé Số" << "*" << endl;
	cout << setw(35) << left << "" << "---------------------------------------\n";
	cout << setw(36) << right << "*" << setw(8) << left << "" << setw(37) << "5. Xem Kết Quả Xổ Số" << "*" << endl ;
	cout << setw(35) << left << "" << "---------------------------------------\n\n";
}

int main()
{
	SetConsoleOutputCP(65001);
	auto option = 0;
	char checkContinue,checkBuyItem;
	int result[6];
	int lenght;
	auto amoutOfTicket = 0;
	string user[100];
	Player player /*= setInforAdmin()*/;
	//Player admin = setInforAdmin();
	vector <Player> list;
	fstream fileAccount,inforOfUser;
	int ticket[100][6];
	do
	{
		system("CLS");
		mainMenu();
		cout << endl;
		cout << setw(25) << left << "" << "Dứt Cái Nào Bạn Ơi: "; cin >> option; cin.ignore();
		switch (option)
		{
		case 1:
			system("CLS");
			setPlayer(player, fileAccount);
			if (addUserToList(list, fileAccount,player))
			{
				cout << setw(25) << left << "" << "Thêm Dữ Liệu Thành Công!\n\n";
			}
			else
			{
				cout << setw(25) << left << "" << "Thêm Dữ Liệu Thất Bại!\n\n";
			}
			break;
		case 2:
			system("CLS");
			readFile(fileAccount, user, lenght);
			if (login(user, player.username, player.password, lenght))
			{
				loading();
				cout << endl << endl;
				cout << setw(30) << left << "" << setw(18) << left << "Chào Mừng " << player.fullName << endl;
				cout<<setw(25)<<left<<""<<" Đến Với Trang Xổ Số Uy Tín VL ^_^\n\n";
			}
			else
			{
				cout << endl << endl;
				cout << setw(30) << left << "" << "Hãy Liên Hệ Với ADMIN Để Xin Lại TK ^_^\n\n";
			}
			break;
		case 3:
buyAgain :	cout << setw(15) << left << "" << "Số Lượng Vé Mà Bạn Muốn Mua Là: "; cin >> amoutOfTicket; cin.ignore();
			cout << endl;
			cout << setw(15) << left << "" << "LƯU Ý: CHỌN 6 CẶP SỐ TỪ 0 -> 55 KHÔNG ĐƯỢC TRÙNG NHAU!\n\n"; 
			loading();
			if (buyTicket(player, ticket, amoutOfTicket))
			{
				system("CLS");
				cout << endl << endl;
				cout << setw(30) << left << "" << "CẢM ƠN BẠN. DƯỚI ĐÂY LÀ VÉ CỦA BẠN" << endl ;
				printTicket(player, ticket, amoutOfTicket);
				
			}
			else
			{
				cout << endl << endl;
				cout << setw(15) << left << "" << "Mua Vé Thất Bại T_T Bạn Có Muốn Mua Lại? Y -------> "; cin >> checkBuyItem; cin.ignore();
				if (checkBuyItem == 'Y' || checkBuyItem == 'y')
				{
					goto buyAgain;
				}
			}
			break;
		case 4:
			system("CLS");
			cout << endl << endl;
			cout << setw(30) << left << "" << "CẢM ƠN BẠN. DƯỚI ĐÂY LÀ VÉ CỦA BẠN" << endl;
			printTicket(player, ticket, amoutOfTicket);
			break;
		case 5:
			loading();
			system("CLS");
			checkResultOficket(player, result, ticket, amoutOfTicket);
			break;
		default: exit(0);
			break;
		}
		cout << endl << endl;
		cout << setw(20) << left << "" << "Bạn Đang Có " << player.token << " Token.\n\n";
		cout << setw(25) << left << "" << "CÒN THỞ LÀ CÒN GỠ. DỪNG LẠI LÀ THẤT BẠI? Y/N -------> "; cin >> checkContinue; cin.ignore();
		if (checkContinue != 'Y' && checkContinue != 'y')
		{
			cout << endl;
			cout << setw(20) << left << "" << "NHÙNG QUÁ BẠN ƠI ^_^ \n\n";
		}
	} while (checkContinue == 'Y' || checkContinue == 'y');
	saveDataToFile(inforOfUser, list, fileAccount);
	cout << endl;
	return 0;
}