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
        

    private:
        std::string m_name;     // オブジェクト名
    };
}


#endif // !I_BASEOBJECT_H_
