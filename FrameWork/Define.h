#define SCREEN_WITH 1200	// ȭ�� ���� �ȼ�ũ��
#define SCREEN_HEIGHT 720	// ȭ�� ���� �ȼ�ũ��
#define ID_MAX 20 // ȸ�� �ִ�
#define SELECT_MAX 6 // ���� �ɷ�ġ ���� ����


// ����Ÿ ���̽�
//#define DB_HOST "localhost"
//#define DB_HOST "127.0.0.1"
//#define DB_USER "root"
//#define DB_PASS "5214"
#define DB_HOST "192.168.0.49"
#define DB_USER "test"
#define DB_PASS "1234"
#define DB_NAME "test"
#define CHOP(x) x[strlen(x) - 1] = ' ' // �����ٰ� �Ⱦ�...

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