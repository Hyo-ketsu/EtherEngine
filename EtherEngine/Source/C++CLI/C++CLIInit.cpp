#include <C++CLI/C++CLIInit.h>
#include <Base/GameObject.h>
#include <C++CLI/GameComponent.h>
#include <C++CLI/GameDrawComponent.h>


//----- �֐���`
namespace EtherEngine {
    // �R���|�[�l���g�����֐�
    template <Concept::BaseOfConcept<ComponentBase> ComponentType, Concept::BaseOfConcept<ComponentBase> CreateType>
    std::shared_ptr<ComponentType>&& GetComponent(GameObject* gameObject, const std::string& createName) {
        return std::move(std::make_shared<CreateType>(gameObject, createName));
    }
}


//----- �������E�I��������`
namespace EtherEngine {
    // ����������
    void CPPCLI::Init(void) {
        GameObject::ms_getComponent = GetComponent<ComponentBase, GameComponent>;
        GameObject::ms_getDrawComponent = GetComponent<DrawComponent, GameDrawComponent>;
    }
    // �I������
    void CPPCLI::Uninit(void) {
    }
}
