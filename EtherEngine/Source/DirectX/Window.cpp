#include <DirectX/Window.h>


//----- Window実装
namespace EtherEngine {
    // コンストラクタ
    Window::Window(const std::string& name)
        : m_name(name)
        , m_windowSize(1,1) {
    }
}
