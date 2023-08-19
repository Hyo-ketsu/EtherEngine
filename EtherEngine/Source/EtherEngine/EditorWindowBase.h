#ifndef I_EDITORWINDOWBASE_H
#define I_EDITORWINDOWBASE_H
#include <EtherEngine/EditorObject.h>
#include <EtherEngine/EditorComponentBase.h>


//----- EditorWindowBase 宣言
namespace EtherEngine {
    // エディターのウィンドウの抽象クラス
    class EditorWindowBase : public EditorComponentBase {
    public:
        // コンストラクタ
        // @ Arg1 : 親となるエディターオブジェクト
        // @ Arg2 : ウィンドウ名
        // @ Arg3 : フラグ設定(Default : 何も設定しない)
        EditorWindowBase(EditorObject* editorObject, const std::string& name, const ImGuiBackendFlags& flag = ImGuiBackendFlags_None);


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
        // 表示するかアクセサー
        bool& AccessIsOpen(void) { return m_isOpen; }

        // 表示フラグゲッター
        ImGuiWindowFlags GetFlags(void) const { return m_flags; }
        // 表示フラグセッター
        void SetFlags(const ImGuiWindowFlags& in) { m_flags = in; }
        // 表示フラグアクセサー
        ImGuiWindowFlags& AccessFlags(void) { return m_flags; }


        // 描画処理
        virtual void Draw(void) override;
        // サブクラス用描画処理
        virtual void DrawWindow(void) {}


        // 外部出力
        Json Output(void) override { return Json(); }
        // 外部入力
        void Input(const Json& input) override {}
        // Inspector表示
        void ShowInspector(void) override {}


    protected:
        std::string m_name; // 表示名
        bool m_isOpen;      // 表示するか
        ImGuiWindowFlags m_flags;  // 表示フラグ
    };
}


#endif // !#define I_EDITORWINDOWBASE_H
