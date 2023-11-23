#ifndef I_CONVERTMANAGE_H
#define I_CONVERTMANAGE_H
#include <Base/PathClass.h>
#include <EngineLibrary/EngineLibraryDefine.h>


//----- �ϊ��}�N��
namespace EtherEngine {
#define UNMANAGE_TO_MANAGE_STRING(text) gcnew System::String(text.c_str())
}


//----- �ϊ��֐�
namespace EtherEngine {
#ifdef _ENGINELIBRARY
    //----- �}�l�[�W����A���}�l�[�W�ւ̕ϊ�
    public ref class ManageToUnmanage {
    public:
        // ������ϊ�
        static std::string String(System::String^ manage);

        // �p�X�ϊ�
        static PathClass Path(PathString^ manage);
    };
#endif
}

#endif // !I_CONVERTMANAGE_H
