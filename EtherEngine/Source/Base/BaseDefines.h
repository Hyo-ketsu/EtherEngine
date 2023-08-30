#ifndef I_BASEDEFINES_H
#define I_BASEDEFINES_H
#include <Base/ConceptUtility.h>


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
        const std::string SCENE = ".scenedata"; // シーン情報の拡張子
        const std::string CPPCLISCRIPT = ".h";  // スクリプト用拡張子
        const std::string SOLUTION = ".sln";    // ソリューションの拡張子
        const std::string PROJECT = ".vcxproj"; // プロジェクト拡張子
        const std::string PROJECTNAME = "EtherEngineProject";   // プロジェクト名

        const std::string CPPCLISCRIPT_FILE_STRING = R"(//===== 仮で書いてます。のちに修正してください。=====//
#include <C++CLI/UserComponent.h>

public ref class クラス名 : public UserBaseComponent {
public:

}
)";

        const int JSON_DUMP_NUMBER_OF_STAGES = 2;   // JsonのDump数
    }
}


#endif // !I_BASEDEFINES_H
