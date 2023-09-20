#include "Include.h"

Mysql sql;


Mysql::Mysql()
{

}

Mysql::~Mysql()
{
	// mysql(����Ÿ ���̽�) ���� ����
	mysql_close(connection);
}

void Mysql::Init()
{
	// mysql ����ü ���� �ʱ�ȭ
	mysql_init(&conn);

	// ip, ���� id , pass, ����Ÿ ���̽���, ��Ʈ��ȣ ������ ����
	connection = mysql_real_connect(&conn, DB_HOST,	DB_USER, DB_PASS, DB_NAME, 3306,(char*)NULL, 0); // ����� db ����

	// ���� ���ӿ� �����ϸ� ���� ����
	if (connection == NULL)
	{
		sprintf_s(state, "Mysql connection error : %s", mysql_error(&conn));
		mysql_Success = false;
		// �׽�Ʈ ���̵� �ϳ� �߰� �� ����		
		sprintf_s(name[index], "test");
		sprintf_s(password[index], "1234");
		CreateID();
		return;
	}
	else // �ƴϸ�...
	{
		mysql_Success = true;
	}

	// ���� mysql_query() �Լ��� MYSQL ����ü�� ���� ������ ����
	query_start = mysql_query(connection, "select * from login");
	if (query_start != 0) // ���� ���н�
	{
		sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
	}
	else // ������
	{
		mysql_Success = true;
	}

	// mysql_store_result �Լ��� �Ѿ�� ����Ÿ ���̽� �� ����
	sql_result = mysql_store_result(connection); // ����� db ������ ������

	// ID, ��й�ȣ �������� 
	// select * from login where ?? ��� ��������... �� ���ڵ� �� ��ŭ �Ѿ��(�� ��ŭ ������ ����)
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		sprintf_s(name[count], "%s", sql_row[0]);
		sprintf_s(password[count], "%s", sql_row[1]);
		level[count] = atoi(sql_row[2]); // level ����
		exp[count] = atoi(sql_row[3]); // exp ����
		gold[count] = atoi(sql_row[4]); // gold ����		

		// ���ڵ� ����ŭ ����... 
		count += 1; // ���� ���ڵ� Ȯ���ϱ� ����
	}

	// sql_result �� ����
	mysql_free_result(sql_result);
}

// ��� ����
void Mysql::Update(double frame)
{


}

void Mysql::Draw()
{
}

void Mysql::QueryCheck()
{
	query_start = mysql_query(connection, query);
	if (query_start != 0) // ���� ���н�
	{
		sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
		mysql_Success = false;
	}
	else // ������
	{
		mysql_Success = true;
	}
}

void Mysql::CreateID()
{	
	if (mysql_Success)
	{
		// ȸ�� ����
		sprintf_s(query, "insert into login(id, pw) values('%s', '%s');", name[count], password[count]);
		QueryCheck();
		sprintf_s(query, "insert into ItemBow(id) values('%s');", name[count]);
		QueryCheck();
		sprintf_s(query, "insert into ItemCap(id) values('%s');", name[count]);
		QueryCheck();
		sprintf_s(query, "insert into ItemArmor(id) values('%s');", name[count]);
		QueryCheck();
		sprintf_s(query, "insert into ItemShoes(id) values('%s');", name[count]);
		QueryCheck();
		sprintf_s(query, "update login set level = '%d', exp = '%d', gold = '%d' where id = '%s';", level[count], exp[count], gold[count], name[count]);
		QueryCheck();		
	}
	level[count] = 1;
	exp[count] = 0;
	gold[count] = 100000;
	count++;
}

void Mysql::DeleteID()
{	
	if (mysql_Success)
	{
		// �α��� ���� ȸ�� Ż��
		sprintf_s(query, "delete from login where id = '%s';", name[index]);
		QueryCheck();
		sprintf_s(query, "delete from ItemBow where id = '%s';", name[index]);
		QueryCheck();
		sprintf_s(query, "delete from ItemCap where id = '%s';", name[index]);
		QueryCheck();
		sprintf_s(query, "delete from ItemArmor where id = '%s';", name[index]);
		QueryCheck();
		sprintf_s(query, "delete from ItemShoes where id = '%s';", name[index]);
		QueryCheck();
		count = 0;
		Init();
	}
}

