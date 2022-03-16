#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <string.h>
using namespace std;

const int SUCC = 100; //使用常量替代枚举类型
const int FAIL = 101;
const int ONGO = 102;
const int SIZE = 10;
const int OPENED = 0;
const int CLOSED = 1;
const int SIGNED = 2;

class Grid
{
	bool hasBomb;
	int NeighborBombNums;
	char GridIcon;
	int CurrentGridStat;

public:
	void Reset();
	Grid()
	{
		NeighborBombNums = 0;
		hasBomb = false;
		GridIcon = ' ';
		CurrentGridStat = CLOSED;
	}																												 //构造函数初始化
	void sethasBomb(bool a) { hasBomb = a; };								 // bool 型设置雷数
	bool ishasBomb() { return hasBomb; };										 //是否有雷
	void setNeighborBombNums() { NeighborBombNums++; };			 //周围雷数加1
	int getCurrentGridStat() { return CurrentGridStat; }		 //返回此棋子的当前状态
	void setCurrentGridStat(int x) { CurrentGridStat = x; }; //设置当前棋子状态
	void decideGridIcon();
	char getGridIcon() { return GridIcon; } // 返回当前真实图标
	char PrintGridIcon();
};
void Grid ::Reset() //清空Grid
{
	NeighborBombNums = 0;
	hasBomb = false;
	GridIcon = ' ';
	CurrentGridStat = CLOSED;
}
char Grid::PrintGridIcon() //用于打印的Icon
{
	if (CurrentGridStat == CLOSED)
	{
		return '-';
	} //根据状态显示是否为真实Icon
	if (CurrentGridStat == OPENED)
	{
		return GridIcon;
	}
	if (CurrentGridStat == SIGNED)
	{
		return '!';
	}
	return 0;
};

void Grid::decideGridIcon()
{ //定义图标

	if (hasBomb)
	{
		GridIcon = '*'; //有雷图标 “*”
	}
	else
	{
		if (NeighborBombNums == 0)
		{
			GridIcon = ' '; //空白图标
		}
		else
		{
			GridIcon = NeighborBombNums + 48; //ASCII码加48为相应的字符asc码
		};
	};
};

class Panel
{ //定义棋盘类
	Grid GridSet[SIZE + 1][SIZE + 1];
	int iBombNums, iSignedNums, iOpenedNums, gamestat;

public:
	void Reset();
	Panel()
	{
		iBombNums = 0;
		iSignedNums = 0;
		iOpenedNums = 0;
	}
	void arrangeBombs();
	char getGridIcon(int x, int y); //没用到 否则是函数更复杂
	void displayPanel();
	int judgeGameStat();
	void openGrid(int x, int y);
	void final_displayPanel();
	void setBombNums()
	{
		cout << "请输入雷数(少于20)" << endl;
		cin >> iBombNums;
	};
	int getOpenedNums();
	int getRestNums() { return (iBombNums - iSignedNums); }
	void SignGrid(int x, int y) { GridSet[x][y].setCurrentGridStat(SIGNED); }; //标记棋子函数
};
void Panel::Reset() //清空Panel
{
	int x, y;
	iBombNums = 0;
	iSignedNums = 0;
	iOpenedNums = 0;
	for (x = 1; x <= SIZE; x++)
		for (y = 1; y <= SIZE; y++)
		{
			GridSet[x][y].Reset();
		};
}
void Panel::final_displayPanel() //最终显示结果函数
{
	int x, y;
	for (x = 1; x <= SIZE; x++)
	{
		for (y = 1; y <= SIZE; y++)
		{
			if (GridSet[x][y].ishasBomb())
			{
				if (GridSet[x][y].getCurrentGridStat() != SIGNED)
				{
					GridSet[x][y].setCurrentGridStat(OPENED);
				}; //设置有雷的为打开
			};
		}
	};
	displayPanel(); //调用显示函数
};

int Panel::judgeGameStat() //判断状态是否succ or fail
{
	int x, y;
	int n = 0, m = 0;
	iOpenedNums = 0;
	iSignedNums = 0; //循环前设置初始值为0
	for (x = 1; x <= SIZE; x++)
	{
		for (y = 1; y <= SIZE; y++)
		{
			if (GridSet[x][y].ishasBomb())
			{
				if (GridSet[x][y].getCurrentGridStat() == SIGNED)
				{
					iSignedNums = iSignedNums + 1;
				}; //标识数加一
				if (GridSet[x][y].getCurrentGridStat() == OPENED)
				{
					return FAIL;
				}; //返回失败
			}
			else
			{

				if (GridSet[x][y].getCurrentGridStat() == OPENED)
				{
					iOpenedNums = iOpenedNums + 1;
				}; //正确数加一
			};
		};
	};
	if ((iSignedNums == iBombNums) || (iOpenedNums == (SIZE * SIZE - iBombNums)))
	{
		return SUCC;
	} // 剩余棋子数等于雷数返回成功
	else
	{
		return ONGO;
	} //  返回继续
};

