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
        // 番号を追加で保持する
        // @ Ret  : 番号が追加されたか
        // @ Arg1 : 生成された番号
        bool AddNumber(IDNumberType id);

    private:
        std::vector<IDNumberType> m_number;   // 保持している番号
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
        // コンストラクタ
        // @ Arg1 : 生成時に与える番号
        IDClass(const IDNumberType& number);
        // デストラクタ
        virtual ~IDClass(void);
        // コピーコンストラクタ
        IDClass(const IDClass& copy) = default;
        // ムーブコンストラクタ
        IDClass(IDClass&& move) = default;
        // コピー演算子
        IDClass& operator =(const IDClass& copy) = default;
        // コピー演算子
        IDClass& operator =(IDClass&& move) = default;


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
