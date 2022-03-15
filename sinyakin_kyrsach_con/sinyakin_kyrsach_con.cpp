// sinyakin_kyrsach_con.cpp: главный файл проекта.

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <malloc.h>
#include <clocale>
#include <iostream>
#include <string>  

using namespace std;
using namespace System;
using namespace System::IO;

#define ENTER 13
#define ESC 27
#define UP 72
#define DOWN 80

char dan[15][60]={
"Вывести всю базу данных                               ",
"Вывести всю базу данных в алфавитном порядке          ",
"Вывести всю базу данных в обратном алфавитном порядке ",
"Самое первое взятие в аренду                          ",
"Крайнее взятие в аренду                               ",
"Первая сдача арендатору                               ",
"Последняя сдача арендатору                            ",
"Диаграмма - Процентное соотношение стоимости аренды   ",
"Диаграмма - рейтинг арендаторов                       ",
"Максимальная сумма                                    ",
"Минимальная сумма                                     ",
"Рейтинг лучшего арендатора                            ",
"Рейтинг худшего арендатора                            ",
"Расширенный тариф и нечетная сумма                    ",
"Выход                                                 "
};
char BlankLine[ ]=" ";




int NC;

struct z{
	char name[20];
	long summa;
	long reiting;
	char date_start[20];
	char date_end[20];
	char tarif[20];
};
struct sp {
	char fio[20];
	long summa;
	struct sp* sled;
		} *spisok;

void vstavka(struct z* client,char* fio)
{
	int i;
	struct sp *nov,*nt,*z=0;
	for(nt=spisok; nt!=0 && strcmp(nt->fio,fio)<0; z=nt, nt=nt->sled);
	if(nt && strcmp(nt->fio,fio)==0) return;
	nov=(struct sp *) malloc(sizeof(struct sp));
	strcpy(nov->fio,fio);
	nov->sled=nt;
	nov->summa=0;
	for(i=0;i<NC;i++){
		if(strcmp(client[i].name,fio)==0)
			nov->summa+=client[i].summa;
	}
	if(!z) spisok=nov;
	else z->sled=nov;
	return;
}

// Вывод списка в алфавитном порядке

void alfalist(struct z* client)
{
	int i;
	struct sp* nt;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::Clear();
	if(!spisok){
		for(i=0;i<NC;i++)
			vstavka(client,client[i].name);
	}
	Console::Clear();
	printf("\n Алфавитный список арендаторов");
	printf("\n =============================\n");
	for(nt=spisok; nt!=0; nt=nt->sled)
		printf("\n %-20s %ld",nt->fio,nt->summa);
	getch();
}

// Вывод списка в обратном алфавитном порядке

void alfalist_obr(struct z* client){
	int i;
	struct sp* nt;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::Clear();
	if(!spisok){
		for(i=0;i<NC;i++)
			vstavka(client,client[i].name);
	}
	Console::Clear();
	printf("\n Обратный алфавитный список арендаторов");
	printf("\n ======================================\n");
	for(nt=spisok; nt!=0; nt=nt->sled)
		printf("\n %-20s %ld",nt->fio,nt->summa);
	getch();
}

// Вывод списка
void print_DB(struct z *client)
{
	char a[] ="ФИО";
	char b[] ="Сумма";
	char c[] ="Рейтинг";
	char d[] ="Дата выдачи";
	char e[] ="Дата сдачи";
	char f[] ="Тариф";
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::Clear();
	printf("%-15s %10s %10s %20s %20s %20s",a,b,c,d,e,f);
	for(int i=0;i<NC;i++)
		printf("\n%-15s %10ld %10d %20s %20s %20s",client[i].name, client[i].summa,
		client[i].reiting, client[i].date_start, client[i].date_end, client[i].tarif);
	getch();
}

// Преобразование даты формата 2003.01.12 в 12 января 2003

void text_data(char *s,char *sd)
{
	char s0[3],month[12][9]={
		"января","февраля","марта","апреля","мая","июня",
		"июля","августа","сентября","октября","ноября","декабря"};
	strcpy(s,sd+8);
	strcat(s," ");
	strncpy(s0,sd+5,2); 
	s0[2]=0;
	strcat(s,month[ atoi(s0)-1]);
	strcat(s," ");
	strncat(s,sd,4);
}


// функция поиска самой ранней даты взятия аренды

void first_arenda(struct z* client)
{
	int i;
	char s[17];
	struct z* best=client;
	for(i=1;i<NC;i++)
		if (strcmp(client[i].date_start,best->date_start)<0)
			best=&client[i];
	text_data(s,best->date_start);
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::Clear();
	printf("\nСамый первый арендатор");
	printf("\n%s %s",best->name,s);
	getch();
}

// функция поиска самой поздней даты взятия аренды

