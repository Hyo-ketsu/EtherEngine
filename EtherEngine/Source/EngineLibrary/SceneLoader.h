#ifndef I_SCENELOADER_H
#define I_SCENELOADER_H
#include <Base/BaseDefines.h>
#include <EngineLibrary/ManageSingleton.h>


//----- SceneLoader ’è‹`
namespace EtherEngine {
    public ref class SceneLoader {
        ETHER_ENGINE_MANAGE_SINGLETON(SceneLoader);
    public:


    private:
        System::Collections::Generic::List<SceneType>^ m_thisScenes;
    };
}


#endif // !I_SCENELOADER_H
