#ifndef I_COMPONENTBASE_H
#define I_COMPONENTBASE_H


namespace EtherEngine {
    // コンポーネントの基礎となるクラス
    class ComponentBase {
    public:
        // コンストラクタ
        ComponentBase(void);
        // デストラクタ
        ~ComponentBase(void) {}

        // 更新処理を行う
        void UpdateFuntion(void);
        // 描画処理を行う
        void DrawFuntion(void);


    protected:
        virtual void Start(void) {}
        virtual void Update(void) {}
        virtual void Draw(void) {}

    private:
        bool m_isStart; // 既にStart処理を行っているか
    };
}


#endif // !I_COMPONENTBASE_H
