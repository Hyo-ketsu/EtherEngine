#ifndef I_MSVCMEDIATION_H
#define I_MSVCMEDIATION_H
#include <Base/Singleton.h>
#include <Base/PathClass.h>


//----- MSVCMediation 定義
namespace EtherEngine {
    class MSVCMediation : public Singleton<MSVCMediation> {
    public:
        // デストラクタ
        ~MSVCMediation(void) {}

        // 初期化する
        // @ Arg1 : コマンドプロンプトパス
        // @ Arg2 : MSVCパス
        void Init(const PathClass& cmdPath, const PathClass& msvcPath);
        // 終了処理
        void Uninit(void);


        // コマンド入力
        // @ Ret  : コマンド入力が成功したか
        // @ Arg1 : コマンド入力
        bool Command(const std::string& commnad);


        // 


    private:
        // コンストラクタ
        MSVCMediation(void);

        friend class Singleton<MSVCMediation>;

        std::string m_output;   // 外部出力
        std::string m_error;    // エラー出力
        PROCESS_INFORMATION m_processInfo;
        HANDLE m_childStdInRead;
        HANDLE m_childStdInWrite;
    };
}


#endif // !I_MSVCMEDIATION_H
