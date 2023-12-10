#include <Base/ThreadPool.h>
#include <Base/EditorException.h>


//----- ThreadPool 定義
namespace EtherEngine {
    // コンストラクタ
    ThreadPool::ThreadPool(void) {
        throw std::exception();
    }
    // デストラクタ
    ThreadPool::~ThreadPool(void) {
        throw std::exception();
    }


    // タスクを投げる
    void ThreadPool::AddTask(TaskType task) {
        throw std::exception();
    }
    // タスクを投げる
    void ThreadPool::AddNotMainThreadTask(TaskType task) {
        throw std::exception();
    }
    // タスクを取得する
    TaskType ThreadPool::GetTask(void) {
        throw std::exception();
    }
}
