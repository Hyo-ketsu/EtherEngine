#include <Base/ThreadPool.h>
#include <Base/EditorException.h>


//----- ThreadPool ��`
namespace EtherEngine {
    // �R���X�g���N�^
    ThreadPool::ThreadPool(void) {
        throw std::exception();
    }
    // �f�X�g���N�^
    ThreadPool::~ThreadPool(void) {
        throw std::exception();
    }


    // �^�X�N�𓊂���
    void ThreadPool::AddTask(TaskType task) {
        throw std::exception();
    }
    // �^�X�N�𓊂���
    void ThreadPool::AddNotMainThreadTask(TaskType task) {
        throw std::exception();
    }
    // �^�X�N���擾����
    TaskType ThreadPool::GetTask(void) {
        throw std::exception();
    }
}
