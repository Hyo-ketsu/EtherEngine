#ifndef I_THREADPOOL_H
#define I_THREADPOOL_H
#include <Base/MessageQue.h>
#include <Base/Singleton.h>


//----- ThreadPool �錾
namespace EtherEngine {
    // �^�X�N��`
    using TaskType = std::function<void(void)>;


    // �X���b�h��ێ����Ă���N���X
    class ThreadPool : public Singleton<ThreadPool> {
    public:
        // �f�X�g���N�^
        ~ThreadPool(void);


        // �^�X�N�𓊂���
        // @ Memo : ���C���X���b�h�Ɍ��肳��܂�
        // @ Arg1 : ������^�X�N
        void AddTask(TaskType task);
        // �^�X�N�𓊂���
        // @ Memo : ���C���X���b�h�ȊO����������邱�Ƃ��ł��܂��B�Q�샍�b�N�ɗ��ӂ��Ă��g�����������B
        // @ Arg1 : ������^�X�N
        void AddNotMainThreadTask(TaskType task);

    private:
        // �R���X�g���N�^
        ThreadPool(void);


        // �^�X�N���擾����
        // @ Ret  : �擾�����^�X�N(�^�X�N���Ȃ����nullptr)
        TaskType GetTask(void);


        friend class CentrallySingleton;

        //static std::thread::id ms_mainThread;           // ���C���X���b�h��ID
    };
}


#endif // !I_THREADPOOL_H
