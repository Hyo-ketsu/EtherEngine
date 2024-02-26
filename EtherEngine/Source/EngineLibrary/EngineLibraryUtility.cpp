#include <EngineLibrary/EngineLibraryUtility.h>


namespace EtherEngine {
}


namespace EtherEngine {
    generic <typename Type>
    Type EditorUtility::ListGet(System::Collections::Generic::List<Type>^ list, int index) {
        auto it = list->GetEnumerator();
        for (int i = -1; i < index; i++) {  // 最低一回はMoveNextするため
            it.MoveNext();
        }

        return it.Current;
    }


    // 4x4行列の行・列インデックスから数値を取得する
    float MatrixHelper::GetElement(System::Numerics::Matrix4x4% matrix, int row, int column) {
        switch (row) {
        case 0:
            switch (column) {
            case 0: return matrix.M11;
            case 1: return matrix.M12;
            case 2: return matrix.M13;
            case 3: return matrix.M14;
            default: throw gcnew System::ArgumentOutOfRangeException("column");
            }
        case 1:
            switch (column) {
            case 0: return matrix.M21;
            case 1: return matrix.M22;
            case 2: return matrix.M23;
            case 3: return matrix.M24;
            default: throw gcnew System::ArgumentOutOfRangeException("column");
            }
        case 2:
            switch (column) {
            case 0: return matrix.M31;
            case 1: return matrix.M32;
            case 2: return matrix.M33;
            case 3: return matrix.M34;
            default: throw gcnew System::ArgumentOutOfRangeException("column");
            }
        case 3:
            switch (column) {
            case 0: return matrix.M41;
            case 1: return matrix.M42;
            case 2: return matrix.M43;
            case 3: return matrix.M44;
            default: throw gcnew System::ArgumentOutOfRangeException("column");
            }
        default: throw gcnew System::ArgumentOutOfRangeException("row");
        }
    }
    // 4x4行列の行・列インデックスから数値を設定する
    void MatrixHelper::SetElement(System::Numerics::Matrix4x4% matrix, int row, int column, float value) {
        switch (row) {
        case 0:
            switch (column) {
            case 0: matrix.M11 = value; break;
            case 1: matrix.M12 = value; break;
            case 2: matrix.M13 = value; break;
            case 3: matrix.M14 = value; break;
            default: throw gcnew System::ArgumentOutOfRangeException("column");
            }
            break;
        case 1:
            switch (column) {
            case 0: matrix.M21 = value; break;
            case 1: matrix.M22 = value; break;
            case 2: matrix.M23 = value; break;
            case 3: matrix.M24 = value; break;
            default: throw gcnew System::ArgumentOutOfRangeException("column");
            }
            break;
        case 2:
            switch (column) {
            case 0: matrix.M31 = value; break;
            case 1: matrix.M32 = value; break;
            case 2: matrix.M33 = value; break;
            case 3: matrix.M34 = value; break;
            default: throw gcnew System::ArgumentOutOfRangeException("column");
            }
            break;
        case 3:
            switch (column) {
            case 0: matrix.M41 = value; break;
            case 1: matrix.M42 = value; break;
            case 2: matrix.M43 = value; break;
            case 3: matrix.M44 = value; break;
            default: throw gcnew System::ArgumentOutOfRangeException("column");
            }
            break;
        default: throw gcnew System::ArgumentOutOfRangeException("row");
        }
    }
}
