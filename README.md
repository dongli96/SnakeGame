# SnakeGame
贪吃蛇游戏/Snake Game
##### 这个C程序涉及到：
##### 1.结构和链表的灵活使用
##### 2.自编函数尽量不要返回结构指针（int\*, double\*等指向简单类型的指针都没问题）
##### 3.C语言随机数和随机种子的理解，为什么srand(time(0))语句只需要使用一次，而不需要在每个rand()前面都加
##### 4.为什么在链表添加结点的时候要用malloc()函数？因为如果直接定义一个结构变量（局部变量）然后连到链表中，离开函数就会被释放，会出现各种错误
##### 5.\_getch()和\_kbhit()的使用
##### 6.碰撞检测和蛇的拐弯
##### 7.以后还可以加一个可视化界面，还可以加一个从本地读入的游戏存档的功能；可以加上连网的功能，多个玩家互相PK
