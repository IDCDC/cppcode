#include <iostream>
#include <string>
#include <iomanip>
#include <cstring>
using namespace std;

int main_string()
{

    string name;
    cout << "Please enter your name: ";
    cin >> name;

    switch (name.size())
    {
    case 0:
        cout << "You haven't input a valid name!" << endl;
        break;
    case 1:
        cout << "You only entered one character!" << endl;
        break;
    case 2:
        cout << "You only entered two character!" << endl;
        break;
    default:
        cout << "Hello, " << name << "! Well comback!" << endl;
        break;
    }
    return 0;
}


int main_char()
{
    // 必须分配一个大小固定的空间
    const int nm_size = 128;
    char user_name[ nm_size ];
    cout << "Please enter your name:";
    cin >> setw( nm_size ) >> user_name;

    switch ( strlen( user_name ) ){
        // 这里处理case 0和case 
        case 127:
            // 也许所得的字符串已被setw()舍弃掉部分内容
            cout << "That is a very big name, indeed -- "
                 << "we may have needed to shorten it!\n"
                 << "In any case,\n";
            
            // 此处不加break，往下继续执行
        default:
            // 如果符合前述条件，也会执行至此处，因为先前并没有break
            cout << "Hello, " << user_name
                 << " -- happy to make your acquaintance!\n";
            break;
    }
    return 0;
}

int main_c()
{
    char* name;
    cout << "Please enter your name: " ;
    // cin >> name;
    // cerr << strlen(name);
    cout << "hh" << flush;
    // switch (strlen(name))
    // {
    // case 0:
    //     cout << "You haven't input a valid name!" << endl;
    //     break;
    // case 1:
    //     cout << "You only entered one character!" << endl;
    //     break;
    // case 2:
    //     cout << "You only entered two character!" << endl;
    //     break;
    // default:
    //     cout << "Hello, " << name << "! Well comback!" << endl;
    //     break;
    // }

    /*{
        在此处发现了一个很奇怪的问题，应该是与字符串的格式有关；
        cout 无结果，等以后有进一步知识在研究。
    }*/
    return 0;
}



int main()
{
    int number;
    cout << "Please enter the string type represented by the number:" 
    << "\n 1 stand for C-style, 2 stand for string class." << endl;
    cin >> number;
    switch (number)
    {
    case 1:
        main_char();
        break;
    case 2:
        main_string();
        break;
    default:
        cout << "Please input the right number!" << endl;
        break;
    }
}
