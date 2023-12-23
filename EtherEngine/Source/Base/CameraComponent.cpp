//#include <Base/CameraComponent.h>
//#include <Base/NativeGameObject.h>
//
//
//namespace EtherEngine {
//    // コンストラクタ
//    CameraComponent::CameraComponent(NativeGameObject* gameObject, const Eigen::Vector3f& look)  
//        : ComponentBase(gameObject)
//        , CameraBase({},look) {
//        AccessCameraData().SetPos(ComponentHelper::GetParentObject(this)->AccessTransform().AccessPostion());
//    }
//
//    // 更新処理
//    void CameraComponent::Update(void) {
//        AccessCameraData().SetPos(ComponentHelper::GetParentObject(*this)->AccessTransform().AccessPostion());
//    }
//}
