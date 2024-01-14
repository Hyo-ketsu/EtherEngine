#ifndef I_EDITOROBJECTUPDATER_H
#define I_EDITOROBJECTUPDATER_H
#include <Base/Singleton.h>
#include <EtherEngine/EditorObjectStorage.h>


//----- EditorUpdater�錾
namespace EtherEngine {
    class EditorUpdater : public Singleton<EditorUpdater> {
    public:
        // �G�f�B�^�[�I�u�W�F�N�g�ɍX�V�������s��
        void Update(void);
        // �G�f�B�^�[�I�u�W�F�N�g�̕`�揈�����s��
        void Draw(void);
        // �G�f�B�^�[�I�u�W�F�N�g�̕`��㏈�����s��
        void LateDraw(void);

    private:
        // �R���X�g���N�^
        EditorUpdater(void) {}

        friend class CentrallySingleton;

        std::vector<Handle<EditorObject>> m_windows; // ���ݕ\�����Ă���E�B���h�E�ꗗ
    };
}


#endif // !I_EDITOROBJECTUPDATER_H
