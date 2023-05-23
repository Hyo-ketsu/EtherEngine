#ifndef I_COMPONENTBASE_H
#define I_COMPONENTBASE_H


namespace EtherEngine {
    // コンポーネントの基礎となるクラス
    class ComponentBase {
    public:
        // コンストラクタ
        ComponentBase(void) {}
        // デストラクタ
        ~ComponentBase(void) {}

        virtual void Start(void) {}
        virtual void Update(void) {}
        virtual void Draw(void) {}
    };
}


#endif // !I_COMPONENTBASE_H
