#include <EtherEngine/ImGuiClass.h>


namespace EtherEngine {
    // コンストラクタ
    IMGUI::IMGUI(ID3D11Device* device, ID3D11DeviceContext* context)
        : m_device(device) 
        , m_context(context) {
        ImGui_ImplDX11_Init(device, context);
    }
    // デストラクタ
    IMGUI::~IMGUI(void) {
        ImGui_ImplDX11_Shutdown();
    }
}
