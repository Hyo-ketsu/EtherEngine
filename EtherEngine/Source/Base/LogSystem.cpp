#include <Base/LogSystem.h>


//----- ��ʏo�͂�����̒�`
namespace EtherEngine {
    // �R���X�g���N�^
    // @ Arg1 : �\�����b�Z�[�W�^�C�v
    // @ Arg2 : ���b�Z�[�W�o�͎���
    // @ Arg3 : ���b�Z�[�W
    LogWindowMessage::LogWindowMessage(const LogWindowMessageType& type, const std::chrono::steady_clock::time_point& timeStamp, const std::string& message) 
        : m_type(type)
        , m_timeStamp(timeStamp) 
        , m_message(message) {
    }
}


//----- LogSystem ��`
namespace EtherEngine {
    // ��ʕ\�����O�Ƀ��b�Z�[�W��ǉ�����
    void LogSystem::AddLogWindowMessage(const LogWindowMessage& message) {
        //----- ���b�N
        auto lock = ms_spinlock.KeyLock();

        //----- �ǉ�
        ms_logWindowMessage.push_back(message);
    }
    // ��ʕ\�����O���擾����
    std::vector<LogWindowMessage> LogSystem::GetLogWindowMessage(void) {
        //----- ���b�N
        auto lock = ms_spinlock.KeyLock();

        //----- �ԋp
        return ms_logWindowMessage;
    }
    // ��ʕ\�����O����������
    void LogSystem::DeleteLogWindowMessage(void) {
        //----- ���b�N
        auto lock = ms_spinlock.KeyLock();

        //----- �폜
        ms_logWindowMessage.clear();
    }

    
    std::vector<LogWindowMessage> LogSystem::ms_logWindowMessage;   // ��ʕ\���̃��O
    SpinLock LogSystem::ms_spinlock; // �X�s�����b�N��񋟂���
}
