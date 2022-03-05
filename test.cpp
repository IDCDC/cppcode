// #include <stdio.h>
// int main()
// {

//    // char name[100];
//    // printf("What is your name?\n");
//    // scanf("%s",name);
//    // printf("Hello,%s,nice to meet you!\n",name);
   
// }


// #include "stdio.h"
 
// int main()
// {
// 	char* str1 = "hello world\n";
// 	str1 = "aa";
// 	str1[1] = "a";	//报错
 
// 	printf("%s",str1);
 
// }


// #include<iostream>
// using namespace std;
 
// int main()
// {
// 	char* pstr = "hello world";
// 	pstr = "aa";
// 	pstr[1] = "a";	//报错 
// 	cout<<pstr<<endl;
// }


#include<iostream>
#include<string>
 
using namespace std;
 
int main()
{
	string str1;
	str1= "hello world";
	str1="aa";
	// str1[1]="a";
	cout<< ( str1 )<<endl;
   cout << ( 5 % 2 ? ' ' : '\n');
   bool usr_more;
   if (!usr_more)
      cout << usr_more << "4" << endl;
}