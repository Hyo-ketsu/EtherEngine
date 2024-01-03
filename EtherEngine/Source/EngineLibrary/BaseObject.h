#ifndef I_BASEOBJECT_H
#define I_BASEOBJECT_H
#include <EngineLibrary/IDClass.h>


#pragma managed
namespace EtherEngine {
    // �ėp�I�ɃG���W�����ň�����I�u�W�F�N�g
    public ref class BaseObject {
    public:
        // �R���X�g���N�^
        BaseObject(void);
        // �R���X�g���N�^
        // @ Arg1 : �R�s�[ID
        BaseObject(IDClass^ id);

        // ID
        property IDClass^ ID {
            IDClass^ get(void) { return gcnew IDClass(m_id->ID); }
        }
        // �A�N�e�B�u
        property bool Active {
            bool get(void) { return m_isActive; }
            void set(bool value) { m_isActive = value; }
        }
        // ���O
        property System::String^ Name {
            System::String^ get(void) { return m_name; }
            void set(System::String^ value) { m_name = value; }
        }

    private:
        bool m_isActive;    // �L���ɂȂ��Ă��邩
        IDClass^ m_id;      // id
        System::String^ m_name; // �I�u�W�F�N�g�̖��O
    };
}


#endif // !I_USERBASEOBJECT_H
