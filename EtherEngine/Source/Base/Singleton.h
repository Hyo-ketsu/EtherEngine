#ifndef I_SINGLETON_H
#define I_SINGLETON_H
#include <Base/Mutex.h>
#include <Base/ExclusionData.h>
#include <Base/ExclusionObject.h>
#include <Base/CentrallySingleton.h>


//----- Singleton�錾
namespace EtherEngine {
    // �N���X�݂̂�\������R���Z�v�g
    template <typename T>
    concept SingletonConcept = std::is_class_v<T>;


    // Singleton���ۃN���X
    // @ Memo : ���̃N���X���t�����h�錾���Ă�������
    // @ Memo : protected �� private �ŃR���X�g���N�^��錾���Ă�������
    // @ Temp : �ԋp����N���X
    template<SingletonConcept SingletonType>
    class Singleton {
    public:
        // �R�s�[�R���X�g���N�^
        Singleton<SingletonType>(const Singleton<SingletonType>& copy) = delete;
        // ���[�u�R���X�g���N�^
        Singleton<SingletonType>(Singleton<SingletonType>&& move) = delete;
        // �R�s�[���
        Singleton<SingletonType>& operator=(const Singleton<SingletonType>& copy) = delete;
        // ���[�u���
        Singleton<SingletonType>& operator=(Singleton<SingletonType>&& move) = delete;


        // �C���X�^���X�̎擾
        // @ Ret  : ��������݂��Ȃ����Ƃ����m�ȃC���X�^���X
        static SingletonType* const Get(void);

         
        // �C���X�^���X�̖����I���
        static void DeleteInstance(void);


        // �~���[�e�b�N�X�擾
        // @ Ret  : �~���[�e�b�N�X
        Mutex* const GetMutex(void);

    protected:
        // �R���X�g���N�^
        Singleton(void) {}
        // �f�X�g���N�^
        virtual ~Singleton(void) {}

    private:
        friend class CentrallySingleton;

        Mutex m_mutex;   // �T�u�N���X�p�~���[�e�b�N�X
    };
}




//----- Singleton����
namespace EtherEngine {
    // �C���X�^���X�̎擾
    template<SingletonConcept SingletonType>
    SingletonType* const Singleton<SingletonType>::Get(void) {
        return CentrallySingleton::Get()->GetSingleton<SingletonType>();
    }


    // �C���X�^���X�̖����I���
    template<SingletonConcept SingletonType>
    void Singleton<SingletonType>::DeleteInstance(void) {
        CentrallySingleton::Get().DeleteSingleton<SingletonType>();
    }


    // �~���[�e�b�N�X�擾
    template<SingletonConcept SingletonType>
    Mutex* const Singleton<SingletonType>::GetMutex(void) {
        return &m_mutex;
    }
}


#endif // !I_SINGLETON_H
