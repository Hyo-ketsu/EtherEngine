#include <CPPCLI/CameraComponent.h>


namespace EtherEngine {
    // �f�X�g���N�^
    CameraComponent::~CameraComponent(void) {
        this->!CameraComponent();
    }
    // �t�@�C�i���C�U
    CameraComponent::!CameraComponent(void) {
        m_camera.MaintainerClear();
    }


    // ����������
    void CameraComponent::Start(void) {
        if (m_camera.HasValue() == false) {
            auto look = GetGameObject()->GetTransform().GetPostion();
            look.z() -= 1;
            m_camera.SetValue(CameraBase(GetGameObject()->GetTransform().GetPostion(), look));
        }
    }
    // �X�V����
    void CameraComponent::Update(void) {
        m_camera.GetValue().AccessCameraData().SetPos(GetGameObject()->GetTransform().GetPostion());
    }
}
