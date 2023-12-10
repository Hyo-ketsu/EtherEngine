#include <Base/IDClass.h>
#include <Base/Random.h>
#include <Base/ThreadingUtility.h>


//----- IDClass定義
namespace EtherEngine {
    // コンストラクタ
    IDClass::IDClass(void)
        : m_number(GetNumber().AddNumber()) {
    }
    // コンストラクタ
    IDClass::IDClass(const IDNumberType& number)
        : m_number(number) {
        GetNumber().AddNumber(number);
    }
    // デストラクタ
    IDClass::~IDClass(void) {
    }


    // 番号を取得する
    const IDNumberType& IDClass::Get(void) const {
        return m_number;
    }
    // 番号を取得する
    IDClass::operator const IDNumberType&(void) const {
        return Get();
    }


    // 番号を取得する
    IDClassStorage& IDClass::GetNumber(void) {
        if (ms_idClassStorage.has_value() == false) {
            ms_idClassStorage = {};
            return ms_idClassStorage.value();
        }
    }


    std::optional<IDClassStorage> IDClass::ms_idClassStorage;    // IDを管理しているクラス
}


//----- IDClassStorage定義
namespace EtherEngine {
    // コンストラクタ
    IDClassStorage::IDClassStorage(void) 
        : m_mutex(ThreadingUtility::GetMutex()) {
    }
    // 番号を生成、追加する
    [[nodiscard]] IDNumberType IDClassStorage::AddNumber(void) {
        //----- スピンロックを行う
        auto lock = m_mutex->KeySpinLock();

        //----- 変数宣言
        IDNumberType createNumber;  // 現在の生成番号

        //----- 生成する
        while (true) {
            //----- 生成
            createNumber = Random::GetRandom<IDNumberType>();

            //----- 番号を追加する
            if (AddNumber(createNumber)) break;
        }


        //----- 返却
        return createNumber;
    }
    // 番号を追加で保持する
    bool IDClassStorage::AddNumber(IDNumberType id) {
        //----- スピンロックを行う
        auto lock = m_mutex->KeySpinLock();

        //----- 昇順でソートされているとして仮定、頭から舐める
        int i = 0;
        for (auto& it : m_number) {
            //----- 同値はそのまま終了する
            if (id == it) return false;

            //----- 自身より大きいか。そうであればないものと判定する
            if (id < it) break;

            i++;
        }

        //----- 追加する
        m_number.emplace(m_number.begin() + i, id);
        return true;
    }
}
