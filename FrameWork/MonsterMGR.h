#include "Include.h"

class MonsterMGR // 몬스터 포인터 배열을 통해 객체 저장을 위한 매니저
{	
	Container<Monster*> monsterboss;  // 몬스터 인덱스 관리 객체
public:
	enum { INSERT = 0, // 몬스터 생성
		REMOVE, // 몬스터 삭제
		};	
	void Insert_Monster();
	void Remove_Monster(int idx);
	void Reset_Monster();
	void Draw_Monster(int idx);
	void Update_Monster(int idx);
	int GetMonsterCount(); // 소환된 몬스터 총 개수
	Monster* GetMonster(int idx); // 해당 인덱스의 몬스터 객체로 반환
};