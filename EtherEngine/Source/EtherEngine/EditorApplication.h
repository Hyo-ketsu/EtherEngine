#ifndef I_EDITORAPPLICATION_H
#define I_EDITORAPPLICATION_H
#include <Base/ProjectData.h>
#include <CPPCLI/BaseMainWindow.h>
#include <EtherEngine/ImGuiClass.h>
#include <EtherEngine/ProjectEditorData.h>


namespace EtherEngine {
    // �G�f�B�^�[(�Q�[���G���W��)��\������N���X(Singleton)
    class EditorApplication : public BaseMainWindow, public Singleton<EditorApplication> {
    public:
        // �f�X�g���N�^
        ~EditorApplication(void);


        // �E�B���h�E�@�\�g�p�ۃQ�b�^�[
        bool GetIsWindowFunctionEnable(void) const { return m_isWindowFunctionEnable; }


        // �Q�[�����[�h���J�n����
        // @ Memo : ���ɊJ�n���Ă���ۂ̓Q�[�����[�h�̍ċN�����s���܂�
        void StartGameMode(void);
        // �Q�[�����[�h���ꎞ���f����
        // @ Memo : �J�n���Ă��Ȃ��ꍇ�͓��ɉ����N����܂���
        void StopGameMode(void);
        // �Q�[�����[�h���I������
        // @ Memo : �J�n���Ă��Ȃ��ꍇ�͓��ɉ����N����܂���
        void EndGameMode(void);


        // �E�B���h�E�̈ړ��Ȃǂ̗L��������؂�ւ���
        // @ Arg1 : �L�������̐ݒ�
        // @ Arg2 : �E�B���h�E����邱�Ƃ��L��������؂�ւ��邩(Default : true)
        void SetWindowFunctionEnable(const bool isEnable, const bool isClose = true);
        
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
        bool m_isWindowFunctionEnable;  // �E�B���h�E�̋@�\���L����
        std::unique_ptr<IMGUI> m_imGui; // �ێ����Ă���IMGUI
        std::unique_ptr<ProjectData> m_projectData; // ���ݕێ����Ă���v���W�F�N�g�f�[�^
        std::unique_ptr<EditorData> m_editorData; // ���ݕێ����Ă���G�f�B�^�[�f�[�^

        friend Singleton<EditorApplication>;
    };
}


#endif // !I_EDITORAPPLICATION_H
