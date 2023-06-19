#ifndef I_BASEDEFINES_H
#define I_BASEDEFINES_H
#include <Base/ConceptUtility.h>

//// �R�s�[�R���X�g���N�^��`
//#define DEFAULT_COPY_CONSTRUCTOR(type) type(const type& copy) = default
//// ���[�u�R���X�g���N�^��`
//#define DEFAULT_MOVE_CONSTRUCTOR(type) type(type&& move) = default

//----- �萔��`
namespace EtherEngine {
    // ��ʔ䗦
    namespace AspectDefine {
        // HD�䗦
        template <Concept::ArithmeticConcept T = float>
        const float HD = 16.0f / 9.0f;
    }
    // �J�����p�̒萔
    namespace CameraDefine {
        const Eigen::Vector3f UP = { 0.0f,1.0f,0.0f };      // �J�����̏����
        const float FOVY = DirectX::XMConvertToRadians(60); // ����p
        const float ASPECT = AspectDefine::HD<>;    // ��ʃA�X�y�N�g��
        const float NEAR = 0.2f;                    // �ŒZ�N���b�v����
        const float FAR = 1000.0f;                  // �Œ��N���b�v����
    }
}


#endif // !I_BASEDEFINES_H
