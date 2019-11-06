#include "Visual.h"
#include "Memory.h"

#include "MakeJMP.h"
Visuals* Visuals::m_pInstance;

#define BONES_PER_SECTION 5
#define SKELETON_SECTIONS 6
enum Stance {
	Standing = 0,
	Crouched = 1,
	Walking = 2,
	Running = 3,
	Jumping = 4,
	Crouching = 5,
	Prone = 6,
	Crawling = 7
};

enum Bones
{
	CharacterWorldSpaceTM = 0,
	Male = 1,
	worldRoot = 2,
	trajectory = 3,
	COG = 4,
	L_hip = 5,
	L_knee = 6,
	L_ankle = 7,
	L_ball = 8,
	L_toe = 9,
	L_kneeArmor = 10,
	L_shinHolster = 11,
	L_hipHolster = 12,
	spineLower = 13,
	spineMiddle = 14,
	spineUpper = 15,
	neck = 16,
	head = 17,
	jaw = 18,
	tongue = 19,
	L_lip_lower = 20,
	L_lip_corner = 21,
	R_lip_corner = 22,
	R_lip_lower = 23,
	L_lip_upper = 24,
	L_cheek = 25,
	L_brow = 26,
	L_eye = 27,
	L_eyelid_lower = 28,
	L_eyelid_upper = 29,
	R_eyelid_upper = 30,
	R_eyelid_lower = 31,
	R_eye = 32,
	R_brow = 33,
	R_cheek = 34,
	R_lip_upper = 35,
	hat = 36,
	glasses = 37,
	headset = 38,
	ponytailA_1 = 39,
	ponytailA_2 = 40,
	ponytailB_1 = 41,
	ponytailB_2 = 42,
	L_clavicle = 43,
	L_shoulder = 44,
	L_shoulderRoll = 45,
	L_elbow = 46,
	L_forearm = 47,
	L_wristAttachment = 48,
	L_wrist = 49,
	L_thumbA = 50,
	L_thumbB = 51,
	L_thumbC = 52,
	L_indexA = 53,
	L_indexB = 54,
	L_indexC = 55,
	L_middleA = 56,
	L_middleB = 57,
	L_middleC = 58,
	L_ringA = 59,
	L_ringB = 60,
	L_ringC = 61,
	L_pinkyA = 62,
	L_pinkyB = 63,
	L_pinkyC = 64,
	L_weapon = 65,
	L_shoulderArmor = 66,
	R_clavicle = 67,
	R_shoulder = 68,
	R_shoulderRoll = 69,
	R_elbow = 70,
	R_forearm = 71,
	R_wristAttachment = 72,
	R_wrist = 73,
	R_thumbA = 74,
	R_thumbB = 75,
	R_thumbC = 76,
	R_indexA = 77,
	R_indexB = 78,
	R_indexC = 79,
	R_middleA = 80,
	R_middleB = 81,
	R_middleC = 82,
	R_ringA = 83,
	R_ringB = 84,
	R_ringC = 85,
	R_pinkyA = 86,
	R_pinkyB = 87,
	R_pinkyC = 88,
	R_weapon = 89,
	R_shoulderArmor = 90,
	R_longWeapon_2 = 91,
	R_longWeapon_1 = 92,
	R_longWeapon_3 = 93,
	backpackUpper = 94,
	bedroll_top = 95,
	backpackLower = 96,
	bedroll_bottom = 97,
	chestPack_Armor = 98,
	L_breast = 99,
	R_breast = 100,
	stomachFat = 101,
	R_hip = 102,
	R_knee = 103,
	R_ankle = 104,
	R_ball = 105,
	R_toe = 106,
	R_kneeArmor = 107,
	R_shinHolster = 108,
	R_hipHolster = 109,
	R_shortWeapon_1 = 110,
	R_shortWeapon_2 = 111,
	R_shortWeapon_3 = 112,
	L_shortWeapon_1 = 113,
	L_shortWeapon_2 = 114,
	L_shortWeapon_3 = 115,
	L_longCoat_main = 116,
	L_longCoat_midRear = 117,
	L_longCoat_bottomRear = 118,
};
int piSkeletonBones[BONES_PER_SECTION] = { Bones::hat, Bones::head, Bones::neck, -1, -1 };
int piSkeletonSpine[BONES_PER_SECTION] = { Bones::neck, Bones::spineUpper, Bones::spineMiddle, Bones::spineLower, -1 };
int piSkeletonRightArm[BONES_PER_SECTION] = { Bones::neck, Bones::R_shoulder, Bones::R_elbow, Bones::R_wrist, -1 };
int piSkeletonLeftArm[BONES_PER_SECTION] = { Bones::neck, Bones::L_shoulder, Bones::L_elbow, Bones::L_wrist, -1 };
int piSkeletonLowerRight[BONES_PER_SECTION] = { Bones::spineLower, Bones::R_hip, Bones::R_knee, Bones::R_ankle, Bones::R_toe };
int piSkeletonLowerLeft[BONES_PER_SECTION] = { Bones::spineLower, Bones::L_hip, Bones::L_knee, Bones::L_ankle, Bones::L_toe };

