#ifndef I_DIRECTX_H
#define I_DIRECTX_H
#include <DirectX/ComPointer.h>
#include <Base/Handle.h>


namespace EtherEngine {
    // 1�����_�[�e�N�X�`���[�ɑΉ�����`��p�N���X
    class DirectXRender {
    public:
        // �R���X�g���N�^
        DirectXRender(void);
        // �f�X�g���N�^
        ~DirectXRender(void);


        // SwapChain�Q�b�^�[
        IDXGISwapChain* const GetSwapChain(void) const { return m_swapChain.Get(); }
        // Device�Q�b�^�[
        ID3D11Device* const GetDevice(void) const { return m_device.Get(); }
        // DeviceContext�Q�b�^�[
        ID3D11DeviceContext* const GetContext(void) const { return m_context.Get(); }
        // �����_�[�^�[�Q�b�g�Q�b�^�[
        ID3D11RenderTargetView* const GetRenderTargetView(void) const { return m_rtv; }
        // �[�x�o�b�t�@�[�Q�b�^�[
        ID3D11DepthStencilView* const GetDepthStencilView(void) const { return m_dsv; }


        // �������֐�
        // @ Ret  : ������������������
        // @ Arg1 : �t���[���o�b�t�@�̉���
        // @ Arg2 : �t���[���o�b�t�@�̏c��
        // @ Arg3 : DirextX�����蓖�Ă�E�B���h�E
        // @ Arg4 : �t���X�N���[���w��
        // @ Arg5 : �r�f�I�J�[�h�w��
        // @ Arg6 : �t�@�N�g���w��
        HRESULT Init(const UINT width, const UINT height, const HWND hWnd, const bool fullScreen, IDXGIAdapter1* adapter, IDXGIFactory1* factory);
        // �I������
        void Uninit(void);


        // �`��O����
        void BeginDraw(void);
        // �`�揈��
        void Draw();
        // �`��㏈��
        void EndDraw(void);

    private:
        ComPtr<IDXGISwapChain> m_swapChain; // �X���b�v�`�F�C��
        ComPtr<ID3D11Device>   m_device;
        ComPtr<ID3D11DeviceContext> m_context;
        ID3D11RenderTargetView* m_rtv;
        ID3D11DepthStencilView* m_dsv;
    };
}


#endif // !I_DIRECTX_H
