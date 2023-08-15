#include <ImGUI/ImGUIWrapFunction.h>


//----- �e�^�\���֐�
namespace EtherEngine {
    namespace ImGuiFunction {
        // ������\��
        bool ImGuiShow(std::string& numberParam, const std::string& message, const bool& isMulti) {
            //----- �ϐ��錾
            // @ MEMO : ���l�B��Œ���
            char input[1024];
            bool isSelect = false;
            strcpy_s(input, sizeof(input), numberParam.c_str());

            //----- �\��
            if (isMulti) {
                isSelect = ImGui::InputTextMultiline(message.c_str(), input, sizeof(input));
            }
            else {
                isSelect = ImGui::InputText(message.c_str(), input, sizeof(input));
            }

            //----- �đ��
            numberParam = input;
            return isSelect;
        }
    }
}
