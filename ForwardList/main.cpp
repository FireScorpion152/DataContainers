#include<iostream>
using namespace std;
using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		count++;
	}
	~Element()
	{
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}
	friend class ForwardList;
};
int Element::count = 0;

class ForwardList
{
	Element* Head;
	unsigned int size;
public:
	ForwardList()
	{
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);*/

		*this = other;

		cout << "LCopyConstructor: " << this << endl;
	}
	ForwardList(ForwardList&& other)noexcept
	{
		/*this->Head = other.Head;
		this->size = other.size;

		other.size = 0;
		other.Head = nullptr;*/

		*this = std::move(other);

		cout << "LMoveConstructor: " << this << endl;
	}
	~ForwardList()
	{
		while (Head) pop_front();
		pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//	Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other) return *this;

		while (Head)
			pop_front();

		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_front(Temp->Data);

		reverse();

		cout << "LCopyAssignment: " << this << endl;

		return *this;
	}
	ForwardList& operator=(ForwardList&& other)noexcept
	{
		if (this == &other) return *this;

		while (Head)
			pop_front();

		this->Head = other.Head;
		this->size = other.size;

		other.size = 0;
		other.Head = nullptr;

		cout << "LMoveAssignment: " << this << endl;

		return *this;
	}

	class Iterator
	{
		Element* Iter;
	public:
		Iterator(Element* Iter) :Iter(Iter) {}
		~Iterator() {}

		Iterator operator++()
		{
			Iter = Iter->pNext;
			return *this;
		}
		int operator*() const
		{
			return Iter->Data;
		}
		bool operator!=(const Iterator& other) const
		{
			return Iter != other.Iter;
		}
	};

	class ConstIterator
	{
		Element* ConstIter;
	public:
		ConstIterator(Element* ConstIter) :ConstIter(ConstIter) {}
		~ConstIterator() {}

		ConstIterator operator++()
		{
			ConstIter = ConstIter->pNext;
			return *this;
		}
		const int operator*() const
		{
			return ConstIter->Data;
		}
		bool operator!=(const ConstIterator& other) const
		{
			return ConstIter != other.ConstIter;
		}
	};

	Iterator begin()
	{
		return Iterator(Head);
	}
	Iterator end()
	{
		return Iterator(nullptr);
	}
	ConstIterator begin() const
	{
		return ConstIterator(Head);
	}
	ConstIterator end() const
	{
		return ConstIterator(nullptr);
	}

	//	Adding elements:
	void push_front(int Data)
	{
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/

		Head = new Element(Data, Head);

		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);

		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;

		/*Element* New = new Element(Data);
		Temp->pNext = New;*/

		Temp->pNext = new Element(Data);
		size++;
	}
	void pop_front()
	{
		if (Head == nullptr) return;
		Element* Temp = Head;
		Head = Head->pNext;
		delete Temp;
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr || Head->pNext == nullptr) return pop_front();

		Element* Temp = Head;
		while (Temp->pNext->pNext)
			Temp = Temp->pNext;

		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}
	void insert(int Data, int index)
	{
		if (index > Head->count) return;
		if (index == 0) return push_front(Data);

		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;

		/*Element* New = new Element(Data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/

		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	void erase(int index)
	{
		if (index > size) return;
		if (index == 0) return pop_front();

		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
			Temp = Temp->pNext;

		Element* errased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete errased;

		size--;
	}

	//	Methods:
	void reverse()
	{
		ForwardList buffer;

		while (Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}

		this->Head = buffer.Head;
		this->size = buffer.size;
		buffer.Head = nullptr;
	}
	void print()const
	{
		cout << "Head:\t" << Head << endl;

		/*Element* Temp = Head;	//Temp - это итератор
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;
		}*/

		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;

		cout << "Количество элементов списка: " << size << endl;
		cout << "Общее количество элементов списка: " << Element::count << endl;
	}
};
std::ostream& operator<<(std::ostream& os, const Element& el)
{
	return os << el;
}

//#define BASE_CHECK
//#define PERFOMANCE_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	//Element element(5);
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.push_back(123);
	list.print();

	list.pop_front();
	list.pop_back();
	list.print();

	int index;
	cout << "Введите индекс вставляемого элемента: "; cin >> index;
	list.insert(234, index);
	list.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
#endif // BASE_CHECK

#ifdef PERFOMANCE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//if (i % (1024*1024) == 0) cout << i << tab;
		list.push_front(rand() % 100);
		//list.push_back(rand() % 100);
	}
	cout << "List filled" << endl;
	list.print();

	//ForwardList list2 = list;
	ForwardList list2 = std::move(list);
	//ForwardList list2;
	//list2 = list;
	//list2 = std::move(list);
	list2.print();
#endif // PERFOMANCE_CHECK


#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3, 5, 8, 13, 21, 34, 55, 89, 144 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;

	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;

	Print(arr);
#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3, 5, 8, 13, 21 };

	//list.print();

	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST
}