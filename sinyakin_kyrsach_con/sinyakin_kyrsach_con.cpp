// sinyakin_kyrsach_con.cpp: главный файл проекта.

#include "stdafx.h"//подключение библиотек
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

#define ENTER 13//обозначение кнопок
#define ESC 27
#define UP 72
#define DOWN 80
#define HOME 71
#define END 79
// массив с вопросами
char dan[21][60]={
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
"Расширенный и одинаковая аренда                       ",
"Выход                                                 ",
"Удалить постояльца                                    ",
"Удалить постояльца выше текущего                      ",
"Удалить постояльца ниже текущего                      ",
"Добавить постояльца                                   ",
"Поиск                                                 "
};//задание списка вопросов - пунктов меню
char BlankLine[ ]=
"                                                        ";

int NC;//количество позиций задано глобально
// Структура клиента
struct z{
	char name[25]; // имя клиента
	long summa; // сумма аренды
	long reiting; // рейтинг
	char date_start[20]; // дата взятия
	char date_end[20]; // дата сдачи
	char tarif[20]; // тариф
};//шаблон структуры для исходных данных

struct sp {
	char fio[20];
	long summa;
	struct sp* sled;
		} *spisok;//шаблон, глобальное описание структуры двустроннего списка(1)

struct sp_obr {
	char fio_obr[20];
	long summa_obr;
	struct sp_obr* sled_obr;
		} *spisok_obr;//шаблон, глобальное описание структуры двустроннего списка(2)

// Вставка для алфавита

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

// Вставка для обратного алфавита

void vstavka_obr(struct z* client,char* fio_obr)
{
	int i;
	struct sp_obr *nov_obr,*nt_obr,*z=0;
	for(nt_obr=spisok_obr; nt_obr!=0 && strcmp(nt_obr->fio_obr,fio_obr)>0; z=nt_obr, nt_obr=nt_obr->sled_obr);
	if(nt_obr && strcmp(nt_obr->fio_obr,fio_obr)==0) return;
	nov_obr=(struct sp_obr *) malloc(sizeof(struct sp_obr));
	strcpy(nov_obr->fio_obr,fio_obr);
	nov_obr->sled_obr=nt_obr;
	nov_obr->summa_obr=0;
	for(i=0;i<NC;i++){
		if(strcmp(client[i].name,fio_obr)==0)
			nov_obr->summa_obr+=client[i].summa;
	}
	if(!z) spisok_obr=nov_obr;
	else z->sled_obr=nov_obr;
	return;
}

// Вывод списка в алфавитном порядке

void alfalist(struct z* client)
{
	FILE *in;
	int i;
	struct sp* nt;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::Clear();

	if((in=fopen("client_info.dat","r"))==NULL)
	{
		printf("\nclient_info.dat не открыт !");
		getch(); 
		exit(1);
	}
	fscanf(in,"%d",&NC);
	client=(struct z*)malloc(NC*sizeof(struct z));
	for(i=0;i<NC;i++)//считываем данные из файла
		fscanf(in,"%s%ld%d%s%s%s",client[i].name, &client[i].summa,
		&client[i].reiting, client[i].date_start, client[i].date_end, client[i].tarif);
	fclose(in);

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
	FILE *in;
	int i;
	struct sp_obr* nt_obr;
	Console::ForegroundColor=ConsoleColor::White;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::Clear();

	if((in=fopen("client_info.dat","r"))==NULL)
	{
		printf("\nclient_info.dat не открыт !");
		getch(); 
		exit(1);
	}
	fscanf(in,"%d",&NC);
	client=(struct z*)malloc(NC*sizeof(struct z));
	for(i=0;i<NC;i++)//считываем данные из файла
		fscanf(in,"%s%ld%d%s%s%s",client[i].name, &client[i].summa,
		&client[i].reiting, client[i].date_start, client[i].date_end, client[i].tarif);
	fclose(in);

	if(!spisok_obr){
		for(i=0;i<NC;i++)
			vstavka_obr(client,client[i].name);
	}
	Console::Clear();
	printf("\n Обратный алфавитный список арендаторов");
	printf("\n =============================================\n");
	for(nt_obr=spisok_obr; nt_obr!=0; nt_obr=nt_obr->sled_obr)
		printf("\n %-20s %ld",nt_obr->fio_obr,nt_obr->summa_obr);
	getch();
}

