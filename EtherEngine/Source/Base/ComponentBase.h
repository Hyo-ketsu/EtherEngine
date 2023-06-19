#ifndef I_COMPONENTBASE_H
#define I_COMPONENTBASE_H
#include <Base/Handle.h>


//----- ComponentBase宣言
namespace EtherEngine {
    // コンポーネントの基礎となるクラス
    class ComponentBase {
    public:
        // コンストラクタ
        // @ Arg1 : ゲームオブジェクト
        ComponentBase(void* gameObject);
        // デストラクタ
        ~ComponentBase(void);
        ComponentBase(const ComponentBase& copy) = delete;
        // ムーブコンストラクタ
        ComponentBase(ComponentBase&& move) = default;


        // 所属ゲームオブジェクトの取得
        // @ MEMO : 循環参照の関係上面倒なことになっています。ヘルパーをご使用ください。
        // @ Arg1 : ゲームオブジェクトを格納する
        void GetGameObject(void** gameObject) const;


        // 更新処理を行う
        void UpdateFuntion(void);

    protected:
        virtual void Start(void) {}
        virtual void Update(void) {}

    private:
        class GameObject* m_gameObject;   // 所属ゲームオブジェクト
        bool m_isStart; // 既にStart処理を行っているか
    };
}


#endif // !I_COMPONENTBASE_H
