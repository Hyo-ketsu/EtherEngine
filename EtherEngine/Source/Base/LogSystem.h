#ifndef I_LOGSYSTEM_H
#define I_LOGSYSTEM_H
#include <Base/SpinLock.h>


//----- ��ʏo�͂�����̐錾
namespace EtherEngine {
    // ��ʏo�̓��O�̎��
    enum class LogWindowMessageType {
        MessageShow = 0,    // �ʏ�̃��b�Z�[�W
        HelpShow,           // �w���v�\��
        WarningShow,        // �x���\��
        ErrorShow,          // �G���[�\��
        NoneShow,           // ���ɕ\�����Ȃ�
    };


    // ��ʕ\�����O�p�N���X
    struct LogWindowMessage {
        // �R���X�g���N�^
        // @ Arg1 : �\�����b�Z�[�W�^�C�v
        // @ Arg2 : ���b�Z�[�W�o�͎���
        // @ Arg3 : ���b�Z�[�W
        LogWindowMessage(const LogWindowMessageType& type, const std::chrono::steady_clock::time_point& timeStamp, const std::string& message);


        LogWindowMessageType m_type;    // �\�����b�Z�[�W�^�C�v
        std::chrono::steady_clock::time_point m_timeStamp;  // ���b�Z�[�W�o�͎���
        std::string m_message;          // ���b�Z�[�W
    };
}


//----- LogSystem �錾
namespace EtherEngine {
    // ���O�i��ʂɕ\��������̂�t�@�C���ɏo�͂��郍�O�j���Ǘ�����N���X
    class LogSystem {
    public:
        // �R���X�g���N�^
        LogSystem(void) = delete;
        // �R�s�[�R���X�g���N�^
        LogSystem(const LogSystem& copy) = delete;
        // ���[�u�R���X�g���N�^
        LogSystem(LogSystem&& move) = delete;


        // ��ʕ\�����O�Ƀ��b�Z�[�W��ǉ�����
        // @ Arg1 : �ǉ����郁�b�Z�[�W
        static void AddLogWindowMessage(const LogWindowMessage& message);
        // ��ʕ\�����O���擾����
        // @ Ret  : �擾���郁�b�Z�[�W
        static std::vector<LogWindowMessage> GetLogWindowMessage(void);
        // ��ʕ\�����O����������
        static void DeleteLogWindowMessage(void);

    private:
        static std::vector<LogWindowMessage> ms_logWindowMessage;    // ��ʕ\���̃��O
        static SpinLock ms_spinlock; // �X�s�����b�N��񋟂���
    };
}


#endif // !I_LOGSYSTEM_H
