#ifndef __Game_H__
#define __Game_H__

class Game : public Chap
{
public:
	Game();

	~Game();
	DWORD GameTime; // ���� �ð�
	DWORD PauseTime; // �Ͻ����� �ð�
	int MonsterMax = 5; // ���� �� ����
	char statValue[20];

	virtual void Init(); // �ʱ�ȭ
	virtual void Update(double frame); // ������Ʈ
	virtual void Draw(); // �̹��� ���

	virtual void OnMessage(MSG* msg); // �޽��� �Լ�
};

#endif