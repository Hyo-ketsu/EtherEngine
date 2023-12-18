#ifndef I_EXCLUSIONDATA_H
#define I_EXCLUSIONDATA_H


namespace EtherEngine {
    // 排他された情報を取得するクラス
    // @ Temp : データの型
    template <class DataType>
    class ExclusionData {
    public:
        ExclusionData(const ExclusionData<DataType>&) = delete;
        ExclusionData& operator=(ExclusionData<DataType>&) = delete;

        // コンストラクタ
        // @ Arg1 : データ
        // @ Arg2 : コンストラクタで実行される処理
        // @ Arg3 : デストラクタで実行される処理
        ExclusionData(DataType& data, std::function<void(void)> constructor, std::function<void(void)> destructor);
        // デストラクタ
        ~ExclusionData(void) noexcept;
        // ムーブコンストラクタ
        ExclusionData(ExclusionData<DataType>&& move) noexcept;


        // データを取得する
        // @ Ret  : データ
        DataType& GetData(void) const noexcept;

    private:
        DataType& m_atomicData; // 排他制御されたデータへの参照
        std::function<void(void)> m_constructor;// コンストラクタで実行される処理
        std::function<void(void)> m_destructor; // デストラクタで実行される処理
    };
}




//----- AtomicData実装
namespace EtherEngine {
    // コンストラクタ
    // @ Arg1 : データ
    // @ Arg2 : コンストラクタで実行される処理
    // @ Arg3 : デストラクタで実行される処理
    template <class DataType>
    ExclusionData<DataType>::ExclusionData(DataType& data, std::function<void(void)> constructor, std::function<void(void)> destructor)
        : m_atomicData(data)
        , m_constructor(constructor)
        , m_destructor(destructor) {
        //----- 初期化時ラムダ実行
        m_constructor();
    }
    // デストラクタ
    template <class DataType>
    ExclusionData<DataType>::~ExclusionData(void) noexcept {
        //----- 終了時ラムダ実行
        if (this->m_destructor != nullptr) this->m_destructor();
    }
    // ムーブコンストラクタ
    template <class DataType>
    ExclusionData<DataType>::ExclusionData(ExclusionData<DataType>&& move) noexcept
        : m_atomicData(move.m_atomicData)
        , m_constructor(move.m_constructor)
        , m_destructor(move.m_destructor) {
        move.m_constructor = nullptr;
        move.m_destructor = nullptr;
    }


    // データを取得する
    // @ Ret  : データ
    template <class DataType>
    DataType& ExclusionData<DataType>::GetData(void) const noexcept {
        //----- 返却
        return this->m_atomicData;
    }
}


#endif // !I_EXCLUSIONDATA_H
