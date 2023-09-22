#include <EtherEngine/ImGuiClass.h>


//----- ImGui 定義
namespace EtherEngine {
    // コンストラクタ
    IMGUI::IMGUI(ID3D11Device* device, ID3D11DeviceContext* context, HWND hWnd)
        : m_imGuiContext(ImGui::CreateContext())
        , m_device(device) 
        , m_context(context) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); 
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.ConfigViewportsNoAutoMerge      = true;
        io.ConfigDockingAlwaysTabBar       = true;
        io.ConfigDockingTransparentPayload = true;
        ImGui::SetCurrentContext(m_imGuiContext);
        ImGui::StyleColorsDark();
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
        ImGui_ImplWin32_Init(hWnd);
        ImGui_ImplDX11_Init(device, context);
    }
    // デストラクタ
    IMGUI::~IMGUI(void) {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }
}
