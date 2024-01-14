#ifndef I_ENGINELIBRARYSINGLETONGETTER_H
#define I_ENGINELIBRARYSINGLETONGETTER_H
#include <EngineLibrary/ManageSingleton.h>
#include <Base/CentrallySingleton.h>


//----- EngineLibrarySingletonGetter 宣言
namespace EtherEngine {
    public ref class EngineLibrarySingletonGetter {
        ETHER_ENGINE_MANAGE_SINGLETON(EngineLibrarySingletonGetter);
    public:
        // CentrallySingletonを取得する
        // @ Arg1 : 取得したCentrallySingleton
        void GetCentrallySingleton(void** singleton);
    };
}


#endif // !I_ENGINELIBRARYSINGLETONGETTER_H
