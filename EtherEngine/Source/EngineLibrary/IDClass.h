#ifndef I_IDCLASS_H
#define I_IDCLASS_H
#include <Base/BaseDefines.h>


#pragma managed
//----- IDClass ��`
namespace EtherEngine {
    // ID���Ǘ��E�\������N���X
    public ref class IDClass {
    public:
        // �f�t�H���g�R���X�g���N�^
        IDClass(void);
        // ID�𐶐������擾����R���X�g���N�^
        IDClass(IDNumberType copyId);


        // ID���擾����
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
        IDNumberType m_id;  // id�ԍ�
    };
}


#endif // !I_IDCLASS_H
