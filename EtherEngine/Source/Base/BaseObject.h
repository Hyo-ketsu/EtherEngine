#ifndef I_BASEOBJECT_H_
#define I_BASEOBJECT_H_
#include <Base/EtherEngineUtility.h>
#include <Base/BaseDefines.h>
// @ MEMO : ファイルパスを含めるか検討？


//----- BaseObject 宣言
namespace EtherEngine {
    // エンジンで汎用的に使われる基底クラス
    class BaseObject {
    public:
        // コンストラクタ
        // @ Arg1 : オブジェクト名
        BaseObject(const std::string& name);


        // IDゲッター
        const IDNumberType& GetId(void) const { return m_id; }
        // IDセッター
        void SetId(const IDNumberType& in) { m_id = in; }

        // オブジェクトアクティブゲッター
        bool GetActive(void) const { return m_isActive; }
        // オブジェクトアクティブセッター
        void SetActive(const bool in) { m_isActive = in; }

        // 削除済みゲッター
        bool GetDelete(void) const { return m_isDelete; }


        // このオブジェクトを削除する
        void DeleteObject(void);
        // このオブジェクトが使えないか判定する
        // @ Ret  : 使用できないなら true
        bool IsUnvalidObject(void) const;

    private:
        IDNumberType m_id;      // 自身のID
        bool m_isActive;        // そのオブジェクトが有効か
        bool m_isDelete;        // そのオブジェクトは削除済みか
    };
}


#endif // !I_BASEOBJECT_H_
