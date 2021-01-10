﻿#define _CRT_SECURE_NO_WARNINGS
#include<Model.h>
#include<stdio.h>
#include <graphics.h>
#include <conio.h>
#include<stdbool.h> //布尔型，把书的已借/在库状态用布尔型存储
#include<string.h>
#include<time.h> //获取时间函数

// 录入图书(管理员操作）   
//在链表结尾添加新节点
void add_book(book *head) {
	int n;
	//InputBox(n, 100, 0, L"请输入您要新录入图书的数量:", 0, 0, 0, false); 
	scanf("%d", &n);
	book *newhead = (book*)malloc(sizeof(book));
	book *newp = (book*)malloc(sizeof(book));
	newhead->next = newp;
	outtext("请输入您要录入图书的信息，格式（书号 书名 作者 出版社 出版日期年 月 日 价格 类别 总库存数 现库存数 已借出数)");
	for (int i = 0; i < n; i++) {
		scanf("%s %s %s %s %d %d %d %lf %s %d %d %d", newp->id, newp->name, newp->author, newp->publish, &newp->date.year, &newp->date.month, &newp->date.day, &newp->price, newp->type, &newp->tnum, &newp->nnum, &newp->bnum);
		if (i == n - 1) newp->next = NULL;
		else {
			newp->next = (book*)malloc(sizeof(book));
			newp = newp->next;
		}
	}
	book *p = head->next;
	while (p->next != NULL) {
		p = p->next;
	}
	p->next = newhead->next;
	printf("录入完成，更新后图书库信息为:\n");
	outlink(head);
}

//按书号查询图书（管理员操作、借书操作）
//原则上书号应该唯一，所以此函数也提供查询书号录入错误的书的功能，之后可用删除函数进行删除
void findbook_id(book *head) {
	char id[20];
	InputBox(id, 100, 0, "请输入您想要查询的书的书号:", 0, 0, 0, false);
	//char *id_new = (char*)malloc(20);
	//wcstombs(id_new, id, 20);
	book *p = head->next;
	book *head_find = (book*)malloc(sizeof(book));
	book *find_q, *find_p;
	find_p = find_q = head_find;
	if (head == NULL)//链表为空链表
	{
		outtext("图书库中没有图书");
		return;
	}
	while (p != NULL) {
		if (strcmp(p->id, id) == 0) { //找到相同书号的书
			book *find_q = (book*)malloc(sizeof(book));
			strcpy(find_q->id, p->id);
			strcpy(find_q->name, p->name);
			strcpy(find_q->author, p->author);
			strcpy(find_q->publish, p->publish);
			find_q->date.year = p->date.year;
			find_q->date.month = p->date.month;
			find_q->date.day = p->date.day;
			find_q->price = p->price;
			strcpy(find_q->type, p->type);
			find_q->tnum = p->tnum;
			find_q->nnum = p->nnum;
			find_q->bnum = p->bnum;
			find_p->next = find_q;
			find_p = find_q;
		}
		p = p->next;
	}
	find_p->next = NULL;
	if (head_find->next == NULL) {
		outtext("未找到相关图书");
	}
	else {
		outtext("您的查找结果为:");
		outlink(head_find);
	}
}

//按书名查询图书（管理员操作、借书操作）
void findbook_name(book *head) {
	char name[50];
	InputBox(name, 100, 0, "请输入您想要查询的书的书名:", 0, 0, 0, false);
	//char *name_new = (char*)malloc(50);
	//wcstombs(name_new, name, 20);
	book *p = head->next;
	book *head_find = (book*)malloc(sizeof(book));
	book *find_q, *find_p;
	find_p = find_q = head_find;
	if (head == NULL)//链表为空链表
	{
		printf("图书库中没有图书\n");
		return;
	}
	while (p != NULL) {
		if (strcmp(p->name, name) == 0) { //找到相同书名的书
			book *find_q = (book*)malloc(sizeof(book));
			strcpy(find_q->id, p->id);
			strcpy(find_q->name, p->name);
			strcpy(find_q->author, p->author);
			strcpy(find_q->publish, p->publish);
			find_q->date.year = p->date.year;
			find_q->date.month = p->date.month;
			find_q->date.day = p->date.day;
			find_q->price = p->price;
			strcpy(find_q->type, p->type);
			find_q->tnum = p->tnum;
			find_q->nnum = p->nnum;
			find_q->bnum = p->bnum;
			find_p->next = find_q;
			find_p = find_q;
		}
		p = p->next;
	}
	find_p->next = NULL;
	if (head_find->next == NULL) {
		printf("未找到相关图书\n");
	}
	else {
		printf("您的查找结果为:\n");
		outlink(head_find);
	}
}

//根据书号删除图书（管理员操作、借书操作可调用）
void delbook_id(book *head) {
	char id[20];
	printf("请输入您想要删除的书的书号:\n");
	scanf("%s", id);
	book *p_front = head;
	book *p = head->next;
	if (p == NULL) {//链表为空链表
		printf("图书库中没有图书\n");
	}
	while (p->next != NULL) {
		if (strcmp(p->id, id) == 0) {
			p_front->next = p->next;
			free(p);
			p = p_front->next;
		}
		else {
			p_front = p_front->next;
			p = p->next;
		}
	}
	printf(" 删除完成，更新后图书库信息为:\n");
	outlink(head);
}

//根据书名删除图书（管理员操作、清除由于输错书号的书的信息）
void delbook_name(book *head) {
	char name[50];
	printf("请输入您想要删除的书的书名:\n");
	scanf("%s", name);
	book *p_front = head;
	book *p = head->next;
	if (p == NULL) {//链表为空链表
		printf("图书库中没有图书\n");
	}
	while (p->next != NULL) {
		if (strcmp(p->name, name) == 0) {
			p_front->next = p->next;
			free(p);
			p = p_front->next;
		}
		else {
			p_front = p_front->next;
			p = p->next;
		}
	}
	printf(" 删除完成，更新后图书库信息为:\n");
	outlink(head);
}