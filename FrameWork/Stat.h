#include "Include.h"
class Stat
{

public:
	Stat();
	~Stat();
	char StatInfo[200]; // ǥ���� ���
	char StatInfoData[200]; // ǥ���� ���
	char statValue[20]; // ���Ȱ�
	double plusAtk;
	double plusAtkSpeed;
	double plusSklDelay;
	double plusHitPer;
	double plusDef;
	double plusHp;
	double plusMoveSpeed;
	double plusMissPer;

	void Init();
	void Update();
	void Draw();
	void ShowStat();
};

extern Stat statInfo;