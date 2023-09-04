#ifndef I_ETHERENGINEUTILITY_H
#define I_ETHERENGINEUTILITY_H
#include <Base/BaseDefines.h>
#include <Base/PathClass.h>


// DLL�Ăяo���p
#define DLL_CALL(ReturnType) extern "C" __declspec(dllexport) ReturnType  


//----- �C���^�[�t�F�[�X��`
namespace EtherEngine {
    //----- �^����`
    using Json = nlohmann::json;    // Json


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
//----- �֗��N���X ��`
namespace EtherEngine {
    // bool�̃g���K�[���s���N���X
    // @ Memo : �t���O�� true �̍ۂ� false ��ݒ肵�Ă��t���O�͐܂�܂���
    class Trigger {
    public:
        // �R���X�g���N�^
        Trigger(void) : m_isFrag(false) {}
        // �f�X�g���N�^
        ~Trigger(void) {}
        

        // �t���O���擾����
        bool GetFrag(void);
        // �t���O���擾����
        operator bool(void);

        // �t���O��ݒ肷��
        void SetFrag(const bool& isFrag);
        // �t���O��ݒ肷��
        void operator=(const bool& isFrag);

    private:
        bool m_isFrag;
    };
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
        // �t�@�C���������֐�
        // @ Ret  : ���茋�ʂ̃t�@�C����
        // @ Arg1 : ����Ώ�
        // @ Arg2 : �����@��
        std::string GetFileName(const PathClass& path, const Utilty::DuplicationNameObjectName& nameRule); 
    }
}


#endif // !I_ETHERENGINEUTILITY_H
