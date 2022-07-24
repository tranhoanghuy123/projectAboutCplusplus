#include<iostream>
#include<cstring>
#include<iomanip>
#include<fstream>
using namespace std;
struct Goods
{
    char id[5];
    char name[21];
    float cost;
};
struct Node
{
    Goods Data;
    struct Node* Next;
};
typedef Node* List;
void InitList(List& L) {
    L = NULL;
}
Node* createNode(Goods &G) {
    Node* newNode = new Node; 
    newNode->Next = NULL;
    newNode->Data = G;
    return newNode;
}
Goods createGoods(Goods& G)
{
    cout << "Nhap ma mat hang: ";
    cin.getline(G.id, 5);
    cout << "Nhap ten mat hang: ";
    cin.getline(G.name, 21);
    cout << "Nhap gia mat hang: "; cin >> G.cost;
    return G;
}
List InsFirst(List& L, Goods x) {
    Node* P = createNode(x);
    P->Next = L;
    L = P;
    return L;
}
void insertGoods(List& L,Goods &G,int n) {
    int i = 1;
    while (n > 0)
    {
        cout << "Mat hang thu " << i++ << " can them! \n";
        G = createGoods(G);
        L = InsFirst(L, G);
        cin.ignore();
        n--;
    }
}
void printGoods(List &L)
{
    cout << "Ma Hang \t"  << "Ten MAT Hang \t \t " << "     Gia Mat Hang \n";
    for (List p = L; p!= NULL; p=p->Next)
    {
        cout << p->Data.id << "\t \t"<< p->Data.name << "\t"<<right<<setw(20) << right << p->Data.cost << endl;
    }
}
int findIndexID(List &L, char* &id) {
    int index = -1;
    for (List p = L; p != NULL; p = p->Next) {
        index++;
        if (strcmp(p->Data.id, id) == 0) {
            return index;
        }
    }
    return -1; 
}
void printOneGoods(List& L,char *key)
{
    cout << "Nhap ma  hang can in ra: "; cin.getline(key, 4);
    for (List p = L; p != NULL; p = p->  Next)
    {
        
        if (strcmp(p->Data.id, key) == 0)
        {
            cout << p->Data.id << "\t \t" << p->Data.name << "\t" << right << setw(20) << right << p->Data.cost << endl;
            break;
        }
    }
}
List delHead(List &L) {
    if (L == NULL) {
        cout<<"\nCha co gi de xoa het!";
    }
    else {
        L = L->Next;
    }
    return L;
}

List delTail(List &L) {
    if (L == NULL ||L->Next == NULL) {
        return delHead(L);
    }
    List p = L;
    while (p->Next->Next != NULL) {
        p = p->Next;
    }
    p->Next = p->Next->Next;
    return L;
}
List delAt(List &L, int position) {
    if (position == 0 || L == NULL || L->Next == NULL) {
        L = delHead(L); 
    }
    else {
        int k = 1;
        List p = L;
        while (p->Next->Next != NULL && k != position) {
            p = p->Next;
            ++k;
        }
        if (k != position) {
           L = delTail(L);
        }
        else {
            p->Next = p->Next->Next;
        }
    }
    return L;
}
void deleteOneGoodsHasID(List& L,char* id)
{
    int pos = findIndexID(L, id);
    cout << "Nhap ma  hang can xoa: "; cin.getline(id, 4);
    if ( pos > 0)
    {
        delAt(L, pos);
        cout << "Xoa Thanh cong\n";
    }
    else
    {
        cout << "Xoa that bai!\n";
    }
}
int main()
{
    Goods G;
    List L;
    fstream f;
    int n;
    char key[4];
    cout << "Nhap so luong mat hang can them: "; cin >> n;
    cin.ignore();
    insertGoods(L, G, n);
    //printOneGoods(L, key);
    deleteOneGoodsHasID(L, key);
    printGoods(L);
    f.open("E:\DS.dat", ios::out | ios::binary);
    while (1)
    {
        List p = L;
        p->Next;
        if (p->Next != NULL)
            fwrite(&G, sizeof(G), 1, f);
        else
        {
            break;
        }
    }
    fclose(f);
    delete L;
    cout << endl;
    return 0;
}