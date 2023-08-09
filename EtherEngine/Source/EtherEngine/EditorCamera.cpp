#include <EtherEngine/EditorCamera.h>
#include <Base/BaseInput.h>
#include <Base/Converter.h>
#include <EtherEngine/EditorComponentHelper.h>
#include <EtherEngine/EditorDefine.h>


namespace EtherEngine {
    // �R���X�g���N�^
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


	// ����������
	void EditorCamera::Start(void) {
        ////----- ���̓L�[������
        //m_front = decltype(m_front)(KeyboardInput('W'));
        //m_back  = decltype(m_back)(KeyboardInput('S'));
        //m_left  = decltype(m_left)(KeyboardInput('A'));
        //m_right = decltype(m_right)(KeyboardInput('D'));
        //m_up    = decltype(m_up)(KeyboardInput('Q'));
        //m_down  = decltype(m_down)(KeyboardInput('E'));
	}
    // �X�V����
    void EditorCamera::Update(void) {
        //----- �ϐ��錾
        auto& transform = EditorComponentHelper::GetEditorObject(this)->AccessTransform();
        Eigen::Vector4f front;

        //----- �O���̌v�Z
        front = decltype(front)(
            (AccessCameraData().GetLook() - transform.AccessPostion()).x(),
            (AccessCameraData().GetLook() - transform.AccessPostion()).y(), 
            (AccessCameraData().GetLook() - transform.AccessPostion()).z(),
            1.0f);

        //----- ���K��
        front.normalize();

        //----- �J�����������擾
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

        //----- �����ړ�
        {
            Eigen::Vector3f move = { 0.0f,0.0f,0.0f };
            if (InputSystem::IsPress(m_front)) move += Eigen::Vector3f(front.x(), front.y(), front.z());
            if (InputSystem::IsPress(m_back))  move -= Eigen::Vector3f(front.x(), front.y(), front.z());
            if (InputSystem::IsPress(m_left))  move -= Eigen::Vector3f(side.x(), side.y(), side.z());
            if (InputSystem::IsPress(m_right)) move += Eigen::Vector3f(side.x(), side.y(), side.z());
            if (InputSystem::IsPress(m_up))    move += Eigen::Vector3f(up.x(), up.y(), up.z());
            if (InputSystem::IsPress(m_down))  move -= Eigen::Vector3f(up.x(), up.y(), up.z());

            //----- �ړ��͐ݒ�
            move *= m_speed;

            //----- �ړ��i�����ړ��Ȃ̂Œ����_�������Ɉړ��j
            transform.AccessPostion() += move;
            AccessCameraData().SetLook(AccessCameraData().GetLook() += move);
        }
        //----- �����_�̈ړ�
        // @ MEMO : �L�[�͌�ōl����
        do {
            if (InputSystem::IsPress(KeyboardInput(VK_SHIFT)) == false) break;

            Eigen::Vector3f move = { 0.0f,0.0f,0.0f };
            if (InputSystem::IsPress(m_front)) move += Eigen::Vector3f(front.x(), front.y(), front.z());
            if (InputSystem::IsPress(m_back))  move -= Eigen::Vector3f(front.x(), front.y(), front.z());
            if (InputSystem::IsPress(m_left))  move -= Eigen::Vector3f(side.x(), side.y(), side.z());
            if (InputSystem::IsPress(m_right)) move += Eigen::Vector3f(side.x(), side.y(), side.z());
            if (InputSystem::IsPress(m_up))    move += Eigen::Vector3f(up.x(), up.y(), up.z());
            if (InputSystem::IsPress(m_down))  move -= Eigen::Vector3f(up.x(), up.y(), up.z());

            //----- �ړ��͐ݒ�
            move *= m_speed;

            //----- �ړ�
            AccessCameraData().SetLook(AccessCameraData().GetLook() += move);
        } while (false);

        //----- �J�����֐ݒ�
        AccessCameraData().SetPos(transform.AccessPostion());
    }
}
