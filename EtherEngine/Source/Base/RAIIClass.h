#ifndef I_RAIICLASS_H
#define I_RAIICLASS_H


//----- RAIIClass ����
namespace EtherEngine {
    // �R���X�g���N�^�A�f�X�g���N�^�Ŏw�肵���������s���N���X
    class RAIIClass {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �R���X�g���N�^����
        // @ Arg2 : �f�X�g���N�^����
        RAIIClass(std::function<void(void)> init, std::function<void(void)> unInit);
        // �f�X�g���N�^
        ~RAIIClass(void);
        RAIIClass(const RAIIClass& copy) = delete;
        RAIIClass(RAIIClass&& move) = delete;

    private:
        std::function<void(void)> m_unInit; // �I�����ɍs������
    };
}


#endif // !I_RAIICLASS_H
