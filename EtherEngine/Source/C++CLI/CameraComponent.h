#ifndef I_CAMERACOMPONENT_H
#define I_CAMERACOMPONENT_H
#include <Base/CameraBase.h>
#include <C++CLI/UserComponent.h>
#include <C++CLI/C++CLIUtility.h>
#include <C++CLI/AttributeDefine.h>


//----- CameraComponent 定義
namespace EtherEngine {
#ifndef CPPCLI_CPPCLI_CLASS_DECLARATION
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
#endif
}


#endif // !I_CAMERACOMPONENT_H
