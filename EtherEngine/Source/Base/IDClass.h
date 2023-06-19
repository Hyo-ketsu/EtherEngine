#ifndef I_IDCLASS_H
#define I_IDCLASS_H
#include <Base/SpinLock.h>


//-----
namespace EtherEngine {
    // IDで使用する型
    using IDNumberType = ullint;
}


//----- IDClassStorage宣言
namespace EtherEngine {
    // 生成された番号を保持しておくクラス
    class IDClassStorage {
    public:
        // コンストラクタ
        IDClassStorage(void) {}
        // デストラクタ
        ~IDClassStorage(void) {}

        // 番号を生成、追加する
        // @ Ret  : 生成された番号
        [[nodiscard]] IDNumberType AddNumber(void);

    private:
        std::vector<IDNumberType> m_number;   // 保持している番号と参照数一覧
        SpinLock m_spinlock; // スピンロック用変数
    };
}


//----- ID宣言
namespace EtherEngine {
    // 一意の番号を持ったクラス
    class IDClass {
    public:
        // コンストラクタ
        IDClass(void);
        // デストラクタ
        virtual ~IDClass(void);
        // コピーコンストラクタ
        IDClass(const IDClass& copy);
        // ムーブコンストラクタ
        IDClass(IDClass&& move) noexcept;
        // 代入演算子
        IDClass& operator =(const IDClass& copy);


        // 番号を取得する
        const IDNumberType& Get(void) const;
        // 番号を取得する
        operator const IDNumberType&(void) const;

    private:
        static IDClassStorage ms_idClassStorage;    // IDを管理しているクラス
        IDNumberType m_number;                      // 自身が保持しているID番号
    };
}




#endif // !I_IDCLASS_H
