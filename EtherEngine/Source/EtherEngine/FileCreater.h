#ifndef I_FILECREATER_H
#define I_FILECREATER_H
#include <Base/PathClass.h>
#include <Base/EtherEngineUtility.h>


namespace EtherEngine {
    // @ ファイルを生成、同時に(行うのであれば)処理を行う
    // @ Ret  : 生成ファイル
    // @ Arg1 : ファイル名
    // @ Arg2 : ファイル拡張子
    // @ Arg3 : ファイル生成ディレクトリ
    // @ Arg4 : ファイル命名規則
    // @ Arg5 : 生成時にファイルに与える文字列(Default : "")
    // @ Arg6 : ファイルではなくディレクトリを生成するか(Default : false)
    PathClass FileCreate(const std::string& fileName, const PathClass& extension, const PathClass& createDirectory, 
        const Utilty::DuplicationNameObjectName& nameRule, const std::string& fileString = "", bool isCreateDirectory = false);
}


#endif // !I_FILECREATER_H
