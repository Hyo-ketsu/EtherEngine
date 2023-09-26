#include <EtherEngine/EditorProgressBar.h>
#include <Base/WindowsDefine.h>
#include <Base/MathUtility.h>


//----- �i���N���X ��`
namespace EtherEngine {
    // �R���X�g���N�^
    ProgressClass::ProgressClass(const float progress, const float max) 
        : m_progress(progress) 
        , m_max(max) {
    }


    // �i�����擾����
    float ProgressClass::GetProgress(void) const {
        return m_progress / m_max;
    }
    // �I��������
    bool ProgressClass::IsEnd(void) const {
        return MathUtility::FloatEqual(GetProgress(), 1.0f) || GetProgress() >= 1.0f;
    }
}




//----- EditorProgressBar ��`
namespace EtherEngine {
    // �R���X�g���N�^
    EditorProgressBar::EditorProgressBar(EditorObject* editorObject, const std::string& message, Progress progress, const bool isSound) 
        : EditorPopupWindow(editorObject, ImGuiDefine::Name::WINDOW_PROGRESS_TITLE, EditorPopupControl::None, {100,30})
        , m_message(message) 
        , m_progress(progress) 
        , m_isSound(isSound) {
    }

    // �E�B���h�E�`��
    void EditorProgressBar::DrawWindow(void) {
        //----- �e�L�X�g�\��
        ImGui::Text(m_message.c_str());

        //----- �i���Ǘ����������Ă��邩
        if (m_progress.expired()) {
            WindowKill();
            return;
        }

        //----- �v���O���X�o�[�̕\��
        ImGui::ProgressBar(m_progress.lock()->GetProgress());

        //----- �Ō�܂Ői��ł���Ύ��E�B���h�E���폜����
        if (m_progress.lock()->IsEnd()) {
            WindowKill();
            return;
        }
    }


    // �v���O���X�o�[���폜����
    void EditorProgressBar::WindowKill(void) {
        //----- ����炷
        if (m_isSound) {
            MessageBeep(-1);
        }

        //----- ���|�b�v�A�b�v���폜����
        m_isOpen = false;
    }
}
