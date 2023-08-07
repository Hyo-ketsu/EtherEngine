#include <Base/Transform.h>


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


    // �O���o��
    std::string Transform::Output(void) {
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

        return json.dump(IInOuter::msc_dump);
    }
    // �O������
    void Transform::Input(const std::string& input) {
        nlohmann::json json = nlohmann::json::parse(input);

        auto& transform = json["Transform"];
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
