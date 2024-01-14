#ifndef I_THREADPOOL_H
#define I_THREADPOOL_H
#include <Base/MessageQue.h>
#include <Base/Singleton.h>


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

    private:
        // コンストラクタ
        ThreadPool(void);


        // タスクを取得する
        // @ Ret  : 取得したタスク(タスクがなければnullptr)
        TaskType GetTask(void);


        friend class CentrallySingleton;

        //static std::thread::id ms_mainThread;           // メインスレッドのID
    };
}


#endif // !I_THREADPOOL_H
