#include "Include.h"

void MonsterMGR::Insert_Monster() {
	monsterboss.Insert(new Monster(monsterboss.GetItemCount())); // 추후 생성자 조정
	if(monsterboss.GetItemCount() != monsterboss.GetLength()) // 꽉차지 않을때만 생성
		monsterboss.GetItem(monsterboss.GetItemCount()-1)->Init();
}

void MonsterMGR::Remove_Monster(int idx) {
	monsterboss.Remove(idx); // 해당 몬스터 제거
}

void MonsterMGR::Reset_Monster() {
	monsterboss.Reset(); // 해당 몬스터 제거
}

void MonsterMGR::Draw_Monster(int idx) {
	monsterboss.GetItem(idx)->Draw();
}

void MonsterMGR::Update_Monster(int idx) {
	monsterboss.GetItem(idx)->Update();
}

int MonsterMGR::GetMonsterCount() // 총 인덱스 반환
{
	return monsterboss.GetItemCount();
}

Monster* MonsterMGR::GetMonster(int idx) // 해당 인덱스의 몬스터 포인터 객체로 반환
{
	return monsterboss.GetItem(idx);
}
