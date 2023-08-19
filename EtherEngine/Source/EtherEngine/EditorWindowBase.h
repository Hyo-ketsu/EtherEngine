#ifndef I_EDITORWINDOWBASE_H
#define I_EDITORWINDOWBASE_H
#include <EtherEngine/EditorObject.h>
#include <EtherEngine/EditorComponentBase.h>


//----- EditorWindowBase �錾
namespace EtherEngine {
    // �G�f�B�^�[�̃E�B���h�E�̒��ۃN���X
    class EditorWindowBase : public EditorComponentBase {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �e�ƂȂ�G�f�B�^�[�I�u�W�F�N�g
        // @ Arg2 : �E�B���h�E��
        // @ Arg3 : �t���O�ݒ�(Default : �����ݒ肵�Ȃ�)
        EditorWindowBase(EditorObject* editorObject, const std::string& name, const ImGuiBackendFlags& flag = ImGuiBackendFlags_None);


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
        // �\�����邩�A�N�Z�T�[
        bool& AccessIsOpen(void) { return m_isOpen; }

        // �\���t���O�Q�b�^�[
        ImGuiWindowFlags GetFlags(void) const { return m_flags; }
        // �\���t���O�Z�b�^�[
        void SetFlags(const ImGuiWindowFlags& in) { m_flags = in; }
        // �\���t���O�A�N�Z�T�[
        ImGuiWindowFlags& AccessFlags(void) { return m_flags; }


        // �`�揈��
        virtual void Draw(void) override;
        // �T�u�N���X�p�`�揈��
        virtual void DrawWindow(void) {}


        // �O���o��
        Json Output(void) override { return Json(); }
        // �O������
        void Input(const Json& input) override {}
        // Inspector�\��
        void ShowInspector(void) override {}


    protected:
        std::string m_name; // �\����
        bool m_isOpen;      // �\�����邩
        ImGuiWindowFlags m_flags;  // �\���t���O
    };
}


#endif // !#define I_EDITORWINDOWBASE_H
