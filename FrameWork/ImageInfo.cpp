#include "Include.h"
ImageInfo imageInfo;

ImageInfo::ImageInfo(){ // 이미지 생성자
	sprintf_s(FileName, ""); // 초기화
}
ImageInfo::~ImageInfo() { // 이미지 생성자

}

void ImageInfo::Init() { // 이미지 초기화	
	centerWith = SCREEN_WITH / 2; // 가로 센터 좌표
						 /*////////////////////////////////////////메뉴 이미지///////////////////////////////////////////////////*/
	// 메뉴 배경(상점, 장비, 홈, 퀘스트, 설정)
	menuImg[0].Create("./resource/Img/menu/BG/mainShop.png", false, D3DCOLOR_XRGB(0, 0, 0));
	menuImg[1].Create("./resource/Img/menu/BG/mainItem.png", false, D3DCOLOR_XRGB(0, 0, 0));
	menuImg[2].Create("./resource/Img/menu/BG/mainHome.jpg", false, D3DCOLOR_XRGB(0, 0, 0));
	menuImg[3].Create("./resource/Img/menu/BG/mainQuest.jpg", false, D3DCOLOR_XRGB(0, 0, 0));
	menuImg[4].Create("./resource/Img/menu/BG/mainSet.jpg", false, D3DCOLOR_XRGB(0, 0, 0));

	// 장비 타입 배경
	for (int i = 0; i < 4; i++)
	{
		sprintf_s(FileName, "./resource/Img/menu/itemBG/mainItem%01d.png", i);
		itemTypeImg[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	// 버튼 이미지(상점, 장비, 홈, 퀘스트, 설정)
	for (int i = 0; i < 5; i++)
	{
		sprintf_s(FileName, "./resource/Img/menu/btn/menu_btn%d.png", i);
		bt_menu[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	
	// 버튼 이미지(시작, 종료, 로그아웃)
	bt_start.Create("./resource/Img/menu/btn/menu_btnStart.png", false, D3DCOLOR_XRGB(0, 0, 0));
	bt_exit.Create("./resource/Img/menu/btn/menu_btnExit.png", false, D3DCOLOR_XRGB(0, 0, 0));
	bt_logout.Create("./resource/Img/menu/btn/menu_btnLogout.png", false, D3DCOLOR_XRGB(0, 0, 0));
	
	// 버튼 효과
	bt_menuBorder.Create("./resource/Img/menu/effect/menu_btnBolder.png", false, D3DCOLOR_XRGB(0, 0, 0));
	bt_shopBorder.Create("./resource/Img/menu/effect/shop_btnBorder.png", false, D3DCOLOR_XRGB(0, 0, 0));
	bt_shopSelect.Create("./resource/Img/menu/effect/shop_btnSelect.png", false, D3DCOLOR_XRGB(0, 0, 0));
	bt_itemSelect.Create("./resource/Img/menu/effect/item_btnSelect.png", false, D3DCOLOR_XRGB(0, 0, 0));
	bt_itemTypeSelect.Create("./resource/Img/menu/effect/itemType_btnSelect.png", false, D3DCOLOR_XRGB(0, 0, 0));

	itemInfo.Init();

	/*////////////////////////////////////////플레이어 이미지///////////////////////////////////////////////////*/
	
	// 플레이어 이미지
	PlayerImgR.Create("./resource/Img/Player/userR.png", false, D3DCOLOR_XRGB(0, 0, 0)); // 이미지 우측 보게끔 출력
	AttackImgR.Create("./resource/Img/Player/AttackR.png", false, D3DCOLOR_XRGB(0, 0, 0)); // 공격 모션 우측으로 설정
	SkillImgR.Create("./resource/Img/Player/SkillR.png", false, D3DCOLOR_XRGB(0, 0, 0)); // 공격 모션 우측으로 설정
	PlayerImgL.Create("./resource/Img/Player/userL.png", false, D3DCOLOR_XRGB(0, 0, 0)); // 이미지 좌측 보게끔 출력
	AttackImgL.Create("./resource/Img/Player/AttackL.png", false, D3DCOLOR_XRGB(0, 0, 0)); // 공격 모션 좌측으로 설정
	SkillImgL.Create("./resource/Img/Player/SkillL.png", false, D3DCOLOR_XRGB(0, 0, 0)); // 공격 모션 좌측으로 설정

	for (int i = 0; i < 26; i++)
	{
		sprintf_s(FileName, "./resource/Img/Monster/boom/%02d.png", i);
		AtkEffectimg1[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}

	/*////////////////////////////////////////몬스터 이미지///////////////////////////////////////////////////*/
	GenjiImgR.Create("./resource/Img/Monster/boss/GenjiR.png", false, D3DCOLOR_XRGB(0, 0, 0));
	GenjiAtkImgR.Create("./resource/Img/Monster/boss/GenjiAtkR.png", false, D3DCOLOR_XRGB(0, 255, 0));
	GenjiImgL.Create("./resource/Img/Monster/boss/GenjiL.png", false, D3DCOLOR_XRGB(0, 0, 0));
	GenjiAtkImgL.Create("./resource/Img/Monster/boss/GenjiAtkL.png", false, D3DCOLOR_XRGB(0, 255, 0));

	/*////////////////////////////////////////도움말 이미지///////////////////////////////////////////////////*/
	HelpLogo.Create("./resource/Img/Help/HelpLogo.png", false, D3DCOLOR_XRGB(0, 255, 0)); // 로그인 도움말
	HelpMenu.Create("./resource/Img/Help/HelpMenu.png", false, D3DCOLOR_XRGB(0, 255, 0)); // 메뉴 도움말
	HelpShop.Create("./resource/Img/Help/HelpShop.png", false, D3DCOLOR_XRGB(0, 255, 0)); // 상점 도움말
	HelpItem.Create("./resource/Img/Help/HelpItem.png", false, D3DCOLOR_XRGB(0, 255, 0)); // 아이템 도움말
	HelpGame.Create("./resource/Img/Help/HelpGame.png", false, D3DCOLOR_XRGB(0, 255, 0)); // 게임 도움말

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