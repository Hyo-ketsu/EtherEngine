#include <Base/CameraBase.h>
#include <Base/MathUtility.h>
#include <Base/BaseDefines.h>
#include <Base/Converter.h>
#include <Base/CameraStorage.h>
#include <Base/EditorException.h>


//----- CameraData��`
namespace EtherEngine {
    // �R���X�g���N�^
    CameraData::CameraData(const IDNumberType& id, const Eigen::Vector3f& pos, const Eigen::Vector3f& look)
        : m_id(id)
        , m_pos(pos)
        , m_look(look)
        , m_up(CameraDefine::UP)
        , m_fovy(CameraDefine::FOVY)
        , m_aspect(CameraDefine::ASPECT)
        , m_near(CameraDefine::NEAR_)
        , m_far(CameraDefine::FAR_) {
        SetPos(pos);
        SetLook(look);
    }
    // Json�R���X�g���N�^
    CameraData::CameraData(const std::string& json) {
        this->Input(json);
    }


    // ���W�Q�b�^�[
    Eigen::Vector3f CameraData::GetPos(void) const {
        CheckPosLookPosition();
        return m_pos;
    }
    // ���W�Z�b�^�[
    void CameraData::SetPos(const Eigen::Vector3f& in) {
        m_pos = in;
    }
    // �����_�Q�b�^�[
    Eigen::Vector3f CameraData::GetLook(void) const {
        CheckPosLookPosition();
        return m_look;
    }
    // �����_�Z�b�^�[
    void CameraData::SetLook(const Eigen::Vector3f& in) {
        m_look = in;
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
        // @ MEMO : ���l�ȉ��ɂ���ƕ��Q������悤�Ȃ�t���܂�
        // if (m_near < 1.0f) m_near = 1.0f;
        if (m_near > m_far) m_near = m_far;
    }
    // �Œ��N���b�v�����Z�b�^�[
    void CameraData::SetFar(const float in) {
        m_far = in;
        // @ MEMO : ���l�ȏ�ɂ���ƕ��Q������悤�Ȃ�t���܂�
        // if (m_far > 1000.0f) m_far = 1000.0f;
        if (m_far < m_near) m_far = m_near;
    }


    // �O���o�͂���
    Json CameraData::Output(void) {
        nlohmann::json json;

        json["CameraData"]["id"] = m_pos.x();
        json["CameraData"]["posX"] = m_pos.x();
        json["CameraData"]["posY"] = m_pos.y();
        json["CameraData"]["posZ"] = m_pos.z();
        json["CameraData"]["lookX"] = m_look.x();
        json["CameraData"]["lookY"] = m_look.y();
        json["CameraData"]["lookZ"] = m_look.z();
        json["CameraData"]["upX"] = m_up.x();
        json["CameraData"]["upZ"] = m_up.z();
        json["CameraData"]["upY"] = m_up.y();
        json["CameraData"]["priority"] = m_priority;
        json["CameraData"]["fovy"]     = m_fovy;
        json["CameraData"]["aspect"]   = m_aspect;
        json["CameraData"]["near"]     = m_near;
        json["CameraData"]["far"]      = m_far;

        return json;
    }
    // �O�����͂���
    void CameraData::Input(const Json& input) {
        auto& cameraData = input["CameraData"];
        m_id = cameraData["id"];
        m_pos.x() = cameraData["posX"];
        m_pos.y() = cameraData["posY"];
        m_pos.z() = cameraData["posZ"];
        m_look.x() = cameraData["lookX"];
        m_look.y() = cameraData["lookY"];
        m_look.z() = cameraData["lookZ"];
        m_up.x() = cameraData["upX"];
        m_up.z() = cameraData["upZ"];
        m_up.y() = cameraData["upY"];
        m_priority = cameraData["priority"];
        m_fovy     = cameraData["fovy"];
        m_aspect   = cameraData["aspect"];
        m_near     = cameraData["near"];
        m_far      = cameraData["far"];
    }


    // ���W�ƒ����_�������W�̏ꍇ�ɗ�O���o�͂��܂�
    void CameraData::CheckPosLookPosition(void) const {
        if (MathUtility::FloatEqual(m_pos.x(), m_look.x()) &&
            MathUtility::FloatEqual(m_pos.y(), m_look.y()) &&
            MathUtility::FloatEqual(m_pos.z(), m_look.z()) 
            ) {
            throw EditorException("Exception! pos and look are the same coordinates.");
        }
    }


    // �r���[�s����擾����
    Eigen::Matrix4f CameraData::GetView(const bool isTranspose) const {
        //----- �ϐ��錾
        DirectX::XMFLOAT3 pos;
        DirectX::XMFLOAT3 look;
        DirectX::XMFLOAT3 up;
        Eigen::Matrix4f ret;

        //----- ������
        MathConverter::EigenToDX(GetPos(), &pos);
        MathConverter::EigenToDX(GetLook(), &look);
        MathConverter::EigenToDX(GetUp(), &up);

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
    Eigen::Matrix4f CameraData::GetProjection(const bool isTranspose) const {
        //----- �ϐ��錾
        Eigen::Matrix4f ret;

        //----- �v���W�F�N�V�����s��v�Z
        auto projection = DirectX::XMMatrixPerspectiveFovLH(GetFovy(), GetAspect(), GetNear(), GetFar());

        //----- �]�u
        if (isTranspose) projection = DirectX::XMMatrixTranspose(projection);

        //----- �ϊ�
        MathConverter::DXToEigen(projection, &ret);

        //----- �ԋp
        return ret;
    }
}


//----- CameraBase��`
namespace EtherEngine {
    // �R���X�g���N�^
    CameraBase::CameraBase(const Eigen::Vector3f& pos, const Eigen::Vector3f& look, const bool isRegister, const int priority)
        : CameraBase(CameraData(m_id, pos, look), isRegister, priority) {
    }
    // �R���X�g���N�^
    CameraBase::CameraBase(const CameraData& data, const bool isRegister, const int priority)
        : m_cameraData(std::make_shared<CameraData>(data)) {
        if (isRegister) {
            m_id = CameraSystem::Get()->AddData(std::weak_ptr<CameraData>(m_cameraData), priority);
        }
    }
    // �f�X�g���N�^
    CameraBase::~CameraBase(void) {
    }


    // �r���[�s����擾����
    Eigen::Matrix4f CameraBase::GetView(const bool isTranspose) const {
        return m_cameraData->GetView();
    }
    // �v���W�F�N�V�����s����擾����
    Eigen::Matrix4f CameraBase::GetProjection(const bool isTranspose) const {
        return m_cameraData->GetProjection();
    }


    // �O���o�͂���
    Json CameraBase::Output(void) {
        nlohmann::json json;

        json["CameraBase"] = m_cameraData->Output();

        return json;
    }
    // ���͂���
    void CameraBase::Input(const Json& input) {
        m_cameraData->Input(input["CameraBase"]);
    }
}
