#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <d3d11.h>
#include <thread>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_glfw.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_internal.h"
#include "ImGui/imgui_helper.hpp"
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#include "Memory.h"
#include "XXOR.h"
#include <winsock.h>
#include <ShlObj.h>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;
#pragma comment(lib, "leechcore.lib")
#pragma comment(lib, "vmm.lib")  
#pragma comment(lib, "winmm.lib")


#include <mutex>
inline std::mutex mtx;
extern ImFont* font_text1;
extern ImFont* font_text2;
extern ImFont* font_text3;
inline GLFWwindow* window1;
inline GLFWwindow* window2;
