#ifndef __NETSYSTEM_H_
#define __NETSYSTEM_H_

#include <stdbool.h>

//数据类型
typedef struct User   //用户
{
	char Username[20];//用户名
	char password[20];//用户密码
	char Realname[20];//真实姓名
	char cellphone[11];//手机号
	char mail[20];//邮箱号
	//int saving;//账户资金
	//int ku;//库存
}User;

//链表节点类型
typedef struct Node
{
	struct User data;
	struct Node* pNext;
}Node;



Node* createNode(User* pData);
void appendNode(Node** root, User* pData);
void travel(Node* root);
Node* findNodeByPos(Node* root, int n);
void deleteNode(Node** root, int n);
bool deleteList(Node** root);
void printwelcome();
void loginUser();
void appendUser();
void showAllUser();
void deleteUser();
void changeUser();

#define FILEPATH "1.dat" 

#endif
