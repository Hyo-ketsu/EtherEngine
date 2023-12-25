#ifndef I_CLASSLOADER_H
#define I_CLASSLOADER_H
#include <EngineLibrary/EngineLibraryDefine.h>


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
        // @ Arg2 : 入力する型の実際のデータ
        static void Input(System::String^ data, System::Object^ object);
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
