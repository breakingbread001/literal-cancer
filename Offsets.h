#pragma once

#define M_PI 3.1415926535897931

#define ADDRESS_CGAME 0x14476D290
#define ADDRESS_CGRAPHICS 0x14476E748
#define ADDRESS_PHYSICS 0x145FEDC50

#define AimKey VK_RMB

#define OFFSET_LocalPlayer 0x780 // 

#define OFFSET_EntityCount 0x50 

#define OFFSET_YAW 0x530 // 
#define OFFSET_PITCH 0x534 // 
#define OFFSET_STANCE 0x954 // 
#define OFFSET_PLAYER_BASE 0x300 //
#define OFFSET_NEXTPLAYER 0x720 //
#define OFFSET_NEXTOBJECT 0x748 //

#define OFFSET_NOCLIP 0x3A58
// ^Write 0 to walk through walls etc.

#define OFFSET_PLAYERWEAPON 0xCA8
#define OFFSET_WEAPON_BULLET_POSITION 0x210
 // ^Add OFFSET_WEAPON to localplayer then add OFFSET_WEAPON_BULLET_POSITION, then write position to enemy's head = magic bullet

#define OFFSET_INVENTORY 0xD10
#define OFFSET_WEAPON_BASE 0x230
#define OFFSET_WEAPON_NAME 0x24
#define OFFSET_CAMERA 0x48 //
#define OFFSET_MATRIX 0x30 // 
#define OFFSET_MATRIX_DEF 0x1B0 //
 
#define OFFSET_HEALTHBASE 0x3DC8 //
#define OFFSET_HEALTH 0xB0 // 
#define OFFSET_VBASEPOS 0x3A8 //
#define OFFSET_VPELVISPOS 0x3F0 // 
#define OFFSET_ITEMPOS 0x18C0 //
#define OFFSET_CARPOS 0x9D0 //
#define OFFSET_TYPE 0x3F8 //
#define OFFSET_NAME 0x7C0 //
#define OFFSET_VELOCITY 0x430 //
#define OFFSET_ID 0x688 //


#define OFFSET_SkeletonActors 0x5C0 //
#define OFFSET_SkeletonStarts  0x250 //
#define OFFSET_SkeletonInfos  0x50 //
#define OFFSET_BoneInfo  0x28 //
#define OFFSET_HEAD 0x1A0

#define OFFSET_SPEED 0x45D0
#define OFFSET_SPEEDVERTICAL 0x45D0

// #define OFFSET_WEAPON_CONTEXT 0xBA0 

//#define TYPE_Loot 0x2E //
//#define TYPE_Player 0x10E //
//#define TYPE_Weapon 0x34 //
//#define TYPE_Ammo 0x15 //
//#define TYPE_Grenade 0xAE //
//#define TYPE_NonLethal 0xB2 //
//#define TYPE_OffRoader 0x11 //
//#define TYPE_CAR_2 0x72 //
//#define TYPE_CAR_3 0x76 //
//#define TYPE_ATV 0xCC //
//#define TYPE_ITEM 0x2C //
//#define TYPE_ITEM_2  
// thanks majorupdates ^^

#define TYPE_Loot 0x2E
#define TYPE_Player 0x10E
#define TYPE_Weapon 0x34
#define TYPE_Ammo 0x15
#define TYPE_Grenade 0xAE
#define TYPE_NonLethal 0xB2
#define TYPE_OffRoader 0x11
#define TYPE_CAR_2 0x72
#define TYPE_CAR_3 0x76
#define TYPE_ATV 0xCC
#define TYPE_PARACHUTE 0x78
#define TYPE_ITEM 0x2C
#define TYPE_FUEL 0xB5
#define TYPE_FLARE 0x2D
#define TYPE_THROWN_FRAG 0xB9
#define TYPE_THROWN_FLASHBANG 0x9C
#define TYPE_THROWN_MOLOTOV 0xB7
#define TYPE_THROWN_SMOKE 0xB8
#define TYPE_THROWN_GAS_GRENADE 0xB6
#define TYPE_MOLOTOV_FIRE 0xAC
#define TYPE_WOODEN_ARROW 0x11E
#define TYPE_CAMPER_DOOR 0x79
#define TYPE_BUILDING_DOOR 0x19
#define TYPE_WOODEN_DOOR 0xE2
#define TYPE_RESIDENTIAL_DOOR 0x7B
#define TYPE_WAREHOUSE_DOOR 0x7C
#define TYPE_GLASS_DOOR 0x109
#define TYPE_LAMBORGHINI 0x1C3
#define TYPE_SHOTTY_SNIPER_CRATE 0x16B
#define TYPE_MILITARY_CRATE_1 0x17A
#define TYPE_MILITARY_CRATE_2 0x178
#define TYPE_MILITARY_CRATE_3 0x173
