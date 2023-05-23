#ifndef I_COMPONENTBASE_H
#define I_COMPONENTBASE_H


namespace EtherEngine {
    // �R���|�[�l���g�̊�b�ƂȂ�N���X
    class ComponentBase {
    public:
        // �R���X�g���N�^
        ComponentBase(void) {}
        // �f�X�g���N�^
        ~ComponentBase(void) {}

        virtual void Start(void) {}
        virtual void Update(void) {}
        virtual void Draw(void) {}
    };
}


#endif // !I_COMPONENTBASE_H