int* ppiSkeletonBones[SKELETON_SECTIONS] = { piSkeletonBones, piSkeletonLeftArm, piSkeletonRightArm, piSkeletonSpine, piSkeletonLowerRight, piSkeletonLowerLeft };
Visuals::Visuals()
{
}

Visuals::~Visuals()
{
}

void Visuals::VisualsMain()
{
	Visuals::DrawPlayers();
	Visuals::DrawVisuals();
	Visuals::Misc();
	Visuals::DrawObjects();
}
Engine::Vector3 RotatePoint(Engine::Vector3 origin, float angle)
{
	float rad = angle;
	float s = -sin(rad);
	float c = cos(rad);

	float xnew = origin.x * c - origin.z * s;
	float znew = origin.x * s + origin.z * c;

	return Engine::Vector3(xnew, origin.y, znew);
}
void Visuals::DrawObjects()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	//Helpers::Log(XorStr("DrawESP"));

	auto pCGame = Engine::CGame::GetInstance();
	//Helpers::Log(XorStr("CGaME"));
	auto pCGraphics = Engine::CGraphics::GetInstance();

	std::vector<Engine::Entity*> list = pCGame->GetObjects();

	//Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, "project odium v2.0", ImVec2(1855, 5), 15.f, 0xff3ad8cd, true);
	/*
	if (Settings::GetInstance()->bGuiText)
	{
		if (Hooks::PressedKeys[VK_F6]) {
			if (Settings::GetInstance()->bESPEnabled == true) {
				// disable
				Settings::GetInstance()->bESPEnabled = false;
			}
			else if (Settings::GetInstance()->bESPEnabled == false) {
				// enable
				Settings::GetInstance()->bESPEnabled = true;

			}
			Sleep(600);


		}
		if (Hooks::PressedKeys[VK_F7]) {
			if (Settings::GetInstance()->bVisualsAimFov == true) {
				// disable
				Settings::GetInstance()->bVisualsAimFov = false;
			}
			else if (Settings::GetInstance()->bVisualsAimFov == false) {
				// enable
				Settings::GetInstance()->bVisualsAimFov = true;

			}
			Sleep(600);


		}


		if (Settings::GetInstance()->bESPEnabled)
		{
			Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, "[F6] esp   ", ImVec2(1820, 55), 15.f, 0xff9ee889, false);
		}
		else {
			Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, "[F6] esp   ", ImVec2(1820, 55), 15.f, 0xffea9593, false);

		}
		if (Settings::GetInstance()->bVisualsAimFov)
		{
			Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, "[F7] aimbot", ImVec2(1820, 75), 15.f, 0xff9ee889, false);
		}
		else {
			Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, "[F7] aimbot", ImVec2(1820, 75), 15.f, 0xffea9593, false);

		}

	}
	*/




	int fuckingGod;
	for (int i = 0; i < list.size() && list.at(i) != nullptr && list.at(i) && Engine::Memory::IsValidPtr<Engine::Entity>(list.at(i)); i++)
	{
		DWORD type = list.at(i)->GetType();
		// LOOTBAG - 46
	   // Millie - 44
	   // Helmet - 44
		if (Settings::GetInstance()->bITEMWeapon && (type == TYPE_Weapon) && list.at(i)->GetItemPos().Distance(pCGame->GetLocalPlayer()->GetPosition()) < 50.f)
		{
			Engine::Vector3 loc = list.at(i)->GetItemPos();
			Engine::Vector3 Position = pCGraphics->W2S(loc);
			float distance = list.at(i)->GetItemPos().Distance(pCGame->GetLocalPlayer()->GetPosition());
			Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Helpers::VariableText(XorStr("%s: %.1fm"), list.at(i)->GetName(), distance), ImVec2(Position.x, Position.y), 16.f, 0xff81d557, true);
		}
		if (Settings::GetInstance()->bITEMOther && (type == TYPE_Ammo || type == TYPE_Grenade) && list.at(i)->GetItemPos().Distance(pCGame->GetLocalPlayer()->GetPosition()) < 50.f)
		{
			Engine::Vector3 loc = list.at(i)->GetItemPos();
			Engine::Vector3 Position = pCGraphics->W2S(loc);
			float distance = list.at(i)->GetItemPos().Distance(pCGame->GetLocalPlayer()->GetPosition());
			Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Helpers::VariableText(XorStr("%s: %.1fm"), list.at(i)->GetName(), distance), ImVec2(Position.x, Position.y), 16.f, 0xff81d557, true);
		}
		if (Settings::GetInstance()->bITEMOther && (type == TYPE_ITEM) && list.at(i)->GetItemPos().Distance(pCGame->GetLocalPlayer()->GetPosition()) < 50.f)
		{
			Engine::Vector3 loc = list.at(i)->GetItemPos();
			Engine::Vector3 Position = pCGraphics->W2S(loc);
			float distance = list.at(i)->GetItemPos().Distance(pCGame->GetLocalPlayer()->GetPosition());
			Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Helpers::VariableText(XorStr("%s: %.1fm"), list.at(i)->GetName(), distance), ImVec2(Position.x, Position.y), 16.f, 0xffff672d, true);
		}
		if (Settings::GetInstance()->bITEMCar && (type == TYPE_OffRoader || type == TYPE_CAR_2 || type == TYPE_CAR_3 || type == TYPE_ATV || type == TYPE_LAMBORGHINI) && list.at(i)->GetCarPos().Distance(pCGame->GetLocalPlayer()->GetPosition()) < 700.f)
		{
			Engine::Vector3 loc = list.at(i)->GetCarPos();
			Engine::Vector3 Position = pCGraphics->W2S(loc);
			float distance = list.at(i)->GetCarPos().Distance(pCGame->GetLocalPlayer()->GetPosition());
			if (distance > 6) {
				Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Helpers::VariableText(XorStr("%s: %.1fm"), list.at(i)->GetName(), distance), ImVec2(Position.x, Position.y), 16.f, 0xFFFFFFFF, true);
			}

		}
		if (Settings::GetInstance()->bITEMLootbag && (type == 46) && list.at(i)->GetCarPos().Distance(pCGame->GetLocalPlayer()->GetPosition()) < 50.f)
		{
			Engine::Vector3 loc = list.at(i)->GetItemPos();
			Engine::Vector3 Position = pCGraphics->W2S(loc);
			float distance = list.at(i)->GetCarPos().Distance(pCGame->GetLocalPlayer()->GetPosition());
			Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, "Lootbag", ImVec2(Position.x, Position.y), 16.f, 0xFFFFFFFF, true);
		}
		if (Settings::GetInstance()->bITEMOther && list.at(i)->GetItemPos().Distance(pCGame->GetLocalPlayer()->GetPosition()) < 50.f)
		{
			Engine::Vector3 loc = list.at(i)->GetItemPos();
			Engine::Vector3 Position = pCGraphics->W2S(loc);
			float distance = list.at(i)->GetItemPos().Distance(pCGame->GetLocalPlayer()->GetPosition());
			Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Helpers::VariableText(XorStr("%s: %.1fm"), list.at(i)->GetName(), distance), ImVec2(Position.x, Position.y), 16.f, 0xffff672d, true);
		}
	}
}


