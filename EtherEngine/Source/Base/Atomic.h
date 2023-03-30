#ifndef I_HOGE_H
#define I_HOGE_H
// 排他された情報を取得するクラス
// @ Temp : データの型
template <class DataType>
class AtomicData {
public:
    AtomicData(const AtomicData<DataType>&) = delete;
    AtomicData& operator=(AtomicData<DataType>&) = delete;

    // コンストラクタ
    // @ Arg1 : データ
    // @ Arg2 : コンストラクタで実行される処理
    // @ Arg3 : デストラクタで実行される処理
    AtomicData(DataType& data, std::function<void(void)> constructor, std::function<void(void)> destructor);
    // デストラクタ
    ~AtomicData(void) noexcept;
    // ムーブコンストラクタ
    AtomicData(AtomicData<DataType>&& move) noexcept;


    // データを取得する
    // @ Ret  : データ
    DataType& GetData(void) const noexcept;

private:
    DataType& m_atomicData; // 排他制御されたデータへの参照
    std::function<void(void)> m_constructor;// コンストラクタで実行される処理
    std::function<void(void)> m_destructor; // デストラクタで実行される処理
    bool                      m_isRelease;  // 既に
};
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




// 排他制御を行うクラス
// @ Temp : 排他を行う型
template <class AtomicType>
class Atomic {
public:
    Atomic(const Atomic&) = delete;
    Atomic& operator=(const Atomic&) = delete;


    // コンストラクタ
    // @ Memo : 引数は右辺値のみ受け付けます
    // @ Arg1 : 排他を行う情報
    Atomic(AtomicType&& data);
    // デストラクタ
    ~Atomic(void) noexcept;
    // ムーブコンストラクタ
    // @ Memo : 所有権の移動を表現しています
    Atomic(Atomic&& move) noexcept;


    // データを取得する
    // @ Ret  : 排他制御されたデータ
    AtomicData<AtomicType> GetData(void);
    // 読み取り専用データを取得する
    // @ Ret  : 排他制御された読み取り専用データ
    AtomicReadData<AtomicType> GetReadData(void);

private:
    std::unique_ptr<AtomicType> m_data;  // 保持しているデータ
    std::recursive_mutex        m_mutex; // 排他用ミューテックス
    std::mutex                m_readMutex;     // 読み取りロック用ミューテックス
    std::condition_variable   m_readCondition; // 読み取りロック用条件変数
    std::atomic<unsigned int> m_readCount;     // 読み取りロック用Read数
};




// コンストラクタ
// @ Arg1 : データ
// @ Arg2 : コンストラクタで実行される処理
// @ Arg3 : デストラクタで実行される処理
template <class DataType>
AtomicData<DataType>::AtomicData(DataType& data, std::function<void(void)> constructor, std::function<void(void)> destructor)
    : m_atomicData(data)
    , m_constructor(constructor)
    , m_destructor(destructor) {
    //----- 初期化時ラムダ実行
    m_constructor();
}
// デストラクタ
template <class DataType>
AtomicData<DataType>::~AtomicData(void) noexcept {
    //----- 終了時ラムダ実行
    if (this->m_destructor != nullptr) this->m_destructor();
}
// ムーブコンストラクタ
template <class DataType>
AtomicData<DataType>::AtomicData(AtomicData<DataType>&& move) noexcept
    : m_atomicData(move.m_atomicData)
    , m_constructor(move.m_constructor)
    , m_destructor(move.m_destructor) {
    move.m_constructor = nullptr;
    move.m_destructor = nullptr;
}


// データを取得する
// @ Ret  : データ
template <class DataType>
DataType& AtomicData<DataType>::GetData(void) const noexcept {
    //----- 返却
    return this->m_atomicData;
}




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




// コンストラクタ
// @ Memo : 引数はムーブされたもののみ受け付けます
// @ Arg1 : 排他を行う情報
template <class AtomicType>
Atomic<AtomicType>::Atomic(AtomicType&& data)
    : m_data(std::make_unique<AtomicType>(data)) {
}
// デストラクタ
template <class AtomicType>
Atomic<AtomicType>::~Atomic(void) noexcept {
}
// ムーブコンストラクタ
// @ Memo : 所有権の移動を表現しています
template <class AtomicType>
Atomic<AtomicType>::Atomic(Atomic&& move) noexcept {
    //----- ロックを行う
    {
        std::lock_guard<std::recursive_mutex> lock(move.m_mutex);

        //----- 読み取りロックがされているか
        if (m_readCount.load() > 0) {
            //----- 読み込み数が1以上。読み取りロック（書き込み側のスレッドを寝かす）を行う
            std::unique_lock<std::mutex> lock(m_readMutex);
            m_readCondition.wait(lock, [this] {return m_readCount.load() > 0; });
        }
    }

    //----- ムーブ
    m_data = std::move(move.m_data);
    m_mutex = std::move(move.m_mutex);
}




// データを取得する
// @ Ret  : 排他制御されたデータ
template <class AtomicType>
AtomicData<AtomicType> Atomic<AtomicType>::GetData(void) {
    //----- 書き込みが終了するまで待機する
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    //----- 読み取りロックがされているか
    if (m_readCount.load() > 0) {
        //----- 読み込み数が1以上。読み取りロック（書き込み側のスレッドを寝かす）を行う
        std::unique_lock<std::mutex> lock(m_readMutex);
        m_readCondition.wait(lock, [this] {return m_readCount.load() > 0; });
    }

    //----- 排他データの作成と返却
    return std::move(AtomicData<AtomicType>(*m_data,
        [this](void) -> void { m_mutex.lock(); }, [this](void) -> void { m_mutex.unlock(); }));
}
// 読み取り専用データを取得する
// @ Ret  : 排他制御された読み取り専用データ
template <class AtomicType>
AtomicReadData<AtomicType> Atomic<AtomicType>::GetReadData(void) {
    //----- 書き込みが終了するまで待機する
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    //----- 排他データの作成と返却
    return std::move(AtomicReadData<AtomicType>(*m_data,
        [this](void) -> void { m_readCount.store(m_readCount.load() + 1); }, [this](void) -> void { m_readCount.store(m_readCount.load() - 1); }));
}

#endif // !I_HOGE_H
