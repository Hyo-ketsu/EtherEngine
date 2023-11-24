#include <Base/ThreadPool.h>
#include <Base/EditorException.h>


//----- ThreadPool 定義
namespace EtherEngine {
    // コンストラクタ
    ThreadPool::ThreadPool(void) {
        //----- ひたすらタスクを回すラムダ
        auto doTask = [&](uint threadIndex) {
            //----- キャッシング
            auto& thread = m_threads[threadIndex];

            //----- 初期化
            thread.m_isGetUp = true;

            while (thread.m_isEnd == false) {
                //----- タスクを取得する
                auto task = GetTask();

                //----- タスクの実行かそのまま寝るか
                if (task != nullptr) {
                    //----- タスクの実行
                    thread.m_isGetUp = true;
                    task();
                }
                else {
                    thread.m_isGetUp = false;
                    //----- タスクがない。寝る
                    std::unique_lock<std::mutex> lock(thread.m_mutex);
                    thread.m_cv.wait(lock, [&]() -> bool {return m_tasks.GetMessageCount() > 0 || thread.m_isEnd; });
                }
            }

            //----- 念のため起きていることにする
            thread.m_isGetUp = true;
            };

        //----- スレッドの立ち上げと条件変数の設定
        for (int i = 0; i < m_threads.size(); i++) {
            //----- スレッドの立ち上げ
            m_threads[i].m_thread = std::thread(doTask, i);
        }
    }
    // デストラクタ
    ThreadPool::~ThreadPool(void) {
        //----- 念のためタスクを握りつぶす
        while (m_tasks.GetMessageCount() > 0) {
            m_tasks.Get();
        }

        //----- 全スレッドの起床と終了
        for (auto& thread : m_threads) {
            thread.m_isEnd = true;
            thread.m_cv.notify_all();
        }
    }


    // タスクを投げる
    void ThreadPool::AddTask(TaskType task) {
        //----- ロックを行う
        auto lock = m_spinLock.KeyLock();

        //----- 非MainThreadからタスクが送信されているか
        if (ms_mainThread != std::this_thread::get_id()) {
            //----- 非MainThreadからタスクが送られてきている。例外を送出
            throw EditorException("Error! Not main thread to task");
        }

        //----- タスクを投げる
        AddNotMainThreadTask(task);
    }
    // タスクを投げる
    void ThreadPool::AddNotMainThreadTask(TaskType task) {
        //----- タスク送信
        m_tasks.Send(task);

        //----- 一つスレッドを起こす
        for (auto& thread : m_threads) {
            if (thread.m_isGetUp == false) {
                //----- 寝ている。起こす
                // @ MEMO : Allでいいのか？
                thread.m_cv.notify_all();
                break;
            }
        }
    }
    // タスクを取得する
    TaskType ThreadPool::GetTask(void) {
        //----- ロックを行う
        auto lock = m_spinLock.KeyLock();

        //----- タスク取得・返却
        auto task = m_tasks.Get();
        if (task.has_value()) {
            return std::get<0>(*task);
        }
        else {
            return nullptr;
        }
    }


    // 寝ているスレッド数を計算する
    uint ThreadPool::CountSleepThread(void) {
        //----- 変数宣言
        uint ret = 0;

        //----- 確認
        for (auto& thread : m_threads) {
            if (thread.m_isGetUp == false) {
                ret++;
            }
        }

        //----- 返却
        return ret;
    }

    std::thread::id ThreadPool::ms_mainThread = std::this_thread::get_id();
}
