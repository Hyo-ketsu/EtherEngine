#include <EtherEngine/EditorWindowBase.h>
#include <Base/MathUtility.h>
#include <EtherEngine/EditorObjectStorage.h>
#include <EtherEngine/EditorApplication.h>
#include <EtherEngine/EditorComponentHelper.h>


namespace EtherEngine {
    // �R���X�g���N�^
    EditorWindowBase::EditorWindowBase(EditorObject* editorObject, const std::string& name, const bool isUseTransform, 
        const ImGuiWindowFlags& flag, const EditorWindowSizeType& sizeType, const Eigen::Vector2i& windowSize)
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

        //----- �E�B���h�E�̃T�C�Y�֘A�ݒ�
        if (windowSize.x() < 0 && windowSize.y() < 0) {
            //----- �ǂ���������B�ݒ肳��Ă��Ȃ����̂Ƃ���
            m_sizeType = decltype(m_sizeType)::ManualSize;
        }
        else {
            //----- �ǂ��炩�������B�ݒ�
            m_windowSize = ImVec2(windowSize.x(), windowSize.y());
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

        //----- �L���b�V���O
        auto gameObject = EditorComponentHelper::GetEditorObject(this);
        auto& transform = gameObject->AccessTransform();
        auto& postion = transform.AccessPostion();
        auto& scale = transform.AccessScale();

        //----- �g�k�ɑ΂��鏈��
        do {
            if (m_isUseTranform) {
                //----- �����ꂩ�ɊY������Ȃ珈�������Ȃ�
                if (m_sizeType == EditorWindowSizeType::ManualSize) break;
                if (m_windowSize.has_value() == false) break;

                //----- Transform�̊g�k�ɑ΂���ImGui�E�B���h�E�̃T�C�Y��K�p����
                switch (m_sizeType) {
                case EtherEngine::EditorWindowSizeType::AutoSizeFixed:  // �����Œ�T�C�Y
                    for (int i = 0; i < 2; i++) {
                        scale[i] = fabsf((*m_windowSize)[i]);
                    }
                    break;
                case EtherEngine::EditorWindowSizeType::AutoSizeFluctuation:    // �����ϓ��T�C�Y
                    for (int i = 0; i < 2; i++) {
                        scale[i] = fabsf(ImGui::GetWindowSize()[i]);
                        if (scale[i] < fabsf((*m_windowSize)[i])) scale[i] = fabsf((*m_windowSize)[i]);
                    }
                    break;
                //case EtherEngine::EditorWindowSizeType::SemiAutoSize
                }
                
                //----- ������̊g�k��ImGui�E�B���h�E�ɐݒ肷��
                ImGui::SetWindowSize(ImVec2(scale.x(), scale.y()));
            }
            else {
                //----- ImGui�E�B���h�E�̊g�k��ύX����
                ImVec2 size;
                switch (m_sizeType) {
                case EtherEngine::EditorWindowSizeType::AutoSizeFixed:  // �����Œ�T�C�Y
                    for (int i = 0; i < 2; i++) {
                        size[i] = fabsf((*m_windowSize)[i]);
                    }
                    break;
                case EtherEngine::EditorWindowSizeType::AutoSizeFluctuation:    // �����ϓ��T�C�Y
                    for (int i = 0; i < 2; i++) {
                        size[i] = fabsf(ImGui::GetWindowSize()[i]);
                        if (size[i] < fabsf((*m_windowSize)[i])) size[i] = fabsf((*m_windowSize)[i]);
                    }
                    break;
                    //case EtherEngine::EditorWindowSizeType::SemiAutoSize
                }

                //----- ������̊g�k��ݒ肷��
                ImGui::SetWindowSize(ImVec2(size.x, size.y));
            }
        } while (false);

        //----- ���W�ɑ΂��鏈��
        do {
            //----- Transform���g�p���Ȃ��̂ł���Ή������Ȃ�
            if (m_isUseTranform == false) break;

            //----- ���Ɏ擾���Ă���ߋ����W�ƌ��ݍ��W���Ⴄ(=���R���|�[�l���g���ō��W���ҏW����Ă���)��
            bool isEqualPostion = m_prevTransform.has_value() // �S�ē��l�ł����true
                && MathUtility::FloatEqual(postion.x(), m_prevTransform->GetPostion().x())
                && MathUtility::FloatEqual(postion.y(), m_prevTransform->GetPostion().y());
            bool isEqualImGuiPostion = m_prevImGuiPostion.has_value() == false // �S�ē��l�ł����true
                || MathUtility::FloatEqual(ImGui::GetWindowPos().x, m_prevImGuiPostion->x)
                && MathUtility::FloatEqual(ImGui::GetWindowPos().y, m_prevImGuiPostion->y);

            //----- �ǂ��炩�� true = ImGui�E�B���h�E��Transform�̍��W���ύX����Ă��Ȃ��̂ŉ������Ȃ�
            if (isEqualPostion && isEqualImGuiPostion) break;

            //----- ���ꂼ��̍��W�������i���������Ă����Transform��D�悷��j
            if (isEqualPostion == false) {
                //----- Transform�̍��W���ς���Ă���BTransform�̍��W��ImGui�E�B���h�E�̍��W�ɓK�p
                ImGui::SetWindowPos(ImVec2(postion.x(), postion.y()));
            }
            if (isEqualImGuiPostion == false) {
                //----- ImGui�E�B���h�E�̍��W���ς���Ă���BImGui�E�B���h�E�̍��W��Transform�̍��W�ɓK�p
                postion = Eigen::Vector3f(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, postion.z());
            }
        } while (false);

        //----- �ߋ����W�����݂�Transform�ŏ㏑��
        m_prevTransform = transform;
        m_prevImGuiScale = ImGui::GetWindowSize();
        m_prevImGuiPostion = ImGui::GetWindowPos();
    }


    std::unordered_map<std::string, uint> EditorWindowBase::ms_windowCount; // �E�B���h�E�̎g�p��
}
