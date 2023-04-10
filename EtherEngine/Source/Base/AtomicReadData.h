#ifndef I_ATOMICREADDATA_H
#define I_ATOMICREADDATA_H


namespace EtherEngine {
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
}




//----- AtomicReadData����
namespace EtherEngine {
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
}


#endif // !I_ATOMICREADDATA_H
