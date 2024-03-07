#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include<errno.h>

#define MAX_NAME 20
#define MAX_SEX 10
#define MAX_TELE 12
#define MAX_ADDR 30


#define MAX 1000

#define DEFAULT_SZ 3
#define INC_SZ 2


typedef struct PeoInfo 
{
	char name[MAX_NAME];
	char sex[MAX_SEX];
	int age;
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
}PeoInfo;

////¾²Ì¬°æ±¾
//typedef struct Contact
//{
//	PeoInfo data[MAX];
//	int sz;
//
//}Contact;

//¶¯Ì¬°æ±¾
typedef struct Contact
{
	PeoInfo* data;
	int sz;
	int capacity;
	int autosave;
}Contact;

void InitContact(Contact* pc);

void Download(Contact* pc);

int Search(Contact* pc);

void Destroycontact(Contact* pc);

void CheckCapacity(Contact* pc);

void Addcontact(Contact* pc);

void Delcontact(Contact* pc);

void Searchcontact(Contact* pc);

void Concelcontact(Contact* pc);

void Showcontact(Contact* pc);

void Savecontact(Contact* pc);