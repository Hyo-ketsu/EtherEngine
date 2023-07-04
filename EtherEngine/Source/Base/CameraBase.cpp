#include <Base/CameraBase.h>
#include <Base/BaseDefines.h>
#include <Base/MathUtility.h>
#include <Base/Converter.h>
#include <Base/CameraStorage.h>


//----- CameraData��`
namespace EtherEngine {
    // �R���X�g���N�^
    // @ Arg1 : ���W
    // @ Arg2 : �����_
    CameraData::CameraData(const Eigen::Vector3f& pos, const Eigen::Vector3f& look) 
        : m_pos(pos)
        , m_look(look)
        , m_up(CameraDefine::UP)
        , m_fovy(CameraDefine::FOVY)
        , m_aspect(CameraDefine::ASPECT)
        , m_near(CameraDefine::NEAR_)
        , m_far(CameraDefine::FAR_) {
        SetPos(pos);
        SetLook(look);
    }


    // ���W�Z�b�^�[
    void CameraData::SetPos(const Eigen::Vector3f& in) {
        m_pos = in;
        CheckPosLookPosition();
    }
    // �����_�Z�b�^�[
    void CameraData::SetLook(const Eigen::Vector3f& in) {
        m_look = in;
        CheckPosLookPosition();
    }
    // ����p�Z�b�^�[
    void CameraData::SetFovy(const float in) {
        m_fovy = fabsf(in);
        if (MathUtility::FloatEqual(m_fovy)) m_fovy = DirectX::XMConvertToRadians(1);
    }
    // ��ʃA�X�y�N�g�䗦�Z�b�^�[
    void CameraData::SetAspect(const float in) {
        m_aspect = fabsf(in);
        if (MathUtility::FloatEqual(m_aspect)) m_aspect = DirectX::XMConvertToRadians(1);
    }
    // �ŒZ�N���b�v�����Z�b�^�[
    void CameraData::SetNear(const float in) {
        m_near = in;
        // ���l�ȉ��ɂ���ƕ��Q������悤�Ȃ�t���܂�
        // if (m_near < 1.0f) m_near = 1.0f;
        if (m_near > m_far) m_near = m_far;
    }
    // �Œ��N���b�v�����Z�b�^�[
    void CameraData::SetFar(const float in) {
        m_far = in;
        // ���l�ȏ�ɂ���ƕ��Q������悤�Ȃ�t���܂�
        // if (m_far > 1000.0f) m_far = 1000.0f;
        if (m_far < m_near) m_far = m_near;
    }


    // ���W�ƒ����_�������W�̏ꍇ�ɗ�O���o�͂��܂�
    void CameraData::CheckPosLookPosition(void) const {
        if (MathUtility::FloatEqual(m_pos.x(), m_look.x()) &&
            MathUtility::FloatEqual(m_pos.y(), m_look.y()) &&
            MathUtility::FloatEqual(m_pos.z(), m_look.z()) 
            ) {
            throw std::exception("Exception! pos and look are the same coordinates.");
        }
    }
}


//----- CameraBase��`
namespace EtherEngine {
    // �R���X�g���N�^
    CameraBase::CameraBase(const Eigen::Vector3f& pos, const Eigen::Vector3f& look)
        : CameraBase(CameraData(pos,look)) {
    }
    // �R���X�g���N�^
    CameraBase::CameraBase(const CameraData& data) 
        : m_cameraData(data)
        , m_id(CameraStorage::Get()->AddData(*this)) {
    }
    // �f�X�g���N�^
    CameraBase::~CameraBase(void) {
    }


    // �r���[�s����擾����
    Eigen::Matrix4f CameraBase::GetView(const bool isTranspose) const {
        //----- �ϐ��錾
        DirectX::XMFLOAT3 pos;
        DirectX::XMFLOAT3 look;
        DirectX::XMFLOAT3 up;
        Eigen::Matrix4f ret;

        //----- ������
        MathConverter::EigenToDX(m_cameraData.GetPos(), &pos);
        MathConverter::EigenToDX(m_cameraData.GetLook(), &look);
        MathConverter::EigenToDX(m_cameraData.GetUp(), &up);

        //----- �r���[�s��v�Z
        auto view = DirectX::XMMatrixLookAtLH(
            DirectX::XMLoadFloat3(&pos), DirectX::XMLoadFloat3(&look), DirectX::XMLoadFloat3(&up)
        );

        //----- �]�u
        if (isTranspose) view = DirectX::XMMatrixTranspose(view);
        
        //----- �ϊ�
        MathConverter::DXToEigen(view, &ret);

        //----- �ԋp
        return ret;
    }
    // �v���W�F�N�V�����s����擾����
    Eigen::Matrix4f CameraBase::GetProjection(const bool isTranspose) const {
        //----- �ϐ��錾
        Eigen::Matrix4f ret;

        //----- �v���W�F�N�V�����s��v�Z
        auto projection = DirectX::XMMatrixPerspectiveFovLH(m_cameraData.GetFovy(), m_cameraData.GetAspect(), m_cameraData.GetNear(), m_cameraData.GetFar());

        //----- �]�u
        if (isTranspose) projection = DirectX::XMMatrixTranspose(projection);

        //----- �ϊ�
        MathConverter::DXToEigen(projection, &ret);

        //----- �ԋp
        return ret;
    }
}
