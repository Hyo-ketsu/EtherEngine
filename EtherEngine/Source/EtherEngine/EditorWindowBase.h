#ifndef I_EDITORWINDOWBASE_H
#define I_EDITORWINDOWBASE_H
#include <EtherEngine/EditorObject.h>
#include <EtherEngine/EditorComponentBase.h>


//----- EditorWindow用宣言
namespace EtherEngine {
    // ウィンドウのサイズ等の設定
    enum class EditorWindowSizeType {
        AutoSizeFixed = 0,      // 自動サイズで固定
        AutoSizeFluctuation,    // 自動サイズで変動可（自動サイズを最低値として保証する形）
        // @ MEMO : 気が向けば実装する //SemiAutoSize,           // AutoSizeFluctuationに加え、規定値を設定する。規定値より大きくなることはない
        ManualSize,             // 手動サイズ
    };
}




//----- EditorWindowBase 宣言
namespace EtherEngine {
    // エディターのウィンドウの抽象クラス
    // @ Memo : 同名ウィンドウが存在する際、後ろに空白を追加することで見かけ上の複数ウィンドウを表現しています
    // @ Memo : このオブジェクトのTransformは、以下を想定しています。
    // @ Memo : 座標 : 0,0が画面中央。-1,-1は左上方向
    // @ Memo : 拡縮 : 1ピクセル
    class EditorWindowBase : public EditorComponentBase {
    public:
        // コンストラクタ
        // @ Arg1 : 親となるエディターオブジェクト
        // @ Arg2 : ウィンドウ名
        // @ Arg3 : 親エディターオブジェクトのTransformを使用するか(Default : 使用する)
        // @ Arg4 : フラグ設定(Default : 何も設定しない)
        // @ Arg5 : ウィンドウサイズ設定(Default : 手動)
        // @ Arg6 : 初期ウィンドウサイズ(Default : 0,0)
        EditorWindowBase(EditorObject* editorObject, const std::string& name, const bool isUseTransform = true, const ImGuiWindowFlags& flag = ImGuiWindowFlags_None,
            const EditorWindowSizeType& sizeType = EditorWindowSizeType::ManualSize, const Eigen::Vector2f& windowSize = { 0.0f,0.0f });


        // 表示名ゲッター
        const std::string& GetName(void) const { return m_name; }
        // 表示名セッター
        void SetName(const std::string& in) { m_name = in; }
        // 表示名アクセサー
        std::string& AccessName(void) { return m_name; }

        // 表示するかゲッター
        bool GetIsOpen(void) const { return m_isOpen; }
        // 表示するかセッター
        void SetIsOpen(const bool in) { m_isOpen = in; }

        // Transform使用ゲッター
        bool GetIsUseTransform(void) const { return m_isUseTranform; }
        // Transform使用セッター
        void SetIsUseTransform(const bool in) { m_isUseTranform = in; }

        // 表示フラグゲッター
        ImGuiWindowFlags GetFlags(void) const { return m_flags; }
        // 表示フラグセッター
        void SetFlags(const ImGuiWindowFlags& in) { m_flags = in; }
        // 表示フラグアクセサー
        ImGuiWindowFlags& AccessFlags(void) { return m_flags; }


        // 初期化処理
        void Start(void) override;
        // サブクラス用初期化処理
        virtual void StartWindow(void) {}
        // 削除処理
        void Delete(void) override;
        // サブクラス用削除処理
        virtual void DeleteWindow(void) {}
        // 更新処理
        virtual void Update(void) override;
        // サブクラス用更新処理
        virtual void UpdateWindow(void) {}
        // 描画処理
        virtual void Draw(void) override;
        // サブクラス用描画処理
        virtual void DrawWindow(void) {}


        // ウィンドウ描画後に行う処理
        void DrawLateWindow(void);


        // 外部出力
        Json Output(void) override { return Json(); }
        // 外部入力
        void Input(const Json& input) override {}
        // Inspector表示
        void ShowInspector(void) override {}

    protected:
        std::string m_name;     // 表示名
        bool m_isOpen;          // 表示するか
        bool m_isUseTranform;   // ウィンドウ位置に所属エディターオブジェクトのTransformを使用するか
        ImGuiWindowFlags m_flags;     // 表示フラグ
        EditorWindowSizeType m_sizeType;    // サイズ設定
        std::optional<Transform> m_prevTransform;    // エディターオブジェクトの過去座標
        static std::unordered_map<std::string, uint> ms_windowCount; // ウィンドウの使用数
    };
}


#endif // !#define I_EDITORWINDOWBASE_H
