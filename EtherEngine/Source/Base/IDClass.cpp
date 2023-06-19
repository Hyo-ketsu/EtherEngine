#include <Base/IDClass.h>
#include <Base/Random.h>


//----- IDClass��`
namespace EtherEngine {
    // �R���X�g���N�^
    IDClass::IDClass(void)
        : m_number(ms_idClassStorage.AddNumber()) {
    }
    // �f�X�g���N�^
    IDClass::~IDClass(void) {
    }
    // �R�s�[�R���X�g���N�^
    IDClass::IDClass(const IDClass& copy) 
        : m_number(copy.m_number) {
    }
    // ���[�u�R���X�g���N�^
    IDClass::IDClass(IDClass&& move) noexcept
        : m_number(move.m_number) {
    }
    // ������Z�q
    IDClass& IDClass::operator =(const IDClass& copy) {
        m_number = copy.m_number;
        return *this;
    }


    // �ԍ����擾����
    const IDNumberType& IDClass::Get(void) const {
        return m_number;
    }
    // �ԍ����擾����
    IDClass::operator const IDNumberType&(void) const {
        return Get();
    }


    IDClassStorage IDClass::ms_idClassStorage;    // ID���Ǘ����Ă���N���X
}


//----- IDClassStorage��`
namespace EtherEngine {
    // �ԍ��𐶐��A�ǉ�����
    [[nodiscard]] IDNumberType IDClassStorage::AddNumber(void) {
        //----- �X�s�����b�N���s��
        auto lock = m_spinlock.KeyLock();

        //----- �ϐ��錾
        IDNumberType createNumber;  // ���݂̐����ԍ�

        //----- ��������
        while (true) {
            //----- ����
            createNumber = Random::GetRandom<IDNumberType>();

            //----- �d��Check
            // @ MEMO : �K�v�Ȃ�\�[�g�A�ƍ��������������Ă�������
            bool isDuplication = false;
            for (auto& it : m_number) {
                if (createNumber == it) {
                    isDuplication = true;
                    break;
                }
            }

            //----- �d�����Ă��Ȃ��Ȃ烋�[�v�𔲂���
            if (isDuplication == false) break;
        }

        //----- �ԍ���ǉ�����
        m_number.push_back(createNumber);

        //----- �ԋp
        return createNumber;
    }
}
