/*******************************************************************************
    @file      main.cpp
    @brief    策略模式 ----允许一个对象在其内部状态改变时改变它的行为



	 1、诸葛亮的锦囊妙计，每一个锦囊就是一个策略。
	 2、旅行的出游方式，选择骑自行车、坐汽车，每一种旅行方式都是一个策略。
	 3、JAVA AWT 中的 LayoutManager


	 如果一个系统的策略多于四个，
	 就需要考虑使用混合模式，
	 解决策略类膨胀的问题


    @details   ~
    @date      15.03.2022
    @copyright ? Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/

#include<iostream>
#include<string>
#include<list>
#include<vector>
using namespace std;


//抽象接口
class ReplaceAlgorithm
{
public:
	virtual void Replace() = 0;
};
//三种具体的替换算法
class LRU_ReplaceAlgorithm: public ReplaceAlgorithm
{
public:
	void Replace() override
	{ cout << "Least Recently Used replace algorithm" << endl; }
};

class FIFO_ReplaceAlgorithm: public ReplaceAlgorithm
{
public:
	void Replace() override
	{ cout << "First in First out replace algorithm" << endl; }
};
class Random_ReplaceAlgorithm: public ReplaceAlgorithm
{
public:
	void Replace() override
	{ cout << "Random replace algorithm" << endl; }
};

//Cache需要用到替换算法 最近最少使用 、 先进先出 、随机
enum RA
{
	LRU, FIFO, RANDOM
};

class Cache
{
private:
	ReplaceAlgorithm *m_ra;
public:
	explicit Cache(enum RA ra)
	{
		if (ra == LRU)
			m_ra = new LRU_ReplaceAlgorithm();
		else if (ra == FIFO)
			m_ra = new FIFO_ReplaceAlgorithm();
		else if (ra == RANDOM)
			m_ra = new Random_ReplaceAlgorithm();
		else
			m_ra = nullptr;
	}
	~Cache()
	{ delete m_ra; }
	void Replace()
	{ m_ra->Replace(); }
};

int main()
{
	Cache cache(LRU); //指定标签即可
	cache.Replace();
	getchar();
	return 0;
}