#pragma once
#include "Include.h"

class Key
{

public:
	Key(void);
	~Key(void);
	
	DWORD KeyTime;
	DWORD KeyDash;

	void Update();
};

extern Key key;