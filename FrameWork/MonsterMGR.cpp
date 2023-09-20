#include "Include.h"

void MonsterMGR::Insert_Monster() {
	monsterboss.Insert(new Monster(monsterboss.GetItemCount())); // ���� ������ ����
	if(monsterboss.GetItemCount() != monsterboss.GetLength()) // ������ �������� ����
		monsterboss.GetItem(monsterboss.GetItemCount()-1)->Init();
}

void MonsterMGR::Remove_Monster(int idx) {
	monsterboss.Remove(idx); // �ش� ���� ����
}

void MonsterMGR::Reset_Monster() {
	monsterboss.Reset(); // �ش� ���� ����
}

void MonsterMGR::Draw_Monster(int idx) {
	monsterboss.GetItem(idx)->Draw();
}

void MonsterMGR::Update_Monster(int idx) {
	monsterboss.GetItem(idx)->Update();
}

int MonsterMGR::GetMonsterCount() // �� �ε��� ��ȯ
{
	return monsterboss.GetItemCount();
}

Monster* MonsterMGR::GetMonster(int idx) // �ش� �ε����� ���� ������ ��ü�� ��ȯ
{
	return monsterboss.GetItem(idx);
}
