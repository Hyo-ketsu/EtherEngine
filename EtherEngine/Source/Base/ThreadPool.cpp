#include <Base/ThreadPool.h>
#include <Base/EditorException.h>


//----- ThreadPool ��`
namespace EtherEngine {
    // �R���X�g���N�^
    ThreadPool::ThreadPool(void) {
        //----- �Ђ�����^�X�N���񂷃����_
        auto doTask = [&](uint threadIndex) {
            //----- �L���b�V���O
            auto& thread = m_threads[threadIndex];

            //----- ������
            thread.m_isGetUp = true;

            while (thread.m_isEnd == false) {
                //----- �^�X�N���擾����
                auto task = GetTask();

                //----- �^�X�N�̎��s�����̂܂ܐQ�邩
                if (task != nullptr) {
                    //----- �^�X�N�̎��s
                    thread.m_isGetUp = true;
                    task();
                }
                else {
                    thread.m_isGetUp = false;
                    //----- �^�X�N���Ȃ��B�Q��
                    std::unique_lock<std::mutex> lock(thread.m_mutex);
                    thread.m_cv.wait(lock, [&]() -> bool {return m_tasks.GetMessageCount() > 0 || thread.m_isEnd; });
                }
            }

            //----- �O�̂��ߋN���Ă��邱�Ƃɂ���
            thread.m_isGetUp = true;
            };

        //----- �X���b�h�̗����グ�Ə����ϐ��̐ݒ�
        for (int i = 0; i < m_threads.size(); i++) {
            //----- �X���b�h�̗����グ
            m_threads[i].m_thread = std::thread(doTask, i);
        }
    }
    // �f�X�g���N�^
    ThreadPool::~ThreadPool(void) {
        //----- �O�̂��߃^�X�N������Ԃ�
        while (m_tasks.GetMessageCount() > 0) {
            m_tasks.Get();
        }

        //----- �S�X���b�h�̋N���ƏI��
        for (auto& thread : m_threads) {
            thread.m_isEnd = true;
            thread.m_cv.notify_all();
        }
    }


    // �^�X�N�𓊂���
    void ThreadPool::AddTask(TaskType task) {
        //----- ���b�N���s��
        auto lock = m_spinLock.KeyLock();

        //----- ��MainThread����^�X�N�����M����Ă��邩
        if (ms_mainThread != std::this_thread::get_id()) {
            //----- ��MainThread����^�X�N�������Ă��Ă���B��O�𑗏o
            throw EditorException("Error! Not main thread to task");
        }

        //----- �^�X�N�𓊂���
        AddNotMainThreadTask(task);
    }
    // �^�X�N�𓊂���
    void ThreadPool::AddNotMainThreadTask(TaskType task) {
        //----- �^�X�N���M
        m_tasks.Send(task);

        //----- ��X���b�h���N����
        for (auto& thread : m_threads) {
            if (thread.m_isGetUp == false) {
                //----- �Q�Ă���B�N����
                // @ MEMO : All�ł����̂��H
                thread.m_cv.notify_all();
                break;
            }
        }
    }
    // �^�X�N���擾����
    TaskType ThreadPool::GetTask(void) {
        //----- ���b�N���s��
        auto lock = m_spinLock.KeyLock();

        //----- �^�X�N�擾�E�ԋp
        auto task = m_tasks.Get();
        if (task.has_value()) {
            return std::get<0>(*task);
        }
        else {
            return nullptr;
        }
    }


    // �Q�Ă���X���b�h�����v�Z����
    uint ThreadPool::CountSleepThread(void) {
        //----- �ϐ��錾
        uint ret = 0;

        //----- �m�F
        for (auto& thread : m_threads) {
            if (thread.m_isGetUp == false) {
                ret++;
            }
        }

        //----- �ԋp
        return ret;
    }

    std::thread::id ThreadPool::ms_mainThread = std::this_thread::get_id();
}
