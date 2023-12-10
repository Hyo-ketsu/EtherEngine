#ifndef I_MESSAGEQUE_H
#define I_MESSAGEQUE_H
#include <Base/Mutex.h>


namespace EtherEngine {
    // ���b�Z�[�W�Ƃ��Ďg�p�ł��邩�̃R���Z�v�g
    // @ Memo : �Z�p�^�A�C���̂Ȃ��^���A���[�u�������̓R�s�[���\��
    template <typename T>
    concept MessageTypeConcept = std::is_arithmetic_v<T> || std::is_object_v<T> &&
        std::is_move_constructible_v<T> || std::is_copy_constructible_v<T>;
}


//----- MessageQue �錾
namespace EtherEngine {
    // �X���b�h�Z�[�t�Ƀ��b�Z�[�W�p�b�V���O���s���郁�b�Z�[�W�L���[
    // @ Temps: �R�s�[�R���X�g���N�^�����[�u�R���X�g���N�^����`����Ă��郁�b�Z�[�W�^
    // @ Memo : �e���v���[�g�����ɓ����^���������邱�Ƃ͑z�肵�Ă��܂���
    template <MessageTypeConcept ...ArgsType>
    class MessageQue {
    public:
        // �R���X�g���N�^
        MessageQue(void) {}
        // �f�X�g���N�^
        ~MessageQue(void) {}


        // ���b�Z�[�W�𑗐M����
        // @ Arg1 : ���b�Z�[�W
        template <MessageTypeConcept MessageType>
        void Send(const MessageType& message);
        // ���b�Z�[�W���擾����
        // @ Ret  : ���b�Z�[�W
        std::optional<std::variant<ArgsType...>> Get(void);
        // ���݂̃��b�Z�[�W�����擾����
        // @ Ret  : �ۗL���b�Z�[�W��
        uint GetMessageCount(void);

    private:
        std::vector<std::variant<ArgsType...>> m_messages;  // �i�[���b�Z�[�W
        std::shared_ptr<Mutex> m_mutex;
    };
}




//----- MessageQue ��`
namespace EtherEngine {
    // ���b�Z�[�W�𑗐M����
    // @ Arg1 : ���b�Z�[�W
    template <MessageTypeConcept ...ArgsType>
    template <MessageTypeConcept MessageType>
    void MessageQue<ArgsType...>::Send(const MessageType& message) {
        //----- ���b�N�擾
        auto lock = m_mutex->KeySpinLock();

        //----- ���b�Z�[�W�ǉ�
        m_messages.push_back(std::variant<ArgsType...>(message));
    }
    // ���b�Z�[�W���擾����
    // @ Ret  : ���b�Z�[�W
    template <MessageTypeConcept ...ArgsType>
    std::optional<std::variant<ArgsType...>> MessageQue<ArgsType...>::Get(void) {
        //----- ���b�N�擾
        auto lock = m_mutex->KeySpinLock();
        
        //----- ���b�Z�[�W�擾
        if (m_messages.size() < 1) {
            //----- ���b�Z�[�W�Ȃ�
            return std::optional<std::variant<ArgsType...>>();
        }
        else {
            //----- ���b�Z�[�W����B�擾���ĕԋp
            std::optional<std::variant<ArgsType...>> ret = m_messages.front();
            m_messages.erase(m_messages.begin());
            return ret;
        }
    }
    // ���݂̃��b�Z�[�W�����擾����
    // @ Ret  : �ۗL���b�Z�[�W��
    template <MessageTypeConcept ...ArgsType>
    uint MessageQue<ArgsType...>::GetMessageCount(void) {
        //----- ���b�N�擾
        auto lock = m_mutex->KeySpinLock();

        //----- �ԋp
        return m_messages.size();
    }
}


#endif // !I_MESSAGEQUE_H
