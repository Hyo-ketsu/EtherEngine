#include <Base/ThreadingUtility.h>


namespace EtherEngine {
    // スレッド関連の処理を行う
    namespace ThreadingUtility {
        // 自身のスレッドを指定msスリープする
        void ThisThreadSleep(uint ms) { Sleep(ms); }
    }
}
