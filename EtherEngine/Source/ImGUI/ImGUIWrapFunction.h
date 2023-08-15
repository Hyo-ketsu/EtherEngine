#ifndef I_IMGUIWRAPFUNCTION_H
#define I_IMGUIWRAPFUNCTION_H
#include <Base/ConceptUtility.h>
#include <Base/EtherEngineUtility.h>
#include <ImGUI/imgui.h>


//----- �e�^�\���֐� ��`
namespace EtherEngine {
    namespace ImGuiFunction {
        // �p�����[�^�[�\��
        // @ Memo : vector��list���͖��Ή�
        // @ Ret  : �l���ύX���ꂽ��
        // @ Arg1 : �\���E�ύX����ϐ�(�Q��)
        // @ Arg2 : �\��������
        template <typename Type>
        bool ImGuiShow(Type& numberParam, const std::string& message);
        // ������\��
        // @ Ret  : �l���ύX���ꂽ��
        // @ Arg1 : �\���E�ύX���镶����(�Q��)
        // @ Arg2 : �\��������
        // @ Arg3 : �����s�g�p���邩
        bool ImGuiShow(std::string& numberParam, const std::string& message, const bool& isMulti);


        // ���l�^��ImGui�E�B���h�E�ɕ\������֐�
        // @ Ret  : �l���ύX���ꂽ��
        // @ Arg1 : �\���E�ύX����ϐ�(�Q��)
        // @ Arg2 : �\��������
        template <Concept::ArithmeticConcept NumberType>
        bool ShowNumber(NumberType& numberParam, const std::string& message);


        // Vector�EList�\��
        // @ Ret  : �l���ύX���ꂽ��
        // @ Arg1 : �\���E�ύX����ϐ�(�Q��)
        // @ Arg2 : �\��������
        // @ Arg3 : ���X�g��������
        template <typename Type, template<class> typename ArrayType>
        requires
        Concept::SameConcept<ArrayType<Type>, std::vector<Type>> ||
        Concept::SameConcept<ArrayType<Type>, std::list<Type>> || 
        std::is_constructible_v<Type>
        bool ShowArray(ArrayType<Type>& arrayParam, const std::string& message, const std::string& listName);
        // Array�\��
        // @ Ret  : �l���ύX���ꂽ��
        // @ Arg1 : �\���E�ύX����ϐ�(�Q��)
        // @ Arg2 : �\��������
        // @ Arg3 : ���X�g��������
        template <typename Type, size_t Size, template<class, int> typename ArrayType>
        requires
        Concept::SameConcept<ArrayType<Type, Size>, std::array<Type, Size>> ||
        std::is_constructible_v<Type>
        bool ShowArray(ArrayType<Type, Size>& arrayParam, const std::string& message, const std::string& listName);


        // @ MEMO : �Q�Ɠ��͂͌��
    }
}


//----- �e�^�\���֐� ��`
namespace EtherEngine {
    namespace ImGuiFunction {
        // �p�����[�^�[�\��
        template <typename Type>
        bool ImGuiShow(Type& numberParam, const std::string& message) {
            //----- �w��̌^�ȊO�̏ꍇ�̓G���[���o��
            static_assert(
                Concept::BaseOfConcept<Type, IInspectorShow> ||
                Concept::ArithmeticConcept<Type> ||
                Concept::SameConcept<Type, std::string>
                , "Error! The type cannot be used with ImGuiShow");

            //----- �\��
            if constexpr (Concept::BaseOfConcept<Type, IInspectorShow>) {
                //----- �Ǝ��^�\��
                numberParam.ShowInspector();
            }
            else if constexpr (Concept::ArithmeticConcept<Type>) {
                //----- ���l�\��
                ShowNumber(numberParam, message);
            }
            else if constexpr (Concept::SameConcept<Type, std::string>) {
                //----- ������\���i�����A�P��s�ŕ\��������̂Ƃ���j
                return ImGuiShow(numberParam, message, false);
            }
        }


        // ���l�^��ImGui�E�B���h�E�ɕ\������֐�
        template <Concept::ArithmeticConcept NumberType>
        bool ShowNumber(NumberType& numberParam, const std::string& message) {
            if constexpr (Concept::SameConcept<NumberType, int>) {
                return ImGui::InputInt(message.c_str(), &numberParam);
            }
            else if constexpr (Concept::SameConcept<NumberType, uint>) {
                return ImGui::InputInt(message.c_str(), (int*)&numberParam);
            }
            else if constexpr (Concept::SameConcept<NumberType, llint>) {
                return ImGui::InputInt(message.c_str(), (int*)&numberParam);
            }
            else if constexpr (Concept::SameConcept<NumberType, ullint>) {
                return ImGui::InputInt(message.c_str(), (int*)&numberParam);
            }
            else if constexpr (Concept::SameConcept<NumberType, float>) {
                return ImGui::InputFloat(message.c_str(), &numberParam);
            }
            else if constexpr (Concept::SameConcept<NumberType, double>) {
                return ImGui::InputDouble(message.c_str(), &numberParam);
            }
        }


        // Vector�EList�\��
        template <typename Type, template<class> typename ArrayType>
            requires
        Concept::SameConcept<ArrayType<Type>, std::vector<Type>> ||
        Concept::SameConcept<ArrayType<Type>, std::list<Type>>
        bool ShowArray(ArrayType<Type>& arrayParam, const std::string& message, const std::string& listName) {
            //----- �ϐ��錾
            bool isChange = false;

            ImGui::TreeNode(listName.c_str());
            {
                //----- ���X�g�\��
                ImGui::BeginListBox(listName.c_str());
                {
                    for (auto&& it : arrayParam) {
                        isChange |= ImGuiShow(it, message.c_str());
                    }
                }
                ImGui::EndListBox();

                //----- �����{�^���\��
                if (ImGui::Button("+")) {
                    arrayParam.emplace_back();
                    isChange = true;
                }
                ImGui::SameLine();
                if (ImGui::Button("-")) {
                    arrayParam.erase(arrayParam.end());
                    isChange = true;
                }
            }

            //----- �ԋp
            return isChange;
        }
        // Array�\��
        template <typename Type, size_t Size, template<class, int> typename ArrayType>
            requires
        Concept::SameConcept<ArrayType<Type, Size>, std::array<Type, Size>>
        bool ShowArray(ArrayType<Type, Size>& arrayParam, const std::string& message, const std::string& listName) {
            //----- �ϐ��錾
            bool isChange = false;

            ImGui::TreeNode(listName.c_str());
            {
                //----- ���X�g�\��
                ImGui::BeginListBox(listName.c_str());
                {
                    for (auto&& it : arrayParam) {
                        isChange |= ImGuiShow(it, message.c_str());
                    }
                }
                ImGui::EndListBox();
            }

            //----- �ԋp
            return isChange;
        }
    }
}

#endif // !I_IMGUIWRAPFUNCTION_H
