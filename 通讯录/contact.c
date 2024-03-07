#define _CRT_SECURE_NO_WARNINGS 1
#include "contact.h"

////静态版本
//void InitContact(Contact* pc)
//{
//	pc->sz = 0;
//	memset(pc->data, 0, sizeof(pc->data));
//}

//动态版本
void InitContact(Contact* pc)
{
	PeoInfo* ptr = (PeoInfo*)malloc(DEFAULT_SZ * sizeof(PeoInfo));
	if (ptr == NULL)
	{
		return;
	}
	else
	{
		pc->data = ptr;
		pc->capacity = DEFAULT_SZ;
		pc->sz = 0;
		pc->autosave = 0;
	}
	Download(pc);//文件操作添加代码
}

//文件操作添加函数
void Download(Contact* pc)
{
	FILE* pf = fopen("Contact.dat", "r");

	if (pf == NULL)
	{
		perror("SaveContact");
		return;
	}

	PeoInfo tmp = {0};
	
	while (fread(&tmp, sizeof(PeoInfo), 1, pf) )
	{
		CheckCapacity(pc);
		pc->data[pc->sz] = tmp;
		pc->sz++;
		
	}

	fclose(pf);
	pf = NULL;
}

//动态版本添加函数
void Destroycontact(Contact* pc)
{
	free(pc->data);
	pc->data = NULL;
	pc->sz = 0;
	pc->capacity = 0;
}

int Search(Contact* pc)
{
	char nam[MAX_NAME];
	scanf("%s", nam);
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		if (strcmp(pc->data[i].name, nam) == 0)//if (pc->data[i].name == nam)这样是错误的
		{
			return i;
		}
	}
	return -1;

}

void CheckCapacity(Contact* pc)
{
	if (pc->sz == pc->capacity)
	{
		//PeoInfo* ptr = (PeoInfo*)realloc(pc->data,INC_SZ * sizeof(PeoInfo)+sizeof(pc->data)); error 思考一下为什么：pc->data只有一个PeoInfo类型指针的大小(本机器是八个字节)
		
		PeoInfo* ptr = (PeoInfo*)realloc(pc->data, (INC_SZ+pc->capacity) * sizeof(PeoInfo) );
		if (ptr == NULL)
		{
			return;
		}
		else
		{
			pc->data = ptr;
			printf("增容成功\n");
			pc->capacity += INC_SZ;
		}
	}
}

void Addcontact(Contact* pc)
{
	CheckCapacity(pc);//动态版本添加代码
	if (pc->sz == MAX)
	{
		printf("通讯录已满,无法添加:\n");
	}
	else
	{
		printf("请输入名字:>\n");
		scanf("%s", pc->data[pc->sz].name);//scanf("%s", pc->data[pc->sz]->name)这样写是错误的
		printf("请输入性别:>\n");
		scanf("%s", pc->data[pc->sz].sex);
		printf("请输入年龄:>\n");
		scanf("%d", &(pc->data[pc->sz].age));//这个取地址不要漏了
		printf("请输入电话:>\n");
		scanf("%s", pc->data[pc->sz].tele);
		printf("请输入地址:>\n");
		scanf("%s", pc->data[pc->sz].addr);
		pc->sz++;

	}
	pc->autosave++;
	if (pc->autosave % 3 == 0)
	{
		Savecontact(pc);
		printf("自动保存成功\n");

	}
	

}


void Delcontact(Contact* pc)
{
	printf("请输入要删除对象的名字:>\n");
	int num = Search(pc);
	if (num == -1)
	{
		printf("要删除的对象不存在>\n");
	}
	else
	{
		int i;
		for (i = num;i < pc->sz; i++)
		{
			pc->data[i] = pc -> data[i+1];
		}
		pc->sz--;
		printf("删除成功!\n");
	}
}

void Searchcontact(Contact* pc)
{
	printf("请输入你要寻找人的名字:\n");
	int num= Search(pc);
	if (num>=0 )
	{
		printf("%-20s\t%-5s\t%-5s\t%-12s\t%-20s\n", "名字", "年龄", "性别", "电话", "地址");
		printf("%-20s\t%-5d\t%-5s\t%-12s\t%-20s\n",
			pc->data[num].name,
			pc->data[num].age,
			pc->data[num].sex,
			pc->data[num].tele,
			pc->data[num].addr);
		

	}
	else {
		printf("没有找到:\n");
	}

}

void Concelcontact(Contact* pc)
{
	printf("请输入你要修改的对象:>\n");
	int num= Search(pc);
	if (num == -1)
	{
		printf("要修改的对象不存在>\n");
	}
	else
	{
		printf("请输入修改后的名字:>\n");
		scanf("%s", pc->data[num].name);//scanf("%s", pc->data[num]->name)这样写是错误的
		printf("请输入修改后的性别:>\n");
		scanf("%s", pc->data[num].sex);
		printf("请输入修改后的年龄:>\n");
		scanf("%d", &(pc->data[num].age));//这个取地址不要漏了
		printf("请输入修改后的电话:>\n");
		scanf("%s", pc->data[num].tele);
		printf("请输入修改后的地址:>\n");
		scanf("%s", pc->data[num].addr);
		printf("修改成功!\n");
		
	}

}

void Showcontact(Contact* pc)
{
	printf("%-20s\t%-5s\t%-5s\t%-12s\t%-20s\n", "名字", "年龄", "性别", "电话", "地址");
	int i = 0;
	//打印数据
	for (i = 0; i < pc->sz; i++)
	{
		printf("%-20s\t%-5d\t%-5s\t%-12s\t%-20s\n",
			pc->data[i].name,
			pc->data[i].age,
			pc->data[i].sex,
			pc->data[i].tele,
			pc->data[i].addr);
	}
}

void Savecontact(Contact* pc)
{
	FILE* pf = fopen("Contact.dat", "w");
	if (pf == NULL)
	{
		//printf("%s", strerror(errno));
		perror("SaveContact");
		return;
	}
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		fwrite(pc->data + 1, sizeof(PeoInfo), 1, pf);
	}


	fclose(pf);
	pf = NULL;

}