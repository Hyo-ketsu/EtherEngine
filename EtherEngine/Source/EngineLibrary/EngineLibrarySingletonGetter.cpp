#include <EngineLibrary/EngineLibrarySingletonGetter.h>



//----- EngineLibrarySingletonGetter �錾
namespace EtherEngine {
    // �R���X�g���N�^
    EngineLibrarySingletonGetter::EngineLibrarySingletonGetter(void) {
    }
    // CentrallySingleton���擾����
    void EngineLibrarySingletonGetter::GetCentrallySingleton(void** singleton) {
        *singleton = &CentrallySingleton::Get();
    }
}
