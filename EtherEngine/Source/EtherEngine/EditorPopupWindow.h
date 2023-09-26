#ifndef I_EDITORPOPUPWINDOW_H
#define I_EDITORPOPUPWINDOW_H
#include <EtherEngine/EditorWindowBase.h>
#include <EtherEngine/EditorObjectStorage.h>


//----- Popup�e��N���X��`
namespace EtherEngine {
    // �E�B���h�E�̐���
    // @ Memo : ���ꂼ��A���C���E�B���h�E�����A���C���E�B���h�E�폜�AImGui�E�B���h�E�폜
    enum class EditorPopupControl {
        All = 0,        // ���ׂċ���
        Window,         // �E�B���h�E�����̂݋���
        WindowClose,    // �E�B���h�E�폜�̂݋���
        ImGuiClose,     // ImGui�E�B���h�E�̂ݍ폜����
        Close,          // ���E�B���h�E�폜�̂݋���
        None,           // ���ׂĕs����
    };
    // �ǂ̃��b�Z�[�W�|�b�v�A�b�v���쐬���邩
    enum class EditorMessagePopupType {
        Ok = 0,         // Ok �{�^���̂ݕ\��
        YesNo,          // Yes,No �{�^���̂ݕ\��
        YesNoCancel,    // Yes,No,Cancel �{�^���\��
    };
    // ���b�Z�[�W�|�b�v�A�b�v����
    enum class EditorMessagePopupResultType {
        None = 0,   // ����Ȃɂ�������Ă��Ȃ�
        OkYes,      // Ok �Ⴕ���� Yes �{�^������
        No,         // No �{�^������
        Cancel,     // Cancel �{�^������
    };


    using EditorMessagePopupResult = std::shared_ptr<EditorMessagePopupResultType>;
}




//----- EditorPopupWindow �錾
namespace EtherEngine {
    class EditorPopupWindow : public EditorWindowBase {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �e�ƂȂ�G�f�B�^�[�I�u�W�F�N�g
        // @ Arg2 : �E�B���h�E��
        // @ Arg3 : �E�B���h�E�ł̐���(Default : �E�B���h�E�����A�E�B���h�E&ImGui�E�B���h�Ex�{�^����\��)
        // @ Arg4 : �E�B���h�E�T�C�Y(Default : ����)
        // @ Arg5 : �t���O�ݒ�(Default : �����ݒ肵�Ȃ�)
        EditorPopupWindow(EditorObject* editorObject, const std::string& name, const EditorPopupControl popupControl,
            const Eigen::Vector2i & = { -1,-1 }, const ImGuiWindowFlags& flag = ImGuiWindowFlags_None);

    private:
        void UpdateWindow(void) override;
        void DeleteWindow(void) override;
        void Draw(void) override;

        EditorPopupControl m_popupControl;   // x �{�^����\�����邩
        bool m_isWindowFunction;    // Window�̏������s����
    };
}




//----- EditorMessagePopup ��`
namespace EtherEngine {
    // ���b�Z�[�W�|�b�v�A�b�v��\������
    // @ Temp : �ǂ̕\���^�C�v��(Default : Ok�{�^���̂ݕ\��)
    // @ Memo : �ǂ̃{�^���������ꂽ���̌��ʂ��~�����ꍇ�A�R���X�g���N�^�̑�4�����Ɏ擾�p�̕ϐ���n���Ă��������B
    // @ MEMO : ����u�E�B���h�E�@�\��}������|�b�v�A�b�v�𕡐��o���A�ǂꂩ����������v�Ǝc���Ă�̂ɂ�������炸�E�B���h�E�@�\���g�p�ł��܂��B�v�C��
    template <EditorMessagePopupType Type = EditorMessagePopupType::Ok>
    class EditorMessagePopup : public EditorPopupWindow {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �e�ƂȂ�G�f�B�^�[�I�u�W�F�N�g
        // @ Arg2 : �E�B���h�E��
        // @ Arg3 : �\�����b�Z�[�W
        // @ Arg4 : ����(Default : ���ʂ��擾���Ȃ�)
        // @ Arg5 : �E�B���h�E�T�C�Y(Default : ����)
        EditorMessagePopup(EditorObject* editorObject, const std::string& name, const std::string& message, const EditorMessagePopupResult& result = nullptr);


        void DrawWindow(void) override;

    protected:
        std::string m_message;  // �\�����b�Z�[�W
        std::weak_ptr<EditorMessagePopupResultType> m_result;   // ���ʏo�͐�
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
        : EditorPopupWindow(editorObject, name, EditorPopupControl::None, {600,400}, ImGuiWindowFlags_NoCollapse)
        , m_message(message) 
        , m_result(result == nullptr ? decltype(m_result)() : decltype(m_result)(result)) {
        //----- �O�̂��߂� Result ������
        if (m_result.expired() == false) {
            *m_result.lock() = EditorMessagePopupResultType::None;
        }
    }
    template <EditorMessagePopupType Type>
    void EditorMessagePopup<Type>::DrawWindow(void) {
        //----- �ϐ��錾
        bool isButtonPush = false;  // �����ꂩ�̃{�^���������ꂽ��

        //----- �e�L�X�g�\��
        ImGui::Text(m_message.c_str());

        //----- �e��{�^���\��
        // @ Memo : Ok�{�^�����珇�ɕ\��
        do {
            //----- ���U���g�o�͐悪���݂��邩
            bool hasResult = !(m_result.expired());

            //----- Ok�܂���Yes�\��
            auto decisionButtonMessage = Type == EditorMessagePopupType::Ok ? "OK" : "Yes";
            if (ImGui::Button(decisionButtonMessage)) {
                if (hasResult) *m_result.lock() = EditorMessagePopupResultType::OkYes;
                isButtonPush = true;
                break;
            }

            //----- No�{�^���\��
            // @ Memo : �ȉ��A�\�����Ȃ��̂ł���Α� break ����
            if constexpr (Type == EditorMessagePopupType::Ok) break;
            ImGui::SameLine();
            if (ImGui::Button("No")) {
                if (hasResult) *m_result.lock() = EditorMessagePopupResultType::No;
                isButtonPush = true;
                break;
            }

            //----- Cancel�{�^���\��
            if constexpr (Type == EditorMessagePopupType::YesNo) break;
            ImGui::SameLine();
            if (ImGui::Button("Cancel")) {
                if (hasResult) *m_result.lock() = EditorMessagePopupResultType::Cancel;
                isButtonPush = true;
                break;
            }
        } while (false);

        //----- �����{�^����������Ă���Ύ��g���폜����
        if (isButtonPush) {
            EditorObjectStorage::Get()->DeleteEditorObject(EditorComponentHelper::GetEditorObject(this)->GetHandle());
            return;
        }

        if (m_isOpen == false) {
            // @ MEMO : �e�X�g�R�[�h
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
