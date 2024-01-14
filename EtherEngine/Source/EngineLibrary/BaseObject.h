#ifndef I_BASEOBJECT_H
#define I_BASEOBJECT_H
#include <EngineLibrary/IDClass.h>
#include <EngineLibrary/AttributeDefine.h>


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
            System::String^ get(void) { return m_objectName; }
            void set(System::String^ value) { m_objectName = value; }
        }

        //----- �C�x���g��`
#ifdef _EDITOR
        event System::EventHandler^ UpdateEvent;    // �X�V���ɔ��΂���C�x���g
        // �C�x���g�̔��΂��s��
        void UpdateEventIgnition(System::EventArgs^ e) { UpdateEvent(this, e); }
#endif // _EDITOR

    private:
        [Attribute::OutputAttribute] bool m_isActive;    // �L���ɂȂ��Ă��邩
        IDClass^ m_id;      // id
        [Attribute::OutputAttribute] System::String^ m_objectName; // �I�u�W�F�N�g�̖��O
    };
}


#endif // !I_USERBASEOBJECT_H
