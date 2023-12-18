#ifndef I_EXCLUSIONDATA_H
#define I_EXCLUSIONDATA_H


namespace EtherEngine {
    // �r�����ꂽ�����擾����N���X
    // @ Temp : �f�[�^�̌^
    template <class DataType>
    class ExclusionData {
    public:
        ExclusionData(const ExclusionData<DataType>&) = delete;
        ExclusionData& operator=(ExclusionData<DataType>&) = delete;

        // �R���X�g���N�^
        // @ Arg1 : �f�[�^
        // @ Arg2 : �R���X�g���N�^�Ŏ��s����鏈��
        // @ Arg3 : �f�X�g���N�^�Ŏ��s����鏈��
        ExclusionData(DataType& data, std::function<void(void)> constructor, std::function<void(void)> destructor);
        // �f�X�g���N�^
        ~ExclusionData(void) noexcept;
        // ���[�u�R���X�g���N�^
        ExclusionData(ExclusionData<DataType>&& move) noexcept;


        // �f�[�^���擾����
        // @ Ret  : �f�[�^
        DataType& GetData(void) const noexcept;

    private:
        DataType& m_atomicData; // �r�����䂳�ꂽ�f�[�^�ւ̎Q��
        std::function<void(void)> m_constructor;// �R���X�g���N�^�Ŏ��s����鏈��
        std::function<void(void)> m_destructor; // �f�X�g���N�^�Ŏ��s����鏈��
    };
}




//----- AtomicData����
namespace EtherEngine {
    // �R���X�g���N�^
    // @ Arg1 : �f�[�^
    // @ Arg2 : �R���X�g���N�^�Ŏ��s����鏈��
    // @ Arg3 : �f�X�g���N�^�Ŏ��s����鏈��
    template <class DataType>
    ExclusionData<DataType>::ExclusionData(DataType& data, std::function<void(void)> constructor, std::function<void(void)> destructor)
        : m_atomicData(data)
        , m_constructor(constructor)
        , m_destructor(destructor) {
        //----- �������������_���s
        m_constructor();
    }
    // �f�X�g���N�^
    template <class DataType>
    ExclusionData<DataType>::~ExclusionData(void) noexcept {
        //----- �I���������_���s
        if (this->m_destructor != nullptr) this->m_destructor();
    }
    // ���[�u�R���X�g���N�^
    template <class DataType>
    ExclusionData<DataType>::ExclusionData(ExclusionData<DataType>&& move) noexcept
        : m_atomicData(move.m_atomicData)
        , m_constructor(move.m_constructor)
        , m_destructor(move.m_destructor) {
        move.m_constructor = nullptr;
        move.m_destructor = nullptr;
    }


    // �f�[�^���擾����
    // @ Ret  : �f�[�^
    template <class DataType>
    DataType& ExclusionData<DataType>::GetData(void) const noexcept {
        //----- �ԋp
        return this->m_atomicData;
    }
}


#endif // !I_EXCLUSIONDATA_H
