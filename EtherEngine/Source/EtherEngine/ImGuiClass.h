#ifndef I_IMGUIINIT_H
#define I_IMGUIINIT_H


namespace EtherEngine {
    class IMGUI {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �E�B���h�E�n���h��
        // @ Arg2 : �f�o�C�X�R���e�L�X�g
        IMGUI(ID3D11Device* device, ID3D11DeviceContext* context);
        // �f�X�g���N�^
        ~IMGUI(void);

    private:
        ID3D11Device* m_device;
        ID3D11DeviceContext* m_context;
    };
}


#endif // !I_IMGUIINIT_H
