#pragma once
#include "Include.h"

class Mysql
{

public:
	Mysql();
	~Mysql();

	// MYSQL 구조체 변수 (Logo 챕터에서 1 단계 테스트 접속 확인을 위함...)
	MYSQL mysql;

	// MYSQL 연결 및 구동 변수
	MYSQL		*connection = NULL, conn;
	MYSQL_RES	*sql_result;
	MYSQL_ROW	sql_row;
	int query_start;
	int query_item;

	// 데이타 베이스 칼럼 저장 변수
	char name[ID_MAX][12]; // 아이디
	char password[ID_MAX][80]; // 패스워드
	int level[ID_MAX]; // 레벨
	int exp[ID_MAX]; // 경험치
	int gold[ID_MAX]; // 골드	

	int count; // 데이터베이스 내 아이디 총 개수
	int index; // 로그인한 아이디 인덱스

	char tel[12];
	char query[255];

	// MYSQL 상태 변수
	char state[256];
	bool mysql_Success;

	void Init();
	void Update(double frame);
	void Draw();
	void QueryCheck();
	void CreateID(); // 회원가입
	void DeleteID(); // 회원탈퇴
	void autoSave(); // 자동 저장(레벨, 경험치, 골드)
	void getItem(); // 아이템 로드
	void setItemCount(); // 아이템 개수 변경
	void setItemUse(int num, int type); // 아이템 장착
	void FusionItem(int num, int type); // 아이템 합성
};

extern Mysql sql;