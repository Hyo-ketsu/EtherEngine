#include <CPPCLI/CameraComponent.h>


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
            auto look = GetGameObject()->GetTransform().GetPostion();
            look.z() -= 1;
            m_camera.SetValue(CameraBase(GetGameObject()->GetTransform().GetPostion(), look));
        }
    }
    // 更新処理
    void CameraComponent::Update(void) {
        m_camera.GetValue().AccessCameraData().SetPos(GetGameObject()->GetTransform().GetPostion());
    }
}
