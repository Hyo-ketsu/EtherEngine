#include <EtherEngine/ImGuiClass.h>


namespace EtherEngine {
    // �R���X�g���N�^
    IMGUI::IMGUI(ID3D11Device* device, ID3D11DeviceContext* context)
        : m_imGuiContext(ImGui::CreateContext())
        , m_device(device) 
        , m_context(context) {
        ImGui::SetCurrentContext(m_imGuiContext);
        ImGui_ImplDX11_Init(device, context);
    }
    // �f�X�g���N�^
    IMGUI::~IMGUI(void) {
        ImGui_ImplDX11_Shutdown();
    }
}
