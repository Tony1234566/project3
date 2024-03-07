#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include"contact.h"
void menu()
{
	printf("******************************************\n");
	printf("*****1.增加        2.减少*****************\n");
	printf("*****3.寻找        4.修改*****************\n");
	printf("*****5.打印        6.保存*****************\n");
	printf("**************0.退出************************\n");
	printf("******************************************\n");
}

enum {
	RETURN,
	ADD,
	DEL,
	SEARCH,
	CONCEL,
	SHOW,
	SAVE
};

int main()
{	
	Contact con;
	InitContact(&con);
	int input = 0;
	do
	{
		menu();
		printf("请选择选项:>");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:Addcontact(&con);
			break;
		case DEL:Delcontact(&con);
			break;
		case SEARCH:Searchcontact(&con);
			break;
		case CONCEL:Concelcontact(&con);
			break;
		case SHOW:Showcontact(&con);
			break;
		case SAVE:Savecontact(&con); printf("保存成功\n");
			break;//不加break会走一下default

		case RETURN:printf("退出成功,重启继续:"); Destroycontact(&con);
			break;
		default:printf("选择错误\n"); break;


		}
	} while (input);
	return 0;
}