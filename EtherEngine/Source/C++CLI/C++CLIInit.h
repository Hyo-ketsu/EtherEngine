#ifndef I_CPPCLIINIT_H
#define I_CPPCLIINIT_H


//----- �������E�I��������`
namespace EtherEngine {
    class CPPCLI {
    public:
        // �f�X�g���N�^
        ~CPPCLI(void) {}


        static void Init(void);
        static void Uninit(void);

    private:
        // �R���X�g���N�^
        CPPCLI(void) {}
    };
}


#endif // !I_CPPCLIINIT_H
