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

    private:
        // �R���X�g���N�^
        EditorUpdater(void) {}

        friend class Singleton<EditorUpdater>;
    };
}


#endif // !I_EDITOROBJECTUPDATER_H
