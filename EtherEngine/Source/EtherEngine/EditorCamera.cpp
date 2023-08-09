#include <EtherEngine/EditorCamera.h>
#include <Base/BaseInput.h>
#include <Base/Converter.h>
#include <EtherEngine/EditorComponentHelper.h>
#include <EtherEngine/EditorDefine.h>


namespace EtherEngine {
    // コンストラクタ
    EditorCamera::EditorCamera(EditorObject* editorObject) 
        : EditorComponentBase(editorObject) 
        , CameraBase(editorObject->AccessTransform().AccessPostion(), editorObject->AccessTransform().AccessPostion() - Eigen::Vector3f(0,0,-10.0f)) 
        , m_speed(EditorDefaultConfig::EDITOR_CAMERA_SPEED)
        , m_front(KeyboardInput('W'))
        , m_back(KeyboardInput('S'))
        , m_left(KeyboardInput('A'))
        , m_right(KeyboardInput('D'))
        , m_up(KeyboardInput('Q'))
        , m_down(KeyboardInput('E')) {
    }


	// 初期化処理
	void EditorCamera::Start(void) {
        ////----- 入力キー初期化
        //m_front = decltype(m_front)(KeyboardInput('W'));
        //m_back  = decltype(m_back)(KeyboardInput('S'));
        //m_left  = decltype(m_left)(KeyboardInput('A'));
        //m_right = decltype(m_right)(KeyboardInput('D'));
        //m_up    = decltype(m_up)(KeyboardInput('Q'));
        //m_down  = decltype(m_down)(KeyboardInput('E'));
	}
    // 更新処理
    void EditorCamera::Update(void) {
        //----- 変数宣言
        auto& transform = EditorComponentHelper::GetEditorObject(this)->AccessTransform();
        Eigen::Vector4f front;

        //----- 前方の計算
        front = decltype(front)(
            (AccessCameraData().GetLook() - transform.AccessPostion()).x(),
            (AccessCameraData().GetLook() - transform.AccessPostion()).y(), 
            (AccessCameraData().GetLook() - transform.AccessPostion()).z(),
            1.0f);

        //----- 正規化
        front.normalize();

        //----- カメラ横方向取得
        DirectX::XMMATRIX gameObjectRotation = DirectX::XMMatrixRotationRollPitchYaw(
            transform.AccessRotation().x(),
            transform.AccessRotation().y(),
            transform.AccessRotation().z());
        Eigen::Matrix4f rotation;
        MathConverter::DXToEigen(gameObjectRotation, &rotation);
        MathConverter::DXToEigen(DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(-90.0f)), &rotation);
        Eigen::Vector4f side = rotation * front;
        MathConverter::DXToEigen(DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(-90.0f)), &rotation);
        Eigen::Vector4f up = rotation * front;

        //----- 水平移動
        {
            Eigen::Vector3f move = { 0.0f,0.0f,0.0f };
            if (InputSystem::IsPress(m_front)) move += Eigen::Vector3f(front.x(), front.y(), front.z());
            if (InputSystem::IsPress(m_back))  move -= Eigen::Vector3f(front.x(), front.y(), front.z());
            if (InputSystem::IsPress(m_left))  move -= Eigen::Vector3f(side.x(), side.y(), side.z());
            if (InputSystem::IsPress(m_right)) move += Eigen::Vector3f(side.x(), side.y(), side.z());
            if (InputSystem::IsPress(m_up))    move += Eigen::Vector3f(up.x(), up.y(), up.z());
            if (InputSystem::IsPress(m_down))  move -= Eigen::Vector3f(up.x(), up.y(), up.z());

            //----- 移動力設定
            move *= m_speed;

            //----- 移動（水平移動なので注視点も同時に移動）
            transform.AccessPostion() += move;
            AccessCameraData().SetLook(AccessCameraData().GetLook() += move);
        }
        //----- 注視点の移動
        // @ MEMO : キーは後で考える
        do {
            if (InputSystem::IsPress(KeyboardInput(VK_SHIFT)) == false) break;

            Eigen::Vector3f move = { 0.0f,0.0f,0.0f };
            if (InputSystem::IsPress(m_front)) move += Eigen::Vector3f(front.x(), front.y(), front.z());
            if (InputSystem::IsPress(m_back))  move -= Eigen::Vector3f(front.x(), front.y(), front.z());
            if (InputSystem::IsPress(m_left))  move -= Eigen::Vector3f(side.x(), side.y(), side.z());
            if (InputSystem::IsPress(m_right)) move += Eigen::Vector3f(side.x(), side.y(), side.z());
            if (InputSystem::IsPress(m_up))    move += Eigen::Vector3f(up.x(), up.y(), up.z());
            if (InputSystem::IsPress(m_down))  move -= Eigen::Vector3f(up.x(), up.y(), up.z());

            //----- 移動力設定
            move *= m_speed;

            //----- 移動
            AccessCameraData().SetLook(AccessCameraData().GetLook() += move);
        } while (false);

        //----- カメラへ設定
        AccessCameraData().SetPos(transform.AccessPostion());
    }
}
