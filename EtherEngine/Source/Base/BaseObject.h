#ifndef I_BASEOBJECT_H_
#define I_BASEOBJECT_H_

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

        // オブジェクトアクティブゲッター
        bool GetActive(void) const { return m_isActive; }
        // オブジェクトアクティブセッター
        void SetActive(const bool in) { m_isActive = in; }

        // 削除済みゲッター
        bool GetDelete(void) const { return m_isDelete; }


        // このオブジェクトを削除する
        void DeleteObject(void);

    private:
        std::string m_name;     // オブジェクト名
        bool m_isActive;        // そのオブジェクトが有効か
        bool m_isDelete;        // そのオブジェクトは削除済みか
    };
}


#endif // !I_BASEOBJECT_H_
