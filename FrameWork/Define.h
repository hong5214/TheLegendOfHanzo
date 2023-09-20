#define SCREEN_WITH 1200	// 화면 가로 픽셀크기
#define SCREEN_HEIGHT 720	// 화면 세로 픽셀크기
#define ID_MAX 20 // 회원 최대
#define SELECT_MAX 6 // 랜덤 능력치 선택 개수


// 데이타 베이스
//#define DB_HOST "localhost"
//#define DB_HOST "127.0.0.1"
//#define DB_USER "root"
//#define DB_PASS "5214"
#define DB_HOST "192.168.0.49"
#define DB_USER "test"
#define DB_PASS "1234"
#define DB_NAME "test"
#define CHOP(x) x[strlen(x) - 1] = ' ' // 쓸려다가 안씀...

enum gamechap
{
	LOGO = 0,
	MENU = 1,
	GAME = 2,
	OVER = 3,
	TOTALCHAP
};

enum menu {
	SHOP = 0,
	EQU = 1,
	HOME = 2,
	QUEST = 3,
	SETTING = 4,
	TOTALMENU = 5,
	LOGOUT = 6,
	START = 7,
	EXIT = 8
};