#include <Base/Transform.h>

using namespace EtherEngine;


// �R���X�g���N�^
// @ Arg1 : ���W(�f�t�H���g�F�S��0)
// @ Arg2 : �g�k(�f�t�H���g�F�S��0)
// @ Arg3 : ��](�f�t�H���g�F�S��1)
Transform::Transform(Eigen::Vector3f pos, Eigen::Vector3f sca, Eigen::Vector3f rot) 
    : m_postion(pos)
    , m_scale(sca)
    , m_rotation(rot) {
}
