#ifndef I_EDITORPOPUPWINDOW_H
#define I_EDITORPOPUPWINDOW_H
#include <EtherEngine/EditorWindowBase.h>
#include <EtherEngine/EditorObjectStorage.h>


//----- Popup各種クラス定義
namespace EtherEngine {
    // どのメッセージポップアップを作成するか
    enum class EditorMessagePopupType {
        Ok,             // Ok ボタンのみ表示
        YesNo,          // Yes,No ボタンのみ表示
        YesNoCancel,    // Yes,No,Cancel ボタン表示
    };
    // メッセージポップアップ結果
    enum class EdtiorMessagePopupResult {
        Non,        // 現状なにも押されていない
        OkYes,      // Ok 若しくは Yes ボタン押下
        No,         // No ボタン押下
        Cancel,     // Cancel ボタン押下
    };


    using EditorMessagePopupResult = std::shared_ptr<EdtiorMessagePopupResult>;
}




//----- EditorPopupWindow 宣言
namespace EtherEngine {
    class EditorPopupWindow : public EditorWindowBase {
    public:
        // コンストラクタ
        // @ Arg1 : 親となるエディターオブジェクト
        // @ Arg2 : ウィンドウ名
        // @ Arg3 : 右上のウィンドウの x  ボタンを表示するか
        // @ Arg4 : フラグ設定(Default : 何も設定しない)
        EditorPopupWindow(EditorObject* editorObject, const std::string& name, const bool isCloseButton, const ImGuiBackendFlags& flag = ImGuiBackendFlags_None);

    private:
        void Update(void) override;
        void Draw(void) override;

        bool m_isCloseButton;   // x ボタンを表示するか
    };
}




//----- EditorMessagePopup 定義
namespace EtherEngine {
    // メッセージポップアップを表示する
    // @ Temp : どの表示タイプか(Default : Okボタンのみ表示)
    // @ Memo : どのボタンが押されたかの結果が欲しい場合、コンストラクタの第4引数に取得用の変数を渡してください。
    template <EditorMessagePopupType Type = EditorMessagePopupType::Ok>
    class EditorMessagePopup : public EditorPopupWindow {
    public:
        // コンストラクタ
        // @ Arg1 : 親となるエディターオブジェクト
        // @ Arg2 : ウィンドウ名
        // @ Arg3 : 表示メッセージ
        // @ Arg4 : 結果(Default : 結果を取得しない)
        EditorMessagePopup(EditorObject* editorObject, const std::string& name, const std::string& message, const EditorMessagePopupResult& result = nullptr);


        void DrawWindow(void) override;

    protected:
        std::string m_message;  // 表示メッセージ
        std::weak_ptr<EdtiorMessagePopupResult> m_result;   // 結果出力先
    };
}




//----- ポップアップウィンドウ便利関数 宣言
namespace EtherEngine {
    // ポップアップウィンドウを簡単に作成する
    // @ Temp : 生成するポップアップウィンドウの型
    // @ Temps: 与える引数の型
    // @ Args : 与える引数
    template <Concept::SubClassOnly<EditorPopupWindow> PopupType, typename ...ArgsType>
    BaseHandle<EditorObject> CreatePopWindow(ArgsType ...args);
}




//----- EditorMessagePopup 定義
namespace EtherEngine {
    // コンストラクタ
    template <EditorMessagePopupType Type>
    EditorMessagePopup<Type>::EditorMessagePopup(EditorObject* editorObject, const std::string& name, const std::string& message, const EditorMessagePopupResult& result)
        : EditorPopupWindow(editorObject, name, true)   // @ MEMO : trueは仮うち
        , m_message(message) 
        , m_result(result == nullptr ? decltype(m_result)() : decltype(m_result)(result)) {
    }
    template <EditorMessagePopupType Type>
    void EditorMessagePopup<Type>::DrawWindow(void) {
        ImGui::Text(m_message.c_str());
        if (m_isOpen == false) {
            int hoge = 1;
        }
    }
}




//----- ポップアップウィンドウ便利関数 定義
namespace EtherEngine {
    // ポップアップウィンドウを簡単に作成する
    // @ Temp : 生成するポップアップウィンドウの型
    // @ Temps: 与える引数の型
    // @ Args : 与える引数
    template <Concept::SubClassOnly<EditorPopupWindow> PopupType, typename ...ArgsType>
    BaseHandle<EditorObject> CreatePopWindow(ArgsType ...args) {
        auto gameObject = EditorObjectStorage::Get()->CreateEditorObject();
        gameObject.GetAtomicData().AddComponent<PopupType>(args...);
        return gameObject;
    }
}

#endif // !I_EDITORPOPUPWINDOW_H
