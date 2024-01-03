#ifndef I_IDCLASS_H
#define I_IDCLASS_H
#include <Base/BaseDefines.h>


#pragma managed
//----- IDClass 定義
namespace EtherEngine {
    // IDを管理・表現するクラス
    public ref class IDClass {
    public:
        // デフォルトコンストラクタ
        IDClass(void);
        // IDを生成せず取得するコンストラクタ
        IDClass(IDNumberType copyId);


        // IDを取得する
        property IDNumberType ID {
            IDNumberType get(void);
        }


        static bool operator ==(IDClass^ left, IDClass^ right) {
            if (Object::ReferenceEquals(left, nullptr)) {
                return Object::ReferenceEquals(right, nullptr);
            }

            return left->m_id == right->m_id;
        }
        static bool operator !=(IDClass^ left, IDClass^ right) {
            return !(left == right);
        }
        bool Equals(Object^ obj) override {
            if (Object::ReferenceEquals(obj, nullptr) || obj->GetType() != GetType()) {
                return false;
            }

            return this == safe_cast<IDClass^>(obj);
        }
        int GetHashCode(void) override {
            return m_id.GetHashCode();
        }

    private:
        IDNumberType m_id;  // id番号
    };
}


#endif // !I_IDCLASS_H
