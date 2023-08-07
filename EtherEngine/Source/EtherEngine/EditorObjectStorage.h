#ifndef I_EDITOROBJECTSTORAGE_H
#define I_EDITOROBJECTSTORAGE_H
#include <Base/Singleton.h>
#include <Base/Handle.h>
#include <EtherEngine/EditorObject.h>
#include <EtherEngine/EditorComponentHelper.h>


// @ MEMO : Scene������͌��
//----- GameObejctStorage�錾
namespace EtherEngine {
    // �G�f�B�^�[�I�u�W�F�N�g���Ǘ�����N���X
    class EditorObjectStorage : public Singleton<EditorObjectStorage> {
    public:
        // ��̃G�f�B�^�[�I�u�W�F�N�g���쐬����
        // @ Ret  : �쐬�����G�f�B�^�[�I�u�W�F�N�g�̃n���h��
        // @ Arg1 : ���W(�f�t�H���g : ���W�E��]��0, �g�k��1)
        BaseHandle<EditorObject> CreateEditorObject(const Transform& transform = Transform());
        // �G�f�B�^�[�I�u�W�F�N�g���폜����
        // @ Ret  : �폜������������
        // @ Arg1 : �폜����I�u�W�F�N�g�̃n���h��
        bool DeleteEditorObject(const BaseHandle<EditorObject>& editorObject);


        // �S�ẴG�f�B�^�[�I�u�W�F�N�g���擾����
        std::vector<BaseHandle<EditorObject>> GetEditorObjectAll(void);


        // �폜�ς݂̃G�f�B�^�[�I�u�W�F�N�g���폜����
        void DeleteEditorObjectsDelete(void);

    private:
        friend class Singleton<EditorObjectStorage>;

        std::vector<BaseHandle<EditorObject>> m_editorObjects;   // �G�f�B�^�[�I�u�W�F�N�g�̃n���h��
    };
}


#endif // !I_EDITOROBJECTSTORAGE_H