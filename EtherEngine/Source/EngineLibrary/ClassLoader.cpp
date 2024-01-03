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
        auto serializeFields = ClassLoader::GetClassData(value, System::Object::typeid);

        //----- 書き込みを開始する
        writer->WriteStartObject();

        //----- 全てシリアライズする
        for each (auto serializeField in serializeFields) {
            writer->WritePropertyName(serializeField->Name);
            writer->WriteValue(serializeField);
            serializer->Serialize(writer, serializeField->GetValue(value));
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
        auto deserializeFields = ClassLoader::GetClassData(objectType, System::Object::typeid);

        //----- 
        for each (auto deserializeField in deserializeFields) {
            Linq::JToken^ value;
            if (jsonObject->TryGetValue(deserializeField->Name, System::StringComparison::OrdinalIgnoreCase, value)) {
                // Deserialize the property value
                deserializeField->SetValue(newInstance, value->ToObject(deserializeField->FieldType));
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
        // @ MEMO : 後回し
        //----- クラス情報取得
        //auto fields = GetClassData(object, BaseObject::typeid);
        return gcnew System::String("");
    }
    // クラスの情報を入力する
    void ClassLoader::Input(System::String^ data, System::Object^ object) {
        // @ MEMO : 後回し
    }
    // クラスの各フィールドを出力する
    System::Collections::Generic::List<System::Reflection::FieldInfo^>^ ClassLoader::GetClassData(System::Object^ out, System::Type^ overClass) {
        using namespace System;
        using namespace System::Reflection;
        using namespace System::Collections::Generic;

        //----- 返却用変数宣言
        List<FieldInfo^>^ ret = gcnew List<FieldInfo^>(0);

        //----- 変数宣言
        Type^ type = out->GetType();

        //----- 型取得
        // @ Memo : スーパークラスがSystem::Object または指定したクラスになるまでフィールドを取得し続ける
        while (type != Object::typeid && type != overClass) {
            //----- その型のフィールド取得
            for each (auto field in type->GetFields(BindingFlags::Instance | BindingFlags::Public | BindingFlags::NonPublic | BindingFlags::FlattenHierarchy)) {
                //----- そのフィールドが入出力可能か
                if (field->IsPublic) {
                    //----- パブリック。非入出力属性があればリストに追加しない
                    for each (auto attribute in field->GetCustomAttributes(true)) {
                        if (attribute->GetType() == Attribute::NoOutputAttribute::typeid) {
                            goto END_FIELD;
                        }
                    }

                    //----- 非入出力属性がなかった。リストに追加
                    ret->Add(field);
                }
                else {
                    //----- 非パブリック。入出力属性があればリストに追加
                    // @ Memo : 非入出力属性は無視します
                    for each (auto attribute in field->GetCustomAttributes(true)) {
                        if (attribute->GetType() == Attribute::OutputAttribute::typeid) {
                            //----- 入出力属性があった。リストに追加
                            ret->Add(field);
                        }
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
}