void Visuals::AIM(float x, float y)
{

}
void Visuals::Misc()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	auto pCGame = Engine::CGame::GetInstance();
	auto pCGraphics = Engine::CGraphics::GetInstance();

	//if (Hooks::PressedKeys[VK_OEM_4]) // speed
	//{
		//MakeNOP((BYTE*)0x14375DBF0, 0x8);
	//}
	//else
//	{
	//	BYTE RestoreSpeed[8] = { 0xF3, 0x0F, 0x11, 0x86, 0xD8, 0x45, 0x00, 0x00 }; // movss [rsi+000045D8],xmm0
//
	//	MakeRestore((BYTE*)0x14160D514, 0x8, RestoreSpeed);
	//}
//
	//if (Settings::GetInstance()->bVisualsCrosshair) // when shift
	//{
		//if(Hooks::PressedKeys[VK_LSHIFT])
			//pCGame->GetLocalPlayer()->Speed() = 0;
	//}
}

float GetDistance(float Xx, float Yy, float xX, float yY)
{
	return sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
}

void MouseMove(float x, float y)
{
	INPUT Input = { 0 };
	Input.type = INPUT_MOUSE;
	Input.mi.dx = (LONG)x;
	Input.mi.dy = (LONG)y;
	Input.mi.dwFlags = MOUSEEVENTF_MOVE;
	SendInput(1, &Input, sizeof(INPUT));
}
//0 - stand
//2 - walk
//3 - run
//1 - crouch
//5 - crouch move
//6 - prone
//7 - prone move
//4 - jump
void Visuals::DrawPlayers()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindow* window = ImGui::GetCurrentWindow();

	//Helpers::Log(XorStr("DrawESP"));

	auto pCGame = Engine::CGame::GetInstance();
	auto pCGraphics = Engine::CGraphics::GetInstance();

	Engine::Entity* pLocal = pCGame->GetLocalPlayer();


	std::vector<Engine::Entity*> list = pCGame->GetPlayers();


	float BestDist = 100;
	int BestTarget = -1;
	int drawCircleMeme = 1;

	Engine::Vector3 AimPos = Engine::Vector3();

	for (int i = 0; i < list.size() && list.at(i) != nullptr && list.at(i) && Engine::Memory::IsValidPtr<Engine::Entity>(list.at(i)); i++)
	{
		//Helpers::LogInt(XorStr("Visual Loop"), i);
		Engine::Entity* pEntity = list.at(i);

		if (pEntity == nullptr || pEntity == pCGame->GetLocalPlayer())
			continue;

		if (WhiteList.end() != std::find(WhiteList.begin(), WhiteList.end(), pEntity->GetName())) // if whitelisted.
			continue;

		DWORD Health = pEntity->GetHealth(); // break

		Health /= 100;

		if (Health > 0)
		{
			Engine::Vector3 Position = pCGraphics->W2S(pEntity->GetPosition());


			if (Position.x < 1 || Position.x > io.DisplaySize.x || Position.y < 1 || Position.y > io.DisplaySize.y)
				continue;


			Engine::Vector3 HeadPosition = pCGraphics->W2S((pEntity->GetHead() + pEntity->GetPosition())); // HEAD CHANGE

			if (Settings::GetInstance()->bESPEnabled)
			{
				// Draw our Box
				if (Settings::GetInstance()->bESPBox)
				{
					Engine::Entity* pEnt = list.at(i);

					Engine::Vector3 niggerpos = pEnt->GetPosition();

					Engine::Vector3 HeadPos = pEnt->GetHead(); // HEAD CHANGE
					HeadPos = RotatePoint(HeadPos, pEnt->GetYaw());

					Engine::Vector3 pos1 = pCGraphics->W2S(HeadPos);

					Engine::Vector3 topnigger = pCGraphics->W2S(niggerpos + HeadPos);
					float height = Position.y - topnigger.y;
					Renderer::GetInstance()->DrawBox(ImVec2(Position.x, Position.y), ImVec2(topnigger.x, topnigger.y), 0xfff4584d);
				}

				// Draw our Head
				if (Settings::GetInstance()->bESPHead)
				{
					Engine::Entity* pEnt = list.at(i);

					Engine::Vector3 niggerpos = pEnt->GetPosition();

					Engine::Vector3 HeadPos = pEnt->GetHead(); // HEAD CHANGE
					HeadPos = RotatePoint(HeadPos, pEnt->GetYaw());

					Engine::Vector3 pos1 = pCGraphics->W2S(HeadPos);

					Engine::Vector3 topnigger = pCGraphics->W2S(niggerpos + HeadPos);
					float height = Position.y - topnigger.y;

					//Renderer::GetInstance()->DrawCircleScale(ImVec2(HeadPosition.x, HeadPosition.y), 5.f, 0xffbf94e4, ImVec2(Position.x, Position.y), ImVec2(HeadPosition.x, HeadPosition.y));
					Renderer::GetInstance()->DrawCircle(ImVec2(topnigger.x, topnigger.y), height / 8, 0xffffff00, 1);
				}

				float distance = pCGame->GetLocalPlayer()->GetPosition().Distance(pEntity->GetPosition());
				// Draw our Distance
				if (Settings::GetInstance()->bESPDistance)
				{
					Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Helpers::VariableText(XorStr("[%.1fm]"), distance), ImVec2(Position.x, Position.y + 5), 12.f, 0xffa5c9e8, true);
					if (distance > 150) {
						Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Helpers::VariableText(XorStr("*far away*"), distance), ImVec2(Position.x, Position.y + 17), 12.f, 0xffcf1cc5, true);
					}
					
				}
				// HANDS = 96, 112
				// chest = 136
				if (Settings::GetInstance()->bGhettoBoneEsp) {
					Engine::Entity* pEnt = list.at(i);
					Engine::Vector3 uPos = pEnt->GetPosition();
					auto bones = pEnt->GetBones();
					for (int i = 0; i < bones.size(); i++) {
						Engine::Vector3 fixed = pCGraphics->W2S(uPos + bones[i]);
						Engine::Vector3 hand1 = pCGraphics->W2S(uPos + bones[112]);
						Engine::Vector3 hand2 = pCGraphics->W2S(uPos + bones[96]);
						Engine::Vector3 chest = pCGraphics->W2S(uPos + bones[136]);
						Engine::Vector3 HeadPos = pEnt->GetHead(); // HEAD CHANGE
						HeadPos = RotatePoint(HeadPos, pEnt->GetYaw());

						Engine::Vector3 pos1 = pCGraphics->W2S(HeadPos);

						Engine::Vector3 topnigger = pCGraphics->W2S(uPos + HeadPos);

						Renderer::GetInstance()->DrawLine(ImVec2(hand1.x, hand1.y), ImVec2(topnigger.x, topnigger.y), 0xffcf1cc5, 3.f);
						Renderer::GetInstance()->DrawLine(ImVec2(hand2.x, hand2.y), ImVec2(topnigger.x, topnigger.y), 0xffcf1cc5, 3.f);
						Renderer::GetInstance()->DrawLine(ImVec2(chest.x, chest.y), ImVec2(topnigger.x, topnigger.y), 0xffcf1cc5, 3.f);
						if (Settings::GetInstance()->bEyeCancer) {
							Renderer::GetInstance()->DrawsText(Renderer::GetInstance()->m_pDefault, std::to_string(i).c_str(), ImVec2(fixed.x, fixed.y), 14.f, 0xffcf1cc5, true);
						}

					}
				}



				// Draw our Health
				if (Settings::GetInstance()->bESPHealth)
				{
					Engine::Entity* pLocal = pCGame->GetLocalPlayer();
					Engine::Entity* pEnt = list.at(i);

					Engine::Vector3 localFucker = pLocal->GetPosition(); // HEAD CHANGE

					Engine::Vector3 otherFucker = pEnt->GetPosition(); // HEAD CHANGE
					static float X, Y, Z = 0.0f;
					static float telX, telY, telZ = 0.0f;
					BestTarget = i;

					localFucker = otherFucker;
					BestTarget != -1;
					//MakeNOP((BYTE*)0x14375DBF0, 0x8);

					//for (int i = 0; i < Count && Ent != nullptr && Ent; i++)

					/* 
					LocalPlayer = cGame + offset_LocalPlayer
					EntityEntry = LocalPly + offset_EntityEntry
					vector MyPlayer = <vector>(LocalPlayer + offset_PlayerBase)
					vector EnemyPlayer = <vector>(EntityEntry + offset_PlayerBase)


					EnemyPlayer[0] = MyPlayer[0]
					EnemyPlayer[1] = MyPlayer[1]
					EnemyPlayer[2] = MyPlayer[2]

					vector3 NextEnemyPlayer = <vector3>(EnemyPlayer + EntityEntry) < Loop for mass tp
					*/

					Renderer::GetInstance()->DrawHealth(ImVec2(Position.x, Position.y), ImVec2(HeadPosition.x, HeadPosition.y), Health);
					//Renderer::GetInstance()->DrawOutlinedText(Renderer::sGetInstance()->m_pDefault, Helpers::VariableText(XorStr("[%.1fHP]"), Health), ImVec2(Position.x, Position.y + 10), 12.f, 0xffa5c9e8, true);

				}

				// Draw SnapLines
				if (Settings::GetInstance()->bESPSnapline)
				{
					// DrawBox3d
					Engine::Entity* pEnt = list.at(i);

					Engine::Vector3 niggerpos = pEnt->GetPosition();

					Engine::Vector3 HeadPos = pEnt->GetHead(); // HEAD CHANGE
					HeadPos = RotatePoint(HeadPos, pEnt->GetYaw());

					Engine::Vector3 pos1 = pCGraphics->W2S(HeadPos);

					Engine::Vector3 topnigger = pCGraphics->W2S(niggerpos + HeadPos);
					float height = Position.y - topnigger.y;
					//Renderer::GetInstance()->DrawBox(ImVec2(Position.x, Position.y), ImVec2(topnigger.x, topnigger.y), 0xfff4584d);
					// void Renderer::DrawBox3d(const std::vector<Engine::Vector3>& bones, const Engine::Vector3& base, uint32_t color) // 3d

				}

				// Draw our Name
				if (Settings::GetInstance()->bESPName)
				{
					// Calculations so that our name is at the correct position
					float posoffset = Position.y - HeadPosition.y;
					float posoffset2 = Position.y - posoffset - 15;
					Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, pEntity->GetName(), ImVec2(Position.x, posoffset2), 12.f, 0xFFFFFFFF, true);

				}
			}
			//AIM Semi Pasted, outside ESP if check
			if (Settings::GetInstance()->bVisualsAimFov && WhiteList.end() == std::find(WhiteList.begin(), WhiteList.end(), pEntity->GetName()))
			{
				Engine::Entity* pEnt = list.at(i);
				Engine::Vector3 Velocity = pEnt->GetVelocity();
				float distance = pCGame->GetLocalPlayer()->GetPosition().Distance(pEnt->GetPosition());



				//Aim, with p2000000 iq prediction

				Engine::Vector3 EnginePrediction = pEnt->GetPosition();
				//if (Settings::GetInstance()->bVisualsPred, true) {
					if (distance < 29)
					{
						EnginePrediction.x += 0;
						EnginePrediction.y += 0;
						EnginePrediction.z += 0;
					}
					else if (distance < 39)
					{
						EnginePrediction.x += (Velocity.x) / distance * (distance / 10 * 1.0f);
						EnginePrediction.y += (Velocity.y) / distance * (distance / 10 * 1.0f);
						EnginePrediction.z += (Velocity.z) / distance * (distance / 10 * 1.0f);
					}
					else if (distance < 100)
					{
						EnginePrediction.x += (Velocity.x) / distance * (distance / 10 * 3.5f);
						EnginePrediction.y += (Velocity.y) / distance * (distance / 10 * 3.5f);
						EnginePrediction.z += (Velocity.z) / distance * (distance / 10 * 3.5f);
					}
					else if (distance > 99)
					{
						EnginePrediction.x += (Velocity.x) / distance * (distance / 10 * 15.0f);
						EnginePrediction.y += (Velocity.y) / distance * (distance / 10 * 15.0f);
						EnginePrediction.z += (Velocity.z) / distance * (distance / 10 * 15.0f);
					}
					else if (distance > 149)
					{
						EnginePrediction.x += (Velocity.x) / distance * (distance / 10 * 50.0f);
						EnginePrediction.y += (Velocity.y) / distance * (distance / 10 * 50.0f);
						EnginePrediction.z += (Velocity.z) / distance * (distance / 10 * 50.0f);
					}
					else if (distance > 250)
					{
						EnginePrediction.x += (Velocity.x) / distance * (distance / 10 * 80.0f);
						EnginePrediction.y += (Velocity.y) / distance * (distance / 10 * 80.0f);
						EnginePrediction.z += (Velocity.z) / distance * (distance / 10 * 80.0f);
					}

				//}
				//else {
			//		EnginePrediction.x += 0;
			//		EnginePrediction.y += 0;
			//		EnginePrediction.z += 0;
			//	}
				Engine::Vector3 HeadPos = pEnt->GetHead(); // HEAD CHANGE
				HeadPos = RotatePoint(HeadPos, pEnt->GetYaw());

				HeadPos += EnginePrediction;

				HeadPos = pCGraphics->W2S(HeadPos);

				float FaggotDist = GetDistance(HeadPos.x, HeadPos.y, io.DisplaySize.x / 2, io.DisplaySize.y / 2);

				if (FaggotDist < BestDist)
				{
					AimPos = HeadPos;
					BestDist = FaggotDist;
					BestTarget = i;
				}
			}
		}
	}
	/* #define CVAR_KEY_MOUSE2 "MOUSE2"
					#define CVAR_KEY_MOUSE3 "MOUSE3"
					#define CVAR_KEY_MOUSE4 "MOUSE4"
					#define CVAR_KEY_MOUSE5 "MOUSE5"*/
	//int KEY_CODE = 0;

	/* if (Settings::GetInstance()->bAimKey <= 0)
	{
		KEY_CODE = VK_RBUTTON;
	}
	else if (Settings::GetInstance()->bAimKey == 1)
	{
		KEY_CODE = VK_XBUTTON1;
	}
	else if (Settings::GetInstance()->bAimKey == 2)
	{
		KEY_CODE = VK_XBUTTON2;
	}
	else if (Settings::GetInstance()->bAimKey >= 3)
	{
		KEY_CODE = VK_MBUTTON;
	}

	*/
	//move aimbot
	if (BestTarget != -1 && AimPos.x != 0 && AimPos.y != 0 && Hooks::PressedKeys[VK_RBUTTON])
	{
		if (WhiteList.end() == std::find(WhiteList.begin(), WhiteList.end(), list.at(BestTarget)->GetName()))
		{
			int moveX = AimPos.x - io.DisplaySize.x / 2;
			int moveY = AimPos.y - io.DisplaySize.y / 2;

			MouseMove(moveX, moveY); // because I don't know how to write angles.
		}
	}
	//move whitelist
	if (Settings::GetInstance()->bMiscWhiteList && Hooks::PressedKeys[VK_F4] && BestTarget != -1 && AimPos.x != 0 && AimPos.y != 0)
	{
		if (WhiteList.end() == std::find(WhiteList.begin(), WhiteList.end(), list.at(BestTarget)->GetName()))
			WhiteList.push_back(list.at(BestTarget)->GetName());
	}
	//clean
	if (Hooks::PressedKeys[VK_F5])
		WhiteList.clear();

	// draw name lists
	if (Settings::GetInstance()->bMiscWhiteList)
	{
		//draw out our list
		int y = 60;
		for (int i = 0; i < WhiteList.size(); i++, y += 20)
		{
			Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, WhiteList.at(i), ImVec2(20, y), 16.f, 0xFFFF00FF, false);
		}
	}
}