void last_arenda(struct z* client)
{
	int i;
	char s[17];
	struct z* best=client;
	for(i=1;i<NC;i++)
		if (strcmp(client[i].date_start,best->date_start)>0)
			best=&client[i];
	text_data(s,best->date_start);
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::Clear();
	printf("\nСамый крайний арендатор");
	printf("\n%s %s",best->name,s);
	getch();
}

// функция поиска самой ранней даты сдатия аренды

void first_done_arenda(struct z* client)
{
	int i;
	char s[17];
	struct z* best=client;
	for(i=1;i<NC;i++)
		if (strcmp(client[i].date_end,best->date_end)>0)
			best=&client[i];
	text_data(s,best->date_end);
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::Clear();
	printf("\nСамый крайний сдающий арендатор");
	printf("\n%s %s",best->name,s);
	getch();
}

// функция поиска самой поздней даты сдатия аренды

void last_done_arenda(struct z* client)
{
	int i;
	char s[17];
	struct z* best=client;
	for(i=1;i<NC;i++)
		if (strcmp(client[i].date_end,best->date_end)<0)
			best=&client[i];
	text_data(s,best->date_end);
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::Clear();
	printf("\nСамый первый сдающий арендатор");
	printf("\n%s %s",best->name,s);
	getch();
}

// Отображение диаграммы стоимости

void diagram_cost(struct z *client )
{
	struct sp *nt;
	int len,i,NColor;
	long sum = 0 ;
	char str1[20];
	char str2[20];
	System::ConsoleColor Color;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::White;
	Console::Clear();
	for(i=0;i<NC;i++) sum = sum+client[i].summa ;
	if(!spisok)
		for(i=0;i<NC;i++)
			vstavka(client,client[i].name);
	Color=ConsoleColor::Black; NColor=0;
	for(nt=spisok,i=0; nt!=0; nt=nt->sled,i++)
	{
		sprintf(str1,"%s",nt->fio);
		sprintf(str2,"%3.1f%%",(nt->summa*100./sum));
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor= ConsoleColor::White;
		Console::CursorLeft=5; Console::CursorTop=i+1;
		printf(str1);
		Console::CursorLeft=20;
		printf("%s",str2);
		Console::BackgroundColor=++Color; NColor++;
		Console::CursorLeft=30;
		for	(len=0; len<nt->summa*100/sum; len++) printf(" ");
		if(NColor==14)
			{ Color=ConsoleColor::Black; NColor=0; }
		}
	getch();
}

// Отображение диаграммы рейтинга

void diagram_reiting(struct z *client )
{
	struct sp *nt;
	int len,i,NColor;
	long sum = 0 ;
	char str1[20];
	char str2[20];
	System::ConsoleColor Color;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::White;
	Console::Clear();
	for(i=0;i<NC;i++) sum = sum+client[i].reiting ;
	if(!spisok)
		for(i=0;i<NC;i++)
			vstavka(client,client[i].name);
	Color=ConsoleColor::Black; NColor=0;
	for(nt=spisok,i=0; nt!=0; nt=nt->sled,i++)
	{
		sprintf(str1,"%s",client[i].name);
		sprintf(str2,"%ld",(client[i].reiting));
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor= ConsoleColor::White;
		Console::CursorLeft=5; Console::CursorTop=i+1;
		printf(str1);
		Console::CursorLeft=20;
		printf("% ld",client[i].reiting);
		Console::BackgroundColor=++Color; NColor++;
		Console::CursorLeft=30;
		for	(len=0; len<client[i].reiting; len++) printf(" ");
		if(NColor==14)
			{ Color=ConsoleColor::Black; NColor=0; }
		}
	getch();
}

// Максимальная стоимость аренды

void maxim_stom_arend(struct z* client)
{
	int i=0; struct z best;
	strcpy(best.name,client[0].name);
	best.summa=client[0].summa;
	for(i=1;i<NC;i++)
		if (client[i].summa>best.summa)
		{
			strcpy(best.name,client[i].name);
			best.summa=client[i].summa;
		}
	Console::ForegroundColor=ConsoleColor::Yellow;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::Clear();
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("Максимальная стоимость аренды %ld рублей",best.summa);
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("Арендатор - %s",best.name);
	getch();
}

// Лучший рейтинг арендатора

void maxim_reiting(struct z* client)
{
	int i=0; struct z best;
	strcpy(best.name,client[0].name);
	best.reiting=client[0].reiting;
	for(i=1;i<NC;i++)
		if (client[i].reiting>best.reiting)
		{
			strcpy(best.name,client[i].name);
			best.reiting=client[i].reiting;
		}
	Console::ForegroundColor=ConsoleColor::Yellow;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::Clear();
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("Рейтинг лучшего арендатора %ld",best.reiting);
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("Арендатор - %s",best.name);
	getch();
}

// Наименьшая стоимость аренды

