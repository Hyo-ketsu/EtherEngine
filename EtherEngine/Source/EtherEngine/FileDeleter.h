#ifndef I_FILEDELETER_H
#define I_FILEDELETER_H
#include <Base/PathClass.h>


//----- FileDelete 定義
namespace EtherEngine {
    // 入力ファイル・ディレクトリを削除する
    // @ Ret  : 入力ファイル・ディレクトリが削除されたか
    // @ Arg1 : 削除ファイル・ディレクトリ
    // @ Arg2 : もしディレクトリ削除時、再帰的にディレクトリの削除を行う。通常ファイル時は無効(Default : ture)
    bool FileDelete(const PathClass& deleteFile, bool isRecursion = true);
}


#endif // !I_FILEDELETER_H
