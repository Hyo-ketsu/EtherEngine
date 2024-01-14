#ifndef I_ENGINELIBRARYSINGLETONGETTER_H
#define I_ENGINELIBRARYSINGLETONGETTER_H
#include <EngineLibrary/ManageSingleton.h>
#include <Base/CentrallySingleton.h>


//----- EngineLibrarySingletonGetter éŒ¾
namespace EtherEngine {
    public ref class EngineLibrarySingletonGetter {
        ETHER_ENGINE_MANAGE_SINGLETON(EngineLibrarySingletonGetter);
    public:
        // CentrallySingleton‚ğæ“¾‚·‚é
        // @ Arg1 : æ“¾‚µ‚½CentrallySingleton
        void GetCentrallySingleton(void** singleton);
    };
}


#endif // !I_ENGINELIBRARYSINGLETONGETTER_H
