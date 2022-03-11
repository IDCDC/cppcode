/*
练习 1.6
编写一个程序，从标准输入设备读取一串整数，并将读入的整数依次放到array及
vector，然后遍历这两种容器，求取数值总和。将总和及平均值输出至标准输出设备
*/

// 使用vector实现
#include <iostream>
#include <vector>
using namespace std;

int main_vec()
{
    vector<int> ivec;
    int ival;
    cout << "Please input the element of the vector, "
         <<  "enter null to end the input." << endl;
    while ( cin >> ival ){
        // 将新输入内容添加到ivec之后
        ivec.push_back( ival );
    }
    // 和值为 int 型， average 数据类型就算定义为 float
    // int / int = int， 除非再用两中转变量定义为 float
    // 才可输出为 float 结果。
    int sum = 0;
    for (int ix = 0; ix < ivec.size(); ix++){
        sum += ivec[ ix ];
    }
    int average = sum / ivec.size();
    
    cout << "Sum of " << ivec.size()
         << " elements: " << sum
         << ". Average: " << average << endl;
    cout << "The vector is : [";
    for (int i=0; i<ivec.size()-1; i++)
        cout << ivec[i] << ",";
    cout << ivec.back() << "]." << endl;
    return 0;
}


int main_array()
{
    const int array_size = 128;
    int ia[ array_size ];
    int ival, icnt = 0;  // ival用于暂存输入，icnt表示输入数据量

    while ( cin >> ival && icnt < array_size ){
        ia[ icnt++ ] = ival;
    }

    int sum = 0;
    for (int ix = 0; ix < icnt; ++ix ){
        sum += ia[ ix ];
    }

    int average = sum / icnt;
    cout << "Sum of " << icnt
         << " elements: " << sum
         << ". Average: " << average << endl;
    return 0;
}


int main_array_my()
{
    int n;
    cout << "input the number n: ";
    cin >> n;
    int array[n];
    int val;
    float sum, average=0.0;
    for (int i=0; i<n; i++){
        cin >> val;
        array[i] = val;
    }
    cout << "The vector is : [";
    for (int i=0; i<n-1; i++){
        cout << array[i] << ","; // 输出向量
        sum += array[i];         // 求和
    }
    cout << array[n-1] << "]." << endl;
    sum += array[n-1];
    average = sum / n;               // 计算平均值
    cout << "Sum of " << n
         << " elements: " << sum
         << ". Average: " << average << endl;

    return 0;
}


int main()
{
    int number;
    cout << "Please enter the type represented by the number:" 
    << "\n 1 stand for Vector,\n 2 stand for array,\n" 
    << "3 stand for array function wrote by myself!"<< endl;
    cin >> number;
    switch (number)
    {
    case 1:
        main_vec();
        break;
    case 2:
        main_array();
        break;
    case 3:
        main_array_my();
        break;
    default:
        cout << "Please input the right number!" << endl;
        break;
    }
    // while (cin >> number)
    // {   // 也可选取这种，可以知道输入正确的编号才截至。
    //     if (number == 1)
    //         main_vec();
    //         break;
    // }
    return 0;
}