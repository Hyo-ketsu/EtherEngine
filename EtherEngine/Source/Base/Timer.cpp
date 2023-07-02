#include <Base/Timer.h>


namespace EtherEngine {
    // ���ݎ��Ԃ��擾����
    std::chrono::milliseconds Timer::GetTime(void) {
        using namespace std::chrono;
        return duration_cast<milliseconds>(GlobalTimer::Get()->GetGlobalTime());
    }


    // �O�񂩂�̌o�ߎ��Ԃ��擾����
    std::chrono::milliseconds Timer::GetDeltaTime(void) {
        //----- using�ƕϐ��錾
        using namespace std::chrono;
        std::chrono::milliseconds ret{ 0ms };

        //----- ���Z����
        if (m_deltaTime.has_value()) {
            //----- �L���l�B��������
            ret = duration_cast<milliseconds>(m_deltaTime.value() - std::chrono::steady_clock::now());
        }
        else {
            m_deltaTime.emplace(std::chrono::steady_clock::now());
        }

        //----- ���ԍX�V
        m_deltaTime.value() = std::chrono::steady_clock::now();

        //----- �ԋp
        return ret;
    }
}


namespace EtherEngine {
    // ������
    void GlobalTimer::Init(void) {
        m_firstTime = std::chrono::steady_clock::now();
    }
    // �I��
    void GlobalTimer::Uninit(void) {

    }


    // �O���[�o���^�C�����擾����
    // @ Ret  : GlobalTimer����������̌o�ߎ���
    std::chrono::nanoseconds GlobalTimer::GetGlobalTime(void) {
        return std::chrono::steady_clock::now() - m_firstTime.value();
    }
}
