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
        json["Transform"] = {
            {"px", m_postion.x()}, {"py", m_postion.y()}, {"pz", m_postion.z()},
            {"sx", m_scale.x()}, {"sy", m_scale.y()}, {"sz", m_scale.z()},
            {"rx", m_rotation.x()}, {"ry", m_rotation.y()}, {"rz", m_rotation.z()},
        };

        return json.dump();
    }
    // �O������
    void Transform::Input(const std::string& input) {
        nlohmann::json json = input;

        m_postion.x()  = json["Transform"]["px"]; m_postion.y()  = json["Transform"]["py"]; m_postion.z()  = json["Transform"]["pz"];
        m_scale.x()    = json["Transform"]["sx"]; m_scale.y()    = json["Transform"]["sy"]; m_scale.z()    = json["Transform"]["sz"];
        m_rotation.x() = json["Transform"]["rx"]; m_rotation.y() = json["Transform"]["ry"]; m_rotation.z() = json["Transform"]["rz"];
    }
}
