#include <EngineLibrary/IDClass.h>
#include <Base/RandomManage.h>


//----- IDClass ��`
namespace EtherEngine {
    // �f�t�H���g�R���X�g���N�^
    IDClass::IDClass(void) 
        : m_id(0) {
        //----- 0 �ȊO�̔ԍ��ɂȂ�܂ŗ�����������
        while (m_id == 0) {
            m_id = RandomManage::GetRandom<IDNumberType>();
        }
    }
    // ID�𐶐������擾����R���X�g���N�^
    IDClass::IDClass(IDNumberType copyId) 
        : m_id(copyId) {
    }


    // ID���擾����
    IDNumberType IDClass::ID::get(void) {
        return m_id;
    }
}
