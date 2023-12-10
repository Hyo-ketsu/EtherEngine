#ifndef I_BASEUTILITY_H
#define I_BASEUTILITY_H


namespace {
    template <typename T, typename U>
    concept equalConcept = requires(T t, U u) { t == u; };
}


//----- �����m�F�N���X �錾
namespace EtherEngine {
    // �����m�F�p�C���^�[�t�F�[�X �錾
    class EnableCheckClass {
    public:
        // �R�s�[�R���X�g���N�^
        EnableCheckClass(const EnableCheckClass& copy);


        // �����m�F�p�̃L�[���擾����
        // @ Ret  : �擾�����L�[
        std::weak_ptr<void> GetEnableKey(void);

    protected:
        // �R���X�g���N�^
        EnableCheckClass(void); 

    private:
        std::shared_ptr<void> m_sharedPtr;
    };
}


//----- �֗��֐� �錾
namespace EtherEngine {
    namespace Utility {
        // �S�Ă̓��͂Ɣ�r����
        // @ Ret  : ��r����
        // @ Temp : ��r��
        // @ Temps: ��r�Ώ�
        // @ Arg1 : ��r��
        // @ Arg2 : �S��or�Ȃ� true �S��and�Ȃ� false
        // @ Args : ��r�Ώ�
        template <typename TargetType, equalConcept<TargetType> ArgType, equalConcept<TargetType> ...ArgsType>
        bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg, const ArgsType& ...args);
        // �S�Ă̓��͂Ɣ�r����
        // @ Ret  : ��r����
        // @ Temp : ��r��
        // @ Arg1 : ��r��
        // @ Arg2 : �S��or�Ȃ� true �S��and�Ȃ� false
        template <typename TargetType, equalConcept<TargetType> ArgType>
        bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg);


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
}




//----- �֗��֐� ��`
namespace EtherEngine {
    namespace Utility {
        // �S�Ă̓��͂Ɣ�r����
        // @ Ret  : ��r����
        // @ Temp : ��r��
        // @ Temps: ��r�Ώ�
        // @ Arg1 : ��r��
        // @ Arg2 : �S��or�Ȃ� true �S��and�Ȃ� false
        // @ Args : ��r�Ώ�
        template <typename TargetType, equalConcept<TargetType> ArgType, equalConcept<TargetType> ...ArgsType>
        bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg, const ArgsType& ...args) {
            //----- �ċA���Ĕ���
            if (isOr) {
                return target == arg || IsInputComparison(target, isOr, args...);
            }
            else {
                return target == arg && IsInputComparison(target, isOr, args...);
            }
        }
        // �S�Ă̓��͂Ɣ�r����
        // @ Ret  : ��r����
        // @ Temp : ��r��
        // @ Arg1 : ��r��
        // @ Arg2 : �S��or�Ȃ� true �S��and�Ȃ� false
        template <typename TargetType, equalConcept<TargetType> ArgType>
        bool IsInputComparison(const TargetType& target, const bool isOr, const ArgType& arg) {
            return target == arg;
        }
    }
}


#endif // !I_BASEUTILITY_H
