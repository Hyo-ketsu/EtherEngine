#include <EngineLibrary/ConvertManage.h>


namespace EtherEngine {
    // 文字列変換
    std::string ManageToUnmanage::String(System::String^ manage) {
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

    // パス変換
    PathClass ManageToUnmanage::Path(PathString^ manage) {
        return PathClass(String(manage));
    }
}
