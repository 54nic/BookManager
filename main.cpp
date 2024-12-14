#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;
class BookData{
    public:
    char isbn[14], book[51], author[51], pub[51], dateAdded[20];
    int qrtOnHand;
    double retail, wholesale;
    BookData(char isbn_[14], char name[51], int qrt, double retail_, char author_[51], char pub_[51], char dateAdded_[20], double wholesale_):
    qrtOnHand(qrt),retail(retail_), wholesale(wholesale_){
        strcpy(isbn, isbn_); strcpy(book, name); strcpy(author, author_); strcpy(pub, pub_); strcpy(dateAdded, dateAdded_);
    }
    void Bookinfo(){
        cout << "   ISBN号:\t" << this->isbn << endl;
        cout << "   书名:\t" << this->book << endl;
        cout << "   库存量:\t" << this->qrtOnHand << endl;
        cout << "   零售价:\t" << this->retail << endl;
        cout << "   作者:\t" << this->author << endl;
        cout << "   出版社:\t" << this->pub << endl;
        cout << "   进书日期:\t" << this->dateAdded << endl;
        cout << "   批发价:\t" << this->wholesale << endl;
    }
    void setTitle(char title[51]){
        strcpy(this->book, title);
    }
    void setISBN(char ISBN[14]){
        strcpy(this->isbn, ISBN);
    }
    void setQrt(int qrt){
        this->qrtOnHand = qrt;
    }
    void setRetail(double ret){
        this->retail = ret;
    }
    void setAuthor(char author_[51]){
        strcpy(this->author, author_);
    }
    void setPub(char pub_[51]){
        strcpy(this->pub, pub_);
    }
    void setDateAdded(char dateAdded_[20]){
        strcpy(this->dateAdded, dateAdded_);
    }
    void setWholesale(double wholesale_){
        this->wholesale = wholesale_;
    }
};
vector <BookData> Books;
//将提示文字&输入数据（非字符串）封装成函数模板
template <class T, class output = char>
T input(output s[]){
    cout << s;
    T re;
    cin >> re;
    return re;
}
//将提示文字&输入字符串 封装成函数
void inputStr(char str[],char output[]){
    cout << output;
    cin >> str;
}
//将“按回车键退出” 封装成函数
void pause(char output[] = "按回车键退出"){
    cout << output;
    getchar();
    getchar();
    system("clear");
}
//通过书名查找
void lookUpBook(){
    while (1){
        char name[51];
        inputStr(name, "请输入要查找的书名：");
        system("clear");
        for (int i = 0; i < Books.size(); i++)
        {
            if(strcmp(name,Books[i].book) == 0){
                Books[i].Bookinfo();
                pause();
                return ;
            }
        }
        int opt = input<int, char>("未找到，输入1重新输入书名");
        if(opt != 1) return;
    }
}
void addBook(){
    char isbn[14], book[51], author[51], pub[51], dateAdded[20];
    inputStr(isbn, "输入ISBN：");
    inputStr(book, "输入书名：");
    int qrt = input<int, char>("输入库存量：");
    double retail = input<double, char>("输入零售价：");
    inputStr(author, "作者：");
    inputStr(pub, "出版社：");
    inputStr(dateAdded, "入库日期：");
    double wholesale = input<double>("输入批发价：");
    Books.push_back(*new BookData(isbn, book, qrt, retail, author, pub, dateAdded, wholesale));
    
}
void editBook(){
    while (1)
    {
        char name[51];
        inputStr(name, "请输入书名");
        for (int i = 0; i < Books.size(); i++)
        {
            if(strcmp(name,Books[i].book) == 0){
                Books[i].Bookinfo();
                system("clear");
                int operatorNum = input<int, char>("米椒图书管理系统\n书编辑模块\n1.书名\n2.ISBN\n3.库存\n4.零售价\n5.作者\n6.出版社\n7.进书日期\n8.批发价\n9.返回到书管理菜单\n输入选择(请输人1-9之间的数):");
                while(1){
                    if(operatorNum == 1){
                        char newName[51];
                        inputStr(newName, "输入新书名：");
                        Books[i].setTitle(newName);
                        break;
                    }
                    else if(operatorNum == 2){
                        char ISBN[14];
                        inputStr(ISBN, "输入新ISBN：");
                        Books[i].setISBN(ISBN);
                        break;
                    }
                    else if(operatorNum == 3){
                        int qrt = input<int, char>("输入库存量：");
                        Books[i].setQrt(qrt);
                        break;
                    }
                    else if(operatorNum == 4){
                        double retail = input<double, char>("输入零售价：");
                        Books[i].setRetail(retail);
                        break;
                    }
                    else if(operatorNum == 5){
                        char author[51];
                        inputStr(author, "输入新作者：");
                        Books[i].setAuthor(author);
                        break;
                    }
                    else if(operatorNum == 6){
                        char pub[51];
                        inputStr(pub, "输入新出版社：");
                        Books[i].setPub(pub);
                        break;
                    }
                    else if(operatorNum == 7){
                        char date[51];
                        inputStr(date, "输入新进书日期：");
                        Books[i].setDateAdded(date);
                        break;
                    }
                    else if(operatorNum == 8){
                        double wholesale = input<double,char>("输入新批发价：");
                        Books[i].setWholesale(wholesale);
                        break;
                    }
                    else if(operatorNum == 9){
                        return;
                    }
                    else {
                        int opt = input<int, char>("输错了，输入1重输：");
                        if(opt != 1) return;
                    }
                }
                return ;
            }
        }
        int opt_ = input<int, char>("没找到，按1重输：");
        if(opt_ != 1) return;
    }
    
}
void deleteBook(){
    while(1){
        char name[51];
        inputStr(name, "输入想删除的书名：");
        for (int i = 0; i < Books.size(); i++)
        {
            if(strcmp(Books[i].book, name) == 0){
                //将Books数组的i位换到最后一位，保持其他位顺序不变
                for(int k = i; k < Books.size()-1; k++){
                    swap(Books[k], Books[k+1]);
                }
                Books.pop_back();
                // Books.back().Bookinfo();
                return ;
            }
        }
        int opt_ = input<int, char>("没找到，按1重输：");
        if(opt_ != 1) return;
    }
    
}
void cash(){
    vector <int> list[2];
    while(1){
        system("clear");
        char isbn[14];
        inputStr(isbn, "请输入ISBN号:");
        bool exist = false, overLimit = false;
        for(int i = 0; i < Books.size(); i++){
            if(strcmp(isbn, Books[i].isbn) == 0){
                exist = true;
                int num = input<int, char>("购买数量:");
                if(Books[i].qrtOnHand < num) { 
                    overLimit = true;
                    cout << "库存不足，此书库存为" << Books[i].qrtOnHand;
                    break;
                }
                list[0].push_back(i);
                Books[i].qrtOnHand -= num;
                list[1].push_back(num);
                break;
            }
        }
        if(!exist){
            int opt = input<int, char>("ISBN不存在，是否再次输入，输入1再次输入:");
            if(opt != 1){
                if(list[0].empty()) return;
                break;
            }
        }
        else if(overLimit){
            int opt = input<int, char>(",输入1再次输入：");
            if(opt != 1){
                if(list[0].empty()) return;
                break;
            }
        }
        else {
            int opt = input<int, char>("是否再买点，输入1增加书目:");
            if(opt != 1) break;
        }
    }
        system("clear");
    cout << "\t前台销售模块\n\t日期:2024年\n"
    <<left<<setw(10)<<"数量"
    <<setw(12)<<"ISBN"
    <<setw(53)<<"书名"
    <<setw(10)<<"单价"
    <<setw(10)<<"金额"<<endl;
    double sum = 0;
    for (int i = 0; i < list[0].size(); i++)
    {
        cout<<left<<setw(8)<<list[1][i]
        <<setw(12)<<Books[list[0][i]].isbn
        <<setw(51)<<Books[list[0][i]].book
        <<setw(8)<<Books[list[0][i]].retail
        <<setw(8)<<list[1][i]*(Books[list[0][i]].retail)<<endl;
        sum += list[1][i]*(Books[list[0][i]].retail);
    }
    cout << "----------------------------------------------------\n销售合计:RMB" << sum << endl
    << "零售税:RMB" << 0.06*sum << endl
    << "应付总额:RMB" << 1.06*sum << endl << "谢谢光临！\n";
    pause();
}
void showManageMenu(){
    while (1)
    {    
        system("clear");
        int operatorNum = input<int, char>("\t米椒图书管理系统\n\t  书库管理模块\n1.查找某本书的信息 \n2.增加书 \n3.修改书的信息 \n4.删除书 \n5.返回到主菜单\n输入选择(请输人1-4之间的数):");
        switch (operatorNum)
        {
        case 1:
            lookUpBook();
            break;
        case 2:
            addBook();
            break;
        case 3:
            editBook();
            break;
        case 4:
            deleteBook();
            break;
        case 5:
            return;
        default:
            int opt = input<int, char>("错误,输入1重新输入：\n");
            if(opt != 1) return;
        }
    }
}
bool qrtCmp(BookData a, BookData b){
    return a.qrtOnHand < b.qrtOnHand;
}
void showReportMenu(){
    while (1)
    {
        system("clear");
        int operatorNum = input<int, char>("\t米椒图书管理系统\n\t    报表模块\n1.书库列表\n2.零售价列表\n3.批发价列表\n4.库存量列表\n5.批发价总额\n6.进书日期列表\n7.返回到主菜单\n输入选择(请输人1-7之间的数):");
        switch (operatorNum)
        {
        case 1:
            cout<<left<<setw(12)<<"ISBN"<<setw(53)<<"书名"<<setw(18)<<"库存量" << endl;
            for(int i = 0; i < Books.size(); i++){
                cout<<left<<setw(12)<<Books[i].isbn<<setw(51)<<Books[i].book<<setw(8)<<Books[i].qrtOnHand << endl;
            }
            break;
        case 2:
            cout<<left<<setw(12)<<"ISBN"<<setw(53)<<"书名"<<setw(18)<<"零售价" << endl;
            for(int i = 0; i < Books.size(); i++){
                cout<<left<<setw(12)<<Books[i].isbn<<setw(51)<<Books[i].book<<setw(8)<<Books[i].retail << endl;
            }
            break;
        case 3:
            cout<<left<<setw(12)<<"ISBN"<<setw(53)<<"书名"<<setw(18)<<"批发价" << endl;
            for(int i = 0; i < Books.size(); i++){
                cout<<left<<setw(12)<<Books[i].isbn<<setw(51)<<Books[i].book<<setw(8)<<Books[i].wholesale << endl;
            }
            break;
        case 4:
            //按库存量为关键字将Books的数组排序
            cout<<left<<setw(12)<<"ISBN"<<setw(53)<<"书名"<<setw(18)<<"库存量" << endl;
            sort(Books.begin(), Books.end(), [](BookData a, BookData b){return a.qrtOnHand < b.qrtOnHand;});
            for(int i = 0; i < Books.size(); i++){
                cout<<left<<setw(12)<<Books[i].isbn<<setw(51)<<Books[i].book<<setw(8)<<Books[i].qrtOnHand << endl;
            }
            break;
        case 5:
            //按库存量*批发价为关键字将Books的数组排序
            sort(Books.begin(), Books.end(), [](BookData a, BookData b){return a.qrtOnHand * a.wholesale < b.qrtOnHand * b.wholesale;});
            cout<<left<<setw(12)<<"ISBN"<<setw(53)<<"书名"<<setw(19)<<"总进货价" << endl;
            for(int i = 0; i < Books.size(); i++){
                cout<<left<<setw(12)<<Books[i].isbn<<setw(51)<<Books[i].book<<setw(8)<<Books[i].qrtOnHand * Books[i].wholesale << endl;
            }
            break;
        case 6:
            //按进书日期为关键字将Books的数组排序
            sort(Books.begin(), Books.end(), [](BookData a, BookData b){return strcmp(a.dateAdded,b.dateAdded)<0;});
            cout<<left<<setw(12)<<"ISBN"<<setw(53)<<"书名"<<setw(19)<<"进书日期" << endl;
            for(int i = 0; i < Books.size(); i++){
                cout<<left<<setw(12)<<Books[i].isbn<<setw(51)<<Books[i].book<<setw(15)<<Books[i].dateAdded << endl;
            }
            break;
        case 7:
            return;
        default:
            int opt = input<int, char>("错误,输入1重新输入：\n");
            if(opt == 1) return;
        }
        pause();
    }
}
void showMenu(){
    while(1){
        system("clear");
        int operatorNum = input<int, char>("\t米椒图书管理系统\n\t     主菜单\n1.收银模块\n2.书库管理模块\n3.报表模块\n4.退出系统\n输入选择（请输人1-4之间的数）:"); 

    switch (operatorNum)
    {
    case 1:
        cash();
        break;
    case 2:
        showManageMenu();
        break;
    case 3:
        showReportMenu();
        break;
    case 4:
        return;
    }
    }
}
void readFile(){
    fstream file;
    file.open("books", ios::in);
    char isbn[14], book[51], author[51], pub[51], dateAdded[20];
    int qrtOnHand;
    double retail, wholesale;
    while(file >> isbn){
        file >> book >> qrtOnHand >> retail >> author >> pub >> dateAdded >> wholesale;
        Books.push_back(*new BookData(isbn, book, qrtOnHand, retail, author, pub, dateAdded, wholesale));
        // Books.back().Bookinfo();
        // cout << isbn << " " << book << " " << qrtOnHand << " " << retail << endl;
    }
}
void writeFile(){
    fstream file;
    file.open("books", ios::out);
    for (int i = 0; i < Books.size(); i++)
    {
        file << Books[i].isbn << " ";
        file << Books[i].book << " ";
        file << Books[i].qrtOnHand << " ";
        file << Books[i].retail << " ";
        file << Books[i].author << " ";
        file << Books[i].pub << " ";
        file << Books[i].dateAdded << " ";
        file << Books[i].wholesale << "\n";
    }
    
}
int main(){
    readFile();
    showMenu();
    writeFile();
    return 0;
}