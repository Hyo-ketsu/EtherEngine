#include <EtherEngine/ImGuiClass.h>


//----- ImGui ��`
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
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        ImGui::SetCurrentContext(m_imGuiContext);
        ImGui_ImplDX11_Init(device, context);
        ImGui_ImplWin32_Init(hWnd);
    }
    // �f�X�g���N�^
    IMGUI::~IMGUI(void) {
        ImGui_ImplDX11_Shutdown();
    }
}
