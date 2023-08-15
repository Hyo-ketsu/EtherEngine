#ifndef I_ETHERENGINEUTILITY_H
#define I_ETHERENGINEUTILITY_H
#include <Base/BaseDefines.h>


// DLL�Ăяo���p
#define DLL_CALL(ReturnType) extern "C" __declspec(dllexport) ReturnType  


//----- �C���^�[�t�F�[�X��`
namespace EtherEngine {
    // Serialize�EDeserialize�p�C���^�[�t�F�[�X(Json�z��)
    class IInOuter {
    public:
        // �o�͂���
        // @ Ret  : �o��Json
        virtual Json Output(void) = 0;
        // ���͂���
        // @ Arg1 : ���͕�����
        virtual void Input(const Json& input) = 0;
        // ���͂���
        // @ Arg1 : ���͕�����
        void Input(const std::string& input);
    };


    // Inspector�\���p�C���^�[�t�F�C�X
    class IInspectorShow {
    public:
        // �\������
        virtual void ShowInspector(void) = 0;
    };
}


//----- �֗��֐� ��`
namespace EtherEngine {
    // ���̓t�@�C���̒��g��S�ēǂݎ��
    // @ Exce : �t�@�C�����J���Ȃ�
    // @ Ret  : �ǂݎ��������
    // @ Arg1 : �ǂݎ��t�@�C��
    std::string RoadFileAll(const std::string& file);


    // �����񂩂����̕������u������
    // @ Ret  : �u����̕�����
    // @ Arg1 : ������������
    // @ Arg2 : �u���Ώە�����
    // @ Arg3 : �u���㕶����
    std::string StringSubstitution(const std::string& target, const std::string& dest, const std::string& replacement);
}


//----- �d���I�u�W�F�N�g��������`
namespace EtherEngine {
    namespace Utilty {
        // �d���I�u�W�F�N�g���������@
        enum class DuplicationNameObjectName {
            ParenthesesNumber = 0,  // Hoge (1)
            Number,                 // Hoge 1
            UnderscoreNumber        // Hoge_1
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
