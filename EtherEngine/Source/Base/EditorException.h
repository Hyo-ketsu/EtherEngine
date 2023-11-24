#ifndef I_EDITOREXCEPTION_H
#define I_EDITOREXCEPTION_H
#include <Base/ConceptUtility.h>


//----- EditorException 宣言
namespace EtherEngine {
    // このエンジンでの例外クラス
    class EditorException {
    public:
        // コンストラクタ
        // @ Arg1 : 表示文字列(Default : "")
        // @ Arg2 : スタックトレース(Default : nullptr)
        // @ Arg3 : 例外発生個所(Default : 例外発生個所(Default推奨))
        EditorException(const std::string in = "", const EditorException* const exception = nullptr, std::source_location source = std::source_location::current()) noexcept;
        // デストラクタ
        ~EditorException(void);


        // インデックス付きで例外メッセージを取得する
        // @ Ret  : 取得した例外メッセージ
        // @ Arg1 : インデックス(0で自身のメッセージ取得)
        std::optional<std::string> GetErrorMessage(uint index) const noexcept;
        // 自身の例外メッセージを取得する
        // @ Ret  : 取得した例外メッセージ
        std::string GetErrorMessage(void) const noexcept;

    private:
        std::vector<EditorException> m_exceptions;  // スタックトレース
        std::string m_errorMessage;     // 自身が保持している例外
    };
}


#endif // !I_EDITOREXCEPTION_H
