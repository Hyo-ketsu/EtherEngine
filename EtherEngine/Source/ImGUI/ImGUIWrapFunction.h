#ifndef I_IMGUIWRAPFUNCTION_H
#define I_IMGUIWRAPFUNCTION_H
#include <Base/ConceptUtility.h>
#include <Base/EtherEngineUtility.h>
#include <ImGUI/imgui.h>


//----- 各型表示関数 定義
namespace EtherEngine {
    namespace ImGuiFunction {
        // パラメーター表示
        // @ Memo : vectorやlist等は未対応
        // @ Ret  : 値が変更されたか
        // @ Arg1 : 表示・変更する変数(参照)
        // @ Arg2 : 表示文字列
        template <typename Type>
        bool ImGuiShow(Type& numberParam, const std::string& message);
        // 文字列表示
        // @ Ret  : 値が変更されたか
        // @ Arg1 : 表示・変更する文字列(参照)
        // @ Arg2 : 表示文字列
        // @ Arg3 : 複数行使用するか
        bool ImGuiShow(std::string& numberParam, const std::string& message, const bool& isMulti);


        // 数値型をImGuiウィンドウに表示する関数
        // @ Ret  : 値が変更されたか
        // @ Arg1 : 表示・変更する変数(参照)
        // @ Arg2 : 表示文字列
        template <Concept::ArithmeticConcept NumberType>
        bool ShowNumber(NumberType& numberParam, const std::string& message);


        // Vector・List表示
        // @ Ret  : 値が変更されたか
        // @ Arg1 : 表示・変更する変数(参照)
        // @ Arg2 : 表示文字列
        // @ Arg3 : リスト名文字列
        template <typename Type, template<class> typename ArrayType>
        requires
        Concept::SameConcept<ArrayType<Type>, std::vector<Type>> ||
        Concept::SameConcept<ArrayType<Type>, std::list<Type>> || 
        std::is_constructible_v<Type>
        bool ShowArray(ArrayType<Type>& arrayParam, const std::string& message, const std::string& listName);
        // Array表示
        // @ Ret  : 値が変更されたか
        // @ Arg1 : 表示・変更する変数(参照)
        // @ Arg2 : 表示文字列
        // @ Arg3 : リスト名文字列
        template <typename Type, size_t Size, template<class, int> typename ArrayType>
        requires
        Concept::SameConcept<ArrayType<Type, Size>, std::array<Type, Size>> ||
        std::is_constructible_v<Type>
        bool ShowArray(ArrayType<Type, Size>& arrayParam, const std::string& message, const std::string& listName);


        // @ MEMO : 参照入力は後回し
    }
}


//----- 各型表示関数 定義
namespace EtherEngine {
    namespace ImGuiFunction {
        // パラメーター表示
        template <typename Type>
        bool ImGuiShow(Type& numberParam, const std::string& message) {
            //----- 指定の型以外の場合はエラーを出力
            static_assert(
                Concept::BaseOfConcept<Type, IInspectorShow> ||
                Concept::ArithmeticConcept<Type> ||
                Concept::SameConcept<Type, std::string>
                , "Error! The type cannot be used with ImGuiShow");

            //----- 表示
            if constexpr (Concept::BaseOfConcept<Type, IInspectorShow>) {
                //----- 独自型表示
                numberParam.ShowInspector();
            }
            else if constexpr (Concept::ArithmeticConcept<Type>) {
                //----- 数値表示
                ShowNumber(numberParam, message);
            }
            else if constexpr (Concept::SameConcept<Type, std::string>) {
                //----- 文字列表示（ただ、単一行で表現するものとする）
                return ImGuiShow(numberParam, message, false);
            }
        }


        // 数値型をImGuiウィンドウに表示する関数
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


        // Vector・List表示
        template <typename Type, template<class> typename ArrayType>
            requires
        Concept::SameConcept<ArrayType<Type>, std::vector<Type>> ||
        Concept::SameConcept<ArrayType<Type>, std::list<Type>>
        bool ShowArray(ArrayType<Type>& arrayParam, const std::string& message, const std::string& listName) {
            //----- 変数宣言
            bool isChange = false;

            ImGui::TreeNode(listName.c_str());
            {
                //----- リスト表示
                ImGui::BeginListBox(listName.c_str());
                {
                    for (auto&& it : arrayParam) {
                        isChange |= ImGuiShow(it, message.c_str());
                    }
                }
                ImGui::EndListBox();

                //----- 増減ボタン表示
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

            //----- 返却
            return isChange;
        }
        // Array表示
        template <typename Type, size_t Size, template<class, int> typename ArrayType>
            requires
        Concept::SameConcept<ArrayType<Type, Size>, std::array<Type, Size>>
        bool ShowArray(ArrayType<Type, Size>& arrayParam, const std::string& message, const std::string& listName) {
            //----- 変数宣言
            bool isChange = false;

            ImGui::TreeNode(listName.c_str());
            {
                //----- リスト表示
                ImGui::BeginListBox(listName.c_str());
                {
                    for (auto&& it : arrayParam) {
                        isChange |= ImGuiShow(it, message.c_str());
                    }
                }
                ImGui::EndListBox();
            }

            //----- 返却
            return isChange;
        }
    }
}

#endif // !I_IMGUIWRAPFUNCTION_H
