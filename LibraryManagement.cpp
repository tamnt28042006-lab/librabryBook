#include <iostream>
#include <ctime>
using namespace std;
class Book{
    private:
    string bookName;
    string authorName;
    tm publicDate; 
    int numberOfBooks;
    public:

// Hàm thành phần nhập dữ liệu cho sách
    void insertBook(){
        cout<<"Nhap ten sach:";
        getline(cin,bookName);

        cout<<"Nhap ten tac gia:";
        getline(cin,authorName);

        cout<<"Nhap ngay thang nam san xuat (dd/mm//yy):";
        cin>>publicDate.tm_mday >> publicDate.tm_mon >> publicDate.tm_year;
        cin.ignore();

        publicDate.tm_mon-=1;
        publicDate.tm_year-=1900;

        cout<<"Nhap so luong sach:";
        cin>>numberOfBooks;
    }

// Hàm hiển thị dữ liệu sách
    void display(){
        cout<<"Sach: "<<bookName
        <<" | Tac gia: "<<authorName
        <<" | So luong: "<<numberOfBooks
        <<" | Ngay san xuat: "
        <<publicDate.tm_mday<<"/"
        <<(publicDate.tm_mon+1)<<"/"
        <<(publicDate.tm_year+1900)
        <<endl;
    }

};

struct Node{
    Book data;
    Node* prev;
    Node* next;
    Node(Book value){
        data=value;
        prev=NULL;
        next=NULL;
    }
};

// Hàm in tiêu đề
    void printCentered(string t, int width){
        int len = t.length();
        int left = (width-len) / 2;
        int right = width - len - left;
        for (int i = 0; i < left; i++){
            cout<<"=";
        }
        cout<<t;
        for (int i = 0; i < right; i++){
            cout<<"=";
        }
        cout << endl;
    }

class doublyLinkedList{
    private:
    Node* head;
    public:
    doublyLinkedList(){
        head=NULL;
    }

// Hàm thêm sách vào danh sách liên kết
    void insertBook(Book value){
        Node* newNode=new Node(value);
        if (head==NULL){
            head=newNode;
            return;
        } else {
            Node* temp=head;
            while (temp->next!=NULL){
                temp=temp->next;
            }
            temp->next=newNode;
            newNode->prev=temp;
        }
    }

// In danh sách liên kết
    void display(){
        Node* temp=head;
        printCentered("Thu vien",150);
        while (temp!=NULL){
            temp->data.display();
            temp=temp->next;
        }
        for(int i=0;i<150;i++){
            cout<<"=";
        }
        cout<<endl;
    }

};

int main(){
    int select;
    doublyLinkedList Thuvien;
    do{
        printCentered("Danh sach chuc nang",50);
        cout<<"0: Exit. \n"
            <<"1: Insert book. \n"
            <<"2: Borrow book. \n"
            <<"3: Return book. \n"
            <<"4. Searching: \n +)searchByAuthorName. \n +)searchByBookName.\n"
            <<"5. Sorting. \n"
            <<"6. Display. \n";
            for(int i=0;i<50;i++){
                cout<<"=";
            }
            cout<<endl<<"->";
        cin>>select;
        switch(select){
            case 0:{
                return 0;
            }
            case 1:{
                Book bk;
                cin.ignore();
                bk.insertBook();
                Thuvien.insertBook(bk);
                break;
            }
            case 6:{
                Thuvien.display();
                cout<<endl;
                break;
            }
        }
    }while(select!=0);
}
