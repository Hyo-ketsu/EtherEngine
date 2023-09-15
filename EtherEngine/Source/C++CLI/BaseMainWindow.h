#ifndef I_BASEMAINWINDOW_H
#define I_BASEMAINWINDOW_H
#include <Base/Singleton.h>
#include <Base/InitUninitPerformer.h>
#include <DirectX/Window.h>
#include <DirectX/DirectX.h>


//----- BaseMainWindow�錾
namespace EtherEngine {
    // �N������I���܂ő��݂��Ă���E�B���h�E
    class BaseMainWindow : public Window {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �E�B���h�E�̖��O
        BaseMainWindow(const std::string& name);


        // HInstance�Q�b�^�[
        const HINSTANCE& GetHInstance(void) const { return m_hInstance.value(); }
        // IpCmdLine�Q�b�^�[
        const LPSTR& GetIpCmdLine(void) const { return m_ipCmdLine.value(); }
        // CmdShow�Q�b�^�[
        const int& GetCmdShow(void) const { return m_cmdShow.value(); }
        // Proc�Z�b�^�[
        void SetProc(WNDPROC* in) { m_proc = in; }

        // DirectX�Q�b�^�[
        const BaseHandle<DirectXRender>& GetDirectX(void) const { return m_dxRender; }


        // �������֐�
        void BaseInitFunction(void);
        // �I���֐�
        void BaseUninitFunction(void);
        // ���C���֐�
        void BaseMainFunction(void);

        // �������O�֐�
        virtual void InitFirstFunction(void) {}
        // ��������֐�
        virtual void InitLateFunction(void) {}
        // ����������������֐�
        virtual void EndInitLateFunction(void) {}
        // �I���O�֐�
        virtual void UninitFirstFunction(void) {}
        // �I����֐�
        virtual void UninitLateFunction(void) {}
        // �I������������֐�
        virtual void EndUninitLateFunction(void) {}


        // WinMain �̈�����ێ�����
        void SetApplicationData(const HINSTANCE hInstace, const LPSTR ipCmdLine, const int& cmdShow);

    protected:
        // ���C���֐�
        virtual void MainFunction(void) = 0;


        std::optional<HINSTANCE> m_hInstance;  // �C���X�^���X�n���h��
        std::optional<LPSTR>     m_ipCmdLine;  // �R�}���h���C��
        std::optional<int>       m_cmdShow;    // �A�v���P�[�V�����̏����\�����@
        WNDPROC*                 m_proc;
        InitUninitPerformer m_initUninitPerformer;  // �������E�I���������s�N���X
    };
}


#endif // !I_BASEMAINWINDOW_H
