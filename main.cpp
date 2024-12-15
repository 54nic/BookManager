//  
//  米椒图书管理系统 @ 2024.12.15 @ 052460114 张浩宇
//
//  代码很乱，请谅解，我想尽力写成模块化、高复用度的代码，可能有些地方不符合规范
//
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;
//书的数据类
class BookData{
    public:
    char isbn[14], book[51], author[51], pub[51], dateAdded[20];
    int qrtOnHand;
    double retail, wholesale;
    //传入isbn、书名、库存量、零售价、作者、出版社、进书日期、批发价的构造函数
    BookData(char isbn_[14], char name[51], int qrt, double retail_, char author_[51], char pub_[51], char dateAdded_[20], double wholesale_):
    qrtOnHand(qrt),retail(retail_), wholesale(wholesale_){
        //使用字符串复制函数将字符串初始化
        strcpy(isbn, isbn_); strcpy(book, name); strcpy(author, author_); strcpy(pub, pub_); strcpy(dateAdded, dateAdded_);
    }
    //格式化输出书的信息
    void Bookinfo(){
        //使用left和setw进行输出内容的对齐
        cout<<left<<setw(12)<< "ISBN号:"    <<setw(10)<< this->isbn << endl;
        cout<<left<<setw(13)<< "书名:"      <<setw(10)<< this->book << endl;
        cout<<left<<setw(14)<< "库存量:"    <<setw(10)<< this->qrtOnHand << endl;
        cout<<left<<setw(14)<< "零售价:"    <<setw(10)<< this->retail << endl;
        cout<<left<<setw(13)<< "作者:"      <<setw(10)<< this->author << endl;
        cout<<left<<setw(14)<< "出版社:"    <<setw(10)<< this->pub << endl;
        cout<<left<<setw(15)<< "进书日期:"  <<setw(10)<< this->dateAdded << endl;
        cout<<left<<setw(14)<< "批发价:"    <<setw(10)<< this->wholesale << endl;
    }
    //更改书名(传入书名)
    void setTitle(char title[51]){
        strcpy(this->book, title);
    }
    //更改ISBN(传入ISBN)
    void setISBN(char ISBN[14]){
        strcpy(this->isbn, ISBN);
    }
    //更改库存量(传入库存量)
    void setQrt(int qrt){
        this->qrtOnHand = qrt;
    }
    //更改零售价(传入零售价)
    void setRetail(double ret){
        this->retail = ret;
    }
    //更改作者(传入作者)
    void setAuthor(char author_[51]){
        strcpy(this->author, author_);
    }
    //更改出版社(传入出版社)
    void setPub(char pub_[51]){
        strcpy(this->pub, pub_);
    }
    //更改进书日期(传入进书日期)
    void setDateAdded(char dateAdded_[20]){
        strcpy(this->dateAdded, dateAdded_);
    }
    //更改批发价(传入批发价)
    void setWholesale(double wholesale_){
        this->wholesale = wholesale_;
    }
};
//定义存储书的vector
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
    //等待用户按下回车
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
            //遍历存书的数组，当目标书名与数组元素的成员变量书名相等时
            if(strcmp(name,Books[i].book) == 0){
                Books[i].Bookinfo();
                pause();
                return ;
            }
        }
        //若循环为判断成功，出循环后进行询问
        int opt = input<int, char>("未找到，输入1重新输入书名");
        if(opt != 1) return;
    }
}
//新增书的函数
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
    //将输入内容构造的新对象push到数组末端
    Books.push_back(*new BookData(isbn, book, qrt, retail, author, pub, dateAdded, wholesale));
    
}
//编辑书信息的函数，先选择要编辑的信息，再输入内容
void editBook(){
    while (1)
    {
        char name[51];
        inputStr(name, "请输入书名");
        for (int i = 0; i < Books.size(); i++)
        {
            if(strcmp(name,Books[i].book) == 0){
                system("clear");
                //找到书后输出书的信息
                Books[i].Bookinfo();
                int operatorNum = input<int, char>("米椒图书管理系统\n书编辑模块\n1.书名\n2.ISBN\n3.库存\n4.零售价\n5.作者\n6.出版社\n7.进书日期\n8.批发价\n9.返回到书管理菜单\n输入选择(请输人1-9之间的数):");
                while(1){
                    //通过各设置函数设置书的信息
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
//删除书的函数
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
                //将数组最后一位pop
                Books.pop_back();
                return ;
            }
        }
        int opt_ = input<int, char>("没找到，按1重输：");
        if(opt_ != 1) return;
    }
    
}
//收银模块
void cash(){
    //list[0]代表书对应的数组下标 list[1]代表对应书的购买数量
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
                //处理库存不足的情况
                if(Books[i].qrtOnHand < num) { 
                    overLimit = true;
                    cout << "库存不足，此书库存为" << Books[i].qrtOnHand;
                    break;
                }
                //若正常，则将信息push如收银清单list，并减少库存
                list[0].push_back(i);
                Books[i].qrtOnHand -= num;
                list[1].push_back(num);
                break;
            }
        }
        //未找到书的情况
        if(!exist){
            int opt = input<int, char>("ISBN不存在，是否再次输入，输入1再次输入:");
            if(opt != 1){
                //若购书清单list为空则返回
                if(list[0].empty()) return;
                //否则进入购书清单显示
                break;
            }
        }
        //库存不足的情况
        else if(overLimit){
            int opt = input<int, char>(",输入1再次输入：");
            if(opt != 1){
                //若购书清单list为空则返回
                if(list[0].empty()) return;
                //否则进入购书清单显示
                break;
            }
        }
        //询问是否增加购书
        else {
            int opt = input<int, char>("是否再买点，输入1增加书目:");
            if(opt != 1) break;
        }
    }
    system("clear");
    //购书清单汇总显示
    cout << "\t前台销售模块\n\t日期:2024年\n"
    <<left<<setw(10)<<"数量"
    <<setw(12)<<"ISBN"
    <<setw(53)<<"书名"
    <<setw(10)<<"单价"
    <<setw(10)<<"金额"<<endl;
    double sum = 0;
    for (int i = 0; i < list[0].size(); i++)
    {
        //输出每一项书的购买信息，通过setw对齐输出内容
        cout<<left<<setw(8)<<list[1][i]
        <<setw(12)<<Books[list[0][i]].isbn
        <<setw(51)<<Books[list[0][i]].book
        <<setw(8)<<Books[list[0][i]].retail
        <<setw(8)<<list[1][i]*(Books[list[0][i]].retail)<<endl;
        //同时计算总价
        sum += list[1][i]*(Books[list[0][i]].retail);
    }
    cout << "----------------------------------------------------\n销售合计:RMB" << sum << endl
    << "零售税:RMB" << 0.06*sum << endl
    << "应付总额:RMB" << 1.06*sum << endl << "谢谢光临！\n";
    pause();
}
//管理书库模块
void showManageMenu(){
    while (1)
    {    
        system("clear");
        int operatorNum = input<int, char>("\t米椒图书管理系统\n\t  书库管理模块\n1.查找某本书的信息\n2.增加书\n3.修改书的信息\n4.删除书\n5.返回到主菜单\n输入选择(请输人1-4之间的数):");
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
//报表模块
void showReportMenu(){
    while (1)
    {
        system("clear");
        int operatorNum = input<int, char>("\t米椒图书管理系统\n\t    报表模块\n1.书库列表\n2.零售价列表\n3.批发价列表\n4.库存量列表\n5.批发价总额\n6.进书日期列表\n7.返回到主菜单\n输入选择(请输人1-7之间的数):");
        switch (operatorNum)
        {
        case 1:
            //输出书库列表
            cout<<left<<setw(12)<<"ISBN"<<setw(53)<<"书名"<<setw(18)<<"库存量" << endl;
            for(int i = 0; i < Books.size(); i++){
                cout<<left<<setw(12)<<Books[i].isbn<<setw(51)<<Books[i].book<<setw(8)<<Books[i].qrtOnHand << endl;
            }
            break;
        case 2:
            //输出零售价列表
            cout<<left<<setw(12)<<"ISBN"<<setw(53)<<"书名"<<setw(18)<<"零售价" << endl;
            for(int i = 0; i < Books.size(); i++){
                cout<<left<<setw(12)<<Books[i].isbn<<setw(51)<<Books[i].book<<setw(8)<<Books[i].retail << endl;
            }
            break;
        case 3:
            //输出批发价列表
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
//主菜单模块
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
    //创建文件流
    fstream file;
    //打开 books 文件
    file.open("books", ios::in);
    char isbn[14], book[51], author[51], pub[51], dateAdded[20];
    int qrtOnHand;
    double retail, wholesale;
    //读取ISBN 若未读到 则退出循环
    while(file >> isbn){
        //再读取书的其他信息
        file >> book >> qrtOnHand >> retail >> author >> pub >> dateAdded >> wholesale;
        Books.push_back(*new BookData(isbn, book, qrtOnHand, retail, author, pub, dateAdded, wholesale));
    }
    file.close();
}
void writeFile(){
    fstream file;
    file.open("books", ios::out);
    //输出书的各信息 每行一种书
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
    file.close();
}
int main(){
    readFile();
    showMenu();
    writeFile();
    return 0;
}