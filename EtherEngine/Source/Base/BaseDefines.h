#ifndef I_BASEDEFINES_H
#define I_BASEDEFINES_H
#include <Base/ConceptUtility.h>
// @ MEMO : 現状ソリューションファイルを開くことは想定されていません


//----- 型エイリアス定義
namespace EtherEngine {
    // IDで使用する型
    using IDNumberType = ullint;

    // シーン判別型
    using SceneType = IDNumberType;
}


//----- 定数定義
namespace EtherEngine {
    //----- FPS
    const float ONE_FRAME = 1.f / 60.f;




    //----- 画面比率
    namespace AspectDefine {
        // HD比率
        template <Concept::ArithmeticConcept T = float>
        const float HD = 16.0f / 9.0f;
    }


    //----- カメラ用の定数
    namespace CameraDefine {
        const Eigen::Vector3f UP = { 0.0f,1.0f,0.0f };      // カメラの上方向
        const float FOVY = DirectX::XMConvertToRadians(60); // 視野角
        const float ASPECT = AspectDefine::HD<>;     // 画面アスペクト比
        const float NEAR_ = 0.2f;                    // 最短クリップ距離
        const float FAR_ = 1000.0f;                  // 最長クリップ距離
    }


    //----- ファイル用定義
    namespace FileDefine {
        //----- 拡張子定義
        namespace Extended {
            const std::string SCENE = ".scenedata"; // シーン情報の拡張子
            const std::string SCRIPT = ".cs";  // スクリプト用拡張子
            const std::string SOLUTION = ".sln";    // ソリューションの拡張子
            const std::string PROJECT = ".csproj"; // プロジェクト拡張子
            const std::string PROJECT_DATA = ".projdata"; // プロジェクト情報拡張子
        }

        const std::string PROJECT_NAME = "EtherEngineProject";   // プロジェクト名
        const std::string PROJECT_DATA =    // プロジェクトファイル内容
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
        const std::string SOLUTION_DATA = // ソリューションファイル内容
            R"(

)";

        const std::string SCRIPT_FILE_STRING = 
            R"(//===== 仮で書いてます。のちに修正してください。=====//
#include <EngineLibrary/UserComponent.h>

public ref class クラス名 : public UserBaseComponent {
public:

}
)";

        const int JSON_DUMP_NUMBER_OF_STAGES = 2;   // JsonのDump数
    }


    //----- 言語列挙体
    enum class LanguageEnum : char {
        EN = 0, // 英語
        JP,     // 日本語
        None,   // 言語未設定
    };
}


#endif // !I_BASEDEFINES_H
