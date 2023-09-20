#ifndef __Menu_H__
#define __Menu_H__

class Menu : public Chap
{

public:
	Menu();
	~Menu();

	virtual void Init();
	virtual void Update(double frame);
	virtual void Draw();
	virtual void OnMessage(MSG* msg)
	{
	}
};
#endif