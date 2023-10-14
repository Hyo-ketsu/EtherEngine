#ifndef I_THREADPOOL_H
#define I_THREADPOOL_H
#include <Base/MessageQue.h>
#include <Base/Singleton.h>


//----- �萔��`
namespace {
    const uint THREAD_SIZE = 16; // �X���b�h�v�[���Ŏg�p����X���b�h��
}


//----- �N���X ��`
namespace {
    class WorkerThread {
    public:
        bool m_isEnd;       // �ێ����Ă���X���b�h�̏I���t���O
        bool m_isGetUp;     // �N�����Ă��邩
        std::thread m_thread;   // �ێ��X���b�h
        std::mutex m_mutex;     // �����ϐ��p�~���[�e�b�N�X
        std::condition_variable m_cv; // �ێ����Ă�������ϐ�
    };
}


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
        // �Q�Ă���X���b�h�����v�Z����
        // @ Ret  : �Q�Ă���X���b�h��
        uint CountSleepThread(void);

    private:
        // �R���X�g���N�^
        ThreadPool(void);


        // �^�X�N���擾����
        // @ Ret  : �擾�����^�X�N(�^�X�N���Ȃ����nullptr)
        TaskType GetTask(void);


        friend class Singleton<ThreadPool>;

        MessageQue<TaskType> m_tasks;  // �ێ����Ă���^�X�N
        std::array<WorkerThread, THREAD_SIZE> m_threads;    // �ێ����Ă���X���b�h
        SpinLock m_spinLock;
        static std::thread::id ms_mainThread;           // ���C���X���b�h��ID
    };
}


#endif // !I_THREADPOOL_H
