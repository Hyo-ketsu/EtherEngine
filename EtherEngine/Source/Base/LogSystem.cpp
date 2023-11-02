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


    // �r���h���ʂ̃��b�Z�[�W�����O�ɒǉ�����
    void LogSystem::AddBuildLogMessage(const std::string& message) {
        //----- �ǉ�
        ms_buildLog += message + '\n';
    }
    // �r���h���ʂ̃��O���擾����
    std::string LogSystem::GetBuildLogMessage(void) {
        //----- �擾
        return ms_buildLog;
    }
    // �r���h���O�����ׂď�������
    void LogSystem::DeleteBuildLogMessage(void) {
        ms_buildLog.clear();
    }

    
    std::vector<LogWindowMessage> LogSystem::ms_logWindowMessage;   // ��ʕ\���̃��O
    std::string LogSystem::ms_buildLog; // build���ʂ̏o�̓��O
    SpinLock LogSystem::ms_spinlock; // �X�s�����b�N��񋟂���
}
