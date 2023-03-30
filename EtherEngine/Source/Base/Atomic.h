#ifndef I_HOGE_H
#define I_HOGE_H
// �r�����ꂽ�����擾����N���X
// @ Temp : �f�[�^�̌^
template <class DataType>
class AtomicData {
public:
    AtomicData(const AtomicData<DataType>&) = delete;
    AtomicData& operator=(AtomicData<DataType>&) = delete;

    // �R���X�g���N�^
    // @ Arg1 : �f�[�^
    // @ Arg2 : �R���X�g���N�^�Ŏ��s����鏈��
    // @ Arg3 : �f�X�g���N�^�Ŏ��s����鏈��
    AtomicData(DataType& data, std::function<void(void)> constructor, std::function<void(void)> destructor);
    // �f�X�g���N�^
    ~AtomicData(void) noexcept;
    // ���[�u�R���X�g���N�^
    AtomicData(AtomicData<DataType>&& move) noexcept;


    // �f�[�^���擾����
    // @ Ret  : �f�[�^
    DataType& GetData(void) const noexcept;

private:
    DataType& m_atomicData; // �r�����䂳�ꂽ�f�[�^�ւ̎Q��
    std::function<void(void)> m_constructor;// �R���X�g���N�^�Ŏ��s����鏈��
    std::function<void(void)> m_destructor; // �f�X�g���N�^�Ŏ��s����鏈��
    bool                      m_isRelease;  // ����
};
// �r�����ꂽ�ǂݎ���p�����擾����N���X
// @ Temp : �f�[�^�̌^
template <class DataType>
class AtomicReadData {
public:
    // �R���X�g���N�^
    // @ Arg1 : �f�[�^
    // @ Arg2 : �R���X�g���N�^�Ŏ��s����鏈��
    // @ Arg3 : �f�X�g���N�^�Ŏ��s����鏈��
    AtomicReadData(DataType& data, std::function<void(void)> constructor, std::function<void(void)> destructor);
    // �f�X�g���N�^
    ~AtomicReadData(void) noexcept;
    // ���[�u�R���X�g���N�^
    AtomicReadData(AtomicReadData<DataType>&& move) noexcept;
    // �R�s�[�R���X�g���N�^
    AtomicReadData(const AtomicReadData<DataType>& copy) noexcept;
    // ������Z�q
    AtomicReadData<DataType>& operator=(const AtomicReadData<DataType>& in) noexcept;


    // �ǂݎ���p�f�[�^���擾����
    // @ Ret  : �ǂݎ���p�f�[�^
    const DataType& GetData(void) const noexcept;

private:
    DataType& m_atomicData; // �r�����䂳�ꂽ�f�[�^�ւ̎Q��
    std::function<void(void)> m_constructor;// �R���X�g���N�^�Ŏ��s����鏈��
    std::function<void(void)> m_destructor; // �f�X�g���N�^�Ŏ��s����鏈��
};




// �r��������s���N���X
// @ Temp : �r�����s���^
template <class AtomicType>
class Atomic {
public:
    Atomic(const Atomic&) = delete;
    Atomic& operator=(const Atomic&) = delete;


    // �R���X�g���N�^
    // @ Memo : �����͉E�Ӓl�̂ݎ󂯕t���܂�
    // @ Arg1 : �r�����s�����
    Atomic(AtomicType&& data);
    // �f�X�g���N�^
    ~Atomic(void) noexcept;
    // ���[�u�R���X�g���N�^
    // @ Memo : ���L���̈ړ���\�����Ă��܂�
    Atomic(Atomic&& move) noexcept;


    // �f�[�^���擾����
    // @ Ret  : �r�����䂳�ꂽ�f�[�^
    AtomicData<AtomicType> GetData(void);
    // �ǂݎ���p�f�[�^���擾����
    // @ Ret  : �r�����䂳�ꂽ�ǂݎ���p�f�[�^
    AtomicReadData<AtomicType> GetReadData(void);

private:
    std::unique_ptr<AtomicType> m_data;  // �ێ����Ă���f�[�^
    std::recursive_mutex        m_mutex; // �r���p�~���[�e�b�N�X
    std::mutex                m_readMutex;     // �ǂݎ�胍�b�N�p�~���[�e�b�N�X
    std::condition_variable   m_readCondition; // �ǂݎ�胍�b�N�p�����ϐ�
    std::atomic<unsigned int> m_readCount;     // �ǂݎ�胍�b�N�pRead��
};




// �R���X�g���N�^
// @ Arg1 : �f�[�^
// @ Arg2 : �R���X�g���N�^�Ŏ��s����鏈��
// @ Arg3 : �f�X�g���N�^�Ŏ��s����鏈��
template <class DataType>
AtomicData<DataType>::AtomicData(DataType& data, std::function<void(void)> constructor, std::function<void(void)> destructor)
    : m_atomicData(data)
    , m_constructor(constructor)
    , m_destructor(destructor) {
    //----- �������������_���s
    m_constructor();
}
// �f�X�g���N�^
template <class DataType>
AtomicData<DataType>::~AtomicData(void) noexcept {
    //----- �I���������_���s
    if (this->m_destructor != nullptr) this->m_destructor();
}
// ���[�u�R���X�g���N�^
template <class DataType>
AtomicData<DataType>::AtomicData(AtomicData<DataType>&& move) noexcept
    : m_atomicData(move.m_atomicData)
    , m_constructor(move.m_constructor)
    , m_destructor(move.m_destructor) {
    move.m_constructor = nullptr;
    move.m_destructor = nullptr;
}


