#ifndef I_CAMERACOMPONENT_H
#define I_CAMERACOMPONENT_H
#include <Base/CameraBase.h>
#include <Base/ComponentBase.h>
#include <Base/GameObject.h>


//----- CameraComponent宣言
namespace EtherEngine {
    class CameraComponent : public CameraBase, public ComponentBase {
    public:
        // コンストラクタ
        // @ Arg1 : ゲームオブジェクト
        // @ Arg2 : 注視点
        CameraComponent(GameObject* gameObject, const Eigen::Vector3f& look);


        // 更新処理
        virtual void Update(void) override;


        // カメラデータアクセサー
        CameraData& AccessCameraData(void) { return m_cameraData; }
    };
}


#endif // !I_CAMERACOMPONENT_H
