#include <iostream>
#include <string>
using namespace std;

int main()
{

    string user_name_first, user_name_last;
    cout << "Please enter your first name: ";
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