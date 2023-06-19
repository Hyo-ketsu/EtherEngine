#include <Base/IDClass.h>
#include <Base/Random.h>


//----- IDClass定義
namespace EtherEngine {
    // コンストラクタ
    IDClass::IDClass(void)
        : m_number(ms_idClassStorage.AddNumber()) {
    }
    // デストラクタ
    IDClass::~IDClass(void) {
    }
    // コピーコンストラクタ
    IDClass::IDClass(const IDClass& copy) 
        : m_number(copy.m_number) {
    }
    // ムーブコンストラクタ
    IDClass::IDClass(IDClass&& move) noexcept
        : m_number(move.m_number) {
    }
    // 代入演算子
    IDClass& IDClass::operator =(const IDClass& copy) {
        m_number = copy.m_number;
        return *this;
    }


    // 番号を取得する
    const IDNumberType& IDClass::Get(void) const {
        return m_number;
    }
    // 番号を取得する
    IDClass::operator const IDNumberType&(void) const {
        return Get();
    }


    IDClassStorage IDClass::ms_idClassStorage;    // IDを管理しているクラス
}


//----- IDClassStorage定義
namespace EtherEngine {
    // 番号を生成、追加する
    [[nodiscard]] IDNumberType IDClassStorage::AddNumber(void) {
        //----- スピンロックを行う
        auto lock = m_spinlock.KeyLock();

        //----- 変数宣言
        IDNumberType createNumber;  // 現在の生成番号

        //----- 生成する
        while (true) {
            //----- 生成
            createNumber = Random::GetRandom<IDNumberType>();

            //----- 重複Check
            // @ MEMO : 必要ならソート、照合を効率化させてください
            bool isDuplication = false;
            for (auto& it : m_number) {
                if (createNumber == it) {
                    isDuplication = true;
                    break;
                }
            }

            //----- 重複していないならループを抜ける
            if (isDuplication == false) break;
        }

        //----- 番号を追加する
        m_number.push_back(createNumber);

        //----- 返却
        return createNumber;
    }
}
