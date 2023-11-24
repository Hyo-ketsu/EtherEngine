#include <Base/EditorException.h>


//----- EditorException 定義
namespace EtherEngine {
    // コンストラクタ
    EditorException::EditorException(const std::string in, const EditorException* const exception, std::source_location source) noexcept {
        //----- 例外メッセージ構築
        std::string message = in + '\n';
        message += " Line : " + std::to_string(source.line()) + '\n';
        message += " File : " + std::string(source.file_name()) + '\n';
        message += " Function : " + std::string(source.function_name()) + '\n';

        //----- 例外追加
        m_errorMessage = message;

        //----- 前スタックの例外を追加
        if (exception == nullptr) return;
        m_exceptions.push_back(*exception);
        for (auto&& exception : exception->m_exceptions) {
            m_exceptions.push_back(exception);
        }
    }
    // デストラクタ
    EditorException::~EditorException(void) {
    }


    // インデックス付きで例外メッセージを取得する
    std::optional<std::string> EditorException::GetErrorMessage(uint index) const noexcept {
        //----- 0なら自身のメッセージを返却
        if (index == 0) return m_errorMessage;

        //----- 1インデックスを0インデックスに戻す
        index--;

        //----- 範囲外参照を行っていないか
        if (index >= m_exceptions.size()) return std::optional<std::string>();

        //----- 範囲内。返却する
        return m_exceptions[index].GetErrorMessage();
    }
    // 自身の例外メッセージを取得する
    std::string EditorException::GetErrorMessage(void) const noexcept {
        return m_errorMessage;
    }
}
