#ifndef I_PROJECTMEDIATION_H
#define I_PROJECTMEDIATION_H
#include <Base/Singleton.h>
#include <Base/PathClass.h>


#pragma unmanaged
//----- ProjectMediation 宣言
namespace EtherEngine {
    // vcxproj等との仲介を行うクラス
    // @ MEMO : 現在はエンジン起動時は強制的に「更新されている」ものとします（のちにこのファイル状況をエクスポートできるようにする？）
    class ProjectMediation : public Singleton<ProjectMediation> {
    public:
        // デストラクタ
        ~ProjectMediation(void);
        

        // プロジェクトファイルゲッター
        PathClass GetVcxproj(void) const { return m_vcxproj; }
        // ソリューションファイルゲッター
        PathClass GetSln(void) const { return m_sln; }

        // ファイル更新情報ゲッター
        bool GetIsUpdateFile(void) const { return m_isUpdateFile; }


        // 初期化処理
        // @ Arg1 : ソリューション
        // @ Arg2 : プロジェクトファイル
        void Init(const PathClass& sln, const PathClass& vcxproj);
        // 終了処理
        void Uninit(void);


        // ファイルをプロジェクトに追加する
        // @ Ret  : 追加が行われたか
        // @ Arg1 : 入力ファイル(.hもしくは.cpp)
        bool AddSource(const PathClass& source);
        // ファイルをプロジェクトから削除する
        // @ Ret  : 削除が行われたか
        // @ Arg1 : 削除ファイル(.hもしくは.cpp)
        bool DeleteSource(const PathClass& source);


        // アセンブリをリフレッシュする
        // @ Ret  : 成功したか
        bool RefreshAssembly(void);
        // アセンブリを強制リフレッシュする
        // @ Ret  : 成功したか
        bool CoercionRefreshAssembly(void);


        // 更新情報更新
        // @ Memo : 更新ついでに更新がされているかも判定します(結果はGetIsUpdateFileで確認可能)。
        void FileUpdateDataUpdate(void);

    private:
        // コンストラクタ
        ProjectMediation(void);

        friend class Singleton<ProjectMediation>;

        bool m_isUpdateFile;    // ファイルが更新されているか
        PathClass m_vcxproj;    // プロジェクトファイル
        PathClass m_sln;        // ソリューションファイル
        std::vector<std::string> m_projectFile;   // プロジェクトに含まれている.hや.cpp
        std::unordered_map<std::string, SYSTEMTIME> m_projectFileTime;    // プロジェクトに含まれているファイルの最終更新日
    };
}


#endif // !I_PROJECTMEDIATION_H
