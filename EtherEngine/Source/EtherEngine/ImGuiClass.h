#ifndef I_IMGUIINIT_H
#define I_IMGUIINIT_H


namespace EtherEngine {
    class IMGUI {
    public:
        // コンストラクタ
        // @ Arg1 : ウィンドウハンドル
        // @ Arg2 : デバイスコンテキスト
        IMGUI(ID3D11Device* device, ID3D11DeviceContext* context);
        // デストラクタ
        ~IMGUI(void);

    private:
        ID3D11Device* m_device;
        ID3D11DeviceContext* m_context;
    };
}


#endif // !I_IMGUIINIT_H
