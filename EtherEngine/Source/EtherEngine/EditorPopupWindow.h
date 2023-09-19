#ifndef I_EDITORPOPUPWINDOW_H
#define I_EDITORPOPUPWINDOW_H
#include <EtherEngine/EditorWindowBase.h>
#include <EtherEngine/EditorObjectStorage.h>


//----- Popup�e��N���X��`
namespace EtherEngine {
    // �ǂ̃��b�Z�[�W�|�b�v�A�b�v���쐬���邩
    enum class EditorMessagePopupType {
        Ok,             // Ok �{�^���̂ݕ\��
        YesNo,          // Yes,No �{�^���̂ݕ\��
        YesNoCancel,    // Yes,No,Cancel �{�^���\��
    };
    // ���b�Z�[�W�|�b�v�A�b�v����
    enum class EdtiorMessagePopupResult {
        Non,        // ����Ȃɂ�������Ă��Ȃ�
        OkYes,      // Ok �Ⴕ���� Yes �{�^������
        No,         // No �{�^������
        Cancel,     // Cancel �{�^������
    };


    using EditorMessagePopupResult = std::shared_ptr<EdtiorMessagePopupResult>;
}




//----- EditorPopupWindow �錾
namespace EtherEngine {
    class EditorPopupWindow : public EditorWindowBase {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �e�ƂȂ�G�f�B�^�[�I�u�W�F�N�g
        // @ Arg2 : �E�B���h�E��
        // @ Arg3 : �E��̃E�B���h�E�� x  �{�^����\�����邩
        // @ Arg4 : �t���O�ݒ�(Default : �����ݒ肵�Ȃ�)
        EditorPopupWindow(EditorObject* editorObject, const std::string& name, const bool isCloseButton, const ImGuiBackendFlags& flag = ImGuiBackendFlags_None);

    private:
        void Update(void) override;
        void Draw(void) override;

        bool m_isCloseButton;   // x �{�^����\�����邩
    };
}




//----- EditorMessagePopup ��`
namespace EtherEngine {
    // ���b�Z�[�W�|�b�v�A�b�v��\������
    // @ Temp : �ǂ̕\���^�C�v��(Default : Ok�{�^���̂ݕ\��)
    // @ Memo : �ǂ̃{�^���������ꂽ���̌��ʂ��~�����ꍇ�A�R���X�g���N�^�̑�4�����Ɏ擾�p�̕ϐ���n���Ă��������B
    template <EditorMessagePopupType Type = EditorMessagePopupType::Ok>
    class EditorMessagePopup : public EditorPopupWindow {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �e�ƂȂ�G�f�B�^�[�I�u�W�F�N�g
        // @ Arg2 : �E�B���h�E��
        // @ Arg3 : �\�����b�Z�[�W
        // @ Arg4 : ����(Default : ���ʂ��擾���Ȃ�)
        EditorMessagePopup(EditorObject* editorObject, const std::string& name, const std::string& message, const EditorMessagePopupResult& result = nullptr);


        void DrawWindow(void) override;

    protected:
        std::string m_message;  // �\�����b�Z�[�W
        std::weak_ptr<EdtiorMessagePopupResult> m_result;   // ���ʏo�͐�
    };
}




//----- �|�b�v�A�b�v�E�B���h�E�֗��֐� �錾
namespace EtherEngine {
    // �|�b�v�A�b�v�E�B���h�E���ȒP�ɍ쐬����
    // @ Temp : ��������|�b�v�A�b�v�E�B���h�E�̌^
    // @ Temps: �^��������̌^
    // @ Args : �^�������
    template <Concept::SubClassOnly<EditorPopupWindow> PopupType, typename ...ArgsType>
    BaseHandle<EditorObject> CreatePopWindow(ArgsType ...args);
}




//----- EditorMessagePopup ��`
namespace EtherEngine {
    // �R���X�g���N�^
    template <EditorMessagePopupType Type>
    EditorMessagePopup<Type>::EditorMessagePopup(EditorObject* editorObject, const std::string& name, const std::string& message, const EditorMessagePopupResult& result)
        : EditorPopupWindow(editorObject, name, true)   // @ MEMO : true�͉�����
        , m_message(message) 
        , m_result(result == nullptr ? decltype(m_result)() : decltype(m_result)(result)) {
    }
    template <EditorMessagePopupType Type>
    void EditorMessagePopup<Type>::DrawWindow(void) {
        ImGui::Text(m_message.c_str());
        if (m_isOpen == false) {
            int hoge = 1;
        }
    }
}




//----- �|�b�v�A�b�v�E�B���h�E�֗��֐� ��`
namespace EtherEngine {
    // �|�b�v�A�b�v�E�B���h�E���ȒP�ɍ쐬����
    // @ Temp : ��������|�b�v�A�b�v�E�B���h�E�̌^
    // @ Temps: �^��������̌^
    // @ Args : �^�������
    template <Concept::SubClassOnly<EditorPopupWindow> PopupType, typename ...ArgsType>
    BaseHandle<EditorObject> CreatePopWindow(ArgsType ...args) {
        auto gameObject = EditorObjectStorage::Get()->CreateEditorObject();
        gameObject.GetAtomicData().AddComponent<PopupType>(args...);
        return gameObject;
    }
}

#endif // !I_EDITORPOPUPWINDOW_H
