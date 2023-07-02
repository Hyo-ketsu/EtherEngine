#ifndef I_ETHERENGINEUTILITY_H
#define I_ETHERENGINEUTILITY_H


//----- �d���I�u�W�F�N�g��������`
namespace EtherEngine {
    namespace Utilty {
        // �d���I�u�W�F�N�g���������@
        enum class DuplicationNameObjectName {
            PARENTHESES_NUMBER = 0, // Hoge (1)
            NUMBER,                 // Hoge 1
            UNDERSCORE_NUMBER       // Hoge_1
        };


        // �d�������I�u�W�F�N�g�ɖ��O��t����
        // @ Ret  : �ϊ���̖��O
        // @ Arg1 : �Ώۖ�
        // @ Arg2 : ���ڂ̓����I�u�W�F�N�g���i1 ~ �j
        // @ Arg3 : �������@
        std::string DuplicationName(const std::string& name, const uint number, const DuplicationNameObjectName& type);
        // �d�������I�u�W�F�N�g�ɖ��O��t����
        // @ Arg1 : �Ώۖ�
        // @ Arg2 : ���ڂ̓����I�u�W�F�N�g���i1 ~ �j
        // @ Arg3 : �������@
        void DuplicationName(std::string* name, const uint number, const DuplicationNameObjectName& type);
        // �d�������I�u�W�F�N�g�������肷��
        // @ Ret  : �d�����Ă���� true
        // @ Arg1 : �d������Ώ�
        // @ Arg2 : ���̖��O
        // @ Arg3 : ���ڂ̓����I�u�W�F�N�g���i1 ~ �j
        // @ Arg4 : �������@
        bool IsDuplicationName(const std::string& name, const std::string& base, const uint number, const DuplicationNameObjectName& type);
    }
}


#endif // !I_ETHERENGINEUTILITY_H
