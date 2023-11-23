#ifndef I_CONVERTMANAGE_H
#define I_CONVERTMANAGE_H
#include <Base/PathClass.h>
#include <EngineLibrary/EngineLibraryDefine.h>


//----- 変換マクロ
namespace EtherEngine {
#define UNMANAGE_TO_MANAGE_STRING(text) gcnew System::String(text.c_str())
}


//----- 変換関数
namespace EtherEngine {
#ifdef _ENGINELIBRARY
    //----- マネージからアンマネージへの変換
    public ref class ManageToUnmanage {
    public:
        // 文字列変換
        static std::string String(System::String^ manage);

        // パス変換
        static PathClass Path(PathString^ manage);
    };
#endif
}

#endif // !I_CONVERTMANAGE_H
