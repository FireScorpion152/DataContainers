#include"List.h"
#include "List.cpp"

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int value;
	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

	//list.print();
	//list.reverse_print();
	/*for (List::ReverseIterator it = list3.rbegin(); it != list3.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;*/

	List<int> list1 = { 3, 5, 8, 13, 21 };
	List<int> list2 = { 34, 55, 89, 144, 233 };
	List<int> list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	Grow(list3);
	for (int i : list3)cout << i << tab; cout << endl;

	List<double> d_list1 = { 1.4, 4.2, 5.7 };
	List<double> d_list2 = { 3.4, 5.3, 6.2 };
	List<double> d_list3 = d_list1 + d_list2;
	for (double i : d_list3)cout << i << tab; cout << endl;

	List<std::string> s_list1 = { "PV 319 ", "is " };
	List<std::string> s_list2 = { "the best ", "group!" };
	List<std::string> s_list3 = s_list1 + s_list2;
	for (std::string i : s_list3)cout << i; cout << endl;
}