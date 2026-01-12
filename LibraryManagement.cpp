#include <iostream>
#include <ctime>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Book {
private:
    string bookName;
    string authorName;
    int numberOfBooks=0;
    tm publicDate;

public:
    // Hàm khởi tạo 0 tham số
    Book() {
        bookName = "";
        authorName = "";
        numberOfBooks = 0;
    }

    // Hàm thành phần nhập dữ liệu cho sách
    void insertBook() {
        cout << "Nhap ten sach:";
        getline(cin, bookName);

        cout << "Nhap ten tac gia:";
        getline(cin, authorName);

        cout << "Nhap ngay thang nam san xuat (dd/mm/yy):";
        cin >> publicDate.tm_mday >> publicDate.tm_mon >> publicDate.tm_year;
        cin.ignore();

        publicDate.tm_mon -= 1;
        publicDate.tm_year -= 1900;
        if (publicDate.tm_mday > 31 || publicDate.tm_mday < 1) {
            cout << "Ngay khong hop le, chuong trinh se dong";
            return;
        }
        if (publicDate.tm_mon > 11 || publicDate.tm_mon < 0) {
            cout << "Thang khong hop le, chuong trinh se dong";
            return;
        }
        if(publicDate.tm_year<0){
            cout<<"Nam khong hop le, chuong trinh se dong \n";
            return;
        }
        cout << "Nhap so luong sach:";
        cin >> numberOfBooks;
    }

    // Hàm hiển thị dữ liệu sách
    void display() {
        cout << "Sach: " << bookName
                << " | Tac gia: " << authorName
                << " | So luong: " << numberOfBooks
                << " | Ngay san xuat: "
                << publicDate.tm_mday << "/"
                << (publicDate.tm_mon + 1) << "/"
                << (publicDate.tm_year + 1900)
                << endl;
    }

    int getPublicYear() {
        return publicDate.tm_year + 1900;
    }

    void decreaseNumberOfBooks(){
        numberOfBooks--;
    }
    void increaseNumberOfBooks(){
        numberOfBooks++;
    }
    string getName(){
        return bookName;
    }
    int getSoLuong(){
        return numberOfBooks;
    }
    string getAuthorName() {
        return authorName;
    }
};

struct Node {
    Book *data;
    Node *prev;
    Node *next;

