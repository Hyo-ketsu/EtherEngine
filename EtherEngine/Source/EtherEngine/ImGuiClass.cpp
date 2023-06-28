#include <EtherEngine/ImGuiClass.h>


namespace EtherEngine {
    // �R���X�g���N�^
    IMGUI::IMGUI(ID3D11Device* device, ID3D11DeviceContext* context, HWND hWnd)
        : m_imGuiContext(ImGui::CreateContext())
        , m_device(device) 
        , m_context(context) {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); 
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::SetCurrentContext(m_imGuiContext);
        ImGui_ImplDX11_Init(device, context);
        ImGui_ImplWin32_Init(hWnd);
    }
    // �f�X�g���N�^
    IMGUI::~IMGUI(void) {
        ImGui_ImplDX11_Shutdown();
    }
}
