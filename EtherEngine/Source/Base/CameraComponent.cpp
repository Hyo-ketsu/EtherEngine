#include <Base/CameraComponent.h>
#include <Base/GameObject.h>


namespace EtherEngine {
    // �R���X�g���N�^
    CameraComponent::CameraComponent(GameObject* gameObject, const Eigen::Vector3f& look)  
        : ComponentBase(gameObject)
        , CameraBase({},look) {
        AccessCameraData().SetPos(ComponentHelper::GetGameObject(this)->AccessTransform().AccessPostion());
    }

    // �X�V����
    void CameraComponent::Update(void) {
        AccessCameraData().SetPos(ComponentHelper::GetGameObject(*this)->AccessTransform().AccessPostion());
    }
}