void min_stom_arend(struct z* client)
{
	int i=0; struct z best;
	strcpy(best.name,client[0].name);
	best.summa=client[0].summa;
	for(i=1;i<NC;i++)
		if (client[i].summa<best.summa)
		{
			strcpy(best.name,client[i].name);
			best.summa=client[i].summa;
		}
	Console::ForegroundColor=ConsoleColor::Yellow;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::Clear();
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("Наименьшая стоимость аренды %ld рублей",best.summa);
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("Арендатор - %s",best.name);
	getch();
}

// Худший рейтинг арендатора

void min_reiting(struct z* client)
{
	int i=0; struct z best;
	strcpy(best.name,client[0].name);
	best.reiting=client[0].reiting;
	for(i=1;i<NC;i++)
		if (client[i].reiting<best.reiting)
		{
			strcpy(best.name,client[i].name);
			best.reiting=client[i].reiting;
		}
	Console::ForegroundColor=ConsoleColor::Yellow;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::Clear();
	Console::CursorLeft=10;
	Console::CursorTop=15;
	printf("Рейтинг худшего арендатора %ld",best.reiting);
	Console::CursorLeft=10;
	Console::CursorTop=16;
	printf("Арендатор - %s",best.name);
	getch();
}

// Расширенный и нечетная стоимость

void tarif_summa(struct z* client){
	char a[] ="ФИО";
	char b[] ="Сумма";
	char c[] ="Рейтинг";
	char d[] ="Дата выдачи";
	char e[] ="Дата сдачи";
	char f[] ="Тариф";	
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::Clear();
	printf("%-15s %10s %10s %20s %20s %20s",a,b,c,d,e,f);
	for(int i=0;i<NC;i++){
		if(strcmp(client[i].tarif,"Расширенный")==0&&client[i].summa%2==1)
			printf("\n%-15s %10ld %10d %20s %20s %20s",client[i].name, client[i].summa,
			client[i].reiting, client[i].date_start, client[i].date_end, client[i].tarif);
	}
	getch();
}

// Меню

int menu(int n)
{
	int y1=0,y2=n-1;
	char c=1;
	while (c!=ESC)
	{
	switch(c) {
	case DOWN: y2=y1; y1++; break;
	case UP: y2=y1; y1--; break;
	case ENTER: return y1+1;
	}
	if(y1>n-1){y2=n-1;y1=0;}
	if(y1<0) {y2=0;y1=n-1;}
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::Blue;
	Console::CursorLeft=11;
	Console::CursorTop=y1+5;
	printf("%s",dan[y1]);
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::CursorLeft=11;
	Console::CursorTop=y2+5;
	printf("%s",dan[y2]);
	c=getch();
	}
	exit(0);
	getch();
}


int main(array<System::String ^> ^args)
{	
	int i,n;
	FILE *in;
	struct z *clients;
	char str_data[20];
	char str_data1[20];
	setlocale(LC_CTYPE,"Russian");
	Console::CursorVisible::set(false);
	Console::BufferHeight=Console::WindowHeight;
	Console::BufferWidth=Console::WindowWidth;
	if((in=fopen("client_info.dat","r"))==NULL)
	{
		printf("\nclient_info.dat не открыт !");
		getch(); 
		exit(1);
	}
	fscanf(in,"%d",&NC);
	clients=(struct z*)malloc(NC*sizeof(struct z));
	for(i=0;i<NC;i++)
		fscanf(in,"%s%ld%d%s%s%s",clients[i].name, &clients[i].summa,
		&clients[i].reiting, clients[i].date_start, clients[i].date_end, clients[i].tarif);
	while(1)
	{
		Console::ForegroundColor=ConsoleColor::Gray;
		Console::BackgroundColor=ConsoleColor::Black;
		Console::Clear();
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor=ConsoleColor::Gray;
		Console::CursorLeft=10;
		Console::CursorTop=4;
		printf(BlankLine);
		for(i=0;i<15;i++)
		{
			Console::CursorLeft=10;
			Console::CursorTop=i+5;
			printf(" %s ",dan[i]);
		}
		n=menu(15);
		switch(n) {
		case 1: print_DB(clients); break;
		case 2: alfalist(clients); break;
		case 3: alfalist_obr(clients);break;
		case 4: first_arenda(clients); break;
		case 5: last_arenda(clients); break;
		case 6: first_done_arenda(clients); break;
		case 7: last_done_arenda(clients); break;
		case 8: diagram_cost(clients);break;
		case 9: diagram_reiting(clients);break;
		case 10: maxim_stom_arend(clients);break;
		case 11: min_stom_arend(clients);break;
		case 12: maxim_reiting(clients);break;
		case 13: min_reiting(clients);break;
		case 14: tarif_summa(clients);break;
		case 15: exit(0);
		}
	}
	return 0;
}
