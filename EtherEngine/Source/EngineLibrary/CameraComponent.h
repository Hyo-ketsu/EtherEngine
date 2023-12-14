#ifndef I_CAMERACOMPONENT_H
#define I_CAMERACOMPONENT_H
#include <Base/CameraBase.h>
#include <EngineLibrary/UserComponent.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/AttributeDefine.h>


//----- CameraComponent 定義
//#pragma managed
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
