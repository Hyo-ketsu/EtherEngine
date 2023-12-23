#ifndef I_IDCLASS_H
#define I_IDCLASS_H
#include <Base/BaseDefines.h>


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

    private:
        IDNumberType m_id;  // id�ԍ�
    };
}


#endif // !I_IDCLASS_H
