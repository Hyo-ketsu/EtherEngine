#ifndef I_SINGLETON_H
#define I_SINGLETON_H


namespace EtherEngine {
    // Singleton���ۃN���X
    // @ Memo : ���̃N���X���t�����h�錾���Ă�������
    // @ Memo : protected �� private �ŃR���X�g���N�^��錾���Ă�������
    // @ Temp : �ԋp����N���X
    template<class SingletonType>
    class Singleton {
    public:
        Singleton<SingletonType>(const Singleton<SingletonType>&) = delete;
        Singleton<SingletonType>(Singleton<SingletonType>&&) = delete;
        Singleton<SingletonType>& operator=(const Singleton<SingletonType>&) = delete;
        Singleton<SingletonType>& operator=(Singleton<SingletonType>&&) = delete;


        // �C���X�^���X�̎擾
        // @ Ret  : ��������݂��Ȃ����Ƃ����m�ȃC���X�^���X
        static SingletonType* const Get(void);

         
        // �C���X�^���X�̖����I���
        static void DeleteInstance(void);

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




// Singleton����
namespace EtherEngine {
    // �C���X�^���X�̎擾
    template<class SingletonType>
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


    // �C���X�^���X�̖����I���
    template<class SingletonType>
    void Singleton<SingletonType>::DeleteInstance(void) {
        //----- ���b�N
        std::lock_guard<decltype(ms_updaetrMutex)> lock(ms_updaetrMutex);

        //----- �����I�J��
        ms_instance.reset();
    }




    template <class SingletonType>
    std::mutex Singleton<SingletonType>::ms_updaetrMutex; // �~���[�e�b�N�X
    template <class SingletonType>
    std::unique_ptr<SingletonType> Singleton<SingletonType>::ms_instance; // �V���O���g���T�u�N���X
}


#endif // !I_SINGLETON_H
