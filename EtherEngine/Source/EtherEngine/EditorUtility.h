#ifndef I_EDITORUTILITY_H
#define I_EDITORUTILITY_H


#pragma managed
//----- 便利関数定義
namespace EtherEngine {
    public ref class EditorUtility {
    public:
        // Listから指定したインデックスの要素を取得する
        // @ Ret  : 取得した要素
        // @ Arg1 : リスト
        // @ Arg2 : インデックス
        generic <typename Type>
        static Type ListGet(System::Collections::Generic::List<Type>^ list, uint index);
    };
}


#endif // !I_EDITORUTILITY_H
