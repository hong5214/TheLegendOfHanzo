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
	// 게임화면에 따라 유저 정보창 변경
	if (g_Mng.n_Chap == MENU) {
		itemInfo.PlusOption(); // 증가된 스탯정보 업데이트

		sprintf_s(StatInfo, "ID\nLevel\nExp\nGold");
		sprintf_s(StatInfoData, "%6s\n%6d\n%6d\n%6d", sql.name[sql.index], player.Level , player.Exp, player.Gold);
	}
	else if (g_Mng.n_Chap == GAME) { // 게임중 스탯정보 표시
		sprintf_s(StatInfo, "Level\n Exp\n Gold");
		sprintf_s(StatInfoData, "%6d\n%6d\n%6d", player.PlayLevel, player.PlayExp, player.PlayGold);		
	}
}

void Stat::Draw()
{
	// 정보창 표시
	dv_font.DrawString(StatInfo, 10, 30);
	dv_font.DrawString(StatInfoData, 90, 30);
}

void Stat::ShowStat() {
	dv_font.DrawString("[스탯]", 10, 200);
	dv_font.DrawString("[생명]", 10, 230);
	sprintf_s(statValue, "%.lf (+%.lf)", player.PlayHp, plusHp);
	dv_font.DrawString(statValue, 90, 230);
	dv_font.DrawString("[공격]", 10, 260);
	sprintf_s(statValue, "%.lf (+%.lf)", player.PlayAtk, plusAtk);
	dv_font.DrawString(statValue, 90, 260);
	dv_font.DrawString("[방어]", 10, 290);
	sprintf_s(statValue, "%.lf (+%.lf)", player.PlayDef, plusDef);
	dv_font.DrawString(statValue, 90, 290);
	dv_font.DrawString("[명중]", 10, 320);
	sprintf_s(statValue, "%.lf (+%.lf)", player.PlayHit, plusHitPer);
	dv_font.DrawString(statValue, 90, 320);
	dv_font.DrawString("[회피]", 10, 350);
	sprintf_s(statValue, "%.lf (+%.lf)", player.PlayMissPer, plusMissPer);
	dv_font.DrawString(statValue, 90, 350);
	dv_font.DrawString("[이속]", 10, 380);
	sprintf_s(statValue, "%.lf (+%.lf)", player.PlayMoveSpeed, plusMoveSpeed);
	dv_font.DrawString(statValue, 90, 380);
	dv_font.DrawString("[공속]", 10, 410);
	sprintf_s(statValue, "%.lf (-%.lf)", player.PlayAtkSpeed, plusAtkSpeed);
	dv_font.DrawString(statValue, 90, 410);
	dv_font.DrawString("[쿨감]", 10, 440);
	sprintf_s(statValue, "%.lf (-%.lf)", player.SklDelay - plusSklDelay, plusSklDelay);
	dv_font.DrawString(statValue, 90, 440);
}
