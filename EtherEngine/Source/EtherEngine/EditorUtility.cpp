#include <EtherEngine/EditorUtility.h>


namespace EtherEngine {
    generic <typename Type>
    Type EditorUtility::ListGet(System::Collections::Generic::List<Type>^ list, uint index) {
        auto it = list->GetEnumerator();
        for (int i = 0; i < index; i++) {
            it.MoveNext();
        }

        return it.Current;
    }
}
