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


        // �Q�[�����[�h���J�n����
        // @ Memo : ���ɊJ�n���Ă���ۂ̓Q�[�����[�h�̍ċN�����s���܂�
        void StartGameMode(void);
        // �Q�[�����[�h���ꎞ���f����
        // @ Memo : �J�n���Ă��Ȃ��ꍇ�͓��ɉ����N����܂���
        void StopGameMode(void);
        // �Q�[�����[�h���I������
        // @ Memo : �J�n���Ă��Ȃ��ꍇ�͓��ɉ����N����܂���
        void EndGameMode(void);
        

    private:
        bool m_isGameMode;  // �Q�[�����N�����Ă��邩
        std::unique_ptr<IMGUI> m_imGui; // �ێ����Ă���IMGUI
        std::unique_ptr<ProjectData> m_projectData; // ���ݕێ����Ă���v���W�F�N�g�f�[�^
        std::unique_ptr<ProjectEditorData> m_projectEditorData; // ���ݕێ����Ă���G�f�B�^�[�f�[�^
    };
}


#endif // !I_EDITORAPPLICATION_H