// Вывод списка
void print_DB(struct z *client)
{	
	FILE *in;
	int i;
	char a[] ="ФИО";
	char b[] ="Сумма";
	char c[] ="Рейтинг";
	char d[] ="Дата выдачи";
	char e[] ="Дата сдачи";
	char f[] ="Тариф";
	struct z *clients;
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::Clear();
	printf("%-15s %10s %10s %20s %20s %20s",a,b,c,d,e,f);

	if((in=fopen("client_info.dat","r"))==NULL)
	{
		printf("\nclient_info.dat не открыт !");
		getch(); 
		exit(1);
	}
	fscanf(in,"%d",&NC);
	clients=(struct z*)malloc(NC*sizeof(struct z));
	for(i=0;i<NC;i++)//считываем данные из файла
		fscanf(in,"%s%ld%d%s%s%s",clients[i].name, &clients[i].summa,
		&clients[i].reiting, clients[i].date_start, clients[i].date_end, clients[i].tarif);
	fclose(in);

	for(i=0;i<NC;i++)
		printf("\n%-15s %10ld %10d %20s %20s %20s",clients[i].name, clients[i].summa,
		clients[i].reiting, clients[i].date_start, clients[i].date_end, clients[i].tarif);
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

void diagram_cost(struct z *client )//создаём диаграмму
{
	struct sp *nt;//переменная для работы со списком
	int len,i,NColor;//i-для номера строки
	long sum = 0 ;//число-100%
	char str1[20];
	char str2[20];
	System::ConsoleColor Color;;//Задаѐт константы, которые определяют основной цвет и цвет фона консоли
	Console::ForegroundColor=ConsoleColor::Black;//Цвет символов
	Console::BackgroundColor=ConsoleColor::Green;//Цвет заднего фона
	Console::Clear();
	for(i=0;i<NC;i++) sum = sum+client[i].summa ;
	if(!spisok)
		for(i=0;i<NC;i++)
			vstavka(client,client[i].name);//вставляем из списка названия имен и красим символы в чёрный цвет
	Color=ConsoleColor::Black; NColor=0;
	for(nt=spisok,i=0; nt!=0; nt=nt->sled,i++)
	{
		sprintf(str1,"%s",nt->fio);
		sprintf(str2,"%3.1f%%",(nt->summa*100./sum));
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor= ConsoleColor::Green;
		Console::CursorLeft=5; Console::CursorTop=i+1;
		printf(str1);
		Console::CursorLeft=20;
		printf("%s",str2);
		Console::BackgroundColor=++Color; NColor++;
		Console::CursorLeft=30;
		for	(len=0; len<nt->summa*100/sum; len++) printf(" ");
		if(NColor==14)//выделяем на диаграмму 14 цветов
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
	Console::BackgroundColor=ConsoleColor::Red;
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
		Console::BackgroundColor= ConsoleColor::Red;
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
	strcpy(best.name,client[0].name);//в переменную структуры записываем нулевой элемент
	best.summa=client[0].summa;
	for(i=1;i<NC;i++)
		if (client[i].summa>best.summa)//условие поиска максимальной стоимости
		{
			strcpy(best.name,client[i].name);
			best.summa=client[i].summa;
		}
	Console::ForegroundColor=ConsoleColor::Yellow;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::Clear();
	Console::CursorLeft=10;//задаём область, где будет выведена макс.стоимость
	Console::CursorTop=15;
	printf("Максимальная стоимость аренды %ld рублей",best.summa);//вывод максимальной стоимости
	Console::CursorLeft=10;//задаём область, где будет выведено имя арендатора
	Console::CursorTop=16;
	printf("Арендатор - %s",best.name);//вывод имени арендатора
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

// Расширенный и одинаковая аренда

void tarif_odin_summa(struct z* client){
	int flag=0;
	Console::ForegroundColor=ConsoleColor::Gray;
	Console::BackgroundColor=ConsoleColor::Black;
	Console::Clear();
	Console::CursorLeft=2;
	Console::CursorTop=1;
	for(int i=0;i<NC-1;i++){
		for(int j=i+1;j<NC;j++){
			if(strcmp(client[i].tarif,"Расширенный")==0&& strcmp(client[j].tarif,"Расширенный")==0 && client[i].summa==client[j].summa){
				flag=1;
			}
		}
		if (flag==1) {printf("\nYes");break;}
	}
	if(flag==0) printf("No");
	getch();
}


// Удаление постояльца текущего
void delite_post(struct z* client)
{
	FILE *in;
	struct z *post;
	int n,k,i;
	char search[20];
	Console::Clear();
	in=fopen("client_info.dat","r+");
	printf("Введите имя постояльца:");
	scanf("%s", search);
	fscanf(in,"%d",&n);
	post=(struct z*)malloc(n*sizeof(struct z));
	for(i=0;i<n;i++)
		fscanf(in,"%s%ld%d%s%s%s",post[i].name, &post[i].summa,
		&post[i].reiting, post[i].date_start, post[i].date_end, post[i].tarif);
	fclose(in);
	in=fopen("client_info.dat","w");
	for(i=0;i<n;i++)
	{
		if (strcmp(post[i].name,search)==0) continue;
		k++;
	}
	if(k==n){printf("Нет такого((");}
	else
	{  
		printf("Вы выселите: %s",search);
		fprintf(in,"%d",k);
		for(i=0;i<n;i++)
		{
			if (strcmp(post[i].name,search)==0) continue;
			fprintf(in,"\n%-15s %10ld %10d %20s %20s %20s",post[i].name, post[i].summa,
		post[i].reiting, post[i].date_start, post[i].date_end, post[i].tarif);
			printf("\n%-15s %10ld %10d %20s %20s %20s",post[i].name, post[i].summa,
		post[i].reiting, post[i].date_start, post[i].date_end, post[i].tarif);
		}	
	}
	fclose(in);
	getch();
}
// Удаление постояльца выше текущего
void delite_post_upper(struct z* client)
{
	FILE *in;
	struct z *post;
	int n,k,i,j;
	char search[20];
	Console::Clear();
	in=fopen("client_info.dat","r+");
	printf("Введите имя постояльца:");
	scanf("%s", search);
	fscanf(in,"%d",&n);
	post=(struct z*)malloc(n*sizeof(struct z));
	for(i=0;i<n;i++)
		fscanf(in,"%s%ld%d%s%s%s",post[i].name, &post[i].summa,
		&post[i].reiting, post[i].date_start, post[i].date_end, post[i].tarif);
	fclose(in);

	in=fopen("client_info.dat","w");
	for(i=0;i<n;i++)
	{
		if (strcmp(post[i].name,search)==0){
			j=i-1;
			continue;
		}
		k++;

	}
	if(k==n){printf("Нет такого((");}
	else
	{  

		printf("Вы выселите: %s",post[j].name);
		fprintf(in,"%d",k);
		for(i=0;i<n;i++)
		{
			if (strcmp(post[i].name,post[j].name)==0) continue;
			fprintf(in,"\n%-15s %10ld %10d %20s %20s %20s",post[i].name, post[i].summa,
		post[i].reiting, post[i].date_start, post[i].date_end, post[i].tarif);
			printf("\n%-15s %10ld %10d %20s %20s %20s",post[i].name, post[i].summa,
		post[i].reiting, post[i].date_start, post[i].date_end, post[i].tarif);
		}	
	}
	fclose(in);
	getch();
}
// Удаление постояльца ниже текущего
void delite_post_lower(struct z* client)
{
	FILE *in;
	struct z *post;
	int n,k,i,j;
	char search[20];
	Console::Clear();
	in=fopen("client_info.dat","r+");
	printf("Введите имя постояльца:");
	scanf("%s", search);
	fscanf(in,"%d",&n);
	post=(struct z*)malloc(n*sizeof(struct z));
	for(i=0;i<n;i++)
		fscanf(in,"%s%ld%d%s%s%s",post[i].name, &post[i].summa,
		&post[i].reiting, post[i].date_start, post[i].date_end, post[i].tarif);
	fclose(in);

	in=fopen("client_info.dat","w");
	for(i=0;i<n;i++)
	{
		if (strcmp(post[i].name,search)==0) {
			j=i+1;
			continue;}
		k++;

	}
	if(k==n){printf("Нет такого((");}
	else
	{  

		printf("Вы выселите: %s",post[j].name);
		fprintf(in,"%d",k);
		for(i=0;i<n;i++)
		{
			if (strcmp(post[i].name,post[j].name)==0) continue;
			fprintf(in,"\n%-15s %10ld %10d %20s %20s %20s",post[i].name, post[i].summa,
		post[i].reiting, post[i].date_start, post[i].date_end, post[i].tarif);
			printf("\n%-15s %10ld %10d %20s %20s %20s",post[i].name, post[i].summa,
		post[i].reiting, post[i].date_start, post[i].date_end, post[i].tarif);
		}	
	}
	fclose(in);
	getch();
}

// Добавление
void add(struct z* clients)
{
	FILE *in;
	int n,k,i,j,tr;
	char name[20];
	int summa;
	int reiting;
	char date_start[20];
	char date_end[20];
	char tarif[20];
	char a[] ="ФИО";
	char b[] ="Сумма";
	char c[] ="Рейтинг";
	char d[] ="Дата выдачи";
	char e[] ="Дата сдачи";
	char f[] ="Тариф";
	Console::Clear();
	n = NC;
	NC = NC + 1;

	printf("Пример постояльца:\n");
	printf("%-15s %10s %10s %20s %20s %20s",a,b,c,d,e,f);
	printf("\n%-15s %10ld %10d %20s %20s %20s",clients[0].name, clients[0].summa,
		clients[0].reiting, clients[0].date_start, clients[0].date_end, clients[0].tarif);
	clients=(struct z*)malloc(NC*sizeof(struct z));
	in=fopen("client_info.dat","r");
    fscanf(in,"%d",&tr);
	for(i=0;i<n;i++)//считываем данные из файла
		fscanf(in,"%s%ld%d%s%s%s",clients[i].name, &clients[i].summa,
		&clients[i].reiting, clients[i].date_start, clients[i].date_end, clients[i].tarif);
	fclose(in);

	printf("\nИмя:");
	scanf("%s", clients[n].name);
	printf("Сумма:");
	scanf("%ld", &clients[n].summa);
	printf("Рейтинг:");
	scanf("%d", &clients[n].reiting);
	printf("Дата выдачи:");
	scanf("%s", clients[n].date_start);
	printf("Дата сдачи:");
	scanf("%s", clients[n].date_end);
	printf("Тариф:");
	scanf("%s", clients[n].tarif);

	in=fopen("client_info.dat","w");
	fprintf(in,"%d",NC);
	for(i=0;i<NC;i++)
		fprintf(in,"\n%-15s %10ld %10d %20s %20s %20s",clients[i].name, clients[i].summa,
	clients[i].reiting, clients[i].date_start, clients[i].date_end, clients[i].tarif);
	fclose(in);

	printf("Готово!");
	
	getch();
}

// Поиск
void find(struct z* client)
{
	int i;
	char search[30];
	struct z*nt;
	Console::Clear();
	Console::BackgroundColor = ConsoleColor::Green;
	Console::ForegroundColor = ConsoleColor::Black;
	printf("Введите имя постояльца:");
	scanf("%s", search);
	printf("Сумма %s:", search);
	for (i = 0, nt=client; i < NC;nt++, i++)
		if (strcmp(nt->name, search) == 0)
		{
			printf("%-15ld", nt->summa);
			break;
		}
	getch();
}
// Меню
int menu(int n)
{
	int y1=0,y2=n-1;//устанавливаем выделение для строчки
	char c=1;
	while (c!=ESC)//при нажатии кнопки ESC, меню закроется
	{
	switch(c) {
	case HOME: y2=y1;y1=0; break;//программирование кнопки HOME,которая позволяет встать в начало списка
	case END: y2=y1;y1=n-1; break;//программирование кнопки END,которая позволяет встать в конец списка
	case DOWN: y2=y1; y1++; break;;//программирование кнопки DOWN,которая позволяет перемещаться вниз по меню
	case UP: y2=y1; y1--; break;;//программирование кнопки UP, которая позволяет перемещаться вверх по меню
	case ENTER: return y1+1;;//программирование кнопки ENTER, которая позволяет выбрать вопрос
	}
	if(y1>n-1){y2=n-1;y1=0;} //условие,когда срабатывает кнопка DOWN
	if(y1<0) {y2=0;y1=n-1;}//условие,когда срабатывает кнопка UP
	Console::ForegroundColor=ConsoleColor::Black;//при выборе вопроса,буквы окрашиваются в черный цвет
	Console::BackgroundColor=ConsoleColor::White;//при выборе вопроса фон за буквами подсвечивается белым
	Console::CursorLeft=11;
	Console::CursorTop=y1+5;
	printf("%s",dan[y1]);
	Console::ForegroundColor=ConsoleColor::Black;
	Console::BackgroundColor=ConsoleColor::Gray;
	Console::CursorLeft=11;
	Console::CursorTop=y2+5;
	printf("%s",dan[y2]);
	c=getch();
	} // конец while(c!=ESC)...
	exit(0);
	getch();
}

int main(array<System::String ^> ^args)
{	
	//на локальном уровне осуществляем открытие файла,
	//считываем данные из файла в выделенную память


	int i,n;
	FILE *in;
	struct z *clients;
	char str_data[20];
	char str_data1[20];
	setlocale(LC_CTYPE,"Russian");//поддержка русского языка
	Console::CursorVisible::set(false);//отключаем выдимость курсора
	Console::BufferHeight=Console::WindowHeight;//установка размера буфера по ширине
	Console::BufferWidth=Console::WindowWidth;//установка размера буфера по высоте
	if((in=fopen("client_info.dat","r"))==NULL)
	{
		printf("\nclient_info.dat не открыт !");
		getch(); 
		exit(1);
	}
	fscanf(in,"%d",&NC);
	clients=(struct z*)malloc(NC*sizeof(struct z));
	for(i=0;i<NC;i++)//считываем данные из файла
		fscanf(in,"%s%ld%d%s%s%s",clients[i].name, &clients[i].summa,
		&clients[i].reiting, clients[i].date_start, clients[i].date_end, clients[i].tarif);
	fclose(in);
	while(1)//в цикле создаем область для вопросов и окрашиваем еѐ в цвета устанавливаем для букв цвет и подсветку для выбранного вопроса
	{
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor=ConsoleColor::Red;
		Console::Clear();
		Console::CursorLeft=10;//первая точка, откуда будем закрашивать область меню
		Console::CursorTop=4;
		Console::ForegroundColor=ConsoleColor::Black;
		Console::BackgroundColor=ConsoleColor::Gray;
		
	printf(BlankLine);
		for(i=0;i<21;i++)//размещение вопросов
		{
			Console::CursorLeft=10;
			Console::CursorTop=i+5;
			printf(" %s ",dan[i]);
		}
		Console::CursorLeft=10;//последняя точка,где будет заканчиваться выделенная область под меню
		Console::CursorTop=26;
		printf(BlankLine);
		n=menu(21);//выбор вопроса в меню
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
		case 15: tarif_odin_summa(clients);break;
		case 16: exit(0);
		case 17: delite_post(clients);break;
		case 18: delite_post_upper(clients);break;
		case 19: delite_post_lower(clients);break;
		case 20: add(clients);break;
		case 21: find(clients);break;
		}
	}// конец while(1)...
	return 0;
}// конец main()
