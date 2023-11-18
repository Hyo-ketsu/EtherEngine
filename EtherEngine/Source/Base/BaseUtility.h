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
}




//----- �֗��֐� ��`
namespace EtherEngine {
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


#endif // !I_BASEUTILITY_H
