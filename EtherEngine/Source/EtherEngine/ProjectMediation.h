#ifndef I_PROJECTMEDIATION_H
#define I_PROJECTMEDIATION_H
#include <Base/Singleton.h>
#include <Base/PathClass.h>


//----- ProjectMediation 宣言
namespace EtherEngine {
    class ProjectMediation : public Singleton<ProjectMediation> {
    public:
        // デストラクタ
        ~ProjectMediation(void);
        

        // プロジェクトファイルゲッター
        PathClass GetVcxproj(void) const { return m_vcxproj; }
        // ソリューションファイルゲッター
        PathClass GetSln(void) const { return m_sln; }


        // 初期化処理
        // @ Arg1 : ソリューション
        // @ Arg2 : プロジェクトファイル
        void Init(const PathClass& sln, const PathClass& vcxproj);
        // 終了処理
        void Uninit(void);


        // .hや.cpp等をプロジェクトに追加する
        // @ Ret  : 追加が行われたか
        // @ Arg1 : 入力ファイル(.hもしくは.cpp)
        bool AddSource(const PathClass& source);
        // .hや.cpp等をプロジェクトから削除する
        // @ Ret  : 削除が行われたか
        // @ Arg1 : 削除ファイル(.hもしくは.cpp)
        bool DeleteSource(const PathClass& source);

    private:
        // コンストラクタ
        ProjectMediation(void);

        friend class Singleton<ProjectMediation>;

        PathClass m_vcxproj;    // プロジェクトファイル
        PathClass m_sln;        // ソリューションファイル
    };
}


#endif // !I_PROJECTMEDIATION_H
