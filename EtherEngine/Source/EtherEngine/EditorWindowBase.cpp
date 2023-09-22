#include <EtherEngine/EditorWindowBase.h>
#include <Base/MathUtility.h>
#include <EtherEngine/EditorObjectStorage.h>
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/EditorComponentHelper.h>


namespace EtherEngine {
    // �R���X�g���N�^
    EditorWindowBase::EditorWindowBase(EditorObject* editorObject, const std::string& name, const bool isUseTransform, 
        const ImGuiWindowFlags& flag, const EditorWindowSizeType& sizeType, const Eigen::Vector2f& windowSize)
        : EditorComponentBase(editorObject)
        , m_name(name) 
        , m_isOpen(true) 
        , m_isUseTranform(isUseTransform)
        , m_flags(flag) 
        , m_sizeType(sizeType) {
        //----- �����E�B���h�E������΃E�B���h�E����ݒ肷��
        auto windowCountFindResult = ms_windowCount.find(m_name);
        if (windowCountFindResult != ms_windowCount.end()) {
            //----- ���݂����B�g�p���̐������󔒒ǉ�(Debug�ł�(��)�̌`��)
#ifdef _DEBUG
            m_name += " (" + std::to_string(windowCountFindResult->second) + ")";
#else
            for (int i = 0; i < windowCountFindResult->second; i++) {
                m_name += " ";
            }
#endif // _DEBUG
            windowCountFindResult->second++;
        }
        else {
            //----- ���݂��Ȃ��B�ǉ�
            ms_windowCount.emplace(m_name, 1);
        }
    }


    // ����������
    void EditorWindowBase::Start(void) {
        //----- �T�u�N���X�������s
        StartWindow(); 
    }
    // �폜����
    void EditorWindowBase::Delete(void) {
        //----- �T�u�N���X�������s
        DeleteWindow();
    }
    // �X�V����
    void EditorWindowBase::Update(void) {
        //----- �T�u�N���X�������s
        UpdateWindow();
    }
    void EditorWindowBase::Draw(void) {
        //----- �E�B���h�E�`��
        ImGui::Begin(m_name.c_str(), &m_isOpen, m_flags);
        DrawWindow();
        DrawLateWindow();
            
        ImGui::End();
    }


    // �E�B���h�E�`���ɍs������
    void EditorWindowBase::DrawLateWindow(void) {
        //----- �����ꂽ�̂ł���΍폜����
        if (m_isOpen == false) {
            EditorObjectStorage::Get()->DeleteEditorObject(EditorComponentHelper::GetEditorObject(this)->GetHandle());
            return;
        }

        //----- �T�C�Y�ݒ肪Manual�Ȃ牽�����Ȃ�
        if (m_sizeType == EtherEngine::EditorWindowSizeType::ManualSize) return;

        //----- �L���b�V���O
        auto gameObject = EditorComponentHelper::GetEditorObject(this);
        auto& transform = gameObject->AccessTransform();
        auto& position = transform.AccessPostion();
        auto& scale = transform.AccessScale();
        return;

        //----- ���Ɏ擾���Ă���ߋ�Transform�ƌ���Transform���Ⴄ(=���R���|�[�l���g���ō��W��g�k���ҏW����Ă���)��
        bool isEqualPos = m_prevTransform.has_value()   // �S�ē��l�ł����true
            && MathUtility::FloatEqual(position.x(), m_prevTransform->GetPostion().x())
            && MathUtility::FloatEqual(position.y(), m_prevTransform->GetPostion().y())
            && MathUtility::FloatEqual(position.z(), m_prevTransform->GetPostion().z());
        bool isEqualScale = m_prevTransform.has_value() // �S�ē��l�ł����true
            && MathUtility::FloatEqual(scale.x(), m_prevTransform->GetScale().x())
            && MathUtility::FloatEqual(scale.y(), m_prevTransform->GetScale().y())
            && MathUtility::FloatEqual(scale.z(), m_prevTransform->GetScale().z());
        if (isEqualPos == false || isEqualScale == false) { // ���l�łȂ����̂����邩
            //----- ImGui�E�B���h�E�̍��W�A�T�C�Y�����g�̐e�G�f�B�^�[�I�u�W�F�N�g��Trasnform�ɓK�p����
            if (m_isUseTranform) {
                //----- �g�k��ݒ�
                switch (m_sizeType) {
                case EtherEngine::EditorWindowSizeType::AutoSizeFixed:
                    for (int i = 0; i < 2; i++) {
                        scale[i] = fabsf(ImGui::GetContentRegionAvail()[i]);
                    }
                    break;
                case EtherEngine::EditorWindowSizeType::AutoSizeFluctuation:
                    for (int i = 0; i < 2; i++) {
                        scale[i] = fabsf(ImGui::GetWindowSize()[i]);
                        if (scale[i] < fabsf(ImGui::GetContentRegionAvail()[i])) scale[i] = fabsf(ImGui::GetContentRegionAvail()[i]);
                    }
                    break;
                    //case EtherEngine::EditorWindowSizeType::SemiAutoSize
                }
                scale = Eigen::Vector3f(ImGui::GetWindowSize().x, ImGui::GetWindowSize().y, scale.z());
            }
        }
        else {
            //----- ���g�̐e�G�f�B�^�[�I�u�W�F�N�g��Transform��ImGui�E�B���h�E�̍��W�A�T�C�Y�ɓK�p����
            if (m_isUseTranform) {
                //----- �œK�ȃT�C�Y��ݒ�
                ImGui::SetWindowSize(ImVec2(scale.x(),scale.y()));
            }
        }

        //----- �ߋ����W�����݂�Transform�ŏ㏑��
        m_prevTransform = transform;
    }


    std::unordered_map<std::string, uint> EditorWindowBase::ms_windowCount; // �E�B���h�E�̎g�p��
}
