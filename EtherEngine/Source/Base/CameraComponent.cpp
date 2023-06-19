#include <Base/CameraComponent.h>
#include <Base/GameObject.h>


namespace EtherEngine {
    // �R���X�g���N�^
    CameraComponent::CameraComponent(GameObject* gameObject, const Eigen::Vector3f& look)  
        : ComponentBase(gameObject)
        , CameraBase({},look) {
        m_cameraData.SetPos(ComponentHelper::GetGameObject(this)->AccessTransform().AccessPostion());
    }

    // �X�V����
    void CameraComponent::Update(void) {
        m_cameraData.SetPos(ComponentHelper::GetGameObject(*this)->AccessTransform().AccessPostion());
    }
}
