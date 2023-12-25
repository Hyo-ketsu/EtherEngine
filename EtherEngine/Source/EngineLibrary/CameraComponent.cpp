#include <EngineLibrary/CameraComponent.h>
#include <EngineLibrary/GameObject.h>


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
            auto look = ParentGameObject->NGameObject.GetData().GetTransform().GetPostion();
            look.z() -= 1;
            m_camera.SetValue(CameraBase(ParentGameObject->NGameObject.GetData().GetTransform().GetPostion(), look, true, 0)); // @ MEMO : ������
        }
    }
    // �X�V����
    void CameraComponent::Update(void) {
        m_camera.GetValue().AccessCameraData().SetPos(ParentGameObject->NGameObject.GetData().GetTransform().GetPostion());
    }
}
