//#include <Base/CameraComponent.h>
//#include <Base/NativeGameObject.h>
//
//
//namespace EtherEngine {
//    // �R���X�g���N�^
//    CameraComponent::CameraComponent(NativeGameObject* gameObject, const Eigen::Vector3f& look)  
//        : ComponentBase(gameObject)
//        , CameraBase({},look) {
//        AccessCameraData().SetPos(ComponentHelper::GetParentObject(this)->AccessTransform().AccessPostion());
//    }
//
//    // �X�V����
//    void CameraComponent::Update(void) {
//        AccessCameraData().SetPos(ComponentHelper::GetParentObject(*this)->AccessTransform().AccessPostion());
//    }
//}
