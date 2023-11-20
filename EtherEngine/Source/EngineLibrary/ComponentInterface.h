#ifndef I_COMPONENTINTERFACE_H
#define I_COMPONENTINTERFACE_H


//----- �e��Interface�錾
namespace EtherEngine {
    // Serialize���s��Interface
    interface class ISerialize {
    public:
        // �O���o�͂���
        // @ Memo : public, ��������EtherEngineSerialize�����Ă���Ώo�͂��܂�
        // @ Ret  : �O���o�͂���Json������
        std::string Serialize(void);
        // �O�����͂���
        // @ Arg1 : �ǂݎ��Json������
        void Deserialize(const std::string& input);
    };
}


#endif // !I_COMPONENTINTERFACE_H
