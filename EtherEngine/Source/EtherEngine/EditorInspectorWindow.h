#ifndef I_EDITORINSPECTORWINDOW_H
#define I_EDITORINSPECTORWINDOW_H
#include <Base/EtherEngineUtility.h>
#include <Base/Handle.h>
#include <EtherEngine/EditorWindowBase.h>


//----- �\���p�I�u�W�F�N�g ��`
namespace EtherEngine {
    // EditorInspectorWindow�p�ɕ\������I�u�W�F�N�g
    class EditorInspectorObject {
    public:
        // �f�t�H���g�R���X�g���N�^
        EditorInspectorObject(void);
        // �R���X�g���N�^
        // @ Arg1 : �\���I�u�W�F�N�g
        // @ Arg2 : ���݊m�F�����_(���݂��Ă���� true)
        EditorInspectorObject(IInspectorShow* showObject, const std::function<bool(void)>& deleteObject);
        

        // �\���I�u�W�F�N�g�擾
        // @ Ret  : �\���I�u�W�F�N�g(���ɍ폜����Ă����nullptr)
        IInspectorShow* GetShowObject(void) const;

    private:
        IInspectorShow* m_showObject;
        std::function<bool(void)> m_deleteObject;
    };
}


//----- EditorInspectorWindow �錾
namespace EtherEngine {
    // �Q�[���I�u�W�F�N�g�̏ڍׂ�\������N���X
    class EditorInspectorWindow : public EditorWindowBase {
    public:
        using EditorWindowBase::EditorWindowBase;


        // �X�V����
        void UpdateWindow(void) override {}
        // �`�揈��
        void DrawWindow(void) override;


        // @ MEMO : �ЂƂ܂��|�C���^�Ŏ����B���Handle�I�Ȃ̂Ŋ���
        // �\���I�u�W�F�N�g���Z�b�g����
        // @ Arg1 : �\���I�u�W�F�N�g
        static void SetInspectorShow(const EditorInspectorObject& in) { ms_showObject = in; }

    private:
        static EditorInspectorObject ms_showObject;   // �\���I�u�W�F�N�g
    };
}


#endif // !I_EDITORINSPECTORWINDOW_H
