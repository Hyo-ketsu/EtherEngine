#include <EngineLibrary/ClassLoader.h>
#include <EngineLibrary/AttributeDefine.h>
#include <EngineLibrary/BaseObject.h>
using namespace System;
using namespace System::Reflection;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace Newtonsoft::Json;


//----- EtherEngineJsonConverter 宣言
namespace EtherEngine {
    void EtherEngineJsonConverter::WriteJson(JsonWriter^ writer, Object^ value, JsonSerializer^ serializer) {
        //----- シリアライズ用変数宣言
        auto serializeFields = ClassLoader::GetClassData(value->GetType(), GetClassDataOption::None, System::Object::typeid);

        //----- 書き込みを開始する
        writer->WriteStartObject();

        //----- 全てシリアライズする
        for each (auto serializeField in serializeFields) {
            writer->WritePropertyName(serializeField->Menber->Name);
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


    Object^ EtherEngineJsonConverter::ReadJson(JsonReader^ reader, Type^ objectType, Object^ existingValue, JsonSerializer^ serializer) {
        //----- Json取得
        auto jsonObject = Newtonsoft::Json::Linq::JObject::Load(reader);

        //----- 型の生成
        auto newInstance = Activator::CreateInstance(objectType);

        //----- デシリアライズ用変数宣言
        auto deserializeFields = ClassLoader::GetClassData(objectType, GetClassDataOption::None, System::Object::typeid);

        //----- 
        for each (auto deserializeField in deserializeFields) {
            Newtonsoft::Json::Linq::JToken^ value;
            if (jsonObject->TryGetValue(deserializeField->Menber->Name, System::StringComparison::OrdinalIgnoreCase, value)) {
                if (jsonObject->TryGetValue(deserializeField->Menber->Name, System::StringComparison::OrdinalIgnoreCase, value)) {
                    //----- フィールド用処理
                    if (deserializeField->IsField) {
                        auto type = deserializeField->Field->FieldType;
                        if (type->IsPrimitive) {
                            deserializeField->SetValue(newInstance, Convert::ChangeType(value->ToObject(type), type));
                        }
                        else {
                            deserializeField->SetValue(newInstance, value->ToObject(type));
                        }
                        continue;
                    }
                    //----- プロパティ用処理
                    if (deserializeField->IsProperty) {
                        auto type = deserializeField->Property->PropertyType;
                        if (type->IsPrimitive) {
                            deserializeField->SetValue(newInstance, Convert::ChangeType(value->ToObject(type), type));
                        }
                        else {
                            deserializeField->SetValue(newInstance, value->ToObject(type));
                        }
                    }
                }
            }
        }

        return newInstance;
    }


    bool EtherEngineJsonConverter::CanConvert(Type^ objectType) {
        return true;
    }
}


//----- ClassLoader 定義
namespace EtherEngine {
    // クラスの情報を出力する
    String^ ClassLoader::Output(Object^ object) {

        auto serializer = gcnew JsonSerializer();
        serializer->Converters->Add(gcnew EtherEngineJsonConverter());
        auto stringWriter = gcnew StringWriter();
        auto jsonWriter = gcnew JsonTextWriter(stringWriter);
        serializer->Serialize(jsonWriter, object);
        return stringWriter->ToString();
    }
    // クラスの情報を入力する
    void ClassLoader::Input(String^ data, Type^ type) {
        // クラス情報をJsonに入力
        auto serializer = gcnew JsonSerializer();
        serializer->Converters->Add(gcnew EtherEngineJsonConverter());
        auto stringReader = gcnew StringReader(data);
        auto jsonReader = gcnew JsonTextReader(stringReader);
        auto newInstance = serializer->Deserialize(jsonReader, type);
    }
    // クラスの各フィールドを出力する
    List<ClassData^>^ ClassLoader::GetClassData(Type^ out, GetClassDataOption option, Type^ overClass) {
        //----- 返却用変数宣言
        List<ClassData^>^ ret = gcnew List<ClassData^>(0);

        //----- 変数宣言
        auto type = out;

        //----- 型取得
        // @ Memo : スーパークラスがSystem::Object または指定したクラスになるまでフィールドを取得し続ける
        while (type != Object::typeid && type != overClass) {
            //----- その型のフィールド取得
            for each (auto member in type->GetMembers(BindingFlags::GetField | BindingFlags::GetProperty | BindingFlags::SetProperty |
                                                      BindingFlags::DeclaredOnly | BindingFlags::Instance | BindingFlags::FlattenHierarchy |
                                                      BindingFlags::Public | BindingFlags::NonPublic)) {
                //----- フィールドの処理を行う？
                auto field = dynamic_cast<FieldInfo^>(member);
                if (field != nullptr) {
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
                        ret->Add(gcnew ClassData(field));
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
                            ret->Add(gcnew ClassData(field));
                        }
                    }
                    //----- プロパティの処理を行う？
                    auto property = dynamic_cast<PropertyInfo^>(member);
                    if (property != nullptr) {
                        //----- Getter,Setter両方がなければ何もしない
                        if (property->GetGetMethod() == nullptr || property->GetSetMethod() == nullptr) goto END_FIELD;

                        //----- そのプロパティが入出力可能か
                        if (property->GetGetMethod()->IsPublic && property->GetSetMethod()->IsPublic) {
                            //----- パブリック。属性をチェックし出力するか判定
                            for each (auto attribute in property->GetCustomAttributes(true)) {
                                //----- 非入出力属性があれば終了。追加しない
                                if (attribute->GetType() == Attribute::NoOutputAttribute::typeid) goto END_FIELD;

                                //----- オプション : エディター非表示があれば終了。追加しない
                                if (option == decltype(option)::Editor) {
                                    if (attribute->GetType() == Attribute::NonEditorOutputAttribute::typeid) goto END_FIELD;
                                }
                            }

                            //----- 出力できる。リストに追加
                            ret->Add(gcnew ClassData(property));
                        }
                        else {
                            //----- 非パブリック。入出力属性があればリストに追加
                            // @ Memo : 非入出力属性は無視します
                            bool isAddList = false; // 追加できるなら true 
                            for each (auto attribute in property->GetCustomAttributes(true)) {
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
                                ret->Add(gcnew ClassData(property));
                            }
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
    // クラスの各フィールドを出力する。自クラスのみ
    List<ClassData^>^ ClassLoader::GetClassData(Type^ out, GetClassDataOption option) {
        return GetClassData(out, option, out->BaseType);
    }
}
