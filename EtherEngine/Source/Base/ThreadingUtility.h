#ifndef I_THREADINGUTILITY_H
#define I_THREADINGUTILITY_H
#include <Base/ManageMediation.h>
#include <Base/Mutex.h>


//----- ThreadingUtility �錾
namespace EtherEngine {
    // �X���b�h�֘A�̏������s��
    class ThreadingUtility {
    public:
        friend class ManageFunctionInit;


        // ���g�̃X���b�h���w��ms�X���[�v����
        // @ Arg1 : �X���[�v�b��(Default : 60/1�b)
        static void ThisThreadSleep(uint ms = 16) { ms_thisThreadSleep.UseLambda(ms); }
        // �~���[�e�b�N�X���擾����
        // @ Arg1 : �擾�����~���[�e�b�N�X
        static std::shared_ptr<Mutex> GetMutex(void) { return ms_getMutex.UseLambda(); }

    private:
        // �R���X�g���N�^
        ThreadingUtility(void);


        static ManageMediation<ThreadingUtility, void, uint> ms_thisThreadSleep;
        static ManageMediation<ThreadingUtility, std::shared_ptr<Mutex>> ms_getMutex;
    };
}


#endif // !I_THREADINGUTILITY_H
