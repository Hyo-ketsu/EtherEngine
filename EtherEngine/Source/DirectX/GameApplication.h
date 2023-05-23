#ifndef I_GAMEAPPLICATION_H
#define I_GAMEAPPLICATION_H
#include <Base/InitUninitPerformer.h>
#include <DirectX/DirectX.h>
#include <DirectX/Window.h>


namespace EtherEngine {
    const std::string WINDOW_CLASS_NAME = "Game";   // ���C���E�B���h�E��


    // �Q�[���A�v���P�[�V������\������N���X
    class GameApplication : public Window {
    public:
        // �R���X�g���N�^
        GameApplication(void);
        // �f�X�g���N�^
        ~GameApplication(void);


        // ���C���֐�
        virtual void MainFunction(void);


        // ���̃N���X�̏������O�ɒǉ��ōs������������
        virtual void InitFirst(void) {}
        // ���̃N���X�̏�������ɒǉ��ōs������������
        virtual void InitLast(void) {}
        // ������������ɒǉ��ōs������������
        virtual void InitLateFuntion(void) {}

        // ���̃N���X�̕`�揈���̑O�ɍs������
        virtual void DrawFirst(void) {}
        // ���̃N���X�̕`�揈���̌�ɍs������
        virtual void DrawLast(void) {}


        // HInstance�Q�b�^�[
        const HINSTANCE& GetHInstance(void) const { return m_hInstance.value(); }
        // IpCmdLine�Q�b�^�[
        const LPSTR& GetIpCmdLine(void) const { return m_ipCmdLine.value(); }
        // CmdShow�Q�b�^�[
        const int& GetCmdShow(void) const { return m_cmdShow.value(); }

        // DirectX�Q�b�^�[
        const Handle<DirectXRender>& GetDirectX(void) const { return m_dxRender; }


        // WinMain �̈�����ێ�����
        void SetApplicationData(const HINSTANCE hInstace, const LPSTR ipCmdLine, const int& cmdShow);

    protected:
        std::optional<HINSTANCE> m_hInstance;  // �C���X�^���X�n���h��
        std::optional<LPSTR>     m_ipCmdLine;  // �R�}���h���C��
        std::optional<int>       m_cmdShow;    // �A�v���P�[�V�����̏����\�����@
        Handle<DirectXRender>    m_dxRender;

        InitUninitPerformer m_initUninitPerformer;  // �������E�I���������s�N���X
    };
}


#endif // !I_GAMEAPPLICATION_H
