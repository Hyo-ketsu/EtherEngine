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
        InputKey m_front;   // 前進
        InputKey m_back;    // 後退
        InputKey m_left;    // 左進
        InputKey m_right;   // 右進
        InputKey m_up;      // 上昇
        InputKey m_down;    // 下降
    };
}


#endif // !I_EDITORCAMERA_H
