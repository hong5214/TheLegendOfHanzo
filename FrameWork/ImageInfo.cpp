#include "Include.h"
ImageInfo imageInfo;

ImageInfo::ImageInfo(){ // �̹��� ������
	sprintf_s(FileName, ""); // �ʱ�ȭ
}
ImageInfo::~ImageInfo() { // �̹��� ������

}

void ImageInfo::Init() { // �̹��� �ʱ�ȭ	
	centerWith = SCREEN_WITH / 2; // ���� ���� ��ǥ
						 /*////////////////////////////////////////�޴� �̹���///////////////////////////////////////////////////*/
	// �޴� ���(����, ���, Ȩ, ����Ʈ, ����)
	menuImg[0].Create("./resource/Img/menu/BG/mainShop.png", false, D3DCOLOR_XRGB(0, 0, 0));
	menuImg[1].Create("./resource/Img/menu/BG/mainItem.png", false, D3DCOLOR_XRGB(0, 0, 0));
	menuImg[2].Create("./resource/Img/menu/BG/mainHome.jpg", false, D3DCOLOR_XRGB(0, 0, 0));
	menuImg[3].Create("./resource/Img/menu/BG/mainQuest.jpg", false, D3DCOLOR_XRGB(0, 0, 0));
	menuImg[4].Create("./resource/Img/menu/BG/mainSet.jpg", false, D3DCOLOR_XRGB(0, 0, 0));

	// ��� Ÿ�� ���
	for (int i = 0; i < 4; i++)
	{
		sprintf_s(FileName, "./resource/Img/menu/itemBG/mainItem%01d.png", i);
		itemTypeImg[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	// ��ư �̹���(����, ���, Ȩ, ����Ʈ, ����)
	for (int i = 0; i < 5; i++)
	{
		sprintf_s(FileName, "./resource/Img/menu/btn/menu_btn%d.png", i);
		bt_menu[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	
	// ��ư �̹���(����, ����, �α׾ƿ�)
	bt_start.Create("./resource/Img/menu/btn/menu_btnStart.png", false, D3DCOLOR_XRGB(0, 0, 0));
	bt_exit.Create("./resource/Img/menu/btn/menu_btnExit.png", false, D3DCOLOR_XRGB(0, 0, 0));
	bt_logout.Create("./resource/Img/menu/btn/menu_btnLogout.png", false, D3DCOLOR_XRGB(0, 0, 0));
	
	// ��ư ȿ��
	bt_menuBorder.Create("./resource/Img/menu/effect/menu_btnBolder.png", false, D3DCOLOR_XRGB(0, 0, 0));
	bt_shopBorder.Create("./resource/Img/menu/effect/shop_btnBorder.png", false, D3DCOLOR_XRGB(0, 0, 0));
	bt_shopSelect.Create("./resource/Img/menu/effect/shop_btnSelect.png", false, D3DCOLOR_XRGB(0, 0, 0));
	bt_itemSelect.Create("./resource/Img/menu/effect/item_btnSelect.png", false, D3DCOLOR_XRGB(0, 0, 0));
	bt_itemTypeSelect.Create("./resource/Img/menu/effect/itemType_btnSelect.png", false, D3DCOLOR_XRGB(0, 0, 0));

	itemInfo.Init();

	/*////////////////////////////////////////�÷��̾� �̹���///////////////////////////////////////////////////*/
	
	// �÷��̾� �̹���
	PlayerImgR.Create("./resource/Img/Player/userR.png", false, D3DCOLOR_XRGB(0, 0, 0)); // �̹��� ���� ���Բ� ���
	AttackImgR.Create("./resource/Img/Player/AttackR.png", false, D3DCOLOR_XRGB(0, 0, 0)); // ���� ��� �������� ����
	SkillImgR.Create("./resource/Img/Player/SkillR.png", false, D3DCOLOR_XRGB(0, 0, 0)); // ���� ��� �������� ����
	PlayerImgL.Create("./resource/Img/Player/userL.png", false, D3DCOLOR_XRGB(0, 0, 0)); // �̹��� ���� ���Բ� ���
	AttackImgL.Create("./resource/Img/Player/AttackL.png", false, D3DCOLOR_XRGB(0, 0, 0)); // ���� ��� �������� ����
	SkillImgL.Create("./resource/Img/Player/SkillL.png", false, D3DCOLOR_XRGB(0, 0, 0)); // ���� ��� �������� ����

	for (int i = 0; i < 26; i++)
	{
		sprintf_s(FileName, "./resource/Img/Monster/boom/%02d.png", i);
		AtkEffectimg1[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	/*////////////////////////////////////////���� �̹���///////////////////////////////////////////////////*/
	GenjiImgR.Create("./resource/Img/Monster/boss/GenjiR.png", false, D3DCOLOR_XRGB(0, 0, 0));
	GenjiAtkImgR.Create("./resource/Img/Monster/boss/GenjiAtkR.png", false, D3DCOLOR_XRGB(0, 255, 0));
	GenjiImgL.Create("./resource/Img/Monster/boss/GenjiL.png", false, D3DCOLOR_XRGB(0, 0, 0));
	GenjiAtkImgL.Create("./resource/Img/Monster/boss/GenjiAtkL.png", false, D3DCOLOR_XRGB(0, 255, 0));

	/*////////////////////////////////////////���� �̹���///////////////////////////////////////////////////*/
	HelpLogo.Create("./resource/Img/Help/HelpLogo.png", false, D3DCOLOR_XRGB(0, 255, 0)); // �α��� ����
	HelpMenu.Create("./resource/Img/Help/HelpMenu.png", false, D3DCOLOR_XRGB(0, 255, 0)); // �޴� ����
	HelpShop.Create("./resource/Img/Help/HelpShop.png", false, D3DCOLOR_XRGB(0, 255, 0)); // ���� ����
	HelpItem.Create("./resource/Img/Help/HelpItem.png", false, D3DCOLOR_XRGB(0, 255, 0)); // ������ ����
	HelpGame.Create("./resource/Img/Help/HelpGame.png", false, D3DCOLOR_XRGB(0, 255, 0)); // ���� ����

	sprintf_s(FileName, "./resource/Img/UI/SkillOK.png");
	SkillUseImg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(FileName, "./resource/Img/UI/SkillEffect.png");
	SkillEffectImg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	sprintf_s(FileName, "./resource/Img/UI/hpFull.png");
	HpFullImg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(FileName, "./resource/Img/UI/hpZero.png");
	HpZeroImg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(FileName, "./resource/Img/UI/skillSelect.png");
	LevelUpImg.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	sprintf_s(FileName, "./resource/Img/UI/Select.png");
	SelectBox.Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));

	for (int i = 0; i < SELECT_MAX; i++)
	{
		sprintf_s(FileName, "./resource/Img/UI/Select%02d.png", i + 1);
		SelectImg[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 3; i++)
	{
		Gmanager.RandomSelect(i);
	}
}