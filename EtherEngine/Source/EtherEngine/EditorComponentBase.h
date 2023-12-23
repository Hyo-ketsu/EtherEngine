#ifndef I_EDITORCOMPONENTBASE_H
#define I_EDITORCOMPONENTBASE_H
#include <Base/NativeBaseObject.h>


//----- EditorComponent�錾
namespace EtherEngine {
    class EditorComponentBase : public NativeBaseObject {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �G�f�B�^�[�I�u�W�F�N�g
        EditorComponentBase(void* editorObject);
        // �������z�f�X�g���N�^
        virtual ~EditorComponentBase(void) = 0 {}


        // �e�G�f�B�^�[�I�u�W�F�N�g�擾
        // @ Memo : �w���p�[�������p��������
        // @ Arg1 : �e�G�f�B�^�[�I�u�W�F�N�g�ւ̃|�C���^
        void GetEditorObject(void** editerObject) const;


        // �X�V����
        void UpdateFunction(void);
        // �`�揈��
        void DrawFunction(void);
        // �폜������
        void DeleteFunction(void);

    protected:
        virtual void Start(void) {}
        virtual void Update(void) {}
        virtual void Draw(void) {}
        virtual void Delete(void) {}

    private:
        void* m_eidtorObject;   // �ێ����Ă�
        bool m_isStart;         // �������֐����s���Ă��邩
    };
}


#endif // !I_EDITORCOMPONENTBASE_H
