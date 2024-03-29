#pragma once
//#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "detours.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3dx9math.h>
#include <iostream>
#include <array>

#include "ImGui\imgui.h"
#include "ImGui\imgui_internal.h"
#include "ImGui\imgui_impl_dx11.h"
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>
#include "Start.h"
#include "Helpers.h"
#include "Hooks.h"
#include "Renderer.h"
#include "UserInterface.h"
#include "Input.h"
#include "XorStr.h"
#include <WinUser.h>
#include "Vector3.h"
#include "Entity.h"
#include "Memory.h"