#include <iostream>
#include <ctime>
#include "conio.h"
#include "Windows.h"
using namespace std;

const int board_len = 20;
const int snake_init_len = 4;

struct SnakeNode
{
	int x;
	int y;
	SnakeNode* next_sn;
};

struct Snake
{
	SnakeNode *snh;
	SnakeNode *snt;
	char direction;
};

//初始化一条长度为4的蛇
const Snake &init_snake()
{
	SnakeNode *snp = new SnakeNode;
	SnakeNode *snh = snp;
	int i;
	for (i = 0; i < snake_init_len; i++)
	{
		snp->x = board_len / 2 - 1;
		snp->y = board_len / 2 - 2 + i;
		SnakeNode* snq = new SnakeNode;
		if (i == snake_init_len - 1)
		{
			snp->next_sn = 0;
		}
		else
		{
			snp->next_sn = snq;
			snp = snq;
		}
	}
	SnakeNode *snt = snp;
	Snake shnt;
	shnt.snh = snh;
	shnt.snt = snt;
	shnt.direction = 'l';
	return shnt;
}

const SnakeNode &generate_point(const Snake& shnt)
{
	srand(time(0));
	//检查新生成的豆子是否在蛇的身上
	SnakeNode *snp = shnt.snh;
	int x, y;
	while (1)
	{
		x = rand() % (board_len - 1);
		y = rand() % (board_len - 1);
		while (snp)
		{
			if (snp->x == x && snp->y == y)
			{
				break;
				continue;
			}
			else
			{
				snp = snp->next_sn;
			}
		}
		break;
	}
	SnakeNode *pp = new SnakeNode;
	pp->x = x;
	pp->y = y;
	return *pp;
}


//这个函数有三个功能:
//检查蛇头是否撞墙
//检查蛇头是否咬到自己身体
//检查蛇头前方是否有豆子
int test_collision(const Snake& shnt, const SnakeNode& point)
{
	SnakeNode *head = shnt.snh;
	int x = head->x;
	int y = head->y;
	//检查蛇头坐标
	if (x < 0 || y < 0 || x > board_len - 1 || y > board_len - 1)
	{
		return -1;
	}
	SnakeNode *p = head->next_sn;
	//检查蛇是否咬到自己的身体
	while (p)
	{
		int next_x = p->x;
		int next_y = p->y;
		if (next_x == x && next_y == y)
		{
			return -2;
		}
		p = p->next_sn;
	}
	//吃到豆子
	char direction = shnt.direction;
	if (direction == 'l' && head->y - 1 == point.y && head->x == point.x)
	{
		return 0;
	}
	else if (direction == 'r' && head->y + 1 == point.y && head->x == point.x)
	{
		return 0;
	}
	else if (direction == 'u' && head->x - 1 == point.x && head->y == point.y)
	{
		return 0;
	}
	else if (direction == 'd' && head->x + 1 == point.x && head->y == point.y)
	{
		return 0;
	}
	//一般游动
	return 1;
}

