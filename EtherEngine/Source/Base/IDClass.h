#ifndef I_IDCLASS_H
#define I_IDCLASS_H
#include <Base/Mutex.h>


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
        IDClassStorage(void);
        // �f�X�g���N�^
        ~IDClassStorage(void) {}

        // �ԍ��𐶐��A�ǉ�����
        // @ Ret  : �������ꂽ�ԍ�
        [[nodiscard]] IDNumberType AddNumber(void);
        // �ԍ���ǉ��ŕێ�����
        // @ Ret  : �ԍ����ǉ����ꂽ��
        // @ Arg1 : �������ꂽ�ԍ�
        bool AddNumber(IDNumberType id);

    private:
        std::vector<IDNumberType> m_number;   // �ێ����Ă���ԍ�
        std::shared_ptr<Mutex> m_mutex; // �X�s�����b�N�p�ϐ�
    };
}




//----- ID�錾
namespace EtherEngine {
    // ��ӂ̔ԍ����������N���X
    class IDClass {
    public:
        // �R���X�g���N�^
        IDClass(void);
        // �R���X�g���N�^
        // @ Arg1 : �������ɗ^����ԍ�
        IDClass(const IDNumberType& number);
        // �f�X�g���N�^
        ~IDClass(void);
        // �R�s�[�R���X�g���N�^
        IDClass(const IDClass& copy) = default;
        // ���[�u�R���X�g���N�^
        IDClass(IDClass&& move) = default;
        // �R�s�[���
        IDClass& operator =(const IDClass& copy) = default;
        // ���[�u���
        IDClass& operator =(IDClass&& move) = default;


        // �ԍ����擾����
        const IDNumberType& Get(void) const;
        // �ԍ����擾����
        operator const IDNumberType& (void) const;


        // ��r
        bool operator ==(const IDClass& other) const;

    private:
        static IDClassStorage ms_idClassStorage;    // ID���Ǘ����Ă���N���X
        IDNumberType m_number;                      // ���g���ێ����Ă���ID�ԍ�
    };
}


//----- �n�b�V���p��`
namespace std {
    template <>
    struct std::hash<EtherEngine::IDClass> {
        std::size_t operator()(const EtherEngine::IDClass& key) const {
            return std::hash<int>()(key.Get());
        }
    };
}


#endif // !I_IDCLASS_H
