#ifndef I_DIRECTX_H
#define I_DIRECTX_H
#include <Base/Handle.h>
#include <Base/BaseUtility.h>
#include <DirectX/ComPointer.h>
#include <DirectX/DXWindowRender.h>


namespace EtherEngine {
    // 1���\�[�X���Ǘ�����N���X
    // @ Memo : ���ۂ̕`���DXWidnowRender�����g����������
    class DirectXRender : public EnableCheckClass {
    public:
        // �R���X�g���N�^
        DirectXRender(void);
        // �f�X�g���N�^
        ~DirectXRender(void);


        // �E�B���h�E�z��A�N�Z�T�[
        std::vector<DXWindowRender>& AccessWindowRenders(void) { return m_windowRenders; }
        // Device�Q�b�^�[
        ID3D11Device* GetDevice(void) const { return m_device.Get(); }
        // �ҏW�\Device�Q�b�^�[
        ID3D11Device** GetEditableDevice(void) { return m_device.GetEditable(); }
        // DeviceContext�Q�b�^�[
        ID3D11DeviceContext* GetContext(void) const { return m_context.Get(); }
        // �ҏW�\DeviceContext�Q�b�^�[
        ID3D11DeviceContext** GetEditableContext(void) { return m_context.GetEditable(); }


        // �ʏ�̃��C���E�B���h�E��̂ݏ���������֐�
        // @ Exce : ���������s��
        // @ Arg1 : �t���[���o�b�t�@�̕�
        // @ Arg2 : DirectX�����蓖�Ă�E�B���h�E
        // @ Arg3 : �t���X�N���[���w��
        void Init(const Eigen::Vector2i size, const HWND hWnd, const bool fullScreen);
        // �I������
        void Uninit(void);


        // �E�B���h�E���쐬����
        // @ Exce : ���������s��
        // @ Ret  : �E�B���h�E��ID
        // @ Arg1 : �t���[���o�b�t�@�̕�
        // @ Arg2 : DirectX�����蓖�Ă�E�B���h�E
        // @ Arg3 : �t���X�N���[���w��
        IDClass CreateDrawWindow(const Eigen::Vector2i size, const HWND hWnd, const bool fullScreen);


        // �E�B���h�E��ID�Ŏ擾����
        // @ Ecex : �͈͊O�Q��
        // @ Ret  : �擾�����E�B���h�E�`����
        // @ Arg1 : ID
        DXWindowRender* const GetWindowRender(IDClass id);

    private:
        std::vector<DXWindowRender> m_windowRenders;   //
        ComPtr<ID3D11Device>        m_device;    //
        ComPtr<ID3D11DeviceContext> m_context;   // 
    };
}


#endif // !I_DIRECTX_H
