#ifndef __Game_H__
#define __Game_H__

class Game : public Chap
{
public:
	Game();

	~Game();
	DWORD GameTime; // 게임 시간
	DWORD PauseTime; // 일시정지 시간
	int MonsterMax = 5; // 몬스터 총 개수
	char statValue[20];

	virtual void Init(); // 초기화
	virtual void Update(double frame); // 업데이트
	virtual void Draw(); // 이미지 출력

	virtual void OnMessage(MSG* msg); // 메시지 함수
};

#endif