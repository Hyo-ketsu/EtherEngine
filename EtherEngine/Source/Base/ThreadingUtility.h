#ifndef I_THREADINGUTILITY_H
#define I_THREADINGUTILITY_H


//----- ThreadingUtility �錾
namespace EtherEngine {
    // �X���b�h�֘A�̏������s��
    namespace ThreadingUtility {
        // ���g�̃X���b�h���w��ms�X���[�v����
        // @ Arg1 : �X���[�v�b��(Default : 60/1�b)
        void ThisThreadSleep(uint ms = 16);
    }
}


#endif // !I_THREADINGUTILITY_H
