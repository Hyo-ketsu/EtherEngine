#ifndef I_CAMERACOMPONENT_H
#define I_CAMERACOMPONENT_H
#include <Base/CameraBase.h>
#include <EngineLibrary/Component.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/AttributeDefine.h>


//----- CameraComponent ��`
namespace EtherEngine {
    public ref class CameraComponent : public Component {
    public: 
        // ����������
        void Start(void) override;
        // �X�V����
        void Update(void) override;
        // �f�X�g���N�^
        ~CameraComponent(void);
        // �t�@�C�i���C�U
        !CameraComponent(void);

    protected:
        [Attribute::Serialize] UnmanageMaintainer<CameraBase> m_camera;   // �J�������
    }; 
}


#endif // !I_CAMERACOMPONENT_H
