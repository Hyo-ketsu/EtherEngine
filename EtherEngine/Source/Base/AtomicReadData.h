#ifndef I_ATOMICREADDATA_H
#define I_ATOMICREADDATA_H


namespace EtherEngine {
    // 排他された読み取り専用情報を取得するクラス
    // @ Temp : データの型
    template <class DataType>
    class AtomicReadData {
    public:
        // コンストラクタ
        // @ Arg1 : データ
        // @ Arg2 : コンストラクタで実行される処理
        // @ Arg3 : デストラクタで実行される処理
        AtomicReadData(DataType& data, std::function<void(void)> constructor, std::function<void(void)> destructor);
        // デストラクタ
        ~AtomicReadData(void) noexcept;
        // ムーブコンストラクタ
        AtomicReadData(AtomicReadData<DataType>&& move) noexcept;
        // コピーコンストラクタ
        AtomicReadData(const AtomicReadData<DataType>& copy) noexcept;
        // 代入演算子
        AtomicReadData<DataType>& operator=(const AtomicReadData<DataType>& in) noexcept;


        // 読み取り専用データを取得する
        // @ Ret  : 読み取り専用データ
        const DataType& GetData(void) const noexcept;

    private:
        DataType& m_atomicData; // 排他制御されたデータへの参照
        std::function<void(void)> m_constructor;// コンストラクタで実行される処理
        std::function<void(void)> m_destructor; // デストラクタで実行される処理
    };
}




//----- AtomicReadData実装
namespace EtherEngine {
    // コンストラクタ
    // @ Arg1 : データ
    // @ Arg2 : コンストラクタで実行される処理
    // @ Arg3 : デストラクタで実行される処理
    template <class DataType>
    AtomicReadData<DataType>::AtomicReadData(DataType& data, std::function<void(void)> constructor, std::function<void(void)> destructor)
        : m_atomicData(data)
        , m_constructor(constructor)
        , m_destructor(destructor) {
        //----- 初期化時ラムダ実行
        m_constructor();
    }
    // ムーブコンストラクタ
    template <class DataType>
    AtomicReadData<DataType>::AtomicReadData(AtomicReadData<DataType>&& move) noexcept
        : m_atomicData(move.m_atomicData)
        , m_constructor(move.m_constructor)
        , m_destructor(move.m_destructor) {
        move.m_constructor = nullptr;
        move.m_destructor = nullptr;
    }
    // デストラクタ
    template <class DataType>
    AtomicReadData<DataType>::~AtomicReadData(void) noexcept {
        //----- 終了時ラムダ実行
        if (this->m_destructor != nullptr) this->m_destructor();
    }
    // コピーコンストラクタ
    template <class DataType>
    AtomicReadData<DataType>::AtomicReadData(const AtomicReadData<DataType>& copy) noexcept
        : AtomicReadData(copy.m_atomicData, copy.m_constructor, copy.m_destructor) {
        //----- 初期化ラムダ実行
        this->m_constructor();
    }
    // 代入演算子
    template <class DataType>
    AtomicReadData<DataType>& AtomicReadData<DataType>::operator=(const AtomicReadData<DataType>& in) noexcept {
        //----- 初期値代入
        this->m_atomicData = in.m_atomicData;
        this->m_constructor = in.m_constructor;
        this->m_destructor = in.m_destructor;

        //----- 初期化ラムダ実行
        this->m_constructor();
    }
    // 読み取り専用データを取得する
    // @ Ret  : 読み取り専用データ
    template <class DataType>
    const DataType& AtomicReadData<DataType>::GetData(void) const noexcept {
        //----- 返却
        return this->m_atomicData;
    }
}


#endif // !I_ATOMICREADDATA_H
