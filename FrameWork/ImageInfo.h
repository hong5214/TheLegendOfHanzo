#include "Include.h"
class ImageInfo
{
public:
	ImageInfo();
	~ImageInfo();
	int centerWith; // ���� ���� ��ǥ
	char FileName[256]; // �̹��� �ҷ����µ� ����� ���ڿ�

	/* �޴� �̹��� */
	// �޴��� ����� ���
	Sprite menuImg[5]; // �޴� ���(����, ���, Ȩ, ����Ʈ, ����)
	Sprite itemTypeImg[4]; // ��� Ÿ�� ���
	// ���� ��ư
	Sprite bt_menu[5]; // ��ư �̹���(����, ���, Ȩ, ����Ʈ, ����)
	Sprite bt_start;
	Sprite bt_exit;
	Sprite bt_logout;
	// ��ư ȿ��
	Sprite bt_menuBorder;
	Sprite bt_shopBorder;
	Sprite bt_shopSelect;
	Sprite bt_itemSelect;
	Sprite bt_itemTypeSelect;

	/* ĳ���� �̹��� */
	Sprite PlayerImgR; // ĳ���� �̹��� ����
	Sprite PlayerImgL; // ĳ���� �̹��� ����
	Sprite AttackImgR; // ���� ���� �̹���
	Sprite AttackImgL; // ���� ���� �̹���
	Sprite SkillImgR; // ��ų ���� �̹���
	Sprite SkillImgL; // ��ų ���� �̹���
	Sprite AtkEffectimg1[26]; // �÷��̾� �⺻ ���� ����Ʈ
	
	/* ���� �̹��� */
	Sprite GenjiImgR; // ���� �̹��� ����
	Sprite GenjiImgL; // ���� �̹��� ����
	Sprite GenjiAtkImgR; // ���� ���� ���� �̹���
	Sprite GenjiAtkImgL; // ���� ���� ���� �̹���

	/* ���� �̹��� */
	Sprite HelpLogo; // �α��� ����
	Sprite HelpMenu; // �޴� ����
	Sprite HelpShop; // ���� ����
	Sprite HelpItem; // ������ ����
	Sprite HelpGame; // ���� ����

	/* UI �̹��� */
	Sprite SkillUseImg; // ��ų�������� ǥ��
	Sprite SkillEffectImg; // ��ųȿ��

	Sprite HpFullImg; // �ִ� ü�� ��
	Sprite HpZeroImg; // �� ü�� ��
	Sprite LevelUpImg; // �������� �ɷ¼����̹���
	Sprite SelectImg[SELECT_MAX];
	Sprite SelectBox;
	Sprite RandomImg[3]; // �������� �ɷ� 3�� ������Ʈ
	// SelectImg ����
	/*
	0 = �������� ���ݾ� �ɷ��̹���
	1 = �������� ���� �ɷ��̹���
	2 = �������� ü�¾� �ɷ��̹���
	3 = �������� ���߾� �ɷ��̹���
	4 = �������� ���Ӿ� �ɷ��̹���
	5 = �������� �̼Ӿ� �ɷ��̹���
	*/

	void Init(); // �ʱ�ȭ �Լ�
};

extern ImageInfo imageInfo;