void Mysql::autoSave()
{
	level[index] = player.Level;
	exp[index] = player.Exp;
	gold[index] = player.Gold;

	if (mysql_Success)
	{
		sprintf_s(query, "update login set level = '%d', exp = '%d', gold = '%d' where id = '%s' and pw = '%s'",
			level[index], exp[index], gold[index], name[index], password[index]);
		query_start = mysql_query(connection, query);
		if (query_start != 0) // ���� ���н�
		{
			sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
			mysql_Success = false;
		}
		else // ������
		{
			mysql_Success = true;
		}
	}	
}

void Mysql::getItem()
{
	if (mysql_Success) {
		for (int i = 0; i < 4; i++)
		{
			if (i == 0) // ���ⵥ���� �ҷ�����
				sprintf_s(query, "select ItemBow.* from login join ItemBow on '%s' = ItemBow.id;", name[index]);
			else if (i == 1) // ��䵥���� �ҷ�����
				sprintf_s(query, "select ItemCap.* from login join ItemCap on '%s' = ItemCap.id;", name[index]);
			else if (i == 2) // ���ʵ����� �ҷ�����
				sprintf_s(query, "select ItemArmor.* from login join ItemArmor on '%s' = ItemArmor.id;", name[index]);
			else if (i == 3) // �Źߵ����� �ҷ�����
				sprintf_s(query, "select ItemShoes.* from login join ItemShoes on '%s' = ItemShoes.id;", name[index]);
			query_start = mysql_query(connection, query);
			if (query_start != 0) // ���� ���н�
			{
				sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
				mysql_Success = false;
			}
			else // ������
			{
				mysql_Success = true;
			}

			sql_result = mysql_store_result(connection); // ����� db ������ ������

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				itemInfo.itemUse[i] = atoi(sql_row[1]); // ���� ���� ����
				switch (i)
				{
				case 0:
					for (int j = 0; j < 16; j++) // 0 = id, 1 = ��������, 2~17 : ������
						itemInfo.itemBow[j] = atoi(sql_row[j + 2]); // ���� ������ ����
					break;
				case 1:
					for (int j = 0; j < 16; j++)
						itemInfo.itemCap[j] = atoi(sql_row[j + 2]); // ��� ������ ����
					break;
				case 2:
					for (int j = 0; j < 16; j++)
						itemInfo.itemArmor[j] = atoi(sql_row[j + 2]); // ���� ������ ����
					break;
				case 3:
					for (int j = 0; j < 16; j++)
						itemInfo.itemShoes[j] = atoi(sql_row[j + 2]); // �Ź� ������ ����

				}

			}
		}
	}
	else
	{
		// �����ͺ��̽� ������ ó�� ���·� �ʱ�ȭ
		for (int i = 0; i < 4; i++)
			itemInfo.itemUse[i] = 16; // ���� ���� ����

		for (int j = 0; j < 16; j++)
		{
			itemInfo.itemBow[j] = 0; // ���� ������ ����
			itemInfo.itemCap[j] = 0; // ��� ������ ����
			itemInfo.itemArmor[j] = 0; // ���� ������ ����
			itemInfo.itemShoes[j] = 0; // �Ź� ������ ����
		}
	}
}
void Mysql::setItemCount()
{
	char addItemIndex[100];
	sprintf(addItemIndex, "item%02d", itemInfo.itemNum);
	if (mysql_Success)
	{
		switch (itemInfo.itemType)
		{
		case 0:
			sprintf_s(query, "update itemBow set %s = '%d' where id = '%s'", addItemIndex, ++itemInfo.itemBow[itemInfo.itemNum], name[index]);
			break;
		case 1:
			sprintf_s(query, "update itemCap set %s = '%d' where id = '%s'", addItemIndex, ++itemInfo.itemCap[itemInfo.itemNum], name[index]);
			break;
		case 2:
			sprintf_s(query, "update itemArmor set %s = '%d' where id = '%s'", addItemIndex, ++itemInfo.itemArmor[itemInfo.itemNum], name[index]);
			break;
		case 3:
			sprintf_s(query, "update itemShoes set %s = '%d' where id = '%s'", addItemIndex, ++itemInfo.itemShoes[itemInfo.itemNum], name[index]);
			break;
		default:
			break;
		}

		query_start = mysql_query(connection, query);
		if (query_start != 0) // ���� ���н�
		{
			sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
			mysql_Success = false;
		}
		else // ������
		{
			mysql_Success = true;
		}
	}	
	else
	{
		switch (itemInfo.itemType)
		{
		case 0:
			itemInfo.itemBow[itemInfo.itemNum]++;
			break;
		case 1:
			itemInfo.itemCap[itemInfo.itemNum]++;
			break;
		case 2:
			itemInfo.itemArmor[itemInfo.itemNum]++;
			break;
		case 3:
			itemInfo.itemShoes[itemInfo.itemNum]++;
			break;
		default:
			break;
		}
	}
}


