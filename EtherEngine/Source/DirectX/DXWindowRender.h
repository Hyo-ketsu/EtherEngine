#ifndef I_DXWINDOWRENDER_H
#define I_DXWINDOWRENDER_H
#include <Base/IDClass.h>
#include <Base/CameraBase.h>
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
        // @ Arg7 : �E�B���h�E���ێ����Ă���ID
        DXWindowRender(DirectXRender* directX, const Eigen::Vector2i size, const HWND& hWnd, const bool fullScreen, IDXGIAdapter1* adapter, IDXGIFactory1* factory);
        // �f�X�g���N�^
        DXWindowRender(void);


        // ID�Q�b�^�[
        const IDClass& GetId(void) const { return m_id; }
        // �E�B���h�EID�A�N�Z�T�[
        ullint& AccessWindowId(void) { return m_windowId; }
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
        // �w�i�F�A�N�Z�T�[
        Eigen::Vector4f AccessBackColor(void) { return m_backColor; }


        // �`��O����
        void BeginDraw(void);
        // �`�揈��
        // @ Ret  : �`�悵����
        // @ Arg1 : �J�������
        bool Draw(const CameraData& cameraData);
        // �`��㏈��
        void EndDraw(void);

    private:
        IDClass m_id;                        // ���g��ID
        ullint m_windowId;                   // �E�B���h�E���ێ����Ă���ID
        DirectXRender* m_directX;            // ���\�[�X
        std::weak_ptr<nullptr_t> m_dxEnable; // ���\�[�X�̐����m�F�p
        ComPtr<IDXGISwapChain> m_swapChain;  // �X���b�v�`�F�C��
        ID3D11RenderTargetView* m_rtv;       // �����_�[�^�[�Q�b�g
        ID3D11DepthStencilView* m_dsv;       // 
        ID3D11DepthStencilState* m_dss;      //
        Eigen::Vector4f m_backColor;         // �w�i�F
    };
}


#endif // !I_DXWINDOWRENDER_H
