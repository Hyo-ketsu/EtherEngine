#include <Base/CameraBase.h>
#include <Base/BaseDefines.h>
#include <Base/MathUtility.h>
#include <Base/Converter.h>
#include <Base/CameraStorage.h>


//----- CameraData��`
namespace EtherEngine {
    // �R���X�g���N�^
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
    // Json�R���X�g���N�^
    CameraData::CameraData(const std::string& json) {
        this->Input(json);
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


    // �O���o�͂���
    std::string CameraData::Output(void) {
        nlohmann::json json;

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

        return json.dump(FileDefine::JSON_DUMP_NUMBER_OF_STAGES);
    }
    // �O�����͂���
    void CameraData::Input(const std::string& input) {
        nlohmann::json json = nlohmann::json::parse(input);

        auto& cameraData = json["CameraData"];
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


    // �O���o�͂���
    std::string CameraBase::Output(void) {
        nlohmann::json json;

        json["CameraBase"] = m_cameraData.Output();

        return json.dump(FileDefine::JSON_DUMP_NUMBER_OF_STAGES);
    }
    // ���͂���
    void CameraBase::Input(const std::string& input) {
        nlohmann::json json = nlohmann::json::parse(input);

        m_cameraData.Input(json["CameraBase"]);
    }
}
