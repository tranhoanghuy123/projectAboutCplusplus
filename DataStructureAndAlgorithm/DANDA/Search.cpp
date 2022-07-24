#include<iostream>
#include<cstring>
using namespace std;
struct SV {
    int msv; //Mã số sinh viên
    char ho[20];// họ + lót sinh viên
    char ten[10]; //tên sinh viên
};
void nhap1sv(SV& sv)
{
    cout << "Nhap ma sinh vien";
    cin >> sv.msv;
    cin.ignore();
    cout << "Nhap ho sinh vien: ";
    cin.get(sv.ho,20);
    cin.ignore();
    cout << "Nhap ten SV: "; cin.get(sv.ten, 10);
    cin.ignore();
}
void xuat1sv(SV& sv)
{
    cout << sv.msv << "\t" << sv.ho << "\t" << sv.ten<<endl;
}
void nhapds(SV a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        nhap1sv(a[i]);
    }
}
void xuatds(SV a[],int n)
{
    for (int i = 0; i < n; i++)
    {
        xuat1sv(a[i]);
    }
}
int main()
{
    SV a[5];
    int n = 5;
    nhapds(a, n);
    xuatds(a, n);
    cout << endl;
    return 0; 
}
