#include <EngineLibrary/Scene.h>


//----- Scene ��`
namespace EtherEngine {
    // �R���X�g���N�^
    Scene::Scene(void) {
    }


    // �V�[���ԍ����擾����
    SceneIDType Scene::GetSceneID(void) {
        return this->GetType()->GetHashCode();
    }
}
