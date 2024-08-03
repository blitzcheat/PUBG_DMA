#include "Entry.h"
#include "Menu/Fonts.hpp"
#include "Menu/Menu.h"
#include "Menu/Fonts_text.h"
#include "Render.h"
#include <dwmapi.h>
#include "Features/Global.h"
#include "util.hpp"


#define HEAD_TO_FONT19(FONTSIZE)  io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyhbd.ttc", FONTSIZE, nullptr, io.Fonts->GetGlyphRangesChineseFull());
#define HEAD_TO_FONT192(FONTSIZE)  io2.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\msyhbd.ttc", FONTSIZE, nullptr, io2.Fonts->GetGlyphRangesChineseFull());

bool open = true;
int 窗口背景模式 = 0;

ImFont* font_text1;
ImFont* font_text2;
ImFont* font_text3;

void Entry::Init()
{
    if (!glfwInit())
        return;
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);//透明
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);//无边框
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE); // 使窗口浮动，可能在某些平台上类似于置顶
    window1 = glfwCreateWindow(1920, 1080, u8"NylDraw", NULL, NULL);
    if (!window1) {
        glfwTerminate();
        return;
    }

    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    window2 = glfwCreateWindow(1920, 1080, u8"NylMenu", NULL, window1);

    if (!window2) {
        glfwTerminate();
        return;
    }

    // 使用 Win32 API 设置第一个窗口的鼠标穿透
    HWND hwnd1 = glfwGetWin32Window(window1);
    LONG style = GetWindowLong(hwnd1, GWL_EXSTYLE);
    SetWindowLong(hwnd1, GWL_EXSTYLE, style | WS_EX_LAYERED | WS_EX_TRANSPARENT);

    IMGUI_CHECKVERSION();
    ImGuiContext* context1 = ImGui::CreateContext();
    ImGuiContext* context2 = ImGui::CreateContext();


    glfwMakeContextCurrent(window1);
    ImGui::SetCurrentContext(context1);
    ImGui_ImplGlfw_InitForOpenGL(window1, true);
    ImGui_ImplOpenGL3_Init();
    //
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //ImGui::StyleColorsDark();

    HEAD_TO_FONT19(19.f);
    //————————————————————————————————————————————————————————————————————
    //向上字体融合
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.FontDataOwnedByAtlas = false;
    icons_config.FontDataSize = 26;
    font_text2 = io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome, sizeof(fontAwesome), 23.0f, &icons_config, icons_ranges);//功能选择图标
    //——————————————————————————————————————————————————————————初始化字体 完毕

    glfwMakeContextCurrent(window2);
    ImGui::SetCurrentContext(context2);
    ImGui_ImplGlfw_InitForOpenGL(window2, true);
    ImGui_ImplOpenGL3_Init();
    ImGuiIO& io2 = ImGui::GetIO(); (void)io2;
    ImGui::StyleColorsDark();
    HEAD_TO_FONT192(19.f);
    //————————————————————————————————————————————————————————————————————
    //向上字体融合
    static const ImWchar icons_ranges2[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config2;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.FontDataOwnedByAtlas = false;
    icons_config.FontDataSize = 26;
    font_text2 = io2.Fonts->AddFontFromMemoryTTF((void*)fontAwesome, sizeof(fontAwesome), 23.0f, &icons_config, icons_ranges);//功能选择图标
    //——————————————————————————————————————————————————————————初始化字体 完毕

    while (!glfwWindowShouldClose(window1) && !glfwWindowShouldClose(window2)) {
        glfwPollEvents();


        // 渲染第一个窗口
        glfwMakeContextCurrent(window1);
        ImGui::SetCurrentContext(context1);
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();
        static bool bOpen = true;
        //ImGui::Begin("DrawWindow", &bOpen, ImGuiWindowFlags_None);

        ImGui::Begin("DrawWindow", &bOpen, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove);
        //ImGui::SetWindowSize({ (float)F::Global.GameData.Width * 2,(float)F::Global.GameData.Height * 2 });

        ImGui::SetWindowPos("DrawWindow", ImVec2{ (float)0 ,(float)0 });//窗口位置
        ImGui::SetWindowSize("DrawWindow", ImVec2{ (float)F::Global.GameData.新窗口W ,(float)F::Global.GameData.新窗口H });//窗口大小


        static bool 初始一次;
        if (初始一次 == false)
        {
            glfwSetWindowPos(window1, F::Global.GameData.新窗口X, F::Global.GameData.新窗口Y);//移动窗口
            glfwSetWindowSize(window1, F::Global.GameData.新窗口W, F::Global.GameData.新窗口H);//改变窗口大小
            初始一次 = true;
        }

        ImGuiStyle& style = ImGui::GetStyle();
        if (F::Global.GameData.串流模式) {
            //串流模式
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f); // 全透明
        }
        else
        {
            //融合器模式
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // 不透明
        }

        // ... ImGui 绘制代码 ...
        G::render.Init();
        G::render.物品绘制();

        ///
        char FPS[10];
        sprintf_s(FPS, u8"%.0f Fps", ImGui::GetIO().Framerate);

        char 数据A[99];
        char 数据B[99];
        char 数据C[99];
        char 数据D[99];
        //sprintf_s(数据A, u8"Player: %d  Item: %d  ArrayCount: %d", G::engine->集_玩家数组.size(), G::engine->集_物品数组.size(), G::engine->ActorCount);

        sprintf_s(数据B, u8"TeamID:%d  物品开关: %s 战斗模式: %s", Local.Teamid, F::Global.Menu.物透开关 ? u8"关" : u8"开", F::Global.KeyBind.战斗模式 ? u8"开" : u8"关");
        sprintf_s(数据C, u8"当前物品组:%c", F::Global.Menu.当前物品组);

        //ImGui::Text(数据A);
        ImGui::Text(数据B);
        ImGui::Text(数据C);
        //ImGui::Text(数据D);


        ImGui::Text(FPS);
        

        ImGui::End();
        //————————————————

        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window1);


        // 渲染第二个窗口
        glfwMakeContextCurrent(window2);
        ImGui::SetCurrentContext(context2);
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        // ... ImGui 绘制代码 ...
        if (GetAsyncKeyState(VK_HOME) & 8001 || GetAsyncKeyState(VK_INSERT) & 8001)
        {
            F::Global.Menu.菜单开关 = !F::Global.Menu.菜单开关;
        }
        if (F::Global.Menu.菜单开关) Gui::自定义菜单();

        ImGui::Begin("DebugHDWN", &bOpen, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowPos("DebugHDWN", ImVec2{ (float)0 ,(float)0 });//窗口位置
        ImGui::SetWindowSize("DebugHDWN", ImVec2{ (float)470 ,(float)70 });//窗口大小
       
        {
            char 数据A[99];
            char 数据B[99];
            char 数据C[99];
            char 数据D[99];
            sprintf_s(数据A, u8"Player: %d  Item: %d  地面物品: %d  ArrayCount: %d", G::engine->集_玩家数组.size(), G::engine->集_物品数组.size(), G::engine->集_地面物品数组.size(), G::engine->ActorCount);
            sprintf_s(数据B, u8"TeamID:%d  物品开关: %s 战斗模式: %s", Local.Teamid, F::Global.Menu.物透开关 ? u8"关" : u8"开", F::Global.KeyBind.战斗模式 ? u8"开" : u8"关");
            sprintf_s(数据C, u8"当前物品组:%c ", F::Global.Menu.当前物品组);

            if (F::Global.Menu.Debug)
            {
                ImGui::Text(u8"调试数组数量 %d",G::engine->调试数组.size());
            }

            ImGui::Text(数据A);
            ImGui::Text(数据B);
            ImGui::Text(数据C);
            //ImGui::Text(数据D);


            char 武器数据[256];
            //for (size_t i = 0; i < F::Global.Menu.weaponNames.size(); i++)
            //{
            //    
            //    string name = F::Global.Menu.weaponNames[i];
            //    //printf("%s  %s\n", name.c_str(), F::Global.Menu.items[F::Global.Menu.item_current[i]]);
            //    //sprintf_s(武器数据, u8"武器:%s  当前物品组是\n", name.c_str());
            //    //ImGui::Text(u8"武器:%s  当前物品组是", name.c_str());
            //}
           


          
        }
        ImGui::End();

        //————————————————

        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window2);

        glfwSwapInterval(1);
    }

    ImGui::SetCurrentContext(context1);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(context1);


    ImGui::SetCurrentContext(context2);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext(context2);


    glfwDestroyWindow(window1);
    glfwDestroyWindow(window2);
    glfwTerminate();
    return;
}
