#include <EngineLibrary/ManageFunctionInit.h>
#include <Base/GameObject.h>
#include <Base/ThreadingUtility.h>
#include <Base/Mutex.h>
#include <EngineLibrary/GameComponent.h>
#include <EngineLibrary/GameDrawComponent.h>
#include <EngineLibrary/EngineLibraryUtility.h>
#include <EngineLibrary/AssemblyHolder.h>
#include <EngineLibrary/WrapperMutex.h>


//----- �֐���`
namespace EtherEngine {
    // �R���|�[�l���g�����֐�
    std::shared_ptr<GameComponent> GetComponent(GameObject* gameObject, const std::string& createName) {
        return std::move(std::make_shared<GameComponent>(gameObject, GetFullName(createName)));
    }


    // AddComponent���j���[�\���֐�
    std::shared_ptr<ComponentBase> AddComponentMenu(GameObject* gameObject) {
        //----- �e�T�u�N���X�擾
        // @ MEMO : �����蔻�肾���ʘg�H
        auto assembly = AssemblyHolder::GetAssembly();
        auto types = assembly->GetTypes();
        std::vector<std::pair<std::string,std::string>> showTypeName;

        //----- Component�ǉ�
        for each (auto type in types) {
            if (UserBaseComponent::typeid->IsAssignableFrom(type) && UserBaseComponent::typeid != type && UserDrawBaseComponent::typeid != type) {
                showTypeName.push_back(std::make_pair<std::string, std::string>(ManageToUnmanage::String(type->Name), ManageToUnmanage::String(type->FullName)));
            }
        }

        //----- �\��
        // @ MEMO : �\�[�g�͌������
        for (auto&& it : showTypeName) {
            if (ImGui::MenuItem(it.first.c_str())) {
                return std::move(std::dynamic_pointer_cast<ComponentBase>(GetComponent(gameObject, it.second)));
            }
        }

        //----- �I������Ȃ��Bnullptr�ԋp
        return nullptr;
    }


    auto GetMutex(void) {
        return std::shared_ptr<Mutex>(new WrapperMutex());
    }
    void ThisThreadSleep(uint ms) {
        System::Threading::Thread::Sleep(ms);
    }
}


//----- �������E�I��������`
namespace EtherEngine {
    // ����������
    void ENGINELIBRARY_API ManageFunctionInit::Init(void) {
        GameObject::ms_getComponent = GetComponent;
        GameObject::ms_addComponentMenu = AddComponentMenu;
        GameObject::ms_getFullName = [](const std::string& name, const uint index = 0, const bool isSystem = false) -> std::string { 
            return GetFullName(name, index, isSystem);
        };

        ThreadingUtility::ms_getMutex.SetLambda(GetMutex);
        ThreadingUtility::ms_thisThreadSleep.SetLambda(ThisThreadSleep);
    }
    // �I������
    void ENGINELIBRARY_API ManageFunctionInit::Uninit(void) {
    }
}
