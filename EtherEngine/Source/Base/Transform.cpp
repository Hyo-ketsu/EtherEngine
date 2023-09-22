#include <Base/Transform.h>
#include <Base/MathUtility.h>
#include <Base/BaseDefines.h>
#include <Base/Converter.h>


namespace EtherEngine {
    // �R���X�g���N�^
    // @ Arg1 : ���W(�f�t�H���g�F�S��0)
    // @ Arg2 : �g�k(�f�t�H���g�F�S��0)
    // @ Arg3 : ��](�f�t�H���g�F�S��1)
    Transform::Transform(Eigen::Vector3f pos, Eigen::Vector3f sca, Eigen::Vector3f rot)
        : m_postion(pos)
        , m_scale(sca)
        , m_rotation(rot) {
    }


    // ���[���h�s����쐬����
    Eigen::Matrix4f Transform::CreateWorld(void) const {
        auto toRad = [](float in) {return DirectX::XMConvertToRadians(in); };    // �V���[�g�J�b�g�����_
        Eigen::Matrix4f ret{};
        auto mat =
            DirectX::XMMatrixScaling(m_scale.x(), m_scale.y(), m_scale.z()) *
            DirectX::XMMatrixRotationX(toRad(m_rotation.x())) *
            DirectX::XMMatrixRotationY(toRad(m_rotation.y())) *
            DirectX::XMMatrixRotationZ(toRad(m_rotation.z())) *
            DirectX::XMMatrixTranslation(m_postion.x(), m_postion.y(), m_postion.z());

        MathConverter::DXToEigen(mat, &ret);
        return ret;
    }


    // ���Z
    Transform Transform::operator+(const Transform& transform) {
        Transform ret = *this;
        ret.m_postion += transform.m_postion;
        ret.m_rotation += transform.m_rotation;
        ret.m_scale += transform.m_scale;
        return ret;
    }
    // ���Z
    Transform Transform::operator-(const Transform& transform) {
        Transform ret = *this;
        ret.m_postion -= transform.m_postion;
        ret.m_rotation -= transform.m_rotation;
        ret.m_scale -= transform.m_scale;
        return ret;
    }
    // ���
    Transform& Transform::operator=(const Transform& transform) {
        m_postion = transform.m_postion;
        m_rotation = transform.m_rotation;
        m_scale = transform.m_scale;
        return *this;
    }
    // ���Z���
    Transform& Transform::operator+=(const Transform& transform) {
        m_postion += transform.m_postion;
        m_rotation += transform.m_rotation;
        m_scale += transform.m_scale;
        return *this;
    }
    // ���Z���
    Transform& Transform::operator-=(const Transform& transform) {
        m_postion -= transform.m_postion;
        m_rotation -= transform.m_rotation;
        m_scale -= transform.m_scale;
        return *this;
    }


    // �O���o��
    Json Transform::Output(void) {
        nlohmann::json json;

        json["Transform"]["px"] = m_postion.x(); 
        json["Transform"]["py"] = m_postion.y(); 
        json["Transform"]["pz"] = m_postion.z(); 
        json["Transform"]["sx"] = m_scale.x(); 
        json["Transform"]["sy"] = m_scale.y(); 
        json["Transform"]["sz"] = m_scale.z(); 
        json["Transform"]["rx"] = m_rotation.x(); 
        json["Transform"]["ry"] = m_rotation.y(); 
        json["Transform"]["rz"] = m_rotation.z(); 

        return json;
    }
    // �O������
    void Transform::Input(const Json& input) {
        auto& transform = input["Transform"];
        m_postion.x() = transform["px"];
        m_postion.y() = transform["py"];
        m_postion.z() = transform["pz"];
        m_scale.x() = transform["sx"];
        m_scale.y() = transform["sy"];
        m_scale.z() = transform["sz"];
        m_rotation.x() = transform["rx"];
        m_rotation.y() = transform["ry"];
        m_rotation.z() = transform["rz"];
    }
}
