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
int ���ڱ���ģʽ = 0;

ImFont* font_text1;
ImFont* font_text2;
ImFont* font_text3;

void Entry::Init()
{
    if (!glfwInit())
        return;
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);//͸��
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);//�ޱ߿�
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE); // ʹ���ڸ�����������ĳЩƽ̨���������ö�
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

    // ʹ�� Win32 API ���õ�һ�����ڵ���괩͸
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
    //����������������������������������������������������������������������������������������������������������������������������������������
    //���������ں�
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.FontDataOwnedByAtlas = false;
    icons_config.FontDataSize = 26;
    font_text2 = io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome, sizeof(fontAwesome), 23.0f, &icons_config, icons_ranges);//����ѡ��ͼ��
    //����������������������������������������������������������������������������������������������������������������������ʼ������ ���

    glfwMakeContextCurrent(window2);
    ImGui::SetCurrentContext(context2);
    ImGui_ImplGlfw_InitForOpenGL(window2, true);
    ImGui_ImplOpenGL3_Init();
    ImGuiIO& io2 = ImGui::GetIO(); (void)io2;
    ImGui::StyleColorsDark();
    HEAD_TO_FONT192(19.f);
    //����������������������������������������������������������������������������������������������������������������������������������������
    //���������ں�
    static const ImWchar icons_ranges2[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config2;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.FontDataOwnedByAtlas = false;
    icons_config.FontDataSize = 26;
    font_text2 = io2.Fonts->AddFontFromMemoryTTF((void*)fontAwesome, sizeof(fontAwesome), 23.0f, &icons_config, icons_ranges);//����ѡ��ͼ��
    //����������������������������������������������������������������������������������������������������������������������ʼ������ ���

    while (!glfwWindowShouldClose(window1) && !glfwWindowShouldClose(window2)) {
        glfwPollEvents();


        // ��Ⱦ��һ������
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

        ImGui::SetWindowPos("DrawWindow", ImVec2{ (float)0 ,(float)0 });//����λ��
        ImGui::SetWindowSize("DrawWindow", ImVec2{ (float)F::Global.GameData.�´���W ,(float)F::Global.GameData.�´���H });//���ڴ�С


        static bool ��ʼһ��;
        if (��ʼһ�� == false)
        {
            glfwSetWindowPos(window1, F::Global.GameData.�´���X, F::Global.GameData.�´���Y);//�ƶ�����
            glfwSetWindowSize(window1, F::Global.GameData.�´���W, F::Global.GameData.�´���H);//�ı䴰�ڴ�С
            ��ʼһ�� = true;
        }

        ImGuiStyle& style = ImGui::GetStyle();
        if (F::Global.GameData.����ģʽ) {
            //����ģʽ
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f); // ȫ͸��
        }
        else
        {
            //�ں���ģʽ
            style.Colors[ImGuiCol_WindowBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f); // ��͸��
        }

        // ... ImGui ���ƴ��� ...
        G::render.Init();
        G::render.��Ʒ����();

        ///
        char FPS[10];
        sprintf_s(FPS, u8"%.0f Fps", ImGui::GetIO().Framerate);

        char ����A[99];
        char ����B[99];
        char ����C[99];
        char ����D[99];
        //sprintf_s(����A, u8"Player: %d  Item: %d  ArrayCount: %d", G::engine->��_�������.size(), G::engine->��_��Ʒ����.size(), G::engine->ActorCount);

        sprintf_s(����B, u8"TeamID:%d  ��Ʒ����: %s ս��ģʽ: %s", Local.Teamid, F::Global.Menu.��͸���� ? u8"��" : u8"��", F::Global.KeyBind.ս��ģʽ ? u8"��" : u8"��");
        sprintf_s(����C, u8"��ǰ��Ʒ��:%c", F::Global.Menu.��ǰ��Ʒ��);

        //ImGui::Text(����A);
        ImGui::Text(����B);
        ImGui::Text(����C);
        //ImGui::Text(����D);


        ImGui::Text(FPS);
        

        ImGui::End();
        //��������������������������������

        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window1);


        // ��Ⱦ�ڶ�������
        glfwMakeContextCurrent(window2);
        ImGui::SetCurrentContext(context2);
        ImGui_ImplGlfw_NewFrame();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        // ... ImGui ���ƴ��� ...
        if (GetAsyncKeyState(VK_HOME) & 8001 || GetAsyncKeyState(VK_INSERT) & 8001)
        {
            F::Global.Menu.�˵����� = !F::Global.Menu.�˵�����;
        }
        if (F::Global.Menu.�˵�����) Gui::�Զ���˵�();

        ImGui::Begin("DebugHDWN", &bOpen, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground
            | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
        ImGui::SetWindowPos("DebugHDWN", ImVec2{ (float)0 ,(float)0 });//����λ��
        ImGui::SetWindowSize("DebugHDWN", ImVec2{ (float)470 ,(float)70 });//���ڴ�С
       
        {
            char ����A[99];
            char ����B[99];
            char ����C[99];
            char ����D[99];
            sprintf_s(����A, u8"Player: %d  Item: %d  ������Ʒ: %d  ArrayCount: %d", G::engine->��_�������.size(), G::engine->��_��Ʒ����.size(), G::engine->��_������Ʒ����.size(), G::engine->ActorCount);
            sprintf_s(����B, u8"TeamID:%d  ��Ʒ����: %s ս��ģʽ: %s", Local.Teamid, F::Global.Menu.��͸���� ? u8"��" : u8"��", F::Global.KeyBind.ս��ģʽ ? u8"��" : u8"��");
            sprintf_s(����C, u8"��ǰ��Ʒ��:%c ", F::Global.Menu.��ǰ��Ʒ��);

            if (F::Global.Menu.Debug)
            {
                ImGui::Text(u8"������������ %d",G::engine->��������.size());
            }

            ImGui::Text(����A);
            ImGui::Text(����B);
            ImGui::Text(����C);
            //ImGui::Text(����D);


            char ��������[256];
            //for (size_t i = 0; i < F::Global.Menu.weaponNames.size(); i++)
            //{
            //    
            //    string name = F::Global.Menu.weaponNames[i];
            //    //printf("%s  %s\n", name.c_str(), F::Global.Menu.items[F::Global.Menu.item_current[i]]);
            //    //sprintf_s(��������, u8"����:%s  ��ǰ��Ʒ����\n", name.c_str());
            //    //ImGui::Text(u8"����:%s  ��ǰ��Ʒ����", name.c_str());
            //}
           


          
        }
        ImGui::End();

        //��������������������������������

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
