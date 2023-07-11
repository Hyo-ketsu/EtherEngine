#ifndef I_BASEMAINWINDOW_G
#define I_BASEMAINWINDOW_G
#include <Base/Singleton.h>
#include <Base/InitUninitPerformer.h>
#include <DirectX/Window.h>
#include <DirectX/DirectX.h>


//----- BaseMainWindow�錾
namespace EtherEngine {
    // �N������I���܂ő��݂��Ă���E�B���h�E
    template <typename Type>
    class BaseMainWindow : public Window, public Singleton<Type> {
    public:
        using Window::Window;


        // HInstance�Q�b�^�[
        const HINSTANCE& GetHInstance(void) const { return m_hInstance.value(); }
        // IpCmdLine�Q�b�^�[
        const LPSTR& GetIpCmdLine(void) const { return m_ipCmdLine.value(); }
        // CmdShow�Q�b�^�[
        const int& GetCmdShow(void) const { return m_cmdShow.value(); }

        // DirectX�Q�b�^�[
        const BaseHandle<DirectXRender>& GetDirectX(void) const { return m_dxRender; }


        // ���C���֐�
        virtual void MainFunction(void) = 0;


        // WinMain �̈�����ێ�����
        void SetApplicationData(const HINSTANCE hInstace, const LPSTR ipCmdLine, const int& cmdShow);

    protected:
        std::optional<HINSTANCE> m_hInstance;  // �C���X�^���X�n���h��
        std::optional<LPSTR>     m_ipCmdLine;  // �R�}���h���C��
        std::optional<int>       m_cmdShow;    // �A�v���P�[�V�����̏����\�����@
        BaseHandle<DirectXRender> m_dxRender;
        InitUninitPerformer m_initUninitPerformer;  // �������E�I���������s�N���X

        friend class Singleton<Type>;
    };
}




//----- BaseMainWindow����
namespace EtherEngine {
    // Application�f�[�^�Z�b�^�[
    template <typename Type>
    void BaseMainWindow<Type>::SetApplicationData(const HINSTANCE hInstance, const LPSTR ipCmdLine, const int& cmdShow) {
        m_hInstance = hInstance;
        m_ipCmdLine = ipCmdLine;
        m_cmdShow = cmdShow;
    }
}


#endif // !I_BASEMAINWINDOW_G
