#ifndef I_EDITORPROGRESSBAR_H
#define I_EDITORPROGRESSBAR_H
#include <EtherEngine/EditorPopupWindow.h>


//----- �i���N���X �錾
namespace EtherEngine {
    // �v���O���X�o�[��\������N���X
    // @ Memo : �ŏ��l�� 0 �̌��ߑł��ł�
    class ProgressClass {
    public:
        // �R���X�g���N�^
        // @ Arg1 : ���݂̐i��
        // @ Arg2 : �i���̍ő�l(Default : 1.0f)
        ProgressClass(const float progress, const float max = 1.0f);


        // �i���A�N�Z�T�[
        float& AccessProgress(void) { return m_progress; }

        // �ő�l�Q�b�^�[
        float GetMax(void) const { return m_max; }
        // �ő�l�A�N�Z�T�[
        float& AccessMax(void) { return m_max; }


        // �i�����擾����
        // @ Ret  : �i��(0.0f ~ 1.0f)
        float GetProgress(void) const;
        // �I��������
        // @ Ret  : �I��������
        bool IsEnd(void) const;

    private:
        float m_progress;   // ���݂̐i��
        float m_max;        // �i���̍ő�l
    };


    using Progress = std::weak_ptr<ProgressClass>;
}




//----- EditorProgressBar �錾
namespace EtherEngine {
    // �v���O���X�o�[��\������|�b�v�A�b�v�E�B���h�E
    // @ Memo : �i���������A�܂��͐i���̊Ǘ��������Ŏ���I�����܂��B
    class EditorProgressBar : public EditorPopupWindow {
    public:
        // �R���X�g���N�^�@
        // @ Arg1 : �G�f�B�^�[�I�u�W�F�N�g
        // @ Arg2 : �\�����b�Z�[�W
        // @ Arg3 : �i��
        // @ Arg4 : �I��������炷��(Default : true)
        EditorProgressBar(EditorObject* editorObject, const std::string& message, Progress progress, const bool isSound = true);


        void DrawWindow(void) override;

    private:
        // �v���O���X�o�[���폜����
        void WindowKill(void);

        std::string m_message;  // �\�����b�Z�[�W
        Progress m_progress;    // �Ǘ����Ă���i��
        bool m_isSound;         // �I�����ʒm����炷��
    };
}


#endif // !I_EDITORPROGRESSBAR_H
