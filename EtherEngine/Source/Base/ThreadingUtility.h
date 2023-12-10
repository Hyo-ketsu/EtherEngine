#ifndef I_THREADINGUTILITY_H
#define I_THREADINGUTILITY_H
#include <Base/ManageMediation.h>
#include <Base/Mutex.h>


//----- ThreadingUtility 宣言
namespace EtherEngine {
    // スレッド関連の処理を行う
    class ThreadingUtility {
    public:
        friend class ManageFunctionInit;


        // 自身のスレッドを指定msスリープする
        // @ Arg1 : スリープ秒数(Default : 60/1秒)
        static void ThisThreadSleep(uint ms = 16) { ms_thisThreadSleep.UseLambda(ms); }
        // ミューテックスを取得する
        // @ Arg1 : 取得したミューテックス
        static std::shared_ptr<Mutex> GetMutex(void) { return ms_getMutex.UseLambda(); }

    private:
        // コンストラクタ
        ThreadingUtility(void);


        static ManageMediation<ThreadingUtility, void, uint> ms_thisThreadSleep;
        static ManageMediation<ThreadingUtility, std::shared_ptr<Mutex>> ms_getMutex;
    };
}


#endif // !I_THREADINGUTILITY_H
