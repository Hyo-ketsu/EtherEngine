#ifndef I_COMPONENTBASE_H
#define I_COMPONENTBASE_H
#include <Base/BaseObject.h>
#include <Base/Handle.h>


//----- ComponentBase 宣言
namespace EtherEngine {
    // コンポーネントの基礎となるクラス
    class ComponentBase : public BaseObject {
    public:
        // コンストラクタ
        // @ Arg1 : ゲームオブジェクト
        // @ Arg2 : コンポーネント名(Default : "Conponent")
        ComponentBase(void* gameObject, const std::string& name = "Conponent");
        // 純粋仮想デストラクタ
        virtual ~ComponentBase(void) = 0 {}
        ComponentBase(const ComponentBase& copy) = delete;
        // ムーブコンストラクタ
        ComponentBase(ComponentBase&& move) = default;


        // 所属ゲームオブジェクトの取得
        // @ MEMO : 循環参照の関係上面倒なことになっています。ヘルパーをご使用ください。
        // @ Arg1 : ゲームオブジェクトを格納する
        void GetParentObject(void** gameObject) const;


        // 更新処理を行う
        void UpdateFuntion(void);
        // 削除時処理を行う
        void DeleteFuntion(void);

    protected:
        virtual void Start(void) {}
        virtual void Update(void) {}
        virtual void Delete(void) {}

    private:
        class GameObject* m_gameObject;   // 所属ゲームオブジェクト
        bool m_isStart; // 既にStart処理を行っているか
    };
}


#endif // !I_COMPONENTBASE_H
