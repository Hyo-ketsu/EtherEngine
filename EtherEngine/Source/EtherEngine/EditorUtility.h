#ifndef I_EDITORUTILITY_H
#define I_EDITORUTILITY_H


#pragma managed
//----- �֗��֐���`
namespace EtherEngine {
    public ref class EditorUtility {
    public:
        // List����w�肵���C���f�b�N�X�̗v�f���擾����
        // @ Ret  : �擾�����v�f
        // @ Arg1 : ���X�g
        // @ Arg2 : �C���f�b�N�X
        generic <typename Type>
        static Type ListGet(System::Collections::Generic::List<Type>^ list, uint index);
    };
}


#endif // !I_EDITORUTILITY_H
