#include <EngineLibrary/UserComponent.h>


//----- UserBaseComponent ��`
namespace EtherEngine {
    // Inspector�\��
    void UserBaseComponent::DrawInspector(void) {
        using namespace System::Reflection;

        //----- �ϐ��錾
        System::Type^ thisType = GetType();

        //----- ���O���͗��ƃA�N�e�B�ucheck



        //----- �S�Ă�Field���擾�A�o�͂���
        auto fields = thisType->GetFields(BindingFlags::NonPublic | BindingFlags::Public | BindingFlags::DeclaredOnly);

        //----- �o�͂���t�B�[���h�𔻒肷��
        for each (auto field in fields) {
            //----- �o�̓t���O�錾
            bool isOutput = false;

            //----- ���J���Ă��邩����
            isOutput = field->IsPublic;

            //----- �w��̑������擾�ł��邩
            auto attributes = field->GetCustomAttributes(true);
            for each (auto attribute in attributes) {
                if (isOutput) {
                    //----- Public���B����J������
                    if (attribute->GetType() == System::Type::GetType("EtherEngineNonSerializeAttribute")) {
                        //----- ��`����Ă���B���̃��[�v���I��
                        isOutput = false;
                        break;
                    }
                }
                else {
                    //----- ��Public���B���J������
                    if (attribute->GetType() == System::Type::GetType("EtherEngineSerializeAttribute")) {
                        //----- ��`����Ă���B���̃��[�v���I��
                        isOutput = true;
                        break;
                    }
                }
            }

            //----- ���J����̂ł����Inspector�\��
            // @ MEMO : ��Ŋ֐���
            do {
                // int
                if (field->GetType() == int::typeid) {
                    auto number = safe_cast<int>(field->GetValue(nullptr));
                    ImGuiFunction::ShowNumber<int>(number, ManageToUn(field->Name));
                    field->SetValue(nullptr, number);
                    break;
                }
                // uint
                if (field->GetType() == uint::typeid) {
                    auto number = safe_cast<uint>(field->GetValue(nullptr));
                    ImGuiFunction::ShowNumber<uint>(number, ManageToUn(field->Name));
                    field->SetValue(nullptr, number);
                    break;
                }
                // ullint
                if (field->GetType() == ullint::typeid) {
                    auto number = safe_cast<ullint>(field->GetValue(nullptr));
                    ImGuiFunction::ShowNumber<ullint>(number, ManageToUn(field->Name));
                    field->SetValue(nullptr, number);
                    break;
                }
                // float
                if (field->GetType() == float::typeid) {
                    auto number = safe_cast<float>(field->GetValue(nullptr));
                    ImGuiFunction::ShowNumber<float>(number, ManageToUn(field->Name));
                    field->SetValue(nullptr, number);
                    break;
                }
                // double
                if (field->GetType() == double::typeid) {
                    auto number = safe_cast<double>(field->GetValue(nullptr));
                    ImGuiFunction::ShowNumber<double>(number, ManageToUn(field->Name));
                    field->SetValue(nullptr, number);
                    break;
                }
                // string
                // @ MEMO : �����s�g�p�����Ή��\��
                if (field->GetType() == System::String::typeid) {
                    auto str = ManageToUn(safe_cast<System::String^>(field->GetValue(nullptr)));
                    ImGuiFunction::ImGuiShow<std::string>(str, ManageToUn(field->Name));
                    field->SetValue(nullptr, UnToManage(str));
                    break;
                }
                // Array
                // @ MEMO : ���
                if (field->GetType() == System::Array::typeid) {

                }
            } while (false);
        }
    }
}
