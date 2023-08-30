#ifndef I_BASEDEFINES_H
#define I_BASEDEFINES_H
#include <Base/ConceptUtility.h>


//----- �萔��`
namespace EtherEngine {
    //----- FPS
    const float ONE_FRAME = 1.f / 60.f;

    //----- ��ʔ䗦
    namespace AspectDefine {
        // HD�䗦
        template <Concept::ArithmeticConcept T = float>
        const float HD = 16.0f / 9.0f;
    }

    //----- �J�����p�̒萔
    namespace CameraDefine {
        const Eigen::Vector3f UP = { 0.0f,1.0f,0.0f };      // �J�����̏����
        const float FOVY = DirectX::XMConvertToRadians(60); // ����p
        const float ASPECT = AspectDefine::HD<>;     // ��ʃA�X�y�N�g��
        const float NEAR_ = 0.2f;                    // �ŒZ�N���b�v����
        const float FAR_ = 1000.0f;                  // �Œ��N���b�v����
    }

    //----- �t�@�C���p��`
    namespace FileDefine {
        const std::string SCENE = ".scenedata"; // �V�[�����̊g���q
        const std::string CPPCLISCRIPT = ".h";  // �X�N���v�g�p�g���q
        const std::string SOLUTION = ".sln";    // �\�����[�V�����̊g���q
        const std::string PROJECT = ".vcxproj"; // �v���W�F�N�g�g���q
        const std::string PROJECTNAME = "EtherEngineProject";   // �v���W�F�N�g��

        const std::string CPPCLISCRIPT_FILE_STRING = R"(//===== ���ŏ����Ă܂��B�̂��ɏC�����Ă��������B=====//
#include <C++CLI/UserComponent.h>

public ref class �N���X�� : public UserBaseComponent {
public:

}
)";

        const int JSON_DUMP_NUMBER_OF_STAGES = 2;   // Json��Dump��
    }
}


#endif // !I_BASEDEFINES_H
