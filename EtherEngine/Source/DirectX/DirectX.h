#ifndef I_DIRECTX_H
#define I_DIRECTX_H
#include <Base/Handle.h>
#include <Base/BaseUtility.h>
#include <DirectX/ComPointer.h>
#include <DirectX/DXWindowRender.h>


namespace EtherEngine {
    // 1リソースを管理するクラス
    // @ Memo : 実際の描画はDXWidnowRenderをお使いください
    class DirectXRender : public EnableCheckClass {
    public:
        // コンストラクタ
        DirectXRender(void);
        // デストラクタ
        ~DirectXRender(void);


        // ウィンドウ配列アクセサー
        std::vector<DXWindowRender>& AccessWindowRenders(void) { return m_windowRenders; }
        // Deviceゲッター
        ID3D11Device* GetDevice(void) const { return m_device.Get(); }
        // 編集可能Deviceゲッター
        ID3D11Device** GetEditableDevice(void) { return m_device.GetEditable(); }
        // DeviceContextゲッター
        ID3D11DeviceContext* GetContext(void) const { return m_context.Get(); }
        // 編集可能DeviceContextゲッター
        ID3D11DeviceContext** GetEditableContext(void) { return m_context.GetEditable(); }


        // 通常のメインウィンドウ一つのみ初期化する関数
        // @ Exce : 初期化失敗時
        // @ Arg1 : フレームバッファの幅
        // @ Arg2 : DirectXを割り当てるウィンドウ
        // @ Arg3 : フルスクリーン指定
        void Init(const Eigen::Vector2i size, const HWND hWnd, const bool fullScreen);
        // 終了処理
        void Uninit(void);


        // ウィンドウを作成する
        // @ Exce : 初期化失敗時
        // @ Ret  : ウィンドウのID
        // @ Arg1 : フレームバッファの幅
        // @ Arg2 : DirectXを割り当てるウィンドウ
        // @ Arg3 : フルスクリーン指定
        IDClass CreateDrawWindow(const Eigen::Vector2i size, const HWND hWnd, const bool fullScreen);


        // ウィンドウをIDで取得する
        // @ Ecex : 範囲外参照
        // @ Ret  : 取得したウィンドウ描画情報
        // @ Arg1 : ID
        DXWindowRender* const GetWindowRender(IDClass id);

    private:
        std::vector<DXWindowRender> m_windowRenders;   //
        ComPtr<ID3D11Device>        m_device;    //
        ComPtr<ID3D11DeviceContext> m_context;   // 
    };
}


#endif // !I_DIRECTX_H
