// #include <stdio.h>
// int main()
// {

//    // char name[100];
//    // printf("What is your name?\n");
//    // scanf("%s",name);
//    // printf("Hello,%s,nice to meet you!\n",name);
   
// }



#include<iostream>
#include<string>
#include<vector>

using namespace std;
 
int main()
{
	
	int seq_size = 10;
	int elem_vals[seq_size] = {
		1, 2, 3, 4, 5 , 6, 7, 8, 9, 10
	};

	for (int i=0; i<seq_size; i++)
	{
		cout << elem_vals[i] << " " << endl;
		// elem_vals.size() << endl;
	}
	
	vector<int> elem_seq(elem_vals, elem_vals+seq_size);
	for (int i=0; i<seq_size; i++)
	{
		cout << elem_seq[i] << " " <<
		elem_seq.size() << endl;
	}
} 