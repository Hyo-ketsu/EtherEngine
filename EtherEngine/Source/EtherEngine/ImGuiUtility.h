#ifndef I_IMGUIUTILITY_H
#define I_IMGUIUTILITY_H


//----- ImGui�p�֗̕��֐�
namespace EtherEngine {
    //----- Selectable�֘A�̒�`
    namespace ImGuiUtility {
        // �������\���\��Selectable
        bool BlankSelectable(const std::string& label, bool selected = false, ImGuiSelectableFlags flags = 0, const ImVec2& size_arg = {0,0});
        // �������\���\��Selectable
        bool BlankSelectable(const std::string& label, bool* selected, ImGuiSelectableFlags flags = 0, const ImVec2& size_arg = {0,0});


        // �֐�����̃��b�Z�[�W
        enum class RenameableSelectableMessage {
            SelectNon = 0,  // �I������Ă��Ȃ�
            SelectYes,      // �I�����ꂽ
            Rename,         // ���l�[�����[�h
            RenameDecision, // ���l�[�����s��ꂽ
            RenameCancel,   // ���l�[�����L�����Z�����ꂽ
        };

        // ���l�[���\��Selectable��\������N���X
        class RenameableSelectable {
        public:
            // �R���X�g���N�^
            // @ Arg1 : 
            RenameableSelectable(void);
            // �f�X�g���N�^
            ~RenameableSelectable(void);
            // �R�s�[�R���X�g���N�^
            RenameableSelectable(const RenameableSelectable& copy) = delete;
            // ���[�u�f�X�g���N�^
            RenameableSelectable(RenameableSelectable&& move) = delete;


            // ������̖��O�Q�b�^�[
            // @ Exce : ������
            std::string GetRename(void) const;
            // ���͒��Q�b�^�[
            bool GetIsRename(void) const { return m_isRename; }


            // ���l�[���\��Selectable
            // @ Ret  : �֐�����̃��b�Z�[�W
            // @ Memo : ������̖��O��GetRename�Ŏ擾���ĉ������B
            // @ Arg1 : �\���E�ύX��
            // @ Arg2 : �C���f�b�N�X
            // @ Arg3 : �I������Ă��邩
            RenameableSelectableMessage Show(const std::string& name, const uint index, const bool isSelect);

        private:
            std::array<char, 256> m_inputText;  // ���͉�����
            bool m_isRename; // ���ݓ��͒���
            uint m_index;    // ���O�ύX�����Ă���C���f�b�N�X
        };
        
    }
}


#endif // !I_IMGUIUTILITY_H
