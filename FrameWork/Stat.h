#include "Include.h"
class Stat
{

public:
	Stat();
	~Stat();
	char StatInfo[200]; // 표시할 목록
	char StatInfoData[200]; // 표시할 목록
	char statValue[20]; // 스탯값
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