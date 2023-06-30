#include <DirectX/Window.h>
#include <Base/WindowsDefine.h>


//----- Window実装
namespace EtherEngine {
    // コンストラクタ
    Window::Window(const std::string& name)
        : m_name(name)
        , m_windowSize(1,1) {
    }


    // ウィンドウキャプションの文字を取得する
    std::string Window::GetCaption(void) {
        //----- 変数宣言と初期化
        std::array<char, WindowDefine::Define::MAX_CAPTION_TEXT_SIZE> captionText = decltype(captionText)();
        captionText.fill(0);

        //----- キャプションの取得
        GetWindowTextA(m_hwnd.value(), captionText.data(), captionText.size());

        //----- 返却
        return std::string(captionText.data());
    }

    // ウィンドウキャプションの文字を設定する
    bool Window::SetCaption(const char* name) {
        return SetWindowTextA(m_hwnd.value(), static_cast<LPCSTR>(name));
    }
}
