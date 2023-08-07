#include <C++CLI/C++CLIUtility.h>
// @ MEMO : w_cahrからcharにしているのでエラー起こすかも
     

//----- 文字列変換関数
namespace EtherEngine {
    // .NET文字列をC++文字列に変換する
    std::string ManageToUn(String^ manage) {
        //----- 宣言・取得
        std::string ret;
        auto wchars = manage->ToCharArray();

        //----- 確保
        ret.reserve(wchars->Length);

        //----- 変換
        for (int i = 0; i < wchars->Length; i++) {
            ret.push_back(static_cast<char>(wchars[i]));
        }

        return ret;
    }
    // C++文字列を.NET文字列に変換する
    String^ UnToManage(const std::string& un) {
        //----- 宣言
        String^ ret;

        //----- 変換
        ret = gcnew String(un.c_str());

        //----- 返却
        return ret;
    }
}
