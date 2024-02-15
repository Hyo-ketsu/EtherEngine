#ifndef I_CLASSDATA_H
#define I_CLASSDATA_H


//----- ClassData 定義
namespace EtherEngine {
    // フィールドとGetSet可能なプロパティをラップするクラス
    public ref class ClassData {
    public:
        // コンストラクタ
        // @ Arg1 : フィールド情報
        ClassData(System::Reflection::FieldInfo^ field);
        // コンストラクタ
        // @ Arg1 : プロパティ情報
        ClassData(System::Reflection::PropertyInfo^ property);


        // 実際の値の取得
        System::Object^ GetValue(System::Object^ getInstance);
        // 実際の値の設定
        void SetValue(System::Object^ setInstance, System::Object^ value);


        // メンバーの取得
        property System::Reflection::MemberInfo^ Menber {
            System::Reflection::MemberInfo^ get(void);
        }
        // フィールド情報の取得
        property System::Reflection::FieldInfo^ Field {
            System::Reflection::FieldInfo^ get(void) { return m_field; }
        }
        // プロパティ情報の取得
        property System::Reflection::PropertyInfo^ Property {
            System::Reflection::PropertyInfo^ get(void) { return m_property; }
        }


        // 保持しているフィールド・プロパティの型を取得
        property System::Type^ TypeData {
            System::Type^ get(void);
        }


        // フィールドを保持しているか？
        property bool IsField {
            bool get(void) { return m_field != nullptr; }
        }
        // プロパティを保持しているか？
        property bool IsProperty {
            bool get(void) { return m_property != nullptr; }
        }

    private:
        // コンストラクタ
        // @ Arg1 : フィールド情報
        // @ Arg2 : プロパティ情報
        ClassData(System::Reflection::FieldInfo^ field, System::Reflection::PropertyInfo^ property);

        System::Reflection::FieldInfo^    m_field;      // 保持しているフィールド情報
        System::Reflection::PropertyInfo^ m_property;   // 保持しているプロパティ情報
    };
}


#endif // !I_CLASSDATA_H
