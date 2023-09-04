#ifndef I_EDITORCAMERA_H
#define I_EDITORCAMERA_H
#include <Base/CameraBase.h>
#include <Base/BaseInput.h>
#include <EtherEngine/EditorComponentBase.h>
#include <EtherEngine/EditorObject.h>


//----- EditorCamera宣言
namespace EtherEngine {
    class EditorCamera : public CameraBase, public EditorComponentBase {
    public:
        // コンストラクタ
        // @ Arg1 : エディターオブジェクト
        EditorCamera(EditorObject* editorObject);


        // カメラ速度ゲッター
        float GetSpeed(void) const { return m_speed; }
        // カメラ速度セッター
        void SetSpeed(const float& in) { m_speed = in; }


        // 初期化処理
        void Start(void) override;
        // 更新処理
        void Update(void) override;

    private:
        float    m_speed;   // カメラの移動速度
        KeyboardInput m_front;   // 前進
        KeyboardInput m_back;    // 後退
        KeyboardInput m_left;    // 左進
        KeyboardInput m_right;   // 右進
        KeyboardInput m_up;      // 上昇
        KeyboardInput m_down;    // 下降
    };
}


#endif // !I_EDITORCAMERA_H
