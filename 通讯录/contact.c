#define _CRT_SECURE_NO_WARNINGS 1
#include "contact.h"

////��̬�汾
//void InitContact(Contact* pc)
//{
//	pc->sz = 0;
//	memset(pc->data, 0, sizeof(pc->data));
//}

//��̬�汾
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
	Download(pc);//�ļ�������Ӵ���
}

//�ļ�������Ӻ���
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

//��̬�汾��Ӻ���
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
		if (strcmp(pc->data[i].name, nam) == 0)//if (pc->data[i].name == nam)�����Ǵ����
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
		//PeoInfo* ptr = (PeoInfo*)realloc(pc->data,INC_SZ * sizeof(PeoInfo)+sizeof(pc->data)); error ˼��һ��Ϊʲô��pc->dataֻ��һ��PeoInfo����ָ��Ĵ�С(�������ǰ˸��ֽ�)
		
		PeoInfo* ptr = (PeoInfo*)realloc(pc->data, (INC_SZ+pc->capacity) * sizeof(PeoInfo) );
		if (ptr == NULL)
		{
			return;
		}
		else
		{
			pc->data = ptr;
			printf("���ݳɹ�\n");
			pc->capacity += INC_SZ;
		}
	}
}

void Addcontact(Contact* pc)
{
	CheckCapacity(pc);//��̬�汾��Ӵ���
	if (pc->sz == MAX)
	{
		printf("ͨѶ¼����,�޷����:\n");
	}
	else
	{
		printf("����������:>\n");
		scanf("%s", pc->data[pc->sz].name);//scanf("%s", pc->data[pc->sz]->name)����д�Ǵ����
		printf("�������Ա�:>\n");
		scanf("%s", pc->data[pc->sz].sex);
		printf("����������:>\n");
		scanf("%d", &(pc->data[pc->sz].age));//���ȡ��ַ��Ҫ©��
		printf("������绰:>\n");
		scanf("%s", pc->data[pc->sz].tele);
		printf("�������ַ:>\n");
		scanf("%s", pc->data[pc->sz].addr);
		pc->sz++;

	}
	pc->autosave++;
	if (pc->autosave % 3 == 0)
	{
		Savecontact(pc);
		printf("�Զ�����ɹ�\n");

	}
	

}


void Delcontact(Contact* pc)
{
	printf("������Ҫɾ�����������:>\n");
	int num = Search(pc);
	if (num == -1)
	{
		printf("Ҫɾ���Ķ��󲻴���>\n");
	}
	else
	{
		int i;
		for (i = num;i < pc->sz; i++)
		{
			pc->data[i] = pc -> data[i+1];
		}
		pc->sz--;
		printf("ɾ���ɹ�!\n");
	}
}

void Searchcontact(Contact* pc)
{
	printf("��������ҪѰ���˵�����:\n");
	int num= Search(pc);
	if (num>=0 )
	{
		printf("%-20s\t%-5s\t%-5s\t%-12s\t%-20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
		printf("%-20s\t%-5d\t%-5s\t%-12s\t%-20s\n",
			pc->data[num].name,
			pc->data[num].age,
			pc->data[num].sex,
			pc->data[num].tele,
			pc->data[num].addr);
		

	}
	else {
		printf("û���ҵ�:\n");
	}

}

void Concelcontact(Contact* pc)
{
	printf("��������Ҫ�޸ĵĶ���:>\n");
	int num= Search(pc);
	if (num == -1)
	{
		printf("Ҫ�޸ĵĶ��󲻴���>\n");
	}
	else
	{
		printf("�������޸ĺ������:>\n");
		scanf("%s", pc->data[num].name);//scanf("%s", pc->data[num]->name)����д�Ǵ����
		printf("�������޸ĺ���Ա�:>\n");
		scanf("%s", pc->data[num].sex);
		printf("�������޸ĺ������:>\n");
		scanf("%d", &(pc->data[num].age));//���ȡ��ַ��Ҫ©��
		printf("�������޸ĺ�ĵ绰:>\n");
		scanf("%s", pc->data[num].tele);
		printf("�������޸ĺ�ĵ�ַ:>\n");
		scanf("%s", pc->data[num].addr);
		printf("�޸ĳɹ�!\n");
		
	}

}

void Showcontact(Contact* pc)
{
	printf("%-20s\t%-5s\t%-5s\t%-12s\t%-20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
	int i = 0;
	//��ӡ����
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