void Visuals::DrawVisuals()
{
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	//auto pGameManager = Engine::GameManager::GetInstance();
	//auto pStatusManager = Engine::StatusManager::GetInstance();


	// Draw Crosshair
	if (Settings::GetInstance()->bVisualsCrosshair)
	{
		//if (pStatusManager->IsIngame())
		//{
			Renderer::GetInstance()->DrawLine(ImVec2(io.DisplaySize.x / 2 - 15, io.DisplaySize.y / 2), ImVec2(io.DisplaySize.x / 2 - 5, io.DisplaySize.y / 2), 0xFF81E1F7, 1.f);
			Renderer::GetInstance()->DrawLine(ImVec2(io.DisplaySize.x / 2 + 16, io.DisplaySize.y / 2), ImVec2(io.DisplaySize.x / 2 + 6, io.DisplaySize.y / 2), 0xFF81E1F7, 1.f);
			Renderer::GetInstance()->DrawLine(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2 - 15), ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2 - 5), 0xFF81E1F7, 1.f);
			Renderer::GetInstance()->DrawLine(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2 + 16), ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2 + 6), 0xFF81E1F7, 1.f);
			//}
	}
	if (Settings::GetInstance()->bVisualsCircle)
	{
		Renderer::GetInstance()->DrawCircle(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y / 2), Settings::GetInstance()->bAimCircle, 0xffd5364e, 1.f);


	}
	// Draw FPS
	if (Settings::GetInstance()->bVisualsFPS)
	{
		//MakeNOP((BYTE*)0x14375DBF0, 0x8);

		Renderer::GetInstance()->DrawOutlinedText(Renderer::GetInstance()->m_pDefault, Helpers::VariableText("%.1f", io.Framerate), ImVec2(20, 20), 26.f, 0xFF00CE11, false);
	}
}

Visuals* Visuals::GetInstance()
{
	if (!m_pInstance)
		m_pInstance = new Visuals();

	return m_pInstance;
}