#include <Base/Timer.h>


//----- �O���錾��`
namespace EtherEngine {
    namespace ForwardDeclaration {
        // TimePointer�p�O���錾
        class TimePointer {
        public:
            // �R���X�g���N�^
            TimePointer(std::chrono::steady_clock::time_point timePoint)
                : m_timePoint(timePoint) {
            }
            // �f�X�g���N�^
            TimePointer(void) {}
            // �R�s�[���
            TimePointer& operator =(const TimePointer& copy) = default;


            operator std::chrono::steady_clock::time_point(void) { return m_timePoint; }


            std::chrono::steady_clock::time_point m_timePoint;  
        };
    }
}


//----- Timer ��`
namespace EtherEngine {
    using namespace EtherEngine::ForwardDeclaration;


    // �R���X�g���N�^
    Timer::Timer(void) 
        : m_deltaTime(nullptr) {
    }
    // �f�X�g���N�^
    Timer::~Timer(void) {
    }
    // ���ݎ��Ԃ��擾����
    milliSecond Timer::GetTime(void) {
        return GlobalTimer::Get()->GetGlobalTime();
    }


    // �O�񂩂�̌o�ߎ��Ԃ��擾����
    milliSecond Timer::GetDeltaTime(void) {
        //----- using�ƕϐ��錾
        milliSecond ret = 0;

        //----- ���Z����
        if (m_deltaTime == nullptr) {
            //----- �����l�B������
            m_deltaTime = new TimePointer(std::chrono::steady_clock::now());
        }
        else {
            //----- �L���l�B��������
            ret = (std::chrono::steady_clock::now() - m_deltaTime->m_timePoint).count() * 0.001f * 0.001f;  // �i�m�b���}�C�N���b�A�~���b�֕ϊ�
        }

        //----- ���ԍX�V
        *m_deltaTime = std::chrono::steady_clock::now();

        //----- �ԋp
        return ret;
    }
}


namespace EtherEngine {
    // �R���X�g���N�^
    GlobalTimer::GlobalTimer(void) 
        : m_firstTime(new TimePointer(std::chrono::steady_clock::now()))
        , m_updateTime(new TimePointer(*m_firstTime)) {
    }
    // �f�X�g���N�^
    GlobalTimer::~GlobalTimer(void) {
        delete m_updateTime;
        delete m_firstTime;
    }


    // ������
    void GlobalTimer::Init(void) {
    }
    // �X�V
    void GlobalTimer::Update(void) {
        *m_updateTime = TimePointer(std::chrono::steady_clock::now());
    }
    // �I��
    void GlobalTimer::Uninit(void) {
    }


    // �O���[�o���^�C�����擾����
    // @ Ret  : GlobalTimer����������̌o�ߎ���
    milliSecond GlobalTimer::GetGlobalTime(void) {
        //----- �o�ߎ��Ԃ��i�m�b�Ŏ擾
        auto second = std::chrono::steady_clock::now() - m_firstTime->m_timePoint;

        //----- �i�m�b���}�C�N���b����~���b�ɕϊ����ĕԋp
        return second.count() * 0.001f * 0.001f;
    }
}