// �f�[�^���擾����
// @ Ret  : �f�[�^
template <class DataType>
DataType& AtomicData<DataType>::GetData(void) const noexcept {
    //----- �ԋp
    return this->m_atomicData;
}




// �R���X�g���N�^
// @ Arg1 : �f�[�^
// @ Arg2 : �R���X�g���N�^�Ŏ��s����鏈��
// @ Arg3 : �f�X�g���N�^�Ŏ��s����鏈��
template <class DataType>
AtomicReadData<DataType>::AtomicReadData(DataType& data, std::function<void(void)> constructor, std::function<void(void)> destructor)
    : m_atomicData(data)
    , m_constructor(constructor)
    , m_destructor(destructor) {
    //----- �������������_���s
    m_constructor();
}
// ���[�u�R���X�g���N�^
template <class DataType>
AtomicReadData<DataType>::AtomicReadData(AtomicReadData<DataType>&& move) noexcept
    : m_atomicData(move.m_atomicData)
    , m_constructor(move.m_constructor)
    , m_destructor(move.m_destructor) {
    move.m_constructor = nullptr;
    move.m_destructor = nullptr;
}
// �f�X�g���N�^
template <class DataType>
AtomicReadData<DataType>::~AtomicReadData(void) noexcept {
    //----- �I���������_���s
    if (this->m_destructor != nullptr) this->m_destructor();
}
// �R�s�[�R���X�g���N�^
template <class DataType>
AtomicReadData<DataType>::AtomicReadData(const AtomicReadData<DataType>& copy) noexcept
    : AtomicReadData(copy.m_atomicData, copy.m_constructor, copy.m_destructor) {
    //----- �����������_���s
    this->m_constructor();
}
// ������Z�q
template <class DataType>
AtomicReadData<DataType>& AtomicReadData<DataType>::operator=(const AtomicReadData<DataType>& in) noexcept {
    //----- �����l���
    this->m_atomicData = in.m_atomicData;
    this->m_constructor = in.m_constructor;
    this->m_destructor = in.m_destructor;

    //----- �����������_���s
    this->m_constructor();
}
// �ǂݎ���p�f�[�^���擾����
// @ Ret  : �ǂݎ���p�f�[�^
template <class DataType>
const DataType& AtomicReadData<DataType>::GetData(void) const noexcept {
    //----- �ԋp
    return this->m_atomicData;
}




// �R���X�g���N�^
// @ Memo : �����̓��[�u���ꂽ���̂̂ݎ󂯕t���܂�
// @ Arg1 : �r�����s�����
template <class AtomicType>
Atomic<AtomicType>::Atomic(AtomicType&& data)
    : m_data(std::make_unique<AtomicType>(data)) {
}
// �f�X�g���N�^
template <class AtomicType>
Atomic<AtomicType>::~Atomic(void) noexcept {
}
// ���[�u�R���X�g���N�^
// @ Memo : ���L���̈ړ���\�����Ă��܂�
template <class AtomicType>
Atomic<AtomicType>::Atomic(Atomic&& move) noexcept {
    //----- ���b�N���s��
    {
        std::lock_guard<std::recursive_mutex> lock(move.m_mutex);

        //----- �ǂݎ�胍�b�N������Ă��邩
        if (m_readCount.load() > 0) {
            //----- �ǂݍ��ݐ���1�ȏ�B�ǂݎ�胍�b�N�i�������ݑ��̃X���b�h��Q�����j���s��
            std::unique_lock<std::mutex> lock(m_readMutex);
            m_readCondition.wait(lock, [this] {return m_readCount.load() > 0; });
        }
    }

    //----- ���[�u
    m_data = std::move(move.m_data);
    m_mutex = std::move(move.m_mutex);
}




// �f�[�^���擾����
// @ Ret  : �r�����䂳�ꂽ�f�[�^
template <class AtomicType>
AtomicData<AtomicType> Atomic<AtomicType>::GetData(void) {
    //----- �������݂��I������܂őҋ@����
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    //----- �ǂݎ�胍�b�N������Ă��邩
    if (m_readCount.load() > 0) {
        //----- �ǂݍ��ݐ���1�ȏ�B�ǂݎ�胍�b�N�i�������ݑ��̃X���b�h��Q�����j���s��
        std::unique_lock<std::mutex> lock(m_readMutex);
        m_readCondition.wait(lock, [this] {return m_readCount.load() > 0; });
    }

    //----- �r���f�[�^�̍쐬�ƕԋp
    return std::move(AtomicData<AtomicType>(*m_data,
        [this](void) -> void { m_mutex.lock(); }, [this](void) -> void { m_mutex.unlock(); }));
}
// �ǂݎ���p�f�[�^���擾����
// @ Ret  : �r�����䂳�ꂽ�ǂݎ���p�f�[�^
template <class AtomicType>
AtomicReadData<AtomicType> Atomic<AtomicType>::GetReadData(void) {
    //----- �������݂��I������܂őҋ@����
    std::lock_guard<std::recursive_mutex> lock(m_mutex);

    //----- �r���f�[�^�̍쐬�ƕԋp
    return std::move(AtomicReadData<AtomicType>(*m_data,
        [this](void) -> void { m_readCount.store(m_readCount.load() + 1); }, [this](void) -> void { m_readCount.store(m_readCount.load() - 1); }));
}

#endif // !I_HOGE_H
