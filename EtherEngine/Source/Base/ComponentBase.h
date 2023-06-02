#ifndef I_COMPONENTBASE_H
#define I_COMPONENTBASE_H


namespace EtherEngine {
    // �R���|�[�l���g�̊�b�ƂȂ�N���X
    class ComponentBase {
    public:
        // �R���X�g���N�^
        ComponentBase(void);
        // �f�X�g���N�^
        ~ComponentBase(void) {}

        // �X�V�������s��
        void UpdateFuntion(void);
        // �`�揈�����s��
        void DrawFuntion(void);


    protected:
        virtual void Start(void) {}
        virtual void Update(void) {}
        virtual void Draw(void) {}

    private:
        bool m_isStart; // ����Start�������s���Ă��邩
    };
}


#endif // !I_COMPONENTBASE_H