    Node(Book *value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

// Hàm in tiêu đề
void printCentered(string t, int width) {
    int len = t.length();
    int left = (width - len) / 2;
    int right = width - len - left;
    for (int i = 0; i < left; i++) {
        cout << "=";
    }
    cout << t;
    for (int i = 0; i < right; i++) {
        cout << "=";
    }
    cout << endl;
}

class librabryManagement {
    unordered_map<string, Book*> hashBook;
public:
    Book *findBook(string bookName) {
        if (hashBook.count(bookName)) {
            return hashBook[bookName];
        }
        return nullptr;
    }
    void addBook(Book* b) {
        hashBook[b->getName()] = b;
    }
};

class Person{
    private:
    string name;
    string cccd;
    string bookName;
    public:
    Person(string n,string id,Book &bk){
        name=n;
        cccd=id;
        bookName=bk.getName();
        bk.decreaseNumberOfBooks();
    }
    void Display(){
        cout<<"Ten:"<<name<<"|"<<"cccd:"<<cccd<<"|"<<"Thong tin sach:"<<bookName<<endl;
    }
    string getNameBook(){
        return bookName;
    }
    string getName(){
        return name;
    }
    string getId(){
        return cccd;
    }
};

// Hiển thị danh sách queue
void displayQueue(queue<Person> q){
        while(!q.empty()){
            q.front().Display();
            q.pop();
        }
    }
 
//Xoá phần tử trong danh sách
bool removeQueue(queue<Person>& q,string t,string n,string id){
    queue<Person> temp;
    bool found =false;
    while(!q.empty()){
        if(!found && q.front().getNameBook() == t && q.front().getName() ==n && q.front().getId() == id ){
            found=true;
            q.pop();
            continue;
        }else{
            temp.push(q.front());
        }
        q.pop();
    }
    q=temp;
    if(found){
        cout<<"Tra sach thanh cong \n";
    }else{
        cout<<"Tra sach khong thanh cong \n";
    }
    return found;
}

class doublyLinkedList {
private:
    Node *head;
    // sắp xếp sách theo năm xuất bản ( sử dụng merge sort)
    // Merge Sort cho DLL
    Node* mergeSort(Node* head) {
        if (!head || !head->next)
            return head;  // TH cơ sở: danh sách rỗng hoặc chỉ có 1 node thì đã "sort"

        // sử dụng kỹ thuật fast-slow pointer để chia double linkedlist thành 2 nửa
        Node* slow = head;
        Node* fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            if (fast) slow = slow->next;
        }
        Node* second = slow->next;  // nhánh phải
        slow->next = nullptr;       // cắt đôi
        if (second) second->prev = nullptr;

        // 2. Đệ quy cho 2 nửa của danh sách
        Node* left  = mergeSort(head);
        Node* right = mergeSort(second);

        // 3. Merge hai nửa đã sort
        return merge(left, right);
    }
    // Gộp 2 danh sách đã sắp xếp
    Node* merge(Node* first, Node* second) {
        if (!first) return second;
        if (!second) return first;
        if (first->data->getPublicYear() >= second->data->getPublicYear()) {
            first->next = merge(first->next, second);
            if (first->next) first->next->prev = first;
            first->prev = nullptr;
            return first;
        } else {
            second->next = merge(first, second->next);
            if (second->next) second->next->prev = second;
            second->prev = nullptr;
            return second;
        }
    }

public:
    doublyLinkedList() {
        head = nullptr;
    }
    // Hàm thêm sách vào danh sách liên kết
    void insertBookIntoDbLinkedList(Book* value) {
        Node *newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            return;
        } else {
            Node *temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
    }
    void display() {
        Node *temp = head;
        printCentered("Thu vien", 50);
        while (temp != nullptr) {
            temp->data->display();
            temp = temp->next;
        }
        for (int i = 0; i < 50; i++) {
            cout << "=";
        }
        cout << endl;
    }
    int count() {
        Node *temp = head;
        int count = 0;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void sortByPublicYear() {
        head = mergeSort(head);
    }
};

class hashTable {
    unordered_map<string, vector<string>> searchByAuthorName;
public:
    void addBook(Book& book) {
        searchByAuthorName[book.getAuthorName()].push_back(book.getName());
    }
    void searching(string authorName) {
        if (searchByAuthorName.find(authorName) == searchByAuthorName.end()) {
            cout <<"Hien khong co sach nao co ten tac gia nay.\n";
            return;
        }
        cout <<"Tac gia: " << authorName <<" co tac pham la: ";
        for (int i = 0; i < searchByAuthorName[authorName].size(); i++) {
           cout << searchByAuthorName[authorName][i];
            if (i != searchByAuthorName[authorName].size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
};

int main() {
    int select;
    doublyLinkedList Thuvien;
    queue<Person> Borrowlist;
    librabryManagement lib;
    hashTable timKiem;
    do {
        printCentered("Danh sach chuc nang", 50);
        cout    << "0: Exit. \n"
                << "1: Insert book. \n"
                << "2: Borrow book. \n"
                << "3: Display borrow book \n"
                << "4: Return book. \n"
                << "5. Searching by author name. \n"
                << "6. Sorting. \n"
                << "7. Display. \n";
        for (int i = 0; i < 50; i++) {
            cout << "=";
        }
        cout << endl << "->";
        cin >> select;
        switch (select) {
            case 0: {
                return 0;
            }
            case 1: {
                cin.ignore();
                Book* book=new Book();
                book->insertBook();
                Thuvien.insertBookIntoDbLinkedList(book);
                lib.addBook(book);
                timKiem.addBook(*book);
                break;
            }
            case 2:{
                int numberOfBooks;
                string nBook,name,id;
                cout<<"Nhap so sach muon muon:";
                cin>>numberOfBooks;
                cin.ignore();
                cout<<"Nhap ten nguoi muon:";
                getline(cin,name);
                cout<<"Nhap id nguoi muon:";
                getline(cin,id);
                for(int i=0; i<numberOfBooks; i++){
                cout<<"Nhap sach cho muon:";
                getline(cin,nBook);
                Book* found;
                found=lib.findBook(nBook);
                if(found){
                    if(found->getSoLuong()>0){
                        Borrowlist.push(Person(name,id,*found));
                    }else{
                        cout<<"Sach da het \n";
                    }
                }else{
                    cout<<"Khong tim thay sach vui long nhap lai \n";
                    i--;
                }
                }
                break;
            }
            case 3:{
                printCentered("Danh sach muon",50);
                displayQueue(Borrowlist);
                for(int i=0;i<50;i++){
                    cout<<"=";
                }
                cout<<endl<<endl;
                break;
            }
            case 4:{
                string bBook,name,id;
                int numberOfBooks;
                cout<<"Nhap so luong sach muon tra:";
                cin>>numberOfBooks;
                cin.ignore();
                cout<<"Nhap ten nguoi muon:";
                getline(cin,name);
                cout<<"Nhap id nguoi muon:";
                getline(cin,id);
                for(int i=0;i<numberOfBooks;i++){
                cout<<"Nhap sach muon tra:";
                getline(cin,bBook);
                bool check = removeQueue(Borrowlist,bBook,name,id);
                if(check){
                    Book* found=lib.findBook(bBook);
                    if(found){
                        found->increaseNumberOfBooks();
                    }
                }
                }
                break;
            }
            case 5:{
                cin.ignore();
                cout <<"Nhap ten tac gia: ";
                string authorName;
                getline(cin, authorName);
                timKiem.searching(authorName);
                break;
            }
            case 6: {
                Thuvien.sortByPublicYear();
                cout<<"Hoan thanh sap xep \n";
                break;
            }
            case 7: {
                Thuvien.display();
                cout << endl;
                break;
            }
            default:
                return 0;
        }
    } while (select != 0);
}