#ifndef I_SINGLETON_H
#define I_SINGLETON_H
#include <Base/AtomicData.h>
#include <Base/AtomicReadData.h>


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
        // �C���X�^���X�̎擾
        // @ Memo : �擾�Ɠ����ɓǂݎ�胍�b�N���擾����
        // @ Ret  : ��������݂��Ȃ����Ƃ����m�ȃC���X�^���X
        static AtomicData<SingletonType* const> GetLock(void);

         
        // �C���X�^���X�̖����I���
        static void DeleteInstance(void);


        // �~���[�e�b�N�X�擾
        // @ Ret  : �~���[�e�b�N�X
        std::recursive_mutex& GetMutex(void);

    protected:
        // �R���X�g���N�^
        Singleton(void) {}
        // �f�X�g���N�^
        virtual ~Singleton(void) {}


        std::recursive_mutex m_mutex;   // �T�u�N���X�p�~���[�e�b�N�X

    private:
        static std::mutex ms_updaetrMutex;                 // �~���[�e�b�N�X
        static std::unique_ptr<SingletonType> ms_instance; // �V���O���g���T�u�N���X
    };
}




//----- Singleton����
namespace EtherEngine {
    // �C���X�^���X�̎擾
    template<SingletonConcept SingletonType>
    SingletonType* const Singleton<SingletonType>::Get(void) {
        //----- �C���X�^���X�̐������f
        if (!(ms_instance)) {
            //----- ���b�N
            std::lock_guard<decltype(ms_updaetrMutex)> lock(ms_updaetrMutex);

            //----- �C���X�^���X�̐������f
            if (!(ms_instance)) {
                //----- �C���X�^���X�����݂��Ȃ����ߐ���
                ms_instance = std::unique_ptr<SingletonType>(new SingletonType());
            }
        }

        //----- �C���X�^���X�̕ԋp
        return ms_instance.get();
    }
    // �C���X�^���X�̎擾
    template<SingletonConcept SingletonType>
    AtomicData<SingletonType* const> Singleton<SingletonType>::GetLock(void) {
        return AtomicData<SingletonType>(Get(),
            []() -> void { ms_updaetrMutex.lock(); }, [=]() -> void { ms_updaetrMutex.unlock(); });
    }


    // �C���X�^���X�̖����I���
    template<SingletonConcept SingletonType>
    void Singleton<SingletonType>::DeleteInstance(void) {
        //----- ���b�N
        std::lock_guard<decltype(ms_updaetrMutex)> lock(ms_updaetrMutex);

        //----- �����I�J��
        ms_instance.reset();
    }


    // �~���[�e�b�N�X�擾
    template<SingletonConcept SingletonType>
    std::recursive_mutex& Singleton<SingletonType>::GetMutex(void) {
        return m_mutex;
    }



    template <SingletonConcept SingletonType>
    std::mutex Singleton<SingletonType>::ms_updaetrMutex; // �~���[�e�b�N�X
    template <SingletonConcept SingletonType>
    std::unique_ptr<SingletonType> Singleton<SingletonType>::ms_instance; // �V���O���g���T�u�N���X
}


#endif // !I_SINGLETON_H
