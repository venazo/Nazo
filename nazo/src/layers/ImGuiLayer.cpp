#include <zpch.h>
#include "ImGuiLayer.h" 
#include "../NazoApplication.h"

namespace Nazo {

#define BIND_EVENT_FN(x) std::bind(&Nazo::ImGuiLayer::x, this, std::placeholders::_1)

    ImGuiLayer::ImGuiLayer(NazoApplication* application)
        :Layer("ImGuiLayer"), m_assetPanel(AssetPanel(this, application->GetAssetPool(), 
        application->GetSceneManager())), m_propertiesPanel(PropertiesPanel(application)), 
        m_sceneHierarchyPanel(SceneHierarchyPanel(application)), 
        m_terminalPanel(TerminalPanel(application->GetLogger())),
        m_gridPanel(GridPanel(application))
    {
        m_application = application;
        m_width = m_application->GetWindow()->GetWidth();
        m_height = m_application->GetWindow()->GetHeight();
        m_isPlaying = false;
        m_editorView = GameViewPort(m_application, "Editor View", true);
        m_gameView = GameViewPort(m_application, "Game View", false);
        m_application->GetInput()->SetTranslationState(true);
    }

    ImGuiLayer::~ImGuiLayer()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnAttach()
    {	
        const char* glsl_version = "#version 450";
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO();

        m_filename = (std::filesystem::current_path().string() + "\\Assets\\nazo\\ImGUI\\ImGUI.ini");
        io.IniFilename = m_filename.c_str();

        std::string bold = (std::string)std::filesystem::current_path().string() + "\\Assets\\Fonts\\OpenSans-Bold.TTF";
        std::string regular = (std::string)std::filesystem::current_path().string() + "\\Assets\\Fonts\\OpenSans-Regular.TTF";
        io.Fonts->AddFontFromFileTTF(bold.c_str(), 21.0f);
        io.FontDefault = io.Fonts->AddFontFromFileTTF(regular.c_str(), 21.0f);
        io.ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable;

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        SetDarkThemeColors();

        ImGui_ImplGlfw_InitForOpenGL(m_application->GetWindow()->GetGLFWwindow(), true);
        ImGui_ImplOpenGL3_Init(glsl_version);

        return;
    }

    void ImGuiLayer::Start()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        SetupDockSpace();
    }

    void ImGuiLayer::SetupDockSpace()
    {
        int windowFlags = ImGuiWindowFlags_MenuBar;
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(m_width, m_height));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        ImGui::Begin("Dockspace", 0, windowFlags);
        ImGui::PopStyleVar(2);

        ImGui::DockSpace(ImGui::GetID("Dockspace"));

        ImGui::End();
    }

    void ImGuiLayer::OnUpdate(float dt)
    {
        Start();

        if(ImGui::BeginMainMenuBar())
        {
            m_isPlaying = m_application->GetEditorLayer()->IsPlaying();
            if(ImGui::BeginMenu("FILE"))
            {
                if(ImGui::MenuItem("Save", "CTR + S"))
                {
                    if(!m_isPlaying)
                    {
                        SaveSceneEvent event;
                        m_eventCallback(event);
                    }
                }

                ImGui::EndMenu();
            }

            if(ImGui::MenuItem("PLAY", "F5", m_isPlaying, !m_isPlaying && m_application->GetSceneManager()->HasActiveScene()))
            {
                GameStartEvent event;
                m_eventCallback(event);
            }
            if(ImGui::MenuItem("STOP", "F4", !m_isPlaying, m_isPlaying))
            {
                GameEndEvent event;
                m_eventCallback(event);
            }
            ImGui::EndMainMenuBar();
        }


		m_gridPanel.OnUpdate(dt);
        
        ImGui::ShowDemoWindow();
        m_editorView.ImGui();
        m_gameView.ImGui();

        m_propertiesPanel.ImGui();
        m_sceneHierarchyPanel.ImGui();
        m_assetPanel.ImGui();
        m_terminalPanel.ImGui();
        m_gridPanel.ImGui();
        
        End();
    }

    void ImGuiLayer::End()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

        ZImGui::Get().OnEvent(event);
    }

    bool ImGuiLayer::OnWindowResize(WindowResizeEvent& e)
    {
        m_gameView.Resize(e.GetWidth(), e.GetHeight());
        m_editorView.Resize(e.GetWidth(), e.GetHeight());
        m_width = e.GetWidth();
        m_height = e.GetHeight();
        return false;
    }

    void ImGuiLayer::SetDarkThemeColors()
    {
        auto& colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

        // Headers
        colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Buttons
        colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Frame BG
        colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
        colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
        colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

        // Tabs
        colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
        colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
        colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

        // Docking
        colors[ImGuiCol_DockingPreview] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

        // Title
        colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    }

    void ImGuiLayer::SetEventCallback(const EventCallbackFn& callback)
    {
        m_eventCallback = callback;
        m_editorView.SetEventCallback(m_eventCallback);
        m_gameView.SetEventCallback(m_eventCallback);
    }
}