#ifndef I_MANAGEFUNCTIONINIT_H
#define I_MANAGEFUNCTIONINIT_H


//----- �������E�I��������`
namespace EtherEngine {
    class  ManageFunctionInit {
    public:
        // �f�X�g���N�^
        ~ManageFunctionInit(void) {}


        static void ENGINELIBRARY_API Init(void);
        static void ENGINELIBRARY_API Uninit(void);
        
    private:
        // �R���X�g���N�^
        ManageFunctionInit(void) {}
    };
}


#endif // !I_CPPCLIINIT_H
