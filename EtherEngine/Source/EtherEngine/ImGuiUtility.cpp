#include <EtherEngine/ImGuiUtility.h>
#include <EtherEngine/EditorDefine.h>


namespace EtherEngine {
    namespace ImGuiUtility {
        // �������\���\��Selectable
        bool BlankSelectable(const std::string& label, bool selected, ImGuiSelectableFlags flags, const ImVec2& size_arg) {
            return ImGui::Selectable(label == "" ? " " : label.c_str(), selected, flags, size_arg);
        }
        // �������\���\��Selectable
        bool BlankSelectable(const std::string& label, bool* selected, ImGuiSelectableFlags flags, const ImVec2& size_arg) {
            return ImGui::Selectable(label == "" ? " " : label.c_str(), selected, flags, size_arg);
        }


        // �R���X�g���N�^
        RenameableSelectable::RenameableSelectable(void) 
            : m_isRename(false)
            , m_index(0) {
            m_inputText.fill('\0');
        }
        // �f�X�g���N�^
        RenameableSelectable::~RenameableSelectable(void) {
        }


        // ������̖��O�Q�b�^�[
        std::string RenameableSelectable::GetRename(void) const {
            if (m_isRename) throw std::exception("Error! Rename");
            return std::string(m_inputText.data());
        }
        // ���l�[���\��Selectable
        RenameableSelectableMessage RenameableSelectable::Show(const std::string& name, const uint index, const bool isSelect) {
            if (m_isRename && index == m_index) {
                //----- ���O����
                ImGui::Text("Rename... :"); 
                ImGui::SameLine();
                ImGui::InputText(" ", m_inputText.data(), m_inputText.size());
                if (m_focus) { ImGui::SetItemDefaultFocus(); }

                //----- ���l�[�������肵�ďI�����邩
                if (InputSystem::IsPress(EditorKey::INPUT_DECISION)) {
                    //----- ���l�[�����[�h�I��
                    m_isRename = false;

                    //----- �ԋp
                    return RenameableSelectableMessage::RenameDecision;
                }

                //----- ���l�[�����L�����Z�����邩
                if (InputSystem::IsPress(EditorKey::INPUT_CANCEL)) {
                    //----- ���l�[�����[�h�I��
                    m_isRename = false;

                    //----- �ύX���ꂽ���O��S��Clear
                    m_inputText.fill('\0');

                    //----- �ԋp
                    return RenameableSelectableMessage::RenameCancel;
                }

                //----- �ԋp
                return RenameableSelectableMessage::Rename;
            }
            else {
                //----- �ʏ��Selectable�\��
                auto ret = ImGuiUtility::BlankSelectable(name, isSelect);

                //----- F2���͂Ń��l�[��
                if (m_isRename == false && ImGui::IsItemFocused() && InputSystem::IsPress(EditorKey::INPUT_RENAME)) {
                    m_isRename = true;
                    m_index = index;
                    m_inputText.fill('\0');
                    // ������R�s�[
                    int i = 0;
                    for (auto&& it : m_inputText) {
                        if (i >= name.size()) break;
                        it = name[i];
                        i++;
                    }
                    m_focus = true;
                }

                //----- �ԋp
                return ret ? RenameableSelectableMessage::SelectYes : RenameableSelectableMessage::SelectNon;
            }
        }
    }
}
