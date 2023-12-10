#include <Base/IDClass.h>
#include <Base/Random.h>
#include <Base/ThreadingUtility.h>


//----- IDClass��`
namespace EtherEngine {
    // �R���X�g���N�^
    IDClass::IDClass(void)
        : m_number(GetNumber().AddNumber()) {
    }
    // �R���X�g���N�^
    IDClass::IDClass(const IDNumberType& number)
        : m_number(number) {
        GetNumber().AddNumber(number);
    }
    // �f�X�g���N�^
    IDClass::~IDClass(void) {
    }


    // �ԍ����擾����
    const IDNumberType& IDClass::Get(void) const {
        return m_number;
    }
    // �ԍ����擾����
    IDClass::operator const IDNumberType&(void) const {
        return Get();
    }


    // �ԍ����擾����
    IDClassStorage& IDClass::GetNumber(void) {
        if (ms_idClassStorage.has_value() == false) {
            ms_idClassStorage = {};
            return ms_idClassStorage.value();
        }
    }


    std::optional<IDClassStorage> IDClass::ms_idClassStorage;    // ID���Ǘ����Ă���N���X
}


//----- IDClassStorage��`
namespace EtherEngine {
    // �R���X�g���N�^
    IDClassStorage::IDClassStorage(void) 
        : m_mutex(ThreadingUtility::GetMutex()) {
    }
    // �ԍ��𐶐��A�ǉ�����
    [[nodiscard]] IDNumberType IDClassStorage::AddNumber(void) {
        //----- �X�s�����b�N���s��
        auto lock = m_mutex->KeySpinLock();

        //----- �ϐ��錾
        IDNumberType createNumber;  // ���݂̐����ԍ�

        //----- ��������
        while (true) {
            //----- ����
            createNumber = Random::GetRandom<IDNumberType>();

            //----- �ԍ���ǉ�����
            if (AddNumber(createNumber)) break;
        }


        //----- �ԋp
        return createNumber;
    }
    // �ԍ���ǉ��ŕێ�����
    bool IDClassStorage::AddNumber(IDNumberType id) {
        //----- �X�s�����b�N���s��
        auto lock = m_mutex->KeySpinLock();

        //----- �����Ń\�[�g����Ă���Ƃ��ĉ���A�������r�߂�
        int i = 0;
        for (auto& it : m_number) {
            //----- ���l�͂��̂܂܏I������
            if (id == it) return false;

            //----- ���g���傫�����B�����ł���΂Ȃ����̂Ɣ��肷��
            if (id < it) break;

            i++;
        }

        //----- �ǉ�����
        m_number.emplace(m_number.begin() + i, id);
        return true;
    }
}
