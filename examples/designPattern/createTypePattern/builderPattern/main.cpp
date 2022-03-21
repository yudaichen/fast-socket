/*******************************************************************************
    @file      main.cpp
    @brief     构建者模式  肯德基，汉堡、可乐、薯条、炸鸡翅等是不变的，而其组合是经常变化的，生成出所谓的"套餐"
    使用场景: 使得同样的构建过程可以创建不同的表示
    使用方式: 建造者：创建和提供实例，导演：管理建造出来的实例的依赖关系
    优点: 1、建造者独立，易扩展。 2、便于控制细节风险
	缺点:  1、产品必须有共同点，范围有限制。 2、如内部变化复杂，会有很多的建造类。

    @details   ~
    @date      15.03.2022
    @copyright © Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief 人类构造器
 */
class humanBuilder {

public:
	virtual void BuildHead() = 0;

	virtual void BuildBody() = 0;

	virtual void BuildLeftArm() = 0;

	virtual void BuildRightArm() = 0;

	virtual void BuildLeftLeg() = 0;

	virtual void BuildRightLeg() = 0;
};

/**
 * @brief 创建一个瘦子
 */
class ThinBuilder : public humanBuilder {
public:
	void BuildHead() override
	{ cout << "build thin body" << endl; }

	void BuildBody() override
	{ cout << "build thin head" << endl; }

	void BuildLeftArm() override
	{ cout << "build thin left arm" << endl; }

	void BuildRightArm() override
	{ cout << "build thin right arm" << endl; }

	void BuildLeftLeg() override
	{ cout << "build thin left leg" << endl; }

	void BuildRightLeg() override
	{ cout << "build thin right leg" << endl; }

};

/**
 * @brief 创建一个胖子
 */
class FatBuilder : public humanBuilder {
public:
	void BuildHead() override
	{ cout << "build fat body" << endl; }

	void BuildBody() override
	{ cout << "build fat head" << endl; }

	void BuildLeftArm() override
	{ cout << "build fat left arm" << endl; }

	void BuildRightArm() override
	{ cout << "build fat right arm" << endl; }

	void BuildLeftLeg() override
	{ cout << "build fat left leg" << endl; }

	void BuildRightLeg() override
	{ cout << "build fat right leg" << endl; }
};

/**
 * @brief 构造的指挥官 类似于 导演：管理建造出来的实例的依赖关系
 */
class Director {
private:
	humanBuilder *m_pBuilder;

public:
	explicit Director(humanBuilder *builder)
	{ m_pBuilder = builder; }

	Director() = default;

	void Create()
	{
		m_pBuilder->BuildHead();
		m_pBuilder->BuildBody();
		m_pBuilder->BuildLeftArm();
		m_pBuilder->BuildRightArm();
		m_pBuilder->BuildLeftLeg();
		m_pBuilder->BuildRightLeg();
	}
};

int main(int argc, char *argv[])
{
	// 导演出一个胖子
	Director *directorForFat = new Director(new FatBuilder());
	directorForFat->Create();

	// 导演出一个瘦子
	Director *directorForThin = new Director(new ThinBuilder());
	directorForThin->Create();

	return 0;
}