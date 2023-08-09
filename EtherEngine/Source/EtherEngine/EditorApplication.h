#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H
#include <Base/ProjectData.h>
#include <DirectX/BaseMainWindow.h>
#include <EtherEngine/ImGuiClass.h>
#include <EtherEngine/ProjectEditorData.h>


namespace EtherEngine {
    // �G�f�B�^�[(�Q�[���G���W��)��\������N���X(Singleton)
    class EditorApplication : public BaseMainWindow<EditorApplication> {
    public:
        // �R���X�g���N�^
        EditorApplication(void);
        // �f�X�g���N�^
        ~EditorApplication(void);


        // �������֐�
        virtual void InitFunction(void) override;
        // ���C���֐�
        void MainFunction(void) override;

    private:
        std::unique_ptr<IMGUI> m_imGui; // �ێ����Ă���IMGUI
        std::unique_ptr<ProjectData> m_projectData; // ���ݕێ����Ă���v���W�F�N�g�f�[�^
        std::unique_ptr<ProjectEditorData> m_projectEditorData; // ���ݕێ����Ă���G�f�B�^�[�f�[�^
    };
}


#endif // !I_EDITORAPPLICATION_H
