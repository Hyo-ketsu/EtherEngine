#ifndef I_WINDOW_H
#define I_WINDOW_H
#include <DirectX/DirectX.h>


//----- Window 定義
namespace EtherEngine {
    // ウィンドウを表現するクラス
    class Window {
    public:
        // コンストラクタ
        // @ Arg1 : ウィンドウの名前
        Window(const std::string& name);


        // ウィンドウを作成する
        bool Create_Window(void);


        // ウィンドウハンドルゲッター
        const HWND& GetHWND(void) const { return m_hwnd.value(); }
        // ウィンドウハンドルセッター
        void SetHWND(HWND in) { m_hwnd.emplace(in); }

        // ウィンドウサイズゲッター
        const Eigen::Array2<int>& GetWindSize(void) const { return m_windowSize; }
        // ウィンドウサイズセッター
        void SetWindSize(const Eigen::Array2<int>& in) { m_windowSize = in; }


        // ウィンドウキャプションの文字を取得する
        // @ Ret  : 現在のウィンドウのキャプション
        std::string GetCaption(void);
        // ウィンドウキャプションの文字を設定する
        // @ Ret  : キャプションの設定ができたか
        // @ Arg1 : 設定するウィンドウのキャプション
        bool SetCaption(const std::string& name) { return SetCaption(name.c_str()); }
        // ウィンドウキャプションの文字を設定する
        // @ Ret  : キャプションの設定ができたか
        // @ Arg1 : 設定するウィンドウのキャプション
        bool SetCaption(const char* name);

    protected:
        std::string m_name;               // ウィンドウの名前 
        std::optional<HWND> m_hwnd;       // ウィンドウハンドル
        Eigen::Array2<int>  m_windowSize; // ウィンドウのサイズ
        BaseHandle<DirectXRender> m_dxRender;
    };
}


#endif // !I_WINDOW_H
