#ifndef I_CLASSLOADER_H
#define I_CLASSLOADER_H
#include <EngineLibrary/EngineLibraryDefine.h>


//----- ClassLoader 宣言
namespace EtherEngine {
    // 指定したクラスを入出力するクラス
    public ref class ClassLoader {
    public:
        // クラスの情報を出力する
        // @ Arg1 : 出力先
        // @ Arg2 : 出力する型の実際のデータ
        static void Output(PathString path, System::Object^ object);
        // クラスの情報を入力する
        // @ Arg1 : 入力情報パス
        // @ Arg2 : 入力する型の実際のデータ
        static void Input(PathString path, System::Object^ object);
        // クラスの各フィールドを出力する
        // @ MEMO : 後でプロパティも出力を行うようにする？
        // @ Arg1 : 出力する型
        static System::Collections::Generic::List<System::Object^>^ 
    };
}


#endif // !I_CLASSLOADER_H
