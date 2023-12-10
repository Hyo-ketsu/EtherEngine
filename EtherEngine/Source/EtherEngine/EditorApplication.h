#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H
#include <Base/ProjectData.h>
#include <EngineLibrary/BaseMainWindow.h>
#include <EtherEngine/ImGuiClass.h>
#include <EtherEngine/ProjectEditorData.h>


//----- EditorApplication �錾
namespace EtherEngine {
    // �G�f�B�^�[(�Q�[���G���W��)��\������N���X(Singleton)
    class EditorApplication : public BaseMainWindow, public Singleton<EditorApplication> {
    public:
        // �f�X�g���N�^
        ~EditorApplication(void);


        // �Q�[�����[�h���J�n����
        // @ Memo : ���ɊJ�n���Ă���ۂ̓Q�[�����[�h�̍ċN�����s���܂�
        void StartGameMode(void);
        // �Q�[�����[�h���ꎞ���f����
        // @ Memo : �J�n���Ă��Ȃ��ꍇ�͓��ɉ����N����܂���
        void StopGameMode(void);
        // �Q�[�����[�h���I������
        // @ Memo : �J�n���Ă��Ȃ��ꍇ�͓��ɉ����N����܂���
        void EndGameMode(void);

    protected:
        // �������O�֐�
        void InitFirstFunction(void) override;
        // ��������֐�
        void InitLateFunction(void) override;
        // �������I����֐�
        void EndInitLateFunction(void) override;
        // �I���O�֐�
        void UninitFirstFunction(void) override;
        // ���C���֐�
        void MainFunction(void) override;

    private:
        // �R���X�g���N�^
        EditorApplication(void);

        bool m_isGameMode;  // �Q�[�����N�����Ă��邩
        std::unique_ptr<IMGUI> m_imGui; // �ێ����Ă���IMGUI
        std::unique_ptr<ProjectData> m_projectData; // ���ݕێ����Ă���v���W�F�N�g�f�[�^
        std::unique_ptr<EditorData> m_editorData;   // ���ݕێ����Ă���G�f�B�^�[�f�[�^

        friend class Singleton<EditorApplication>;
    };
}


//----- Wrapper
namespace EtherEngine {
    namespace Wrapper {
        //----- �G�f�B�^�[�̃A�v���P�[�V����
        public ref class EditorApplication {
        public:
            // �G�f�B�^�[���I��������
            static property bool IsGameLoop {
                void set(bool value){
                    EtherEngine::EditorApplication::Get()->SetIsGameLoop(value);
                }
            }
        };
    }
}


#endif // !I_EDITORAPPLICATION_H
