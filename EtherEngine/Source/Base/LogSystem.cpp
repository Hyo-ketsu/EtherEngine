#include <Base/LogSystem.h>


//----- ��ʏo�͂�����̒�`
namespace EtherEngine {
    // �R���X�g���N�^
    LogWindowMessage::LogWindowMessage(const LogWindowMessageType& type, const std::chrono::system_clock::time_point& timeStamp, const std::string& message)
        : m_type(type)
        , m_timeStamp(timeStamp) 
        , m_message(message) {
    }
    // �R���X�g���N�^
    LogWindowMessage::LogWindowMessage(const std::string& message, const LogWindowMessageType& type)
        : LogWindowMessage(type, std::chrono::system_clock::now(), message){
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
