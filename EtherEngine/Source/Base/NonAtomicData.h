#ifndef I_NONATOMICDATA_H
#define I_NONATOMICDATA_H


namespace EtherEngine {
    // �r������Ă��Ȃ������擾����N���X
    // @ Temp : �f�[�^�̌^
    template <class DataType>
    class NonAtomicData {
    public:
        NonAtomicData(const NonAtomicData<DataType>&) = delete;
        NonAtomicData& operator=(NonAtomicData<DataType>&) = delete;

        // �R���X�g���N�^
        // @ Arg1 : �f�[�^
        NonAtomicData(DataType& data);
        // �f�X�g���N�^
        ~NonAtomicData(void) noexcept;
        // ���[�u�R���X�g���N�^
        NonAtomicData(NonAtomicData<DataType>&& move) noexcept;


        // �f�[�^���擾����
        // @ Ret  : �f�[�^
        DataType& GetData(void) const noexcept;

    private:
        DataType& m_atomicData; // �r�����䂳��Ă��Ȃ��f�[�^�ւ̎Q��
    };
}




//----- NonAtomicData����
namespace EtherEngine {
    // �R���X�g���N�^
    // @ Arg1 : �f�[�^
    template <class DataType>
    NonAtomicData<DataType>::NonAtomicData(DataType& data)
        : m_atomicData(data) {
    }
    // �f�X�g���N�^
    template <class DataType>
    NonAtomicData<DataType>::~NonAtomicData(void) noexcept {
    }
    // ���[�u�R���X�g���N�^
    template <class DataType>
    NonAtomicData<DataType>::NonAtomicData(NonAtomicData<DataType>&& move) noexcept
        : m_atomicData(move.m_atomicData) {
    }


    // �f�[�^���擾����
    // @ Ret  : �f�[�^
    template <class DataType>
    DataType& NonAtomicData<DataType>::GetData(void) const noexcept {
        //----- �ԋp
        return this->m_atomicData;
    }
}


#endif // !I_NONATOMICDATA_H
