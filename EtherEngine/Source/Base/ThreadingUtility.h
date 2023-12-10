#ifndef I_THREADINGUTILITY_H
#define I_THREADINGUTILITY_H


//----- ThreadingUtility 宣言
namespace EtherEngine {
    // スレッド関連の処理を行う
    namespace ThreadingUtility {
        // 自身のスレッドを指定msスリープする
        // @ Arg1 : スリープ秒数(Default : 60/1秒)
        void ThisThreadSleep(uint ms = 16);
    }
}


#endif // !I_THREADINGUTILITY_H
