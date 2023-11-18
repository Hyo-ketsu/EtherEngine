#ifndef I_DXWINDOWRENDER_H
#define I_DXWINDOWRENDER_H
#include <Base/IDClass.h>
#include <DirectX/ComPointer.h>


//----- DXWindowRender �錾
namespace EtherEngine {
    // �O���錾
    class DirectXRender;


    // �`��֐��̌^
    using DrawFunctionLambda = std::function<void(Eigen::Matrix4f view, Eigen::Matrix4f projection)>;
    // �E�B���h�E���������Ă��邩�`�F�b�N�֐�
    using WindowEnableLambda = std::function<bool(void)>;
    // �E�B���h�E���ōs�����̑��̏���
    using WindowFunctionLambda = std::function<void(class DXWindowRender* const)>;


    // 1�E�B���h�E�̕`����Ǘ�����N���X
    class DXWindowRender {
    public:
        // �R���X�g���N�^
        // @ Exce : �������Ɏ��s��
        // @ Arg1 : DirectX
        // @ Arg2 : �t���[���o�b�t�@�̕�
        // @ Arg3 : �E�B���h�E�n���h��
        // @ Arg4 : �t���X�N���[���w��
        // @ Arg5 : �r�f�I�J�[�h�w��
        // @ Arg6 : �t�@�N�g���w��
        // @ Arg7 : �`��֐��ōs������
        // @ Arg8 : �E�B���h�E���������Ă��邩���肷��֐�
        // @ Arg9 : ���̑��E�B���h�E����(Default : �������Ȃ�)
        DXWindowRender(DirectXRender* directX, const Eigen::Vector2i size, const HWND& hWnd, const bool fullScreen, IDXGIAdapter1* adapter, IDXGIFactory1* factory,
            const DrawFunctionLambda& drawFunction, const WindowEnableLambda& windowEnableFunction, const WindowFunctionLambda& windowFunction);
        // �f�X�g���N�^
        DXWindowRender(void);


        // ID�Q�b�^�[
        const IDClass& GetId(void) const { return m_id; }
        // DirectX�Q�b�^�[
        DirectXRender* const GetDirectX(void) const { return m_directX; }
        // DirectX�����Q�b�^�[
        // @ Ret  : �������Ă����� true 
        bool GetIsDirectXEnable(void) const { return m_dxEnable.expired() == false; }
        // SwapChain�Q�b�^�[
        IDXGISwapChain* const GetSwapChain(void) const { return m_swapChain.Get(); }
        // �����_�[�^�[�Q�b�g�Q�b�^�[
        ID3D11RenderTargetView* const GetRenderTargetView(void) const { return m_rtv; }
        // �[�x�o�b�t�@�[�Q�b�^�[
        ID3D11DepthStencilView* const GetDepthStencilView(void) const { return m_dsv; }
        // ID�Q�b�^�[
        const IDClass& GetCameraID(void) const { return m_mainCameraID; }
        // ID�Z�b�^�[
        void SetCameraID(const IDClass& in) { m_mainCameraID = in; }
        // �E�B���h�E�����֐��Q�b�^�[
        WindowEnableLambda GetWindowEnableFunction(void) const { return m_enableFunction; }
        // ���̑��E�B���h�E�����Q�b�^�[
        WindowFunctionLambda GetWindowFunction(void) const { return m_windowFunction; }
        // �w�i�F�A�N�Z�T�[
        Eigen::Vector4f AccessBackColor(void) { return m_backColor; }


        // �E�B���h�E���������Ă��邩
        // @ Ret  :  �E�B���h�E���������Ă��邩
        bool IsEnableWindow(void) const;


        // �`��O����
        void BeginDraw(void);
        // �`�揈��
        // @ Ret  : �`�悵����
        bool Draw(void);
        // �`��㏈��
        void EndDraw(void);

    private:
        IDClass m_id;                        // ���g��id
        DirectXRender* m_directX;            // ���\�[�X
        std::weak_ptr<void> m_dxEnable;      // ���\�[�X�̐����m�F�p
        ComPtr<IDXGISwapChain> m_swapChain;  // �X���b�v�`�F�C��
        ID3D11RenderTargetView* m_rtv;       // �����_�[�^�[�Q�b�g
        ID3D11DepthStencilView* m_dsv;       // 
        ID3D11DepthStencilState* m_dss;      //
        IDClass m_mainCameraID;              // ���C���J����ID
        DrawFunctionLambda m_drawFunction;   // �`��ōs������
        WindowEnableLambda m_enableFunction; // �E�B���h�E���������Ă��邩���肷��֐�
        WindowFunctionLambda m_windowFunction; // ���̑��̃E�B���h�E����
        Eigen::Vector4f m_backColor;         // �w�i�F
    };
}


#endif // !I_DXWINDOWRENDER_H
