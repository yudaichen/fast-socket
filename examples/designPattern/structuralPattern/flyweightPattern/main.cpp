/*******************************************************************************
    @file      main.cpp
    @brief    享元模式 ---  主要用于减少创建对象的数量，以减少内存占用和提高性能
    					   运用共享技术有效地支持大量细粒度的对象

 案例:
	 1、JAVA 中的 String，如果有则返回，如果没有则创建一个字符串保存在字符串缓存池里面。
	 2、数据库的数据池

 使用场景:
	 1、系统有大量相似对象
	 2、需要缓冲池的场景
    @details   ~
    @date      22.03.2022
    @copyright © Yu Dai Cheng Technologies Co Ltd, 2022. All right reserved.
*******************************************************************************/
#include<iostream>
#include<string>
#include<list>
#include <utility>
#include<vector>
using namespace std;

//棋子颜色
enum PieceColor
{
	BLACK, WHITE
};
//棋子位置
struct PiecePos
{
	int x;
	int y;
	PiecePos(int a, int b)
		: x(a), y(b)
	{}
};
//棋子定义
class Piece
{
protected:
	PieceColor m_color; //颜色
public:
	Piece(PieceColor color)
		: m_color(color)
	{}
	~Piece()
	{}
	virtual void Draw()
	{}
};
class BlackPiece: public Piece
{
public:
	BlackPiece(PieceColor color)
		: Piece(color)
	{}
	~BlackPiece()
	{}
	void Draw()
	{ cout << "绘制一颗黑棋\n" << endl; }
};
class WhitePiece: public Piece
{
public:
	WhitePiece(PieceColor color)
		: Piece(color)
	{}
	~WhitePiece()
	{}
	void Draw()
	{ cout << "绘制一颗白棋\n" << endl; }
};

//棋盘的定义
class PieceBoard
{
private:
	vector<PiecePos> m_vecPos; //存放棋子的位置
	Piece *m_blackPiece;       //黑棋棋子
	Piece *m_whitePiece;       //白棋棋子
	string m_blackName;
	string m_whiteName;
public:
	PieceBoard(string black, string white)
		: m_blackName(std::move(black)), m_whiteName(std::move(white))
	{
		m_blackPiece = nullptr;
		m_whitePiece = nullptr;
	}
	~PieceBoard()
	{
		delete m_blackPiece;
		delete m_whitePiece;
	}
	void SetPiece(PieceColor color, PiecePos pos)
	{
		if (color == BLACK)
		{
			if (m_blackPiece == nullptr)  //只有一颗黑棋
				m_blackPiece = new BlackPiece(color);
			cout << m_blackName << "在位置(" << pos.x << ',' << pos.y << ")" << endl;
			m_blackPiece->Draw();
		}
		else
		{
			if (m_whitePiece == nullptr)
				m_whitePiece = new WhitePiece(color);
			cout << m_whiteName << "在位置(" << pos.x << ',' << pos.y << ")" << endl;
			m_whitePiece->Draw();
		}
		m_vecPos.push_back(pos);
	}
};

int main()
{
	PieceBoard pieceBoard("A", "B");
	pieceBoard.SetPiece(BLACK, PiecePos(4, 4));
	pieceBoard.SetPiece(WHITE, PiecePos(4, 16));
	pieceBoard.SetPiece(BLACK, PiecePos(16, 4));
	pieceBoard.SetPiece(WHITE, PiecePos(16, 16));

	getchar();
	return 0;
}