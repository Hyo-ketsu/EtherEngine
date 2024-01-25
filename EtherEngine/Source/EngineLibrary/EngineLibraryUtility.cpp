#include <EngineLibrary/EngineLibraryUtility.h>


namespace EtherEngine {
    generic <typename Type>
    Type EditorUtility::ListGet(System::Collections::Generic::List<Type>^ list, int index) {
        auto it = list->GetEnumerator();
        for (int i = -1; i < index; i++) {  // �Œ����MoveNext���邽��
            it.MoveNext();
        }

        return it.Current;
    }
}
