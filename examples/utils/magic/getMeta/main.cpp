#include <iostream>
#include <string>
#include <typeinfo>
#include "Meta.hpp"

struct Person
{
    std::string name;
    int age;

    META(name, age)
};

template<typename T>
void func(T& t)
{
    auto ret = t.meta();
    std::cout << typeid(ret).name() << std::endl;
}

// 获取成员变量类型
int main()
{
    Person p {"Jack", 10};
    func(p);
    return 0;
}
