#ifndef I_WINDOW_H
#define I_WINDOW_H


//----- Window 定義
namespace EtherEngine {
    // ウィンドウを表現するクラス
    class Window {
    public:
        // コンストラクタ
        // @ Arg1 : ウィンドウの名前
        Window(const std::string& name);


        // ウィンドウハンドルゲッター
        const HWND& GetHWND(void) const { return m_hwnd.value(); }
        // ウィンドウハンドルセッター
        void SetHWND(HWND in) { m_hwnd.emplace(in); }

        // ウィンドウサイズゲッター
        const Eigen::Array2<int>& GetWindSize(void) const { return m_windowSize; }
        // ウィンドウサイズセッター
        void SetWindSize(const Eigen::Array2<int>& in) { m_windowSize = in; }


    protected:
        std::string m_name;               // ウィンドウの名前 
        std::optional<HWND> m_hwnd;       // ウィンドウハンドル
        Eigen::Array2<int>  m_windowSize; // ウィンドウのサイズ
    };
}


#endif // !I_WINDOW_H
