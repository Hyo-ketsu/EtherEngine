#ifndef I_MANAGEFUNCTIONINIT_H
#define I_MANAGEFUNCTIONINIT_H


//----- �������E�I��������`
namespace EtherEngine {
    class  ManageFunctionInit {
    public:
        // �f�X�g���N�^
        ~ManageFunctionInit(void) {}


        void ENGINELIBRARY_API Init(void);
        void ENGINELIBRARY_API Uninit(void);
        
    private:
        // �R���X�g���N�^
        ManageFunctionInit(void) {}
    };
}


#endif // !I_CPPCLIINIT_H