void Mysql::setItemUse(int num, int type)
{	
	// idx : ����, use : ��������
	itemInfo.itemUse[type] = num; // ����ϰ� �ִ� ������ ��ȣ
	if (mysql_Success)
	{
		switch (type)
		{
		case 0:
			sprintf_s(query, "update itemBow set itemUse = '%d' where id = '%s'", num, name[index]);
			break;
		case 1:
			sprintf_s(query, "update itemCap set itemUse = '%d' where id = '%s'", num, name[index]);
			break;
		case 2:
			sprintf_s(query, "update itemArmor set itemUse = '%d' where id = '%s'", num, name[index]);
			break;
		case 3:
			sprintf_s(query, "update itemShoes set itemUse = '%d' where id = '%s'", num, name[index]);
			break;
		default:
			break;
		}

		query_start = mysql_query(connection, query);
		if (query_start != 0) // ���� ���н�
		{
			sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
			mysql_Success = false;
		}
		else // ������
		{
			mysql_Success = true;
		}
	}
}

void Mysql::FusionItem(int num, int type)
{
	// idx : ����
	char fusionItemIndex[100];
	char addItemIndex[100];
	sprintf(fusionItemIndex, "item%02d", num);
	sprintf(addItemIndex, "item%02d", num+1);
	if (mysql_Success) {
		switch (type)
		{
		case 0:
			sprintf_s(query, "update itemBow set %s = '%d' where id = '%s'", fusionItemIndex, itemInfo.itemBow[num], name[index]);
			break;
		case 1:
			sprintf_s(query, "update itemCap set %s = '%d' where id = '%s'", fusionItemIndex, itemInfo.itemCap[num], name[index]);
			break;
		case 2:
			sprintf_s(query, "update itemArmor set %s = '%d' where id = '%s'", fusionItemIndex, itemInfo.itemArmor[num], name[index]);
			break;
		case 3:
			sprintf_s(query, "update itemShoes set %s = '%d' where id = '%s'", fusionItemIndex, itemInfo.itemShoes[num], name[index]);
			break;
		default:
			break;
		}

		query_start = mysql_query(connection, query);
		if (query_start != 0) // ���� ���н�
		{
			sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
			mysql_Success = false;
		}
		else // ������
		{
			mysql_Success = true;
		}
		num++; // ���� ��� ��������
		switch (type)
		{
		case 0:
			sprintf_s(query, "update itemBow set %s = '%d' where id = '%s'", addItemIndex, itemInfo.itemBow[num], name[index]);
			break;
		case 1:
			sprintf_s(query, "update itemCap set %s = '%d' where id = '%s'", addItemIndex, itemInfo.itemCap[num], name[index]);
			break;
		case 2:
			sprintf_s(query, "update itemArmor set %s = '%d' where id = '%s'", addItemIndex, itemInfo.itemArmor[num], name[index]);
			break;
		case 3:
			sprintf_s(query, "update itemShoes set %s = '%d' where id = '%s'", addItemIndex, itemInfo.itemShoes[num], name[index]);
			break;
		default:
			break;
		}

		query_start = mysql_query(connection, query);
		if (query_start != 0) // ���� ���н�
		{
			sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
			mysql_Success = false;
		}
		else // ������
		{
			mysql_Success = true;
		}
	}	
}