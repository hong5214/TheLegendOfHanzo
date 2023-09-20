#include "Include.h"

Mysql sql;


Mysql::Mysql()
{

}

Mysql::~Mysql()
{
	// mysql(데이타 베이스) 연결 해제
	mysql_close(connection);
}

void Mysql::Init()
{
	// mysql 구조체 변수 초기화
	mysql_init(&conn);

	// ip, 접속 id , pass, 데이타 베이스명, 포트번호 등으로 접속
	connection = mysql_real_connect(&conn, DB_HOST,	DB_USER, DB_PASS, DB_NAME, 3306,(char*)NULL, 0); // 사용할 db 선택

	// 만약 접속에 실패하면 다음 실행
	if (connection == NULL)
	{
		sprintf_s(state, "Mysql connection error : %s", mysql_error(&conn));
		mysql_Success = false;
		// 테스트 아이디 하나 추가 후 종료		
		sprintf_s(name[index], "test");
		sprintf_s(password[index], "1234");
		CreateID();
		return;
	}
	else // 아니면...
	{
		mysql_Success = true;
	}

	// 다음 mysql_query() 함수로 MYSQL 구조체를 통한 쿼리문 전송
	query_start = mysql_query(connection, "select * from login");
	if (query_start != 0) // 전송 실패시
	{
		sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
	}
	else // 성공시
	{
		mysql_Success = true;
	}

	// mysql_store_result 함수로 넘어온 데이타 베이스 값 저장
	sql_result = mysql_store_result(connection); // 사용할 db 데이터 가져옴

	// ID, 비밀번호 가져오기 
	// select * from login where ?? 사용 안했으니... 총 레코드 수 만큼 넘어옴(그 만큼 루프를 돈다)
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
	{
		sprintf_s(name[count], "%s", sql_row[0]);
		sprintf_s(password[count], "%s", sql_row[1]);
		level[count] = atoi(sql_row[2]); // level 저장
		exp[count] = atoi(sql_row[3]); // exp 저장
		gold[count] = atoi(sql_row[4]); // gold 저장		

		// 레코드 수만큼 증가... 
		count += 1; // 다음 레코드 확인하기 위함
	}

	// sql_result 값 해제
	mysql_free_result(sql_result);
}

// 사용 안함
void Mysql::Update(double frame)
{


}

void Mysql::Draw()
{
}

void Mysql::QueryCheck()
{
	query_start = mysql_query(connection, query);
	if (query_start != 0) // 전송 실패시
	{
		sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
		mysql_Success = false;
	}
	else // 성공시
	{
		mysql_Success = true;
	}
}

void Mysql::CreateID()
{	
	if (mysql_Success)
	{
		// 회원 가입
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
		// 로그인 중인 회원 탈퇴
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
		if (query_start != 0) // 전송 실패시
		{
			sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
			mysql_Success = false;
		}
		else // 성공시
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
			if (i == 0) // 무기데이터 불러오기
				sprintf_s(query, "select ItemBow.* from login join ItemBow on '%s' = ItemBow.id;", name[index]);
			else if (i == 1) // 헬멧데이터 불러오기
				sprintf_s(query, "select ItemCap.* from login join ItemCap on '%s' = ItemCap.id;", name[index]);
			else if (i == 2) // 갑옷데이터 불러오기
				sprintf_s(query, "select ItemArmor.* from login join ItemArmor on '%s' = ItemArmor.id;", name[index]);
			else if (i == 3) // 신발데이터 불러오기
				sprintf_s(query, "select ItemShoes.* from login join ItemShoes on '%s' = ItemShoes.id;", name[index]);
			query_start = mysql_query(connection, query);
			if (query_start != 0) // 전송 실패시
			{
				sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
				mysql_Success = false;
			}
			else // 성공시
			{
				mysql_Success = true;
			}

			sql_result = mysql_store_result(connection); // 사용할 db 데이터 가져옴

			while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
			{
				itemInfo.itemUse[i] = atoi(sql_row[1]); // 착용 유무 저장
				switch (i)
				{
				case 0:
					for (int j = 0; j < 16; j++) // 0 = id, 1 = 착용유무, 2~17 : 아이템
						itemInfo.itemBow[j] = atoi(sql_row[j + 2]); // 무기 데이터 저장
					break;
				case 1:
					for (int j = 0; j < 16; j++)
						itemInfo.itemCap[j] = atoi(sql_row[j + 2]); // 헬멧 데이터 저장
					break;
				case 2:
					for (int j = 0; j < 16; j++)
						itemInfo.itemArmor[j] = atoi(sql_row[j + 2]); // 갑옷 데이터 저장
					break;
				case 3:
					for (int j = 0; j < 16; j++)
						itemInfo.itemShoes[j] = atoi(sql_row[j + 2]); // 신발 데이터 저장

				}

			}
		}
	}
	else
	{
		// 데이터베이스 없으면 처음 상태로 초기화
		for (int i = 0; i < 4; i++)
			itemInfo.itemUse[i] = 16; // 착용 유무 저장

		for (int j = 0; j < 16; j++)
		{
			itemInfo.itemBow[j] = 0; // 무기 데이터 저장
			itemInfo.itemCap[j] = 0; // 헬멧 데이터 저장
			itemInfo.itemArmor[j] = 0; // 갑옷 데이터 저장
			itemInfo.itemShoes[j] = 0; // 신발 데이터 저장
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
		if (query_start != 0) // 전송 실패시
		{
			sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
			mysql_Success = false;
		}
		else // 성공시
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
	// idx : 부위, use : 착용유무
	itemInfo.itemUse[type] = num; // 사용하고 있는 아이템 번호
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
		if (query_start != 0) // 전송 실패시
		{
			sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
			mysql_Success = false;
		}
		else // 성공시
		{
			mysql_Success = true;
		}
	}
}

void Mysql::FusionItem(int num, int type)
{
	// idx : 부위
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
		if (query_start != 0) // 전송 실패시
		{
			sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
			mysql_Success = false;
		}
		else // 성공시
		{
			mysql_Success = true;
		}
		num++; // 다음 등급 개수증가
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
		if (query_start != 0) // 전송 실패시
		{
			sprintf_s(state, "Mysql query error : %s", mysql_error(&conn));
			mysql_Success = false;
		}
		else // 성공시
		{
			mysql_Success = true;
		}
	}	
}