#ifndef I_CONVERTMANAGE_H
#define I_CONVERTMANAGE_H
#include <Base/PathClass.h>
#include <EngineLibrary/EngineLibraryDefine.h>


//----- ïœä∑É}ÉNÉç
namespace EtherEngine {
#define UNMANAGE_TO_MANAGE_STRING(text) gcnew System::String(text.c_str())
#define UNMANAGE_TO_MANAGE_MATRIX_SET(nativeMatrix, manageMatrix) \
    for (int i = 0; i < 4; i++) {\
        for (int j = 0; j < 4; j++) {\
            MatrixHelper::SetElement(manageMatrix, i, j, nativeMatrix(i, j));\
        }\
    }
#define MANAGE_TO_UNMANAGE_MATRIX_SET(manageMatrix, nativeMatrix)\
    for (int i = 0; i < 4; i++) {\
        for (int j = 0; j < 4; j++) {\
            (nativeMatrix)(i, j) = MatrixHelper::GetElement(manageMatrix, i, j);\
        }\
    }
}


//----- ïœä∑ä÷êî
#define MANAGE_TO_UNMANAGE_CLASS_DECLARE  \
namespace ManageToUnmanage {\
    std::string String(System::String^ manage);\
    PathClass Path(PathString manage);\
}

#define MANAGE_TO_UNMANAGE_CLASS_DEFINE \
namespace ManageToUnmanage {\
    std::string String(System::String^ manage) {\
        std::string ret;\
        auto wchars = manage->ToCharArray();\
        ret.reserve(wchars->Length);\
        for (int i = 0; i < wchars->Length; i++) {\
            ret.push_back(static_cast<char>(wchars[i]));\
        }\
        return ret;\
    }\
    PathClass Path(PathString manage) {\
        return PathClass(String(manage));\
    }\
}


#endif // !I_CONVERTMANAGE_H
