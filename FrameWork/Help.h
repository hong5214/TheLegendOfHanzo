#pragma once
#include "Include.h"
class Help
{

public:
	Help() {}
	~Help() {}
	char StatInfo[200]; // 표시할 목록
	char StatInfoData[200]; // 표시할 목록
	char statValue[20];
};

extern Help helpInfo;