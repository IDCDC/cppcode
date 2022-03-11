/*
练习 1.4
试着扩充这个程序的内容：（1）要求用户同时输入名字（first name）和姓氏（last name），
（2）修改输出结果，同时打印出姓氏和名字。
*/

#include <iostream>
#include <string>
using namespace std;

int my_main()
{

    string user_name_first, user_name_last;
    std::cout << "Please enter your first name: ";
    cin >> user_name_first;
    cout << "Please enter your last name: ";
    cin >> user_name_last;
    cout << '\n'
         << "Hello, "
         << user_name_first
         << user_name_last
         << " ... and goodbye!\n";
    
    return 0;
}

int main()
{
    my_main();
}