int move_elongate_snake(Snake *shnt, const SnakeNode& point)
{
	//test_collision返回值为0的时候表示吃到了豆子，这时豆子作为新头
	if (!test_collision(*shnt, point))
	{
		SnakeNode *snp = new SnakeNode;
		snp->x = point.x;
		snp->y = point.y;
		//原来的头变成了第二结点
		snp->next_sn = shnt->snh;
		shnt->snh = snp;
		return 0;
	}
	int kb_input = 0;
	int useless = 0;
	time_t start_time = time(0);
	while (1)
	{
		//等一定的时间，这段时间内没有输出就跳出；这个时间可以调整
		if (_kbhit())
		{
			useless = _getch();
			kb_input = _getch();
			Sleep(200);
			break;
		}
		time_t end_time = time(0);
		double diff_time = difftime(end_time, start_time);
		if (diff_time >= 0.3)
		{
			break;
		}
	}
	//如果按的是上下方向键
	if (kb_input == 72 || kb_input == 80)
	{
		if (shnt->direction == 'u' || shnt->direction == 'd');
		else
		{
			SnakeNode *snp = new SnakeNode;
			snp->y = shnt->snh->y;
			if (kb_input == 72)
			{
				shnt->direction = 'u';
				snp->x = shnt->snh->x - 1;
			}
			else
			{
				shnt->direction = 'd';
				snp->x = shnt->snh->x + 1;
			}
			snp->next_sn = shnt->snh;
			shnt->snh = snp;
			SnakeNode *p = shnt->snh;
			while (p->next_sn->next_sn)
			{
				p = p->next_sn;
			}
			p->next_sn = NULL;
			p = shnt->snh;
		}
	}
	//如果按的是左右方向键
	else if (kb_input == 75 || kb_input == 77)
	{
		if (shnt->direction == 'l' || shnt->direction == 'r');
		else
		{
			SnakeNode *snp = new SnakeNode;
			snp->x = shnt->snh->x;
			if (kb_input == 75)
			{
				shnt->direction = 'l';
				snp->y = shnt->snh->y - 1;
			}
			else
			{
				shnt->direction = 'r';
				snp->y = shnt->snh->y + 1;
			}
			snp->next_sn = shnt->snh;
			shnt->snh = snp;
			SnakeNode *p = shnt->snh;
			while (p->next_sn->next_sn)
			{
				p = p->next_sn;
			}
			p->next_sn = 0;
			p = shnt->snh;
		}
	}
	//其他情况，包括不按键或者按的不是方向键的情况
	else
	{
		if (shnt->direction == 'l')
		{
			SnakeNode *snp = new SnakeNode;
			snp->x = shnt->snh->x;
			snp->y = shnt->snh->y - 1;
			snp->next_sn = shnt->snh;
			shnt->snh = snp;
		}
		else if (shnt->direction == 'r')
		{
			SnakeNode *snp = new SnakeNode;
			snp->x = shnt->snh->x;
			snp->y = shnt->snh->y + 1;
			snp->next_sn = shnt->snh;
			shnt->snh = snp;
		}
		else if (shnt->direction == 'u')
		{
			SnakeNode *snp = new SnakeNode;
			snp->y = shnt->snh->y;
			snp->x = shnt->snh->x - 1;
			snp->next_sn = shnt->snh;
			shnt->snh = snp;
		}
		else
		{
			SnakeNode *snp = new SnakeNode;
			snp->y = shnt->snh->y;
			snp->x = shnt->snh->x + 1;
			snp->next_sn = shnt->snh;
			shnt->snh = snp;
		}
		SnakeNode *p = shnt->snh;
		while (p->next_sn->next_sn)
		{
			p = p->next_sn;
		}
		p->next_sn = 0;
		shnt->snt = p;
	}
	return 1;
}

void show_snake(const Snake& shnt, const SnakeNode& point)
{
	system("cls");
	int i, j;
	for (i = 0; i < board_len; i++)
	{
		for (j = 0; j < board_len; j++)
		{
			SnakeNode *p = shnt.snh;
			while (p)
			{
				if (p->x == i && p->y == j && p == shnt.snh)
				{
					cout << "H ";
					break;
				}
				else if (p->x == i && p->y == j)
				{
					cout << "S ";
					break;
				}
				else
				{
					p = p->next_sn;
				}
			}
			if (!p)
			{
				if (point.x == i && point.y == j)
				{
					cout << "O ";
				}
				else
				{
					cout << "- ";
				}
			}
		}
		cout << endl;
	}
}

int main()
{
	Snake shnt = init_snake();
	while (1)
	{
		SnakeNode point = generate_point(shnt);
		//
		while (!test_collision(shnt, point) || test_collision(shnt, point) == 1)
		{
			show_snake(shnt, point);
			if (!move_elongate_snake(&shnt, point))
			{
				break;
			}
		}
		if (test_collision(shnt, point) == -1 || test_collision(shnt, point) == -2)
		{
			break;
		}
	}
	cout << "游戏结束" << endl;
	return 0;
}





