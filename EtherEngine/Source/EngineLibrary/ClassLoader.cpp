#include <EngineLibrary/ClassLoader.h>
#include <EngineLibrary/AttributeDefine.h>
#include <EngineLibrary/BaseObject.h>


//----- EtherEngineJsonConverter 宣言
namespace EtherEngine {
    void EtherEngineJsonConverter::WriteJson(Newtonsoft::Json::JsonWriter^ writer, System::Object^ value, Newtonsoft::Json::JsonSerializer^ serializer) {
        using namespace System;
        using namespace System::Reflection;
        using namespace System::Collections::Generic;

        //----- シリアライズ用変数宣言
        auto serializeFields = ClassLoader::GetClassData(value->GetType(), GetClassDataOption::None, System::Object::typeid);

        //----- 書き込みを開始する
        writer->WriteStartObject();

        //----- 全てシリアライズする
        for each (auto serializeField in serializeFields) {
            writer->WritePropertyName(serializeField->Name);
            auto fieldValue = serializeField->GetValue(value);
            if (fieldValue == nullptr) {
                writer->WriteNull();
                continue;
            }
            if (fieldValue->GetType()->IsPrimitive || fieldValue->GetType() == String::typeid) {
                writer->WriteValue(fieldValue);
            }
            else {
                serializer->Serialize(writer, fieldValue);
            }
        }

        writer->WriteEndObject();
    }


    System::Object^ EtherEngineJsonConverter::ReadJson(Newtonsoft::Json::JsonReader^ reader, System::Type^ objectType, System::Object^ existingValue, Newtonsoft::Json::JsonSerializer^ serializer) {
        using namespace Newtonsoft::Json;

        //----- Json取得
        auto jsonObject = Linq::JObject::Load(reader);

        //----- 型の生成
        auto newInstance = System::Activator::CreateInstance(objectType);

        //----- デシリアライズ用変数宣言
        auto deserializeFields = ClassLoader::GetClassData(objectType, GetClassDataOption::None, System::Object::typeid);

        //----- 
        for each (auto deserializeField in deserializeFields) {
            Linq::JToken^ value;
            if (jsonObject->TryGetValue(deserializeField->Name, System::StringComparison::OrdinalIgnoreCase, value)) {
                if (jsonObject->TryGetValue(deserializeField->Name, System::StringComparison::OrdinalIgnoreCase, value)) {
                    if (deserializeField->FieldType->IsPrimitive) {
                        deserializeField->SetValue(newInstance, System::Convert::ChangeType(value->ToObject(deserializeField->FieldType), deserializeField->FieldType));
                    }
                    else {
                        deserializeField->SetValue(newInstance, value->ToObject(deserializeField->FieldType));
                    }
                }
            }
        }

        return newInstance;
    }


    bool EtherEngineJsonConverter::CanConvert(System::Type^ objectType) {
        return true;
    }
}


//----- ClassLoader 定義
namespace EtherEngine {
    // クラスの情報を出力する
    System::String^ ClassLoader::Output(System::Object^ object) {
        using namespace Newtonsoft::Json;

        auto serializer = gcnew JsonSerializer();
        serializer->Converters->Add(gcnew EtherEngineJsonConverter());
        auto stringWriter = gcnew System::IO::StringWriter();
        auto jsonWriter = gcnew JsonTextWriter(stringWriter);
        serializer->Serialize(jsonWriter, object);
        return stringWriter->ToString();
    }
    // クラスの情報を入力する
    void ClassLoader::Input(System::String^ data, System::Type^ type) {
        using namespace Newtonsoft::Json;
        using namespace System;
        using namespace System::IO;
        using namespace System::Collections;
        using namespace System::Collections::Generic;

        // クラス情報をJsonに入力
        auto serializer = gcnew JsonSerializer();
        serializer->Converters->Add(gcnew EtherEngineJsonConverter());
        auto stringReader = gcnew StringReader(data);
        auto jsonReader = gcnew JsonTextReader(stringReader);
        auto newInstance = serializer->Deserialize(jsonReader, type);
    }
    // クラスの各フィールドを出力する
    System::Collections::Generic::List<System::Reflection::FieldInfo^>^ ClassLoader::GetClassData(System::Type^ out, GetClassDataOption option, System::Type^ overClass) {
        using namespace System;
        using namespace System::Reflection;
        using namespace System::Collections::Generic;

        //----- 返却用変数宣言
        List<FieldInfo^>^ ret = gcnew List<FieldInfo^>(0);

        //----- 変数宣言
        auto type = out;

        //----- 型取得
        // @ Memo : スーパークラスがSystem::Object または指定したクラスになるまでフィールドを取得し続ける
        while (type != Object::typeid && type != overClass) {
            //----- その型のフィールド取得
            for each (auto field in type->GetFields(BindingFlags::DeclaredOnly | BindingFlags::Instance | BindingFlags::Public | BindingFlags::NonPublic | BindingFlags::FlattenHierarchy)) {
                //----- そのフィールドが入出力可能か
                if (field->IsPublic) {
                    //----- パブリック。属性をチェックし出力するか判定
                    for each (auto attribute in field->GetCustomAttributes(true)) {
                        //----- 非入出力属性があれば終了。追加しない
                        if (attribute->GetType() == Attribute::NoOutputAttribute::typeid) goto END_FIELD;

                        //----- オプション : エディター非表示があれば終了。追加しない
                        if (option == decltype(option)::Editor) {
                            if (attribute->GetType() == Attribute::NonEditorOutputAttribute::typeid) goto END_FIELD;
                        }
                    }
                    
                    //----- 出力できる。リストに追加
                    ret->Add(field);
                }
                else {
                    //----- 非パブリック。入出力属性があればリストに追加
                    // @ Memo : 非入出力属性は無視します
                    bool isAddList = false; // 追加できるなら true 
                    for each (auto attribute in field->GetCustomAttributes(true)) {
                        //----- 入出力属性があるか
                        if (attribute->GetType() == Attribute::OutputAttribute::typeid) {
                            //----- 追加フラグを立てる
                            isAddList = true;
                        }
                        //----- オプション : エディター非表示があれば終了。追加しない
                        if (option == decltype(option)::Editor) {
                            if (attribute->GetType() == Attribute::NonEditorOutputAttribute::typeid) goto END_FIELD;
                        }
                    }

                    //----- 追加できるなら追加
                    if (isAddList) {
                        ret->Add(field);
                    }
                }

                END_FIELD: {}
            }

            //----- スーパークラスの取得、設定
            type = type->BaseType;
        }

        //----- fieldをスーパー->サブの順にするため反転させる
        ret->Reverse();

        //----- 返却
        return ret;
    }
    // クラスの各フィールドを出力する。自クラスのみ
    System::Collections::Generic::List<System::Reflection::FieldInfo^>^ ClassLoader::GetClassData(System::Type^ out, GetClassDataOption option) {
        return GetClassData(out, option, out->BaseType);
    }
}
