#include "Include.h"

Map map;


Map::Map()
{
	m_Stage = 1;
	MaxStage = 10; // �ִ� ��������
}

Map::~Map()
{
}

void Map::Init()
{
	char FileName[256];
	// �ü��� ���� ��� �̹���
	sprintf_s(FileName, "./resource/Img/map1/BG_Archero/Stage1.jpg");
	m_MapStage1.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/map1/BG_Archero/BGEffect.png");
	m_MapStage1Effect.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	//for(i = 0; i<6; i++ ) // ��� ��� �̹��� ��ħ
	//{
	//	sprintf_s(FileName, "./resource/Img/map1/BG_Hades_1/BG_Hades_%04d.tga", i + 1);
	//	m_MapImg1_1[i].Create( FileName ,false,D3DCOLOR_XRGB(0,0,0));
	//	
	//}

	//j = 1;
	//for(i = 0; i<45; i++ ) // ��� �ִϸ��̼� ȿ�� ����
	//{
	//	sprintf_s(FileName, "./resource/Img/map1/BG_Hades_2/BG_Hades_0002_%06d.tga", j);
	//	m_MapImg1_2[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	//	j+=2;
	//	
	//}

	//for (int i = 0; i<65; i++) // ��� �Ҷ� ȿ�� ����
	//{
	//	sprintf_s(FileName, "./resource/Img/map1/BG_Medusa_3/BG_Medusa_fire_01_%04d.tga", i + 1);
	//	m_MapImg1_3[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	//}

	//for (int i = 0; i<7; i++) // �ٴ� ��� �̹��� ��ħ
	//{
	//	sprintf_s(FileName, "./resource/Img/map1/BG_Poseidon_1/BG_Poseidon_%04d.tga", i + 1);
	//	m_MapImg2_1[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	//}

	//for(int i = 0; i<30; i++ ) // �ٴ� ���� ȿ�� ����
	//{
	//	sprintf_s(FileName, "./resource/Img/map1/BG_Poseidon_2/1%04d.png", i);
	//	m_MapImg2_2[i].Create(FileName,false,D3DCOLOR_XRGB(0,0,0));
	//	
	//} 

	//for(int i = 0; i<45; i++ ) // �ٴ� �¾�� ȿ�� ����
	//{
	//	sprintf_s(FileName, "./resource/Img/map1/BG_Poseidon_3/1%04d.png", i );
	//	m_MapImg2_3[i].Create(FileName,false,D3DCOLOR_XRGB(0,0,0));		
	//} 
}

void Map::Update(double frame)
{
	
}

void Map::Draw()
{
	m_MapStage1.Render(0, 0, 0, 1, 1);
	m_MapStage1Effect.Render(0, 0, 0, 1, 1);

	// �������� ǥ��
	sprintf_s(stageNum, "Stage%d", m_Stage);
	dv_font.DrawString(stageNum, SCREEN_WITH / 2 - 60, 30);
	//���� ����, �� ���� ǥ��
	sprintf_s(monsterCount, "(���� �� : %d / %d)", Gmanager.monsterMaxCount - Gmanager.monsterKillCount, Gmanager.monsterMaxCount);	
	dv_font.DrawString(monsterCount, SCREEN_WITH / 2 - 100, 60);
	// ��ų ��Ÿ�� ǥ��
	player.PlaySklDelay == 0.0 ? // ��� �����ϸ� Ȱ��ȭ, �ƴϸ� ��Ȱ��
		imageInfo.SkillUseImg.SetColor(255, 255, 255, 255)
		: imageInfo.SkillUseImg.SetColor(255, 255, 255, 100);
	imageInfo.SkillUseImg.Draw(SCREEN_WITH - imageInfo.SkillUseImg.imagesinfo.Width - 20, 60);
	sprintf_s(skillDelay, "% .1lf", player.PlaySklDelay);
	dv_font.DrawString(skillDelay, SCREEN_WITH - imageInfo.SkillUseImg.imagesinfo.Width / 2 - 55, 110);

}
