#ifndef I_THREADPOOL_H
#define I_THREADPOOL_H
#include <Base/MessageQue.h>
#include <Base/Singleton.h>


//----- 定数定義
namespace {
    const uint THREAD_SIZE = 16; // スレッドプールで使用するスレッド数
}


//----- クラス 定義
namespace {
    class WorkerThread {
    public:
        bool m_isEnd;       // 保持しているスレッドの終了フラグ
        bool m_isGetUp;     // 起床しているか
        std::thread m_thread;   // 保持スレッド
        std::mutex m_mutex;     // 条件変数用ミューテックス
        std::condition_variable m_cv; // 保持している条件変数
    };
}


//----- ThreadPool 宣言
namespace EtherEngine {
    // タスク定義
    using TaskType = std::function<void(void)>;


    // スレッドを保持しているクラス
    class ThreadPool : public Singleton<ThreadPool> {
    public:
        // デストラクタ
        ~ThreadPool(void);


        // タスクを投げる
        // @ Memo : メインスレッドに限定されます
        // @ Arg1 : 投げるタスク
        void AddTask(TaskType task);
        // タスクを投げる
        // @ Memo : メインスレッド以外からも投げることができます。飢餓ロックに留意してお使いください。
        // @ Arg1 : 投げるタスク
        void AddNotMainThreadTask(TaskType task);
        // 寝ているスレッド数を計算する
        // @ Ret  : 寝ているスレッド数
        uint CountSleepThread(void);

    private:
        // コンストラクタ
        ThreadPool(void);


        // タスクを取得する
        // @ Ret  : 取得したタスク(タスクがなければnullptr)
        TaskType GetTask(void);


        friend class Singleton<ThreadPool>;

        MessageQue<TaskType> m_tasks;  // 保持しているタスク
        std::array<WorkerThread, THREAD_SIZE> m_threads;    // 保持しているスレッド
        SpinLock m_spinLock;
        static std::thread::id ms_mainThread;           // メインスレッドのID
    };
}


#endif // !I_THREADPOOL_H
