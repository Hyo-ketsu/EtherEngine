#include <EngineLibrary/EngineLibraryUtility.h>


namespace EtherEngine {
    generic <typename Type>
    Type EditorUtility::ListGet(System::Collections::Generic::List<Type>^ list, int index) {
        auto it = list->GetEnumerator();
        for (int i = -1; i < index; i++) {  // Å’áˆê‰ñ‚ÍMoveNext‚·‚é‚½‚ß
            it.MoveNext();
        }

        return it.Current;
    }
}
