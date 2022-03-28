/*******************************************************************************
    @file      main.cpp
    @brief    状态模式 ----允许一个对象在其内部状态改变时改变它的行为



	 1、行为随状态改变而改变的场景
	 2、条件、分支语句的代替

	 在行为受状态约束的时候使用状态模式
	 而且状态不超过 5 个


    @details   ~
    @date      15.03.2022
    @copyright ? Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/

#include <iostream>
#include <list>

using namespace std;

class War;

// 状态基类
class State
{
public:
	virtual void Prophase() {}
	virtual void Metaphase() {}
	virtual void Anaphase() {}
	virtual void End() {}
	virtual void CurrentState(War *war) {}
};

//战争
class War
{
private:
	State *m_state;  //目前状态
	int m_days;      //战争持续时间
public:
	War(State *state) : m_state(state), m_days(0) {}
	~War() { delete m_state; }
	int GetDays() { return m_days; }
	void SetDays(int days) { m_days = days; }
	void SetState(State *state) { delete m_state; m_state = state; }
	void GetState() { m_state->CurrentState(this); }
};

//战争结束
class EndState : public State
{
public:
	void End(War *war) //结束阶段的具体行为
	{
		cout << "战争结束" << endl;
	}
	void CurrentState(War *war) override { End(war); }
};
//后期
class AnaphaseState : public State
{
public:
	void Anaphase(War *war) //后期的具体行为
	{
		if (war->GetDays() < 30)
			cout << "第" << war->GetDays() << "天：战争后期，双方拼死一搏" << endl;
		else
		{
			war->SetState(new EndState());
			war->GetState();
		}
	}
	void CurrentState(War *war) override { Anaphase(war); }
};

//中期
class MetaphaseState : public State
{
public:
	void Metaphase(War *war) //中期的具体行为
	{
		if (war->GetDays() < 20)
			cout << "第" << war->GetDays() << "天：战争中期，进入相持阶段，双发各有损耗" << endl;
		else
		{
			war->SetState(new AnaphaseState());
			war->GetState();
		}
	}
	void CurrentState(War *war) override { Metaphase(war); }
};

//前期
class ProphaseState : public State
{
public:
	void Prophase(War *war)  //前期的具体行为
	{
		if (war->GetDays() < 10)
			cout << "第" << war->GetDays() << "天：战争初期，双方你来我往，互相试探对方" << endl;
		else
		{
			war->SetState(new MetaphaseState());
			war->GetState();
		}
	}
	void CurrentState(War *war) override { Prophase(war); }
};


//测试案例
int main()
{
	War *war = new War(new ProphaseState());
	for (int i = 1; i < 40; i += 5)
	{
		war->SetDays(i);
		war->GetState();
	}
	delete war;
	getchar();
	return 0;
}