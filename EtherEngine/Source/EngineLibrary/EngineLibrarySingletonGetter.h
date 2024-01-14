#ifndef I_ENGINELIBRARYSINGLETONGETTER_H
#define I_ENGINELIBRARYSINGLETONGETTER_H
#include <EngineLibrary/ManageSingleton.h>
#include <Base/CentrallySingleton.h>


//----- EngineLibrarySingletonGetter �錾
namespace EtherEngine {
    public ref class EngineLibrarySingletonGetter {
        ETHER_ENGINE_MANAGE_SINGLETON(EngineLibrarySingletonGetter);
    public:
        // CentrallySingleton���擾����
        // @ Arg1 : �擾����CentrallySingleton
        void GetCentrallySingleton(void** singleton);
    };
}


#endif // !I_ENGINELIBRARYSINGLETONGETTER_H
