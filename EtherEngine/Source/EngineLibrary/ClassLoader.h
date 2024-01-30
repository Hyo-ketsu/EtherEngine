#ifndef I_CLASSLOADER_H
#define I_CLASSLOADER_H
#include <EngineLibrary/EngineLibraryDefine.h>


//----- EtherEngineJsonConverter 宣言
namespace EtherEngine {
    // このエンジンのJsonConverter
    public ref class EtherEngineJsonConverter : Newtonsoft::Json::JsonConverter {
    public:
        void WriteJson(Newtonsoft::Json::JsonWriter^ writer, System::Object^ value, Newtonsoft::Json::JsonSerializer^ serializer) override;


        System::Object^ ReadJson(Newtonsoft::Json::JsonReader^ reader, System::Type^ objectType, System::Object^ existingValue, Newtonsoft::Json::JsonSerializer^ serializer)  override;


        bool CanConvert(System::Type^ objectType) override;
    };
}


//----- ClassLoader 宣言
namespace EtherEngine {
    // 指定したクラスを入出力するクラス
    public ref class ClassLoader {
    public:
        // クラスの情報を出力する
        // @ Ret  : 出力データ
        // @ Arg1 : 出力する型の実際のデータ
        static System::String^ Output(System::Object^ object);
        // クラスの情報を入力する
        // @ MEMO : 取得できなかったフィールド等を取得できるようにしておくべき。
        // @ Arg1 : 入力情報データ
        // @ Arg2 : 入力する型
        static void Input(System::String^ data, System::Type^ type);
        // クラスの各フィールドを出力する
        // @ MEMO : 後でプロパティも出力を行うようにする？
        // @ Memo : 標準でSystem::Objectのフィールドは無視します
        // @ Ret  : 出力した型一覧
        // @ Arg1 : 出力するオブジェクト
        // @ Arg2 : フィールドを取得する限界のクラス(Hoge->Fuga->PiyoでPiyoを指定した場合、Hoge,Fugaのフィールドを取得)
        static System::Collections::Generic::List<System::Reflection::FieldInfo^>^ GetClassData(System::Object^ out, System::Type^ overClass);
    };
}


#endif // !I_CLASSLOADER_H
