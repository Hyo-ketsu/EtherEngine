#ifndef I_CPPCLIINIT_H
#define I_CPPCLIINIT_H


//----- �������E�I��������`
namespace EtherEngine {
#ifdef _ENGINELIBRARY
    class EngineLibrary {
    public:
        // �f�X�g���N�^
        ~EngineLibrary(void) {}


        static void Init(void);
        static void Uninit(void);

    private:
        // �R���X�g���N�^
        EngineLibrary(void) {}
    };
#endif
}


#endif // !I_CPPCLIINIT_H
