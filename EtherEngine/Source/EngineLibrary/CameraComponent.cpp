#include <EngineLibrary/CameraComponent.h>
#include <EngineLibrary/GameObject.h>


namespace EtherEngine {
    // デストラクタ
    CameraComponent::~CameraComponent(void) {
        this->!CameraComponent();
    }
    // ファイナライザ
    CameraComponent::!CameraComponent(void) {
        m_camera.MaintainerClear();
    }


    // 初期化処理
    void CameraComponent::Start(void) {
        if (m_camera.HasValue() == false) {
            auto look = ParentGameObject->NGameObject.GetData().GetTransform().GetPostion();
            look.z() -= 1;
            m_camera.SetValue(CameraBase(ParentGameObject->NGameObject.GetData().GetTransform().GetPostion(), look, true, 0)); // @ MEMO : 仮うち
        }
    }
    // 更新処理
    void CameraComponent::Update(void) {
        m_camera.GetValue().AccessCameraData().SetPos(ParentGameObject->NGameObject.GetData().GetTransform().GetPostion());
    }
}
