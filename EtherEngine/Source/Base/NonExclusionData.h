#ifndef I_NONEXCLUSIONDATA_H
#define I_NONEXCLUSIONDATA_H


namespace EtherEngine {
    // 排他されていない情報を取得するクラス
    // @ Temp : データの型
    template <class DataType>
    class NonExclusionData {
    public:
        NonExclusionData(const NonExclusionData<DataType>&) = delete;
        NonExclusionData& operator=(NonExclusionData<DataType>&) = delete;

        // コンストラクタ
        // @ Arg1 : データ
        NonExclusionData(DataType& data);
        // デストラクタ
        ~NonExclusionData(void) noexcept;
        // ムーブコンストラクタ
        NonExclusionData(NonExclusionData<DataType>&& move) noexcept;


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
    NonExclusionData<DataType>::NonExclusionData(DataType& data)
        : m_atomicData(data) {
    }
    // デストラクタ
    template <class DataType>
    NonExclusionData<DataType>::~NonExclusionData(void) noexcept {
    }
    // ムーブコンストラクタ
    template <class DataType>
    NonExclusionData<DataType>::NonExclusionData(NonExclusionData<DataType>&& move) noexcept
        : m_atomicData(move.m_atomicData) {
    }


    // データを取得する
    // @ Ret  : データ
    template <class DataType>
    DataType& NonExclusionData<DataType>::GetData(void) const noexcept {
        //----- 返却
        return this->m_atomicData;
    }
}


#endif // !I_NONEXCLUSIONDATA_H
