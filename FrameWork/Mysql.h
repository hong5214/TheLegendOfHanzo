#pragma once
#include "Include.h"

class Mysql
{

public:
	Mysql();
	~Mysql();

	// MYSQL ����ü ���� (Logo é�Ϳ��� 1 �ܰ� �׽�Ʈ ���� Ȯ���� ����...)
	MYSQL mysql;

	// MYSQL ���� �� ���� ����
	MYSQL		*connection = NULL, conn;
	MYSQL_RES	*sql_result;
	MYSQL_ROW	sql_row;
	int query_start;
	int query_item;

	// ����Ÿ ���̽� Į�� ���� ����
	char name[ID_MAX][12]; // ���̵�
	char password[ID_MAX][80]; // �н�����
	int level[ID_MAX]; // ����
	int exp[ID_MAX]; // ����ġ
	int gold[ID_MAX]; // ���	

	int count; // �����ͺ��̽� �� ���̵� �� ����
	int index; // �α����� ���̵� �ε���

	char tel[12];
	char query[255];

	// MYSQL ���� ����
	char state[256];
	bool mysql_Success;

	void Init();
	void Update(double frame);
	void Draw();
	void QueryCheck();
	void CreateID(); // ȸ������
	void DeleteID(); // ȸ��Ż��
	void autoSave(); // �ڵ� ����(����, ����ġ, ���)
	void getItem(); // ������ �ε�
	void setItemCount(); // ������ ���� ����
	void setItemUse(int num, int type); // ������ ����
	void FusionItem(int num, int type); // ������ �ռ�
};

extern Mysql sql;