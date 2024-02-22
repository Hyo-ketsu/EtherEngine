#ifndef I_GAMEOBJECTUPDATER_H
#define I_GAMEOBJECTUPDATER_H
#include <EngineLibrary/ManageSingleton.h>
#include <Base/CameraBase.h>
#include <EngineLibrary/GameObject.h>


//----- GameObjectUpdater ’è‹`
namespace EtherEngine {
    public ref class GameObjectUpdater {
        ETHER_ENGINE_MANAGE_SINGLETON(GameObjectUpdater);
    public:
        void Update(void);
        void Draw(const CameraData& cameraData);
    };
}


#endif // !I_GAMEOBJECTUPDATER_H
