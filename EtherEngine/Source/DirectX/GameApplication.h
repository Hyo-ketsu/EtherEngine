#ifndef I_GAMEAPPLICATION_H
#define I_GAMEAPPLICATION_H
#include <DirectX/DirectX.h>
#include <Base/InitUninitPerformer.h>


namespace EtherEngine {
    const std::string WINDOW_CLASS_NAME = "Game";   // ���C���E�B���h�E��


    // �Q�[���A�v���P�[�V������\������N���X
    class GameApplication {
    public:
        // �R���X�g���N�^
        GameApplication(void);


        // ���C���֐�
        virtual void MainFunction(void);


        // ���̃N���X�̏������O�ɒǉ��ōs������������
        virtual void InitFirst(void) {}
        // ���̃N���X�̏�������ɒǉ��ōs������������
        virtual void InitLast(void) {}
        // ������������ɒǉ��ōs������������
        virtual void InitLateFuntion(void) {}


        // �E�B���h�E�n���h���Q�b�^�[
        const HWND& GetHWND(void) const { return m_hwnd.value(); }
        // �E�B���h�E�n���h���Z�b�^�[
        void SetHWND(HWND in) { m_hwnd.emplace(in); }

        // �E�B���h�E�T�C�Y�Q�b�^�[
        const Eigen::Array2<int>& GetWindSize(void) const { return m_windowSize; }
        // �E�B���h�E�T�C�Y�Z�b�^�[
        void SetWindSize(const Eigen::Array2<int>& in) { m_windowSize = in; }

        // HInstance�Q�b�^�[
        const HINSTANCE& GetHInstance(void) const { return m_hInstance.value(); }
        // IpCmdLine�Q�b�^�[
        const LPSTR& GetIpCmdLine(void) const { return m_ipCmdLine.value(); }
        // CmdShow�Q�b�^�[
        const int& GetCmdShow(void) const { return m_cmdShow.value(); }

        // DirectX�Q�b�^�[
        const DirectXRender& GetDirectX(void) const { return m_dxRender; }


        // WinMain �̈�����ێ�����
        void SetApplicationData(const HINSTANCE hInstace, const LPSTR ipCmdLine, const int& cmdShow);

    protected:
        std::optional<HWND> m_hwnd; // �E�B���h�E�n���h��
        Eigen::Array2<int>  m_windowSize; // �E�B���h�E�̃T�C�Y
        std::optional<HINSTANCE> m_hInstance;  // �C���X�^���X�n���h��
        std::optional<LPSTR>     m_ipCmdLine;  // �R�}���h���C��
        std::optional<int>       m_cmdShow;    // �A�v���P�[�V�����̏����\�����@
        DirectXRender            m_dxRender;

        InitUninitPerformer m_initUninitPerformer;  // �������E�I���������s�N���X
    };
}


#endif // !I_GAMEAPPLICATION_H
