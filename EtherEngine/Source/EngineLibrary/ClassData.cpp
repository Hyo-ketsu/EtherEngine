#include <EngineLibrary/ClassData.h>


//----- ClassData 定義
namespace EtherEngine {
    using namespace System;
    using namespace System::Reflection;


    // コンストラクタ
    ClassData::ClassData(FieldInfo^ field, PropertyInfo^ property) 
        : m_field(field)
        , m_property(property) {
        //----- どれもnullptr。エラーを出力
        if (m_property != nullptr && m_property->GetGetMethod() == nullptr && m_property->GetSetMethod() == nullptr) {
            throw gcnew Exception("Error! Input is not a field or property!");
        }
    }
    // コンストラクタ
    ClassData::ClassData(System::Reflection::FieldInfo^ field) 
        : ClassData(field, nullptr) {
    }
    // コンストラクタ
    ClassData::ClassData(System::Reflection::PropertyInfo^ property) 
        : ClassData(nullptr, property) {
    }


    // 実際の値の取得
    Object^ ClassData::GetValue(Object^ getInstance) {
        if (m_field != nullptr) {
            return m_field->GetValue(getInstance);
        }
        if (m_property != nullptr) {
            return m_property->GetValue(getInstance);
        }
    }
    // 実際の値の設定
    void ClassData::SetValue(Object^ setInstance, Object^ value) {
        if (m_field != nullptr) {
            return m_field->SetValue(setInstance, value);
        }
        if (m_property != nullptr) {
            return m_property->SetValue(setInstance, value);
        }
    }


    // メンバーの取得
    MemberInfo^ ClassData::Menber::get(void) { 
        if (m_field != nullptr) {
            return m_field;
        }
        if (m_property != nullptr) {
            return m_property;
        }
    }


    System::Type^ ClassData::TypeData::get(void) {
        if (m_field != nullptr) {
            return m_field->FieldType;
        }
        if (m_property != nullptr) {
            return m_property->PropertyType;
        }
    }
}
