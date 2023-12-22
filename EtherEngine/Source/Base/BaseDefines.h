#ifndef I_BASEDEFINES_H
#define I_BASEDEFINES_H
#include <Base/ConceptUtility.h>
// @ MEMO : ����\�����[�V�����t�@�C�����J�����Ƃ͑z�肳��Ă��܂���


//----- �^�G�C���A�X��`
namespace EtherEngine {
    // ID�Ŏg�p����^
    using IDNumberType = ullint;

    // �V�[�����ʌ^
    using SceneType = IDNumberType;
}


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
        //----- �g���q��`
        namespace Extended {
            const std::string SCENE = ".scenedata"; // �V�[�����̊g���q
            const std::string SCRIPT = ".cs";  // �X�N���v�g�p�g���q
            const std::string SOLUTION = ".sln";    // �\�����[�V�����̊g���q
            const std::string PROJECT = ".csproj"; // �v���W�F�N�g�g���q
            const std::string PROJECT_DATA = ".projdata"; // �v���W�F�N�g���g���q
        }

        const std::string PROJECT_NAME = "EtherEngineProject";   // �v���W�F�N�g��
        const std::string PROJECT_DATA =    // �v���W�F�N�g�t�@�C�����e
            R"(
<Project Sdk="Microsoft.NET.Sdk">

  <PropertyGroup>
    <TargetFramework>net7.0</TargetFramework>
    <ImplicitUsings>enable</ImplicitUsings>
    <Nullable>enable</Nullable>
    <AllowUnsafeBlocks>True</AllowUnsafeBlocks>
    <BaseOutputPath>Build\</BaseOutputPath>
    <BaseIntermediateOutputPath>Object\</BaseIntermediateOutputPath>
  </PropertyGroup>

  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|AnyCPU'">
    <DefineConstants>$(DefineConstants);_DEBUG</DefineConstants>
  </PropertyGroup>

  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|AnyCPU'">
    <DefineConstants>$(DefineConstants);_RELEASE</DefineConstants>
  </PropertyGroup>

</Project>
)";
        const std::string SOLUTION_DATA = // �\�����[�V�����t�@�C�����e
            R"(

)";

        const std::string SCRIPT_FILE_STRING = 
            R"(//===== ���ŏ����Ă܂��B�̂��ɏC�����Ă��������B=====//
#include <EngineLibrary/UserComponent.h>

public ref class �N���X�� : public UserBaseComponent {
public:

}
)";

        const int JSON_DUMP_NUMBER_OF_STAGES = 2;   // Json��Dump��
    }


    //----- ����񋓑�
    enum class LanguageEnum : char {
        EN = 0, // �p��
        JP,     // ���{��
        None,   // ���ꖢ�ݒ�
    };
}


#endif // !I_BASEDEFINES_H
