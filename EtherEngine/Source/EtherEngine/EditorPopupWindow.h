#ifndef I_EDITORPOPUPWINDOW_H
#define I_EDITORPOPUPWINDOW_H
#include <EtherEngine/EditorWindowBase.h>
#include <EtherEngine/EditorObjectStorage.h>


//----- Popup各種クラス定義
namespace EtherEngine {
    // ウィンドウの制御
    // @ Memo : それぞれ、メインウィンドウ処理、メインウィンドウ削除、ImGuiウィンドウ削除
    enum class EditorPopupControl {
        All = 0,        // すべて許可
        Window,         // ウィンドウ処理のみ許可
        WindowClose,    // ウィンドウ削除のみ許可
        ImGuiClose,     // ImGuiウィンドウのみ削除許可
        Close,          // 両ウィンドウ削除のみ許可
        None,           // すべて不許可
    };
    // どのメッセージポップアップを作成するか
    enum class EditorMessagePopupType {
        Ok = 0,         // Ok ボタンのみ表示
        YesNo,          // Yes,No ボタンのみ表示
        YesNoCancel,    // Yes,No,Cancel ボタン表示
    };
    // メッセージポップアップ結果
    enum class EditorMessagePopupResultType {
        None = 0,   // 現状なにも押されていない
        OkYes,      // Ok 若しくは Yes ボタン押下
        No,         // No ボタン押下
        Cancel,     // Cancel ボタン押下
    };


    using EditorMessagePopupResult = std::shared_ptr<EditorMessagePopupResultType>;
}




//----- EditorPopupWindow 宣言
namespace EtherEngine {
    class EditorPopupWindow : public EditorWindowBase {
    public:
        // コンストラクタ
        // @ Arg1 : 親となるエディターオブジェクト
        // @ Arg2 : ウィンドウ名
        // @ Arg3 : ウィンドウでの制御(Default : ウィンドウ処理、ウィンドウ&ImGuiウィンドウxボタン非表示)
        // @ Arg4 : ウィンドウサイズ(Default : 負数)
        // @ Arg5 : フラグ設定(Default : 何も設定しない)
        EditorPopupWindow(EditorObject* editorObject, const std::string& name, const EditorPopupControl popupControl,
            const Eigen::Vector2i & = { -1,-1 }, const ImGuiWindowFlags& flag = ImGuiWindowFlags_None);

    private:
        void UpdateWindow(void) override;
        void DeleteWindow(void) override;
        void Draw(void) override;

        EditorPopupControl m_popupControl;   // x ボタンを表示するか
        bool m_isWindowFunction;    // Windowの処理を行うか
    };
}




//----- EditorMessagePopup 定義
namespace EtherEngine {
    // メッセージポップアップを表示する
    // @ Temp : どの表示タイプか(Default : Okボタンのみ表示)
    // @ Memo : どのボタンが押されたかの結果が欲しい場合、コンストラクタの第4引数に取得用の変数を渡してください。
    // @ MEMO : 現状「ウィンドウ機能を抑制するポップアップを複数出し、どれかが解放される」と残ってるのにもかかわらずウィンドウ機能を使用できます。要修正
    template <EditorMessagePopupType Type = EditorMessagePopupType::Ok>
    class EditorMessagePopup : public EditorPopupWindow {
    public:
        // コンストラクタ
        // @ Arg1 : 親となるエディターオブジェクト
        // @ Arg2 : ウィンドウ名
        // @ Arg3 : 表示メッセージ
        // @ Arg4 : 結果(Default : 結果を取得しない)
        // @ Arg5 : ウィンドウサイズ(Default : 負数)
        EditorMessagePopup(EditorObject* editorObject, const std::string& name, const std::string& message, const EditorMessagePopupResult& result = nullptr);


        void DrawWindow(void) override;

    protected:
        std::string m_message;  // 表示メッセージ
        std::weak_ptr<EditorMessagePopupResultType> m_result;   // 結果出力先
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
        : EditorPopupWindow(editorObject, name, EditorPopupControl::None, {600,400}, ImGuiWindowFlags_NoCollapse)
        , m_message(message) 
        , m_result(result == nullptr ? decltype(m_result)() : decltype(m_result)(result)) {
        //----- 念のための Result 初期化
        if (m_result.expired() == false) {
            *m_result.lock() = EditorMessagePopupResultType::None;
        }
    }
    template <EditorMessagePopupType Type>
    void EditorMessagePopup<Type>::DrawWindow(void) {
        //----- 変数宣言
        bool isButtonPush = false;  // いずれかのボタンが押されたか

        //----- テキスト表示
        ImGui::Text(m_message.c_str());

        //----- 各種ボタン表示
        // @ Memo : Okボタンから順に表示
        do {
            //----- リザルト出力先が存在するか
            bool hasResult = !(m_result.expired());

            //----- OkまたはYes表示
            auto decisionButtonMessage = Type == EditorMessagePopupType::Ok ? "OK" : "Yes";
            if (ImGui::Button(decisionButtonMessage)) {
                if (hasResult) *m_result.lock() = EditorMessagePopupResultType::OkYes;
                isButtonPush = true;
                break;
            }

            //----- Noボタン表示
            // @ Memo : 以下、表示しないのであれば即 break する
            if constexpr (Type == EditorMessagePopupType::Ok) break;
            ImGui::SameLine();
            if (ImGui::Button("No")) {
                if (hasResult) *m_result.lock() = EditorMessagePopupResultType::No;
                isButtonPush = true;
                break;
            }

            //----- Cancelボタン表示
            if constexpr (Type == EditorMessagePopupType::YesNo) break;
            ImGui::SameLine();
            if (ImGui::Button("Cancel")) {
                if (hasResult) *m_result.lock() = EditorMessagePopupResultType::Cancel;
                isButtonPush = true;
                break;
            }
        } while (false);

        //----- 何かボタンが押されていれば自身を削除する
        if (isButtonPush) {
            EditorObjectStorage::Get()->DeleteEditorObject(EditorComponentHelper::GetEditorObject(this)->GetHandle());
            return;
        }

        if (m_isOpen == false) {
            // @ MEMO : テストコード
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
