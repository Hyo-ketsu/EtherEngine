#ifndef I_BASEOBJECTSTORAGE_H
#define I_BASEOBJECTSTORAGE_H
#include <EngineLibrary/ManageSingleton.h>
#include <EngineLibrary/BaseObject.h>


//----- BaseObjectStorage 定義
namespace EtherEngine {
    // BaseObjectを管理するクラス
    public ref class BaseObjectStorage {
        ETHER_ENGINE_MANAGE_SINGLETON(BaseObjectStorage);
    public:
        // BaseObjectを追加する
        // @ Arg1 : 追加するBaseObject
        void AddBaseObject(BaseObject^ baseObject);
        // BaseObjectを削除する
        // @ Ret  : 削除が行われたか
        // @ Arg1 : 削除するBaseObject
        void DeleteBaseObject(BaseObject^ baseObject);
        // BaseObjectを削除する
        // @ Ret  : 削除が行われたか
        // @ Arg1 : 削除するBaseObjectのID
        void DeleteBaseObject(IDClass^ id);


        // IDでBaseObjectを取得する
        // @ Ret  : 取得したBaseObject
        // @ Arg1 : ID
        BaseObject^ GetBaseObject(IDClass^ id);

    private:
        System::Collections::Generic::List<BaseObject^>^ m_baseObjects; // 保持しているベースオブジェクト一覧
    };
}


#endif // !I_BASEOBJECTSTORAGE_H
