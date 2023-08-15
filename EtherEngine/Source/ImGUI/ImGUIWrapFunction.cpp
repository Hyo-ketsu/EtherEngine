#include <ImGUI/ImGUIWrapFunction.h>


//----- 各型表示関数
namespace EtherEngine {
    namespace ImGuiFunction {
        // 文字列表示
        bool ImGuiShow(std::string& numberParam, const std::string& message, const bool& isMulti) {
            //----- 変数宣言
            // @ MEMO : 仮値。後で調整
            char input[1024];
            bool isSelect = false;
            strcpy_s(input, sizeof(input), numberParam.c_str());

            //----- 表示
            if (isMulti) {
                isSelect = ImGui::InputTextMultiline(message.c_str(), input, sizeof(input));
            }
            else {
                isSelect = ImGui::InputText(message.c_str(), input, sizeof(input));
            }

            //----- 再代入
            numberParam = input;
            return isSelect;
        }
    }
}
