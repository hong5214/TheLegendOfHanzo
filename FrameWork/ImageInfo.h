#include "Include.h"
class ImageInfo
{
public:
	ImageInfo();
	~ImageInfo();
	int centerWith; // 가로 센터 좌표
	char FileName[256]; // 이미지 불러오는데 사용할 문자열

	/* 메뉴 이미지 */
	// 메뉴에 사용할 배경
	Sprite menuImg[5]; // 메뉴 배경(상점, 장비, 홈, 퀘스트, 설정)
	Sprite itemTypeImg[4]; // 장비 타입 배경
	// 실행 버튼
	Sprite bt_menu[5]; // 버튼 이미지(상점, 장비, 홈, 퀘스트, 설정)
	Sprite bt_start;
	Sprite bt_exit;
	Sprite bt_logout;
	// 버튼 효과
	Sprite bt_menuBorder;
	Sprite bt_shopBorder;
	Sprite bt_shopSelect;
	Sprite bt_itemSelect;
	Sprite bt_itemTypeSelect;

	/* 캐릭터 이미지 */
	Sprite PlayerImgR; // 캐릭터 이미지 우측
	Sprite PlayerImgL; // 캐릭터 이미지 좌측
	Sprite AttackImgR; // 공격 우측 이미지
	Sprite AttackImgL; // 공격 좌측 이미지
	Sprite SkillImgR; // 스킬 우측 이미지
	Sprite SkillImgL; // 스킬 좌측 이미지
	Sprite AtkEffectimg1[26]; // 플레이어 기본 공격 이펙트
	
	/* 몬스터 이미지 */
	Sprite GenjiImgR; // 겐지 이미지 우측
	Sprite GenjiImgL; // 겐지 이미지 좌측
	Sprite GenjiAtkImgR; // 겐지 공격 우측 이미지
	Sprite GenjiAtkImgL; // 겐지 공격 좌측 이미지

	/* 도움말 이미지 */
	Sprite HelpLogo; // 로그인 도움말
	Sprite HelpMenu; // 메뉴 도움말
	Sprite HelpShop; // 상점 도움말
	Sprite HelpItem; // 아이템 도움말
	Sprite HelpGame; // 게임 도움말

	/* UI 이미지 */
	Sprite SkillUseImg; // 스킬가능유무 표시
	Sprite SkillEffectImg; // 스킬효과

	Sprite HpFullImg; // 최대 체력 바
	Sprite HpZeroImg; // 빈 체력 바
	Sprite LevelUpImg; // 레벨업시 능력선택이미지
	Sprite SelectImg[SELECT_MAX];
	Sprite SelectBox;
	Sprite RandomImg[3]; // 랜덤적인 능력 3개 업데이트
	// SelectImg 정보
	/*
	0 = 레벨업시 공격업 능력이미지
	1 = 레벨업시 방어업 능력이미지
	2 = 레벨업시 체력업 능력이미지
	3 = 레벨업시 명중업 능력이미지
	4 = 레벨업시 공속업 능력이미지
	5 = 레벨업시 이속업 능력이미지
	*/

	void Init(); // 초기화 함수
};

extern ImageInfo imageInfo;