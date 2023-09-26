#include <EtherEngine/EditorPopupWindow.h>
#include <EtherEngine/EditorApplication.h>
#include <Base/BaseUtility.h>


//----- EditorPopupWindow ��`
namespace EtherEngine {
    // �R���X�g���N�^
    EditorPopupWindow::EditorPopupWindow(EditorObject* editorObject, const std::string& name, EditorPopupControl popupControl, const Eigen::Vector2i& windowSize, const ImGuiWindowFlags& flag)
        : EditorWindowBase(editorObject, name, true, flag | ImGuiWindowFlags_NoCollapse, EditorWindowSizeType::AutoSizeFixed, windowSize) 
        , m_popupControl(popupControl) {
        //----- 
        m_isWindowFunction = IsInputComparison(m_popupControl, true, EditorPopupControl::All, EditorPopupControl::Window) == false;

        //----- �E�B���h�E�@�\�؂�ւ�
        if (m_isWindowFunction) {
            EditorApplication::Get()->SetWindowFunctionEnable(false);
        }
    }

    void EditorPopupWindow::UpdateWindow(void) {
    }
    void EditorPopupWindow::DeleteWindow(void) {
        //----- �E�B���h�E�@�\�؂�ւ�
        if (m_isWindowFunction) {
            EditorApplication::Get()->SetWindowFunctionEnable(true);
        }
    }
    void EditorPopupWindow::Draw(void) {
        ImGui::OpenPopup(m_name.c_str());

        //----- x�{�^���\����
        bool* isOpen = m_popupControl == EditorPopupControl::All || m_popupControl == EditorPopupControl::ImGuiClose || m_popupControl == EditorPopupControl::Close ? &m_isOpen : nullptr;

        //----- �E�B���h�E�`��
        if (ImGui::BeginPopupModal(m_name.c_str(), isOpen, m_flags)) {
            DrawWindow();

            DrawLateWindow();

            //----- �L���b�V���O
            auto gameObject = EditorComponentHelper::GetEditorObject(this);
            auto& transform = gameObject->AccessTransform();
            auto& position = transform.AccessPostion();

            //----- �ϐ��錾�E���W�擾
            RECT windowRect{};
            GetWindowRect(EditorApplication::Get()->GetHWND(), &windowRect);

            //----- �������W�v�Z
            position.x() = windowRect.left + ((windowRect.right - windowRect.left) / 2);
            position.y() = windowRect.top + ((windowRect.bottom - windowRect.top) / 2);
            position.x() -= ImGui::GetWindowSize().x / 2;
            position.y() -= ImGui::GetWindowSize().y / 2;
            ImGui::SetWindowPos(ImVec2(position.x(), position.y()));
            ImGui::SetWindowFocus();

            ImGui::EndPopup();
        }
    }
}
