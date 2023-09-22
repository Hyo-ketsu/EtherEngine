#ifndef I_EDITORWINDOWBASE_H
#define I_EDITORWINDOWBASE_H
#include <EtherEngine/EditorObject.h>
#include <EtherEngine/EditorComponentBase.h>


//----- EditorWindow�p�錾
namespace EtherEngine {
    // �E�B���h�E�̃T�C�Y���̐ݒ�
    enum class EditorWindowSizeType {
        AutoSizeFixed = 0,      // �����T�C�Y�ŌŒ�
        AutoSizeFluctuation,    // �����T�C�Y�ŕϓ��i�����T�C�Y���Œ�l�Ƃ��ĕۏ؂���`�j
        // @ MEMO : �C�������Ύ������� //SemiAutoSize,           // AutoSizeFluctuation�ɉ����A�K��l��ݒ肷��B�K��l���傫���Ȃ邱�Ƃ͂Ȃ�
        ManualSize,             // �蓮�T�C�Y
    };
}




//----- EditorWindowBase �錾
namespace EtherEngine {
    // �G�f�B�^�[�̃E�B���h�E�̒��ۃN���X
    // @ Memo : �����E�B���h�E�����݂���ہA���ɋ󔒂�ǉ����邱�ƂŌ�������̕����E�B���h�E��\�����Ă��܂�
    // @ Memo : ���̃I�u�W�F�N�g��Transform�́A�ȉ���z�肵�Ă��܂��B
    // @ Memo : ���W : 0,0����ʒ����B-1,-1�͍������
    // @ Memo : �g�k : 1�s�N�Z��
    class EditorWindowBase : public EditorComponentBase {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �e�ƂȂ�G�f�B�^�[�I�u�W�F�N�g
        // @ Arg2 : �E�B���h�E��
        // @ Arg3 : �e�G�f�B�^�[�I�u�W�F�N�g��Transform���g�p���邩(Default : �g�p����)
        // @ Arg4 : �t���O�ݒ�(Default : �����ݒ肵�Ȃ�)
        // @ Arg5 : �E�B���h�E�T�C�Y�ݒ�(Default : �蓮)
        // @ Arg6 : �����E�B���h�E�T�C�Y(Default : 0,0)
        EditorWindowBase(EditorObject* editorObject, const std::string& name, const bool isUseTransform = true, const ImGuiWindowFlags& flag = ImGuiWindowFlags_None,
            const EditorWindowSizeType& sizeType = EditorWindowSizeType::ManualSize, const Eigen::Vector2f& windowSize = { 0.0f,0.0f });


        // �\�����Q�b�^�[
        const std::string& GetName(void) const { return m_name; }
        // �\�����Z�b�^�[
        void SetName(const std::string& in) { m_name = in; }
        // �\�����A�N�Z�T�[
        std::string& AccessName(void) { return m_name; }

        // �\�����邩�Q�b�^�[
        bool GetIsOpen(void) const { return m_isOpen; }
        // �\�����邩�Z�b�^�[
        void SetIsOpen(const bool in) { m_isOpen = in; }

        // Transform�g�p�Q�b�^�[
        bool GetIsUseTransform(void) const { return m_isUseTranform; }
        // Transform�g�p�Z�b�^�[
        void SetIsUseTransform(const bool in) { m_isUseTranform = in; }

        // �\���t���O�Q�b�^�[
        ImGuiWindowFlags GetFlags(void) const { return m_flags; }
        // �\���t���O�Z�b�^�[
        void SetFlags(const ImGuiWindowFlags& in) { m_flags = in; }
        // �\���t���O�A�N�Z�T�[
        ImGuiWindowFlags& AccessFlags(void) { return m_flags; }


        // ����������
        void Start(void) override;
        // �T�u�N���X�p����������
        virtual void StartWindow(void) {}
        // �폜����
        void Delete(void) override;
        // �T�u�N���X�p�폜����
        virtual void DeleteWindow(void) {}
        // �X�V����
        virtual void Update(void) override;
        // �T�u�N���X�p�X�V����
        virtual void UpdateWindow(void) {}
        // �`�揈��
        virtual void Draw(void) override;
        // �T�u�N���X�p�`�揈��
        virtual void DrawWindow(void) {}


        // �E�B���h�E�`���ɍs������
        void DrawLateWindow(void);


        // �O���o��
        Json Output(void) override { return Json(); }
        // �O������
        void Input(const Json& input) override {}
        // Inspector�\��
        void ShowInspector(void) override {}

    protected:
        std::string m_name;     // �\����
        bool m_isOpen;          // �\�����邩
        bool m_isUseTranform;   // �E�B���h�E�ʒu�ɏ����G�f�B�^�[�I�u�W�F�N�g��Transform���g�p���邩
        ImGuiWindowFlags m_flags;     // �\���t���O
        EditorWindowSizeType m_sizeType;    // �T�C�Y�ݒ�
        std::optional<Transform> m_prevTransform;    // �G�f�B�^�[�I�u�W�F�N�g�̉ߋ����W
        static std::unordered_map<std::string, uint> ms_windowCount; // �E�B���h�E�̎g�p��
    };
}


#endif // !#define I_EDITORWINDOWBASE_H
