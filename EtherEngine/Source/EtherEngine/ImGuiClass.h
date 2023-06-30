#ifndef I_IMGUIINIT_H
#define I_IMGUIINIT_H


//----- IMGUI �錾
namespace EtherEngine {
    // IMGUI�̃��b�v�N���X
    class IMGUI {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �f�o�C�X
        // @ Arg2 : �f�o�C�X�R���e�L�X�g
        // @ Arg3 : �E�B���h�E�n���h��
        IMGUI(ID3D11Device* device, ID3D11DeviceContext* context, HWND hWnd);
        // �f�X�g���N�^
        ~IMGUI(void);

    private:
        ImGuiContext* m_imGuiContext;
        ID3D11Device* m_device;
        ID3D11DeviceContext* m_context;
    };
}


#endif // !I_IMGUIINIT_H
