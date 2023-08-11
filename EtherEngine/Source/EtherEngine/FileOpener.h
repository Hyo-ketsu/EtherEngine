#ifndef I_FILEOPENER_H
#define I_FILEOPENER_H
#include <Base/PathClass.h>


//----- FileOpen 宣言
namespace EtherEngine {
    // ファイルを開く
    // @ Arg1 : 開くファイル
    void FileOpen(const PathClass& file);
}


#endif // !I_FILEOPENER_H
