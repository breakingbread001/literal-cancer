/**
* Overlord Project
* Copyright (C) 2016-2017 RangeMachine
*/

#pragma once

#include "stdfx.h"
#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

class UserInterface
{
public:
	void SetStyle();
	void Render();

	static UserInterface* GetInstance();

private:
	void TextColor(bool active);
	UserInterface();
	~UserInterface();
	HANDLE hThread;

	static UserInterface* m_pInstance;
	
};