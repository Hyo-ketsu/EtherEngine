#ifndef I_IMANAGEENUM_H
#define I_IMANAGEENUM_H


#pragma managed
//----- ManageEnum 宣言
namespace EtherEngine {
    // C++CLIのジェネリックでEnumを比較するためのクラス
    // @ Memo : 現状、Enumで非符号intより大きい値が来ることは想定していません。
    public value class ManageEnum {
    public:
        // コンストラクタ
        // @ Arg1 : 比較したいEnum(null許容)
        ManageEnum(System::Enum^ setEnum);


        // nullのEnumを受け取っているか
        property bool IsNull {
            bool get(void) { return this->EnumType == nullptr; }
        }        
        // 実際の型
        property System::Type^ EnumType {
            System::Type^ get(void) { return m_enumType; }
        }
        // 実際に保持している型
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
        System::Type^ m_enumType;   // Enumの実際の型
        int           m_enumValue;  // Enumが実際に保持している値
    };
}


#endif // !I_IMANAGEENUM_H
