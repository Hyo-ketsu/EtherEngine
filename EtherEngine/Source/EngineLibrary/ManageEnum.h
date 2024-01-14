#ifndef I_IMANAGEENUM_H
#define I_IMANAGEENUM_H


#pragma managed
//----- ManageEnum �錾
namespace EtherEngine {
    // C++CLI�̃W�F�l���b�N��Enum���r���邽�߂̃N���X
    // @ Memo : ����AEnum�Ŕ񕄍�int���傫���l�����邱�Ƃ͑z�肵�Ă��܂���B
    public value class ManageEnum {
    public:
        // �R���X�g���N�^
        // @ Arg1 : ��r������Enum(null���e)
        ManageEnum(System::Enum^ setEnum);


        // null��Enum���󂯎���Ă��邩
        property bool IsNull {
            bool get(void) { return this->EnumType == nullptr; }
        }        
        // ���ۂ̌^
        property System::Type^ EnumType {
            System::Type^ get(void) { return m_enumType; }
        }
        // ���ۂɕێ����Ă���^
        property int EnumValue {
            int get(void) { return m_enumValue; }
        }


        static bool operator ==(ManageEnum^ left, ManageEnum^ right) {
            if (Object::ReferenceEquals(left, nullptr)) {
                return Object::ReferenceEquals(right, nullptr);
            }

            return left->m_enumType == right->m_enumType && left->m_enumValue == right->m_enumValue;
        }
        static bool operator !=(ManageEnum^ left, ManageEnum^ right) {
            return !(left == right);
        }
        int GetHashCode(void) override {
            return System::Tuple<System::Type^, int>(m_enumType, m_enumValue).GetHashCode();
        }

    private:
        System::Type^ m_enumType;   // Enum�̎��ۂ̌^
        int           m_enumValue;  // Enum�����ۂɕێ����Ă���l
    };
}


#endif // !I_IMANAGEENUM_H