void Panel::arrangeBombs() //随机布雷函数
{
	int x, y;
	int n = 0;
	srand(unsigned(time(0)));
	while (n < iBombNums)
	{
		x = 1 + rand() % (SIZE - 1);
		y = 1 + rand() % (SIZE - 1);

		if (GridSet[x][y].ishasBomb() == false)
		{
			GridSet[x][y].sethasBomb(true);

			if (x <= SIZE)
			{
				GridSet[x + 1][y].setNeighborBombNums();
			}; //周围雷数加一
			if (x <= SIZE && y < SIZE)
			{
				GridSet[x + 1][y + 1].setNeighborBombNums();
			};
			if (x <= SIZE && y > 1)
			{
				GridSet[x + 1][y - 1].setNeighborBombNums();
			};
			if (y > 1)
			{
				GridSet[x][y - 1].setNeighborBombNums();
			};
			if (y <= SIZE)
			{
				GridSet[x][y + 1].setNeighborBombNums();
			};
			if (x > 1)
			{
				GridSet[x - 1][y].setNeighborBombNums();
			}
			if (x > 1 && y <= SIZE)
			{
				GridSet[x - 1][y + 1].setNeighborBombNums();
			};
			if (x > 1 && y > 1)
			{
				GridSet[x - 1][y - 1].setNeighborBombNums();
			};
			n = n + 1;
		};
	};
	for (x = 1; x <= SIZE; x++) //所有雷初始化图标
	{
		for (y = 1; y <= SIZE; y++)
		{
			GridSet[x][y].setCurrentGridStat(CLOSED);
			GridSet[x][y].decideGridIcon(); //设置初始没有翻开；决定棋子的图标值
		}
	};
};

void Panel::displayPanel() //显示棋盘函数
{
	int x, y;
	cout << "   y";
	for (x = 1; x <= SIZE; x++)
	{
		cout << " " << x;
	}; //打印边框
	cout << endl;
	for (x = 1; x <= SIZE; x++)
	{
		cout << "____";
	};
	cout << endl;

	for (x = 1; x <= SIZE; x++)
	{
		printf("%3d|", x);
		for (y = 1; y <= SIZE; y++)
		{

			cout << " " << GridSet[x][y].PrintGridIcon(); //打印获取的图标
		}
		cout << endl;
	};
	cout << "x" << endl;
};

void Panel::openGrid(int x, int y) //递归调用翻开所有空白块
{

	if (x >= 1 && x <= SIZE && y >= 1 && y <= SIZE && GridSet[x][y].getCurrentGridStat() != OPENED)
	{
		GridSet[x][y].setCurrentGridStat(OPENED); //设置已翻开状态
		if (GridSet[x][y].ishasBomb() == false)
		{

			if (GridSet[x][y].getGridIcon() == ' ') //周围空格打开
			{
				openGrid(x + 1, y);
				openGrid(x + 1, y + 1);
				openGrid(x + 1, y);
				openGrid(x - 1, y + 1);
				openGrid(x - 1, y - 1);
				openGrid(x - 1, y);
				openGrid(x, y + 1);
				openGrid(x, y - 1);
			};
		};
	};
};

class Console
{
	Panel aPanel;
	char chos;
	int menu;

public:
	void Reset();
	void start(); //开始游戏
	void Menu();
	void Choose();
	void ChooseStat();
	void nextFrame();
};

void Console::start() //开始游戏
{
	aPanel.Reset(); //净空
	cout << "游戏开始！";

	aPanel.setBombNums();	 //获取雷数
	aPanel.arrangeBombs(); //随机布雷

	nextFrame();
};

void Console::nextFrame()
{
	int i, q, p;
	i = 0;
	aPanel.displayPanel();
	Menu();
	switch (menu) //选择menu的选项
	{
	case 1:
		cout << "请输入挖开的雷x坐标:"; //输入打开的坐标
		cin >> q;
		cout << "请输入挖开的雷y坐标:";
		cin >> p;
		aPanel.openGrid(q, p);
		break;
	case 2:
		cout << "请输入标记的雷x坐标:"; //输入标记的坐标
		cin >> q;
		cout << "请输入标记的雷y坐标:";
		cin >> p;
		aPanel.SignGrid(q, p);
		break;
	case 3:
		cout << endl
				 << "还剩下“" << aPanel.getRestNums() << "”个雷没有被标记。" << endl;
		break;
	case 4:
		start();
		break;
	case 5:
		exit(0);
		break;
	};
	ChooseStat();
}

void Console::ChooseStat()
{
	switch (aPanel.judgeGameStat()) //判断下一个状态是否继续
	{
	case FAIL:
		aPanel.final_displayPanel();
		cout << "你失败了！！！" << endl;
		Choose();
		break;
	case SUCC:
		aPanel.final_displayPanel();
		cout << "你成功了！！！" << endl;
		Choose();
		break;
	case ONGO:
		nextFrame();
		break;
	};
}

void Console::Menu() //UI的选择菜单
{
	menu = 0;
	cout << " 1=>挖雷   2=>标记  3=>剩余雷数  4=>重启  5=>退出游戏" << endl;
	cout << "please choose:" << endl;
	cin >> menu;
};
void Console::Choose() //选择是否继续游戏
{
	cout << "是否继续？（Y/N)";
	cin >> chos;
	if (chos == 'y' || chos == 'Y')
	{
		start();
	}
	else
	{
		exit(0);
	}
};

int main()
{
	Console c1;
	c1.start();
	cout << "c++ 期中考试 电子（2）班  苗壮 学号：2011210889" << endl;
	return 0;
}