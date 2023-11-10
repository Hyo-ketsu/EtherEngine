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
        // @ Arg1 : 入力コマンド
        void WriteCmd(const std::string& commnad);
        // コマンドプロンプト出力取得
        // @ Memo : この関数は待ちなどは一切行いません。
        // @ Ret  : 取得結果
        std::string ReadCmd(void);
        // コマンドプロンプトエラー出力取得
        // @ Memo : この関数は待ちなどは一切行いません。
        // @ Ret  : 取得結果
        std::string ReadCmdError(void);

    private:
        // コンストラクタ
        MSVCMediation(void);


        // ハンドルのクローズ
        void HandleClose(void);

        friend class Singleton<MSVCMediation>;

        PROCESS_INFORMATION m_processInfo;
        bool m_isInit;  // 初期化されているか
        HANDLE m_childRead;   // cmd用読み取り用パイプ
        HANDLE m_childWrite;  // cmd用書き込み用パイプ
        HANDLE m_read;        // 読み取り用パイプ
        HANDLE m_write;       // 書き込み用パイプ
        HANDLE m_childErrorRead;   // エラー読み取り用パイプ
        HANDLE m_childErrorWrite;  // エラー書き込み用パイプ
    };
}


#endif // !I_MSVCMEDIATION_H
