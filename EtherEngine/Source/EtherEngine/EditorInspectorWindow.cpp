#include <EtherEngine/EditorInspectorWindow.h>


//----- �\���p�I�u�W�F�N�g �錾
namespace EtherEngine {
    // �f�t�H���g�R���X�g���N�^
    EditorInspectorObject::EditorInspectorObject(void) 
        : EditorInspectorObject(nullptr, []() -> bool {return false; }) {
    }
    // �R���X�g���N�^
    EditorInspectorObject::EditorInspectorObject(IInspectorShow* showObject, const std::function<bool(void)>& deleteObject)
        : m_showObject(showObject)
        , m_deleteObject(deleteObject) {
    }


    // �\���I�u�W�F�N�g�擾
    // @ Ret  : �\���I�u�W�F�N�g(���ɍ폜����Ă����nullptr)
    IInspectorShow* EditorInspectorObject::GetShowObject(void) const {
        if (m_showObject == nullptr || m_deleteObject() == false) {
            return nullptr;
        }
        else {
            return m_showObject;
        }
    }
}


//----- EditorInspectorWindow ��`
namespace EtherEngine {
    // �`�揈��
    void EditorInspectorWindow::DrawWindow(void) {
        auto ptr = ms_showObject.GetShowObject();
        if (ptr != nullptr) ptr->ShowInspector();
    }


    EditorInspectorObject EditorInspectorWindow::ms_showObject = EditorInspectorObject();
}
