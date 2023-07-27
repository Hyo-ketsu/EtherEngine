#ifndef I_BASEOBJECT_H_
#define I_BASEOBJECT_H_
#include <Base/IDClass.h>
// @ MEMO : ファイルパスを含めるか検討？


//----- BaseObject 宣言
namespace EtherEngine {
    // GameObject等、外部出力
    class BaseObject {
    public:
        // コンストラクタ
        // @ Arg1 : オブジェクト名
        BaseObject(const std::string& name);


        // オブジェクト名ゲッター
        const std::string& GetName(void) const { return m_name; }
        // オブジェクト名セッター
        void SetName(const std::string& in) { m_name = in; }
        // オブジェクト名アクセサー
        std::string& AccessName(void) { return m_name; }

        // IDゲッター
        const IDClass& GetId(void) const { return m_id; }

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
        std::string m_name;     // オブジェクト名
        IDClass m_id;           // 自身のID
        bool m_isActive;        // そのオブジェクトが有効か
        bool m_isDelete;        // そのオブジェクトは削除済みか
    };
}


#endif // !I_BASEOBJECT_H_
