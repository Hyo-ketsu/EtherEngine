#ifndef I_IDCLASS_H
#define I_IDCLASS_H
#include <Base/SpinLock.h>


//-----
namespace EtherEngine {
    // ID�Ŏg�p����^
    using IDNumberType = ullint;
}


//----- IDClassStorage�錾
namespace EtherEngine {
    // �������ꂽ�ԍ���ێ����Ă����N���X
    class IDClassStorage {
    public:
        // �R���X�g���N�^
        IDClassStorage(void) {}
        // �f�X�g���N�^
        ~IDClassStorage(void) {}

        // �ԍ��𐶐��A�ǉ�����
        // @ Ret  : �������ꂽ�ԍ�
        [[nodiscard]] IDNumberType AddNumber(void);

    private:
        std::vector<IDNumberType> m_number;   // �ێ����Ă���ԍ��ƎQ�Ɛ��ꗗ
        SpinLock m_spinlock; // �X�s�����b�N�p�ϐ�
    };
}


//----- ID�錾
namespace EtherEngine {
    // ��ӂ̔ԍ����������N���X
    class IDClass {
    public:
        // �R���X�g���N�^
        IDClass(void);
        // �f�X�g���N�^
        virtual ~IDClass(void);
        // �R�s�[�R���X�g���N�^
        IDClass(const IDClass& copy);
        // ���[�u�R���X�g���N�^
        IDClass(IDClass&& move) noexcept;
        // ������Z�q
        IDClass& operator =(const IDClass& copy);


        // �ԍ����擾����
        const IDNumberType& Get(void) const;
        // �ԍ����擾����
        operator const IDNumberType&(void) const;

    private:
        static IDClassStorage ms_idClassStorage;    // ID���Ǘ����Ă���N���X
        IDNumberType m_number;                      // ���g���ێ����Ă���ID�ԍ�
    };
}




#endif // !I_IDCLASS_H
