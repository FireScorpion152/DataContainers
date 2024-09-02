#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

void main()
{
	setlocale(LC_ALL, "");
	int arr[] = { 3, 5, 8, 13, 21 };
	cout << arr << endl;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << *(arr + i) << tab;
	}
	cout << endl;
	nullptr;
}