#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include"contact.h"
void menu()
{
	printf("******************************************\n");
	printf("*****1.����        2.����*****************\n");
	printf("*****3.Ѱ��        4.�޸�*****************\n");
	printf("*****5.��ӡ        6.����*****************\n");
	printf("**************0.�˳�************************\n");
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
		printf("��ѡ��ѡ��:>");
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
		case SAVE:Savecontact(&con); printf("����ɹ�\n");
			break;//����break����һ��default

		case RETURN:printf("�˳��ɹ�,��������:"); Destroycontact(&con);
			break;
		default:printf("ѡ�����\n"); break;


		}
	} while (input);
	return 0;
}