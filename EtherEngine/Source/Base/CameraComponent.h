#ifndef I_CAMERACOMPONENT_H
#define I_CAMERACOMPONENT_H
#include <Base/CameraBase.h>
#include <Base/ComponentBase.h>
#include <Base/GameObject.h>


//----- CameraComponent�錾
namespace EtherEngine {
    class CameraComponent : public CameraBase, public ComponentBase {
    public:
        // �R���X�g���N�^
        // @ Arg1 : �Q�[���I�u�W�F�N�g
        // @ Arg2 : �����_
        CameraComponent(GameObject* gameObject, const Eigen::Vector3f& look);


        // �X�V����
        virtual void Update(void) override;


        // �J�����f�[�^�A�N�Z�T�[
        CameraData& AccessCameraData(void) { return m_cameraData; }
    };
}


#endif // !I_CAMERACOMPONENT_H
