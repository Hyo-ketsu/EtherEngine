#ifndef I_EDITORPROGRESSBAR_H
#define I_EDITORPROGRESSBAR_H
#include <EtherEngine/EditorPopupWindow.h>


//----- 進捗クラス 宣言
namespace EtherEngine {
    // プログレスバーを表現するクラス
    // @ Memo : 最小値は 0 の決め打ちです
    class ProgressClass {
    public:
        // コンストラクタ
        // @ Arg1 : 現在の進捗
        // @ Arg2 : 進捗の最大値(Default : 1.0f)
        ProgressClass(const float progress, const float max = 1.0f);


        // 進捗アクセサー
        float& AccessProgress(void) { return m_progress; }

        // 最大値ゲッター
        float GetMax(void) const { return m_max; }
        // 最大値アクセサー
        float& AccessMax(void) { return m_max; }


        // 進捗を取得する
        // @ Ret  : 進捗(0.0f ~ 1.0f)
        float GetProgress(void) const;
        // 終了したか
        // @ Ret  : 終了したか
        bool IsEnd(void) const;

    private:
        float m_progress;   // 現在の進捗
        float m_max;        // 進捗の最大値
    };


    using Progress = std::weak_ptr<ProgressClass>;
}




//----- EditorProgressBar 宣言
namespace EtherEngine {
    // プログレスバーを表示するポップアップウィンドウ
    // @ Memo : 進捗が完了、または進捗の管理元が消滅次第終了します。
    class EditorProgressBar : public EditorPopupWindow {
    public:
        // コンストラクタ　
        // @ Arg1 : エディターオブジェクト
        // @ Arg2 : 表示メッセージ
        // @ Arg3 : 進捗
        // @ Arg4 : 終了時音を鳴らすか(Default : true)
        EditorProgressBar(EditorObject* editorObject, const std::string& message, Progress progress, const bool isSound = true);


        void DrawWindow(void) override;

    private:
        // プログレスバーを削除する
        void WindowKill(void);

        std::string m_message;  // 表示メッセージ
        Progress m_progress;    // 管理している進捗
        bool m_isSound;         // 終了時通知音を鳴らすか
    };
}


#endif // !I_EDITORPROGRESSBAR_H
