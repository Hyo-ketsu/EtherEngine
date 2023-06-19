#include <Base/CameraComponent.h>
#include <Base/GameObject.h>


namespace EtherEngine {
    // コンストラクタ
    CameraComponent::CameraComponent(GameObject* gameObject, const Eigen::Vector3f& look)  
        : ComponentBase(gameObject)
        , CameraBase({},look) {
        m_cameraData.SetPos(ComponentHelper::GetGameObject(this)->AccessTransform().AccessPostion());
    }

    // 更新処理
    void CameraComponent::Update(void) {
        m_cameraData.SetPos(ComponentHelper::GetGameObject(*this)->AccessTransform().AccessPostion());
    }
}
