#ifndef I_NONATOMICDATA_H
#define I_NONATOMICDATA_H


namespace EtherEngine {
    // 排他されていない情報を取得するクラス
    // @ Temp : データの型
    template <class DataType>
    class NonAtomicData {
    public:
        NonAtomicData(const NonAtomicData<DataType>&) = delete;
        NonAtomicData& operator=(NonAtomicData<DataType>&) = delete;

        // コンストラクタ
        // @ Arg1 : データ
        NonAtomicData(DataType& data);
        // デストラクタ
        ~NonAtomicData(void) noexcept;
        // ムーブコンストラクタ
        NonAtomicData(NonAtomicData<DataType>&& move) noexcept;


        // データを取得する
        // @ Ret  : データ
        DataType& GetData(void) const noexcept;

    private:
        DataType& m_atomicData; // 排他制御されていないデータへの参照
    };
}




//----- NonAtomicData実装
namespace EtherEngine {
    // コンストラクタ
    // @ Arg1 : データ
    template <class DataType>
    NonAtomicData<DataType>::NonAtomicData(DataType& data)
        : m_atomicData(data) {
    }
    // デストラクタ
    template <class DataType>
    NonAtomicData<DataType>::~NonAtomicData(void) noexcept {
    }
    // ムーブコンストラクタ
    template <class DataType>
    NonAtomicData<DataType>::NonAtomicData(NonAtomicData<DataType>&& move) noexcept
        : m_atomicData(move.m_atomicData) {
    }


    // データを取得する
    // @ Ret  : データ
    template <class DataType>
    DataType& NonAtomicData<DataType>::GetData(void) const noexcept {
        //----- 返却
        return this->m_atomicData;
    }
}


#endif // !I_NONATOMICDATA_H
