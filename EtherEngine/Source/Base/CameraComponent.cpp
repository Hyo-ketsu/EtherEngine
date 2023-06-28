#include <Base/CameraComponent.h>
#include <Base/GameObject.h>


namespace EtherEngine {
    // コンストラクタ
    CameraComponent::CameraComponent(GameObject* gameObject, const Eigen::Vector3f& look)  
        : ComponentBase(gameObject)
        , CameraBase({},look) {
        AccessCameraData().SetPos(ComponentHelper::GetGameObject(this)->AccessTransform().AccessPostion());
    }

    // 更新処理
    void CameraComponent::Update(void) {
        AccessCameraData().SetPos(ComponentHelper::GetGameObject(*this)->AccessTransform().AccessPostion());
    }
}
