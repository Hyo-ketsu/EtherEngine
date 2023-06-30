#include <DirectX/Window.h>
#include <Base/WindowsDefine.h>


//----- Window����
namespace EtherEngine {
    // �R���X�g���N�^
    Window::Window(const std::string& name)
        : m_name(name)
        , m_windowSize(1,1) {
    }


    // �E�B���h�E�L���v�V�����̕������擾����
    std::string Window::GetCaption(void) {
        //----- �ϐ��錾�Ə�����
        std::array<char, WindowDefine::Define::MAX_CAPTION_TEXT_SIZE> captionText = decltype(captionText)();
        captionText.fill(0);

        //----- �L���v�V�����̎擾
        GetWindowTextA(m_hwnd.value(), captionText.data(), captionText.size());

        //----- �ԋp
        return std::string(captionText.data());
    }

    // �E�B���h�E�L���v�V�����̕�����ݒ肷��
    bool Window::SetCaption(const char* name) {
        return SetWindowTextA(m_hwnd.value(), static_cast<LPCSTR>(name));
    }
}
