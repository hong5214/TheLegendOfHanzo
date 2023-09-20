#include "Include.h"
Stat statInfo;

Stat::Stat()
{
	plusAtk = 0.0;
	plusAtkSpeed = 0.0;
	plusSklDelay = 0.0;
	plusHitPer = 0;
	plusDef = 0;
	plusHp = 0.0;
	plusMoveSpeed = 0.0;
	plusMissPer = 0.0;
}

Stat::~Stat()
{
}

void Stat::Init()
{
	itemInfo.PlusOption();
}

void Stat::Update()
{	
	// ����ȭ�鿡 ���� ���� ����â ����
	if (g_Mng.n_Chap == MENU) {
		itemInfo.PlusOption(); // ������ �������� ������Ʈ

		sprintf_s(StatInfo, "ID\nLevel\nExp\nGold");
		sprintf_s(StatInfoData, "%6s\n%6d\n%6d\n%6d", sql.name[sql.index], player.Level , player.Exp, player.Gold);
	}
	else if (g_Mng.n_Chap == GAME) { // ������ �������� ǥ��
		sprintf_s(StatInfo, "Level\n Exp\n Gold");
		sprintf_s(StatInfoData, "%6d\n%6d\n%6d", player.PlayLevel, player.PlayExp, player.PlayGold);		
	}
}

void Stat::Draw()
{
	// ����â ǥ��
	dv_font.DrawString(StatInfo, 10, 30);
	dv_font.DrawString(StatInfoData, 90, 30);
}

void Stat::ShowStat() {
	dv_font.DrawString("[����]", 10, 200);
	dv_font.DrawString("[����]", 10, 230);
	sprintf_s(statValue, "%.lf (+%.lf)", player.PlayHp, plusHp);
	dv_font.DrawString(statValue, 90, 230);
	dv_font.DrawString("[����]", 10, 260);
	sprintf_s(statValue, "%.lf (+%.lf)", player.PlayAtk, plusAtk);
	dv_font.DrawString(statValue, 90, 260);
	dv_font.DrawString("[���]", 10, 290);
	sprintf_s(statValue, "%.lf (+%.lf)", player.PlayDef, plusDef);
	dv_font.DrawString(statValue, 90, 290);
	dv_font.DrawString("[����]", 10, 320);
	sprintf_s(statValue, "%.lf (+%.lf)", player.PlayHit, plusHitPer);
	dv_font.DrawString(statValue, 90, 320);
	dv_font.DrawString("[ȸ��]", 10, 350);
	sprintf_s(statValue, "%.lf (+%.lf)", player.PlayMissPer, plusMissPer);
	dv_font.DrawString(statValue, 90, 350);
	dv_font.DrawString("[�̼�]", 10, 380);
	sprintf_s(statValue, "%.lf (+%.lf)", player.PlayMoveSpeed, plusMoveSpeed);
	dv_font.DrawString(statValue, 90, 380);
	dv_font.DrawString("[����]", 10, 410);
	sprintf_s(statValue, "%.lf (-%.lf)", player.PlayAtkSpeed, plusAtkSpeed);
	dv_font.DrawString(statValue, 90, 410);
	dv_font.DrawString("[��]", 10, 440);
	sprintf_s(statValue, "%.lf (-%.lf)", player.SklDelay - plusSklDelay, plusSklDelay);
	dv_font.DrawString(statValue, 90, 440);
}
