#ifndef I_CAMERACOMPONENT_H
#define I_CAMERACOMPONENT_H
#include <Base/CameraBase.h>
#include <CPPCLI/UserComponent.h>
#include <CPPCLI/CPPCLIUtility.h>
#include <CPPCLI/AttributeDefine.h>


//----- CameraComponent 定義
namespace EtherEngine {
    public ref class CameraComponent : public UserBaseComponent {
    public: 
        // 初期化処理
        void Start(void) override;
        // 更新処理
        void Update(void) override;
        // デストラクタ
        ~CameraComponent(void);
        // ファイナライザ
        !CameraComponent(void);

    protected:
        [Attribute::Serialize] UnmanageMaintainer<CameraBase> m_camera;   // カメラ情報
    }; 
}


#endif // !I_CAMERACOMPONENT_H
