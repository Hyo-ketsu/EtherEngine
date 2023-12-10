#include <Base/ThreadingUtility.h>


//----- ThreadingUtility ’è‹`
namespace EtherEngine {
    ManageMediation<ThreadingUtility, void, uint> ThreadingUtility::ms_thisThreadSleep = decltype(ms_thisThreadSleep)();
    ManageMediation<ThreadingUtility, std::shared_ptr<Mutex>> ThreadingUtility::ms_getMutex = decltype(ms_getMutex)();
}
