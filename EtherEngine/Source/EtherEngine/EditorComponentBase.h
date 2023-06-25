#ifndef I_EDITORCOMPONENTBASE_H
#define I_EDITORCOMPONENTBASE_H


//----- EditorComponent�錾
namespace EtherEngine {
    class EditorComponentBase {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �G�f�B�^�[�I�u�W�F�N�g
        EditorComponentBase(void* editorObject);
        // �f�X�g���N�^
        ~EditorComponentBase(void) {}


        // �e�G�f�B�^�[�I�u�W�F�N�g�擾
        // @ MEMO : �w���p�[�������p��������
        // @ Arg1 : �e�G�f�B�^�[�I�u�W�F�N�g�ւ̃|�C���^
        void GetEditorObject(void** editerObject) const;


        // �X�V����
        void UpdateFunction(void);
        // �`�揈��
        void DrawFunction(void);

    protected:
        virtual void Start(void) {}
        virtual void Update(void) {}
        virtual void Draw(void) {}

    private:
        void* m_eidtorObject;   // �ێ����Ă�
        bool m_isStart;         // �������֐����s���Ă��邩
    };
}


#endif // !I_EDITORCOMPONENTBASE_H
