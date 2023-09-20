#pragma once
#include "Include.h"

class Character
{
public:
	Character() {};
	~Character() {};

	// ĳ���� �⺻ �ʼ� ����
	bool Life; // true : ����, false : ����
	bool Pos; // �̵� ���� (true : ������, false : ����)
	bool IsDamage; // ������ ���� ����
	bool SklUse1; // ��ų ��� ����

	// ĳ����/���ͺ� ����
	int Level; // �÷��̾� : ����, ���� : 0~3(�ʱ�/���/���� ����)
	int Exp; // �÷��̾� : ���� ����ġ, ���� : ���� ų�� ����ġ
	int MaxExp; // �÷��̾� : �ִ� ����ġ, ���� : ������
	int Gold; // �÷��̾� : ���� ���, ���� : ���� ų�� ���
	int Item; // �÷��̾� : ������ ��� Ȯ��, ���� : ��� ������ ��� Ȯ��
	double X, Y; // ���� ��ġ
	
	// ���� ����
	double Hp; // �����
	double MaxHp; // �ִ� �����
	double Atk; // ���ݷ�
	double Def; // ����
	double AtkSpeed; // �⺻���ݼӵ�
	double MoveSpeed; // �̵��ӵ�

	double PlayHp; // ������ �����
	double PlayAtk; // ������ ���ݷ�
	double PlayDef; // ������ ����
	double PlayAtkSpeed; // ������ ���ݼӵ�
	double PlayMoveSpeed; // ������ �̵��ӵ�

	char PlayState[100]; // �÷��̾� ����
	char AtkDamage[100]; // ������

	RECT HpBox; // ���� ü�� ǥ�ÿ���
	RECT DamageBox; // ������ ǥ�ÿ���

	DWORD DamageTime; // ������ ��ȿ �ð�
	DWORD AttackTime; // ���� �ð�

	void RESET() {
		Life = true; // true : ����, false : ����
		Pos = true; // �̵� ���� (true : right, false : left)
		IsDamage = false;
		SklUse1 = false;
		DamageTime = GetTickCount64(); // ������ ���� ���� �ð� üũ
		AttackTime = GetTickCount64(); // ���� �ð� üũ
		sprintf(PlayState, "%.lf", PlayHp); // ���� ü�� �ʱ�ȭ
	}
};