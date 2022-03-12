/*
练习 1.7
使用你最趁手的编辑工具，输入两行（或更多）文字并存盘。然后编写一个程序，打开该文本文
件，将其中每个字都读取到一个vector<string>对象中。遍历该vector，将内容显示到cout。
然后利用泛型算法sort()，对所有文字排序：
#include <algorithm>
sort( container.beginer(), container.end() );
再将排序后的结果输出到另一个文件。
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;


int main()
{
    // 要读取的文件
    ifstream in_file( "data_read.txt" );
    if ( !in_file ){
        cerr << "oops! unable to open input file, I have creat one for you!\n";
        ofstream File;
        File.open("data_read.txt");
        File.close();
        return -1;
    }
    
    // 需写入的文件
    ofstream out_file( "data_wrote.txt" );
    if ( ! out_file ){
        cerr << "oops! unable to open output file.\n"; 
        return -2;
    }  // out_file 为 false 的情况不可能实现， ofstream 将会自动生成一个文件.

    // 读取文件中的内容
    string word;
    vector< string > text;
    while ( in_file >> word ){
        text.push_back( word );
    }
    
    int ix;
    cout << "unsorted text: \n";

    // 输入到cout中展示
    for ( ix = 0; ix < text.size(); ++ix){
        cout << text[ ix ] << ' ';
    }
    cout << endl;

    // 排序
    sort( text.begin(), text.end() );

    // 写入到另一个文件中
    out_file << "sorted text: \n";
    for ( ix = 0; ix < text.size(); ++ix ){
        out_file << text[ ix ] << ' ';
    }
    out_file << endl;
    return 0;
}
