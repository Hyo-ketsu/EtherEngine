#include <EngineLibrary/EngineLibrarySingletonGetter.h>



//----- EngineLibrarySingletonGetter 宣言
namespace EtherEngine {
    // コンストラクタ
    EngineLibrarySingletonGetter::EngineLibrarySingletonGetter(void) {
    }
    // CentrallySingletonを取得する
    void EngineLibrarySingletonGetter::GetCentrallySingleton(void** singleton) {
        *singleton = &CentrallySingleton::Get();
    }
}
