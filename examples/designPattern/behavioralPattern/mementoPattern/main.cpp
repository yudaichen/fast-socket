/*******************************************************************************
    @file      main.cpp
    @brief     备忘录模式 ---- 回退历史

    通过一个备忘录类专门存储对象状态


	 1、后悔药。
	 2、打游戏时的存档。
	 3、Windows 里的 ctrl + z。
	 4、IE 中的后退。
	 5、数据库的事务管理

    @details   ~
    @date      15.03.2022
    @copyright ? Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/

#include <iostream>
#include <list>
#include<vector>
#include<string>
#include <tuple>
using namespace std;

//需保存的信息
class Memento
{
public:
	int m_vitality; //生命值
	int m_attack;   //进攻值
	int m_defense;  //防守值
public:
	Memento(int vitality, int attack, int defense) :
		m_vitality(vitality), m_attack(attack), m_defense(defense) {}

	Memento& operator=(const Memento &memento)
	{
		m_vitality = memento.m_vitality;
		m_attack = memento.m_attack;
		m_defense = memento.m_defense;
		return *this;
	}
};
//游戏角色
class GameRole
{
private:
	int m_vitality;
	int m_attack;
	int m_defense;
public:
	GameRole() : m_vitality(100), m_attack(100), m_defense(100) {}
	Memento Save()  //保存进度，只与Memento对象交互，并不牵涉到Caretake
	{
		Memento memento(m_vitality, m_attack, m_defense);
		return memento;
	}
	void Load(Memento memento)  //载入进度，只与Memento对象交互，并不牵涉到Caretake
	{
		m_vitality = memento.m_vitality;
		m_attack = memento.m_attack;
		m_defense = memento.m_defense;
	}
	void Show() { cout << "vitality : " << m_vitality << ", attack : " << m_attack << ", defense : " << m_defense << endl; }
	void Attack() { m_vitality -= 10; m_attack -= 10;  m_defense -= 10; }
};
//保存的进度库
class Caretake
{
public:
	Caretake() = default;
	void Save(Memento memento) { m_vecMemento.push_back(memento); }
	Memento Load(int state) { return m_vecMemento[state]; }
private:
	vector<Memento> m_vecMemento;
};

//测试案例
int main()
{
	Caretake caretake;
	GameRole role;
	role.Show();   //初始值
	caretake.Save(role.Save()); //保存状态

	//进攻后
	role.Attack();
	role.Show();
	role.Load(caretake.Load(0)); //载入状态
	role.Show();  //恢复到状态0

	getchar();
	return 0;
}