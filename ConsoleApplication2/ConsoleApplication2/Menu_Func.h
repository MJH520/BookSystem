#ifndef _MENU_FUNC_H

#define _MENU_FUNC_H

#include<Model.h>
#include<Basic_Func.h>

//借书功能
void Book_Borrow(book *head);

//还书功能
void Book_Return(book *head);

//查询功能
void Book_Search(book *head);

//统计功能
void Book_Count();

//管理员功能页面
void administratorfunction();

//管理员添加功能函数
void administratoradd();

//管理员修改功能函数
void administratoramend();

//管理员删除功能函数
void administratordelete();


#endif
