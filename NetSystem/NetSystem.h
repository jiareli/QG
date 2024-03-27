#ifndef __NETSYSTEM_H_
#define __NETSYSTEM_H_

#include <stdbool.h>

//��������
typedef struct User   //�û�
{
	char Username[20];//�û���
	char password[20];//�û�����
	char Realname[20];//��ʵ����
	char cellphone[11];//�ֻ���
	char mail[20];//�����
	//int saving;//�˻��ʽ�
	//int ku;//���
}User;

//����ڵ�����
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
