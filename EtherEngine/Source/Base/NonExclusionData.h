#ifndef I_NONEXCLUSIONDATA_H
#define I_NONEXCLUSIONDATA_H


namespace EtherEngine {
    // �r������Ă��Ȃ������擾����N���X
    // @ Temp : �f�[�^�̌^
    template <class DataType>
    class NonExclusionData {
    public:
        NonExclusionData(const NonExclusionData<DataType>&) = delete;
        NonExclusionData& operator=(NonExclusionData<DataType>&) = delete;

        // �R���X�g���N�^
        // @ Arg1 : �f�[�^
        NonExclusionData(DataType& data);
        // �f�X�g���N�^
        ~NonExclusionData(void) noexcept;
        // ���[�u�R���X�g���N�^
        NonExclusionData(NonExclusionData<DataType>&& move) noexcept;


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
    NonExclusionData<DataType>::NonExclusionData(DataType& data)
        : m_atomicData(data) {
    }
    // �f�X�g���N�^
    template <class DataType>
    NonExclusionData<DataType>::~NonExclusionData(void) noexcept {
    }
    // ���[�u�R���X�g���N�^
    template <class DataType>
    NonExclusionData<DataType>::NonExclusionData(NonExclusionData<DataType>&& move) noexcept
        : m_atomicData(move.m_atomicData) {
    }


    // �f�[�^���擾����
    // @ Ret  : �f�[�^
    template <class DataType>
    DataType& NonExclusionData<DataType>::GetData(void) const noexcept {
        //----- �ԋp
        return this->m_atomicData;
    }
}


#endif // !I_NONEXCLUSIONDATA_H
