#include <EtherEngine/EditorUtility.h>


namespace EtherEngine {
    generic <typename Type>
    Type EditorUtility::ListGet(System::Collections::Generic::List<Type>^ list, int index) {
        auto it = list->GetEnumerator();
        for (int i = -1; i < index; i++) {  // 最低一回はMoveNextするため
            it.MoveNext();
        }

        return it.Current;
    }
}
