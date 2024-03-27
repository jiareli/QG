#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NetSystem.h"
#include <Windows.h>
#include <stdbool.h>


//����һ������ڵ� �����û���Ϣ
Node* createNode(User* pData)
{
	Node* pNew=malloc(sizeof(Node));
	pNew->pNext = NULL;
	if (pNew == NULL)return NULL;


	//���鲻�ܸ�ֵ ֻ�ܿ���
	strcpy_s(pNew->data.Username,20, pData->Username);
	strcpy_s(pNew->data.password,20,pData->password);
	strcpy_s(pNew->data.Realname,20,pData->Realname);
	strcpy_s(pNew->data.mail,20,pData->mail);
	strcpy_s(pNew->data.cellphone,11,pData->cellphone);

	return pNew;//���ص�ַ
}

//���һ���ڵ㵽����ĩβ
void appendNode(Node* *root,User *pData)//���������һ���û������ݽṹ��
{
	if (root == NULL)return;
	if (*root == NULL)//���������
	{
		*root = createNode(pData);
		return;
	}
	Node* pTemp = *root;//�������Ϊ�� �Ǿ��ø�ָ��ָ����

	//��pTempָ���������һ���ڵ�
	while (pTemp->pNext)
	{
		pTemp = pTemp->pNext;
	}
	pTemp->pNext = createNode(pData);//���½ڵ���ӵ�pTemp����
	pTemp->pNext->pNext = NULL;
}

//�����������
void travel(Node* root)//��������ͷ�ڵ�
{
	if (root == NULL)return;
	while (root)
	{
		printf("%s      %s      %s      %s      %s\n", root->data.Username, root->data.Realname,root->data.password, root->data.mail, root->data.cellphone);
		root = root->pNext;
	}
	printf("-------------------------------------------");
}

//����root�����е�n���ڵ�ĵ�ַ
Node* findNodeByPos(Node* root, int n)
{
	if (n < 0)return NULL;
	if (root == NULL)return NULL;
	if (n == 0)return root;//���ص�һ��
	for (int i = 0; i < n; i++)
	{
		if (root == NULL)return NULL;
		root = root->pNext;
	}
	return root;
}

//ɾ��root�����е�n���ڵ� n���±�0��ʼ
void deleteNode(Node** root, int n)
{
	if (root == NULL)return;
	if (*root == NULL)return;
	if (n < 0)return;
	Node* pDel = *root;
	Node* pDelPret = NULL;
	if (n == 0)//ɾ����һ��
	{
		*root = pDel->pNext;
		free(pDel);//�ͷ��ڴ�
		return;
	}


	pDelPret=findNodeByPos(*root, n);
	pDel = pDelPret->pNext;

	if (pDel == NULL)return;
	pDelPret->pNext = pDel->pNext;//pDel��ǰһ����nextָ��ָ��pDel����һ���ڵ�
	free(pDel);
	return;
}

//ɾ����������
bool deleteList(Node** root)
{
	while (1)
	{
		if (*root == NULL)return;
		deleteNode(root, 0);
	}
}

void printwelcome()//�˵�
{
	int n;
	while (1)
	{
		system("cls");
		printf("----------��ӭ��������ƽ̨----------------\n");
		printf("----------1.�û���½---------------------\n");
		printf("----------2.�û�ע��---------------------\n");
		printf("----------3.�鿴��ǰ�����û���Ϣ----------\n");
		printf("----------4.ע���û�---------------------\n");
		printf("----------5.�޸��û���Ϣ-----------------\n");
		printf("----------6.�˳�ƽ̨---------------------\n");
		printf("��ѡ��:\n");
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
	//1 ���ļ�
	FILE* fp;
	errno_t err=fopen_s(&fp,FILEPATH, "rb");//rb��Ϊ�Զ�������ʽ���ļ�
	//2 ��ȡ�ļ����ݲ������������
	Node* pList = NULL;//һ��ʼ����Ϊ��
	int r;
	User temp;//��ʱ��һ��ѧ�����ݵĽṹ��
	if (fp != NULL)
	{
		while (1)  //ѭ����ȡ�ļ�����
		{
			r = fread(&temp, 1, sizeof(User), fp);//���ļ��ж�ȡ���� 1Ϊÿ�ζ�ȡ���ݵĴ�С 1�ֽ� fpΪ���ļ������ȡ
			if (r <= 0)//û����
			{
				break;//ѭ������
			}
			else//������һ��ѧ����Ϣ
			{
				//1 ����һ������ڵ� ��ѧ����Ϣ�Ž�ȥ
				//2 ������ڵ���ӵ�������
				appendNode(&pList, &temp);
			}
		}
		//3 �ر��ļ�
		fclose(fp);
	}
	
	system("cls");
	printf("--------------ע��-----------------");
	printf("�������ʾ�����û���Ϣ\n");
	printf("�봴���û���:\n");
	scanf_s("%s", temp.Username, sizeof(temp.Username));
	printf("��������ʵ����:\n");
	scanf_s("%s", temp.Realname, sizeof(temp.Realname));
	printf("����������:\n");
	scanf_s("%s", temp.password, sizeof(temp.password));
	printf("����������:\n");
	scanf_s("%s", temp.mail, sizeof(temp.mail));
	printf("������绰��:\n");
	scanf_s("%s", temp.cellphone, sizeof(temp.cellphone));
	

	appendNode(&pList, &temp);

	//1 ���ļ�
	err = fopen_s(&fp, FILEPATH, "wb");//rb��Ϊ�Զ�������ʽ���ļ�
	Node* pTemp = pList;//���´�һ������ͷ����Ϊ���ỹҪɾ ����ֱ����pList
	//ѭ������������д��
	while (pTemp)
	{
		fwrite(&(pTemp->data), 1, sizeof(User), fp);
		pTemp = pTemp->pNext;
	}
	
	//�ر��ļ�
	fclose(fp);

	deleteList(&pList);
}
void showAllUser()
{
	//1 ���ļ�
	FILE* fp = fopen(FILEPATH,"rb");//rb��Ϊ�Զ�������ʽ���ļ�
	if (fp == NULL)
	{
		printf("ϵͳ��û��ѧ����Ϣ��\n");
		system("pause");
		return;
	}
	//2 ��ȡ�ļ����ݲ������������
	Node* pList = NULL;//һ��ʼ����Ϊ��
	int r;
	User temp;//��ʱ��һ��ѧ�����ݵĽṹ��
	while (1)  //ѭ����ȡ�ļ�����
	{
		r = fread(&temp,1,sizeof(User),fp);//���ļ��ж�ȡ���� 1Ϊÿ�ζ�ȡ���ݵĴ�С 1�ֽ� fpΪ���ļ������ȡ
		if (r <= 0)//û����
		{
			break;//ѭ������
		}
		else//������һ��ѧ����Ϣ
		{
			//1 ����һ������ڵ� ��ѧ����Ϣ�Ž�ȥ
			//2 ������ڵ���ӵ�������
			appendNode(&pList, &temp);
		}
	  }
	//3 �ر��ļ�
	fclose(fp);
	//4 �����������
	printf("�û���     ��ʵ��     ����                �绰          \n");
	travel(pList);
	//ɾ����������
	deleteList(&pList);
	system("pause");
}
void deleteUser()
{

}
void changeUser()
{

}