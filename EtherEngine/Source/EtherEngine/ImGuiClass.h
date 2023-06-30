#ifndef I_IMGUIINIT_H
#define I_IMGUIINIT_H


//----- IMGUI 宣言
namespace EtherEngine {
    // IMGUIのラップクラス
    class IMGUI {
    public:
        // コンストラクタ
        // @ Arg1 : デバイス
        // @ Arg2 : デバイスコンテキスト
        // @ Arg3 : ウィンドウハンドル
        IMGUI(ID3D11Device* device, ID3D11DeviceContext* context, HWND hWnd);
        // デストラクタ
        ~IMGUI(void);

    private:
        ImGuiContext* m_imGuiContext;
        ID3D11Device* m_device;
        ID3D11DeviceContext* m_context;
    };
}


#endif // !I_IMGUIINIT_H
