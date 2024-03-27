#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NetSystem.h"
#include <Windows.h>
#include <stdbool.h>


//创建一个链表节点 传入用户信息
Node* createNode(User* pData)
{
	Node* pNew=malloc(sizeof(Node));
	pNew->pNext = NULL;
	if (pNew == NULL)return NULL;


	//数组不能赋值 只能拷贝
	strcpy_s(pNew->data.Username,20, pData->Username);
	strcpy_s(pNew->data.password,20,pData->password);
	strcpy_s(pNew->data.Realname,20,pData->Realname);
	strcpy_s(pNew->data.mail,20,pData->mail);
	strcpy_s(pNew->data.cellphone,11,pData->cellphone);

	return pNew;//返回地址
}

//添加一个节点到链表末尾
void appendNode(Node* *root,User *pData)//传入链表和一个用户的数据结构体
{
	if (root == NULL)return;
	if (*root == NULL)//传入空链表
	{
		*root = createNode(pData);
		return;
	}
	Node* pTemp = *root;//如果链表不为空 那就拿个指针指向它

	//让pTemp指向链表最后一个节点
	while (pTemp->pNext)
	{
		pTemp = pTemp->pNext;
	}
	pTemp->pNext = createNode(pData);//把新节点添加到pTemp后面
	pTemp->pNext->pNext = NULL;
}

//遍历链表并输出
void travel(Node* root)//传入链表头节点
{
	if (root == NULL)return;
	while (root)
	{
		printf("%s      %s      %s      %s      %s\n", root->data.Username, root->data.Realname,root->data.password, root->data.mail, root->data.cellphone);
		root = root->pNext;
	}
	printf("-------------------------------------------");
}

//返回root链表中第n个节点的地址
Node* findNodeByPos(Node* root, int n)
{
	if (n < 0)return NULL;
	if (root == NULL)return NULL;
	if (n == 0)return root;//返回第一个
	for (int i = 0; i < n; i++)
	{
		if (root == NULL)return NULL;
		root = root->pNext;
	}
	return root;
}

//删除root链表中第n个节点 n从下标0开始
void deleteNode(Node** root, int n)
{
	if (root == NULL)return;
	if (*root == NULL)return;
	if (n < 0)return;
	Node* pDel = *root;
	Node* pDelPret = NULL;
	if (n == 0)//删掉第一个
	{
		*root = pDel->pNext;
		free(pDel);//释放内存
		return;
	}


	pDelPret=findNodeByPos(*root, n);
	pDel = pDelPret->pNext;

	if (pDel == NULL)return;
	pDelPret->pNext = pDel->pNext;//pDel的前一个的next指针指向pDel的下一个节点
	free(pDel);
	return;
}

//删除整个链表
bool deleteList(Node** root)
{
	while (1)
	{
		if (*root == NULL)return;
		deleteNode(root, 0);
	}
}

void printwelcome()//菜单
{
	int n;
	while (1)
	{
		system("cls");
		printf("----------欢迎来到电商平台----------------\n");
		printf("----------1.用户登陆---------------------\n");
		printf("----------2.用户注册---------------------\n");
		printf("----------3.查看当前所有用户信息----------\n");
		printf("----------4.注销用户---------------------\n");
		printf("----------5.修改用户信息-----------------\n");
		printf("----------6.退出平台---------------------\n");
		printf("请选择:\n");
		scanf_s("%d", &n,sizeof(n));
		switch (n)
		{
		case 1:
			loginUser();
			break;
		case 2:
			appendUser();
			break;
		case 3:
			showAllUser();
			break;
		case 4:
			deleteUser();
			break;
		case 5:
			changeUser();
			break;
		case 6:
			printf("Bey bye\n");
			system("pause");
			exit(1);
			break;
		default:break;
		}
	}
}

void loginUser()
{

}
void appendUser()
{
	//1 打开文件
	FILE* fp;
	errno_t err=fopen_s(&fp,FILEPATH, "rb");//rb意为以二进制形式打开文件
	//2 读取文件内容并存放在链表中
	Node* pList = NULL;//一开始链表为空
	int r;
	User temp;//临时存一个学生数据的结构体
	if (fp != NULL)
	{
		while (1)  //循环读取文件内容
		{
			r = fread(&temp, 1, sizeof(User), fp);//从文件中读取数据 1为每次读取数据的大小 1字节 fp为从文件里面读取
			if (r <= 0)//没读到
			{
				break;//循环结束
			}
			else//读到了一个学生信息
			{
				//1 创建一个链表节点 把学生信息放进去
				//2 把链表节点添加到链表中
				appendNode(&pList, &temp);
			}
		}
		//3 关闭文件
		fclose(fp);
	}
	
	system("cls");
	printf("--------------注册-----------------");
	printf("请根据提示输入用户信息\n");
	printf("请创建用户名:\n");
	scanf_s("%s", temp.Username, sizeof(temp.Username));
	printf("请输入真实姓名:\n");
	scanf_s("%s", temp.Realname, sizeof(temp.Realname));
	printf("请设置密码:\n");
	scanf_s("%s", temp.password, sizeof(temp.password));
	printf("请输入邮箱:\n");
	scanf_s("%s", temp.mail, sizeof(temp.mail));
	printf("请输入电话号:\n");
	scanf_s("%s", temp.cellphone, sizeof(temp.cellphone));
	

	appendNode(&pList, &temp);

	//1 打开文件
	err = fopen_s(&fp, FILEPATH, "wb");//rb意为以二进制形式打开文件
	Node* pTemp = pList;//重新创一个链表头，因为待会还要删 不能直接用pList
	//循环把链表数据写入
	while (pTemp)
	{
		fwrite(&(pTemp->data), 1, sizeof(User), fp);
		pTemp = pTemp->pNext;
	}
	
	//关闭文件
	fclose(fp);

	deleteList(&pList);
}
void showAllUser()
{
	//1 打开文件
	FILE* fp = fopen(FILEPATH,"rb");//rb意为以二进制形式打开文件
	if (fp == NULL)
	{
		printf("系统中没有学生信息！\n");
		system("pause");
		return;
	}
	//2 读取文件内容并存放在链表中
	Node* pList = NULL;//一开始链表为空
	int r;
	User temp;//临时存一个学生数据的结构体
	while (1)  //循环读取文件内容
	{
		r = fread(&temp,1,sizeof(User),fp);//从文件中读取数据 1为每次读取数据的大小 1字节 fp为从文件里面读取
		if (r <= 0)//没读到
		{
			break;//循环结束
		}
		else//读到了一个学生信息
		{
			//1 创建一个链表节点 把学生信息放进去
			//2 把链表节点添加到链表中
			appendNode(&pList, &temp);
		}
	  }
	//3 关闭文件
	fclose(fp);
	//4 遍历链表并输出
	printf("用户名     真实名     邮箱                电话          \n");
	travel(pList);
	//删除整个链表
	deleteList(&pList);
	system("pause");
}
void deleteUser()
{

}
void changeUser()
{

}