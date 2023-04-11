#ifndef I_INITUNINITPERFORMER_H
#define I_INITUNINITPERFORMER_H


namespace EtherEngine {
    // Init,Uninit�����݂��邩�̃R���Z�v�g


    // �w�菇�ɏ����������A�I���������s��
    class InitUninitPerformer {
    public:
        // �����������A�I�������̒ǉ�
        // @ Arg1 : ����������
        // @ Arg2 : �I������
        void AddInitUninit(std::function<void(void)> init, std::function<void(void)> uninit);
        // �w��N���X�̎Q�Ƃ�n���A������Init,Uninti���s��
        // @ Arg1 : Init,Uninit����`���ꂽ�N���X�̎Q��
        template <typename InitUninitType>
        requires requires(InitUninitType instans) {
            instans.Init();
            instans.Uninit();
        }
        void AddInitUninit(InitUninitType* classRef);
        // �w��N���X��n���A������::Init,::Uninit���s��
        template <typename InitUninitType>
            requires requires() {
            InitUninitType::Init();
            InitUninitType::Uninit();
        }
        void AddInitUninit(void);


        // �������������s
        void Init(void);
        // �I���������s
        void UnInit(void);

    private:
        std::deque<std::function<void(void)>> m_init;   // �������֐�
        std::deque<std::function<void(void)>> m_uninit; // �I���֐�
    };
}




//----- InitUninitPerformer����
namespace EtherEngine {
    // @ Arg1 : Init,Uninit����`���ꂽ�N���X�̎Q��
    template <typename InitUninitType>
        requires requires(InitUninitType instans) {
        instans.Init();
        instans.Uninit();
    }
    void InitUninitPerformer::AddInitUninit(InitUninitType* classRef) {
        m_init.push_front([=](void) { classRef->Init(); });
        m_uninit.push_back([=](void) mutable { classRef->Uninit(); });
    }

    // �w��N���X��n���A������::Init,::Uninit���s��
    template <typename InitUninitType>
        requires requires() {
        InitUninitType::Init();
        InitUninitType::Uninit();
    }
    void InitUninitPerformer::AddInitUninit(void) {
        m_init.push_front([=](void) { InitUninitType::Init(); });
        m_uninit.push_back([=](void) mutable { InitUninitType::Uninit(); });
    }
}



#endif // !I_INITUNINITPERFORMER_H
