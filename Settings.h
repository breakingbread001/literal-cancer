/**
* Overlord Project
* Copyright (C) 2016-2017 RangeMachine
*/

#pragma once

#include "stdfx.h"

class Settings
{
public:
	bool bAimEnable;
	static int objectCount;

	//bool bSpinBotX;

	bool bESPEnabled;

	bool bESPBox = 1;
	bool bESPHealth = 1; 
	bool bGhettoBoneEsp;
	bool bESPHealthText = 1;
	bool bEyeCancer;
	bool bESPName = 1;
	bool bESPDistance = 1; 
	bool bESPHead = 1;
	bool bESPEnemyOnly;
	bool bESPSnapline = 1;
	bool bESPHasArmor;
	bool bESPSpottedEsp;

	bool bITEMCar = 1;
	bool bITEMCrates = 1;
	bool bITEMLootbag = 1;
	bool bITEMOther;
	bool bITEMWeapon;

	bool bVisualsCrosshair = 1;
	//float bAimTest;
	bool bVisualsCircle = 1;
	bool bVisualsFPS = 1;
	bool bVisualsDebugInfo = 1;
	bool bVisualsAimFov = 1;
	//bool bAimCustomKey;
	//bool bVisualsPred;
	//int bAimKey;


	bool bMisc;
	float fMiscSpeed;
	float fMiscSmooth;
	bool bMiscWhiteList;

	bool bAccuracyNoSpread;
	float fSpread;
	bool bAccuracyNoRecoil;
	float fRecoil;

	bool bAccuracyAimbot;
	bool bAccuracyAimShowFOV;
	float fAimFov;
	float bAimCircle;
	bool bAccuracyTrigger;
	bool bGuiText;

	bool Menu;
	bool Menu2;

	static Settings* GetInstance();

private:
	Settings();
	~Settings();

	static Settings* m_pInstance;
};