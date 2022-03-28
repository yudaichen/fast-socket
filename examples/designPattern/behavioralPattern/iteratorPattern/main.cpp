/*******************************************************************************
    @file      main.cpp
    @brief     迭代器模式

	 Iterator 模式也正是用来解决对一个聚合对象的遍历问题，将对聚合的遍历封装到一个
	类中进行，这样就避免了暴露这个聚合对象的内部表示的可能

	Iterator: 抽象迭代器
	ConcreteIterator: 具体迭代器
	Aggregate: 抽象聚合类
	ConcreteAggregate: 具体聚合类

    @details   ~
    @date      15.03.2022
    @copyright ? Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/

#include <iostream>
#include <list>
#include<vector>

using namespace std;


class String;
class Iterator
{
public:
	Iterator(String* ps, int idx)
		:pstr(ps), index(idx)
	{}
	bool operator!=(const Iterator rhs) const
	{
		return index != rhs.index;
	}
	const Iterator operator++(int)
	{
		const Iterator tmp(*this);
		index++;
		return tmp;
	}
	Iterator& operator++()
	{
		index++;
		return *this;
	}
	char& operator*();
private:
	String* pstr;
	int index;
};
class String
{
public:
	typedef Iterator iterator;
	explicit String(char* ptr)
	{
		mptr = new char[strlen(ptr) + 1]();
		strcpy_s(mptr, strlen(ptr) + 1, ptr);
	}
	String(const String& rhs)
	{
		mptr = new char[strlen(rhs.mptr) + 1]();
		strcpy_s(mptr, strlen(rhs.mptr) + 1, rhs.mptr);
	}
	String& operator=(const String& rhs)
	{
		if (this != &rhs)
		{
			delete[] mptr;
			mptr = new char[strlen(rhs.mptr) + 1]();
			strcpy_s(mptr, strlen(rhs.mptr) + 1, rhs.mptr);
		}
		return *this;
	}
	~String()
	{
		delete[] mptr;
		mptr = NULL;
	}
	iterator begin()
	{
		return iterator(this, 0);
	}
	//迭代器区间   [)
	iterator end()
	{
		return iterator(this, strlen(mptr));//"hello"  5
	}
	char& operator[](int index)
	{
		return mptr[index];
	}
private:
	char* mptr;
};
//String str("hello"); str[0]// str[1] str[2]
char& Iterator::operator*()
{
	return (*pstr)[index];
}

int main()
{
	int arr[] = { 53, 46, 546, 8, 70, 4 };
	int len = sizeof(arr) / sizeof(arr[0]);
	std::vector<int> vec(arr, arr+len);//char*
	std::vector<int>::iterator it = vec.begin();//it 迭代器   面向对象的指针
	while (it != vec.end())
	{
		std::cout << *it << " ";//operator*
		it++;
	}
	std::cout << std::endl;
	return 0;
}