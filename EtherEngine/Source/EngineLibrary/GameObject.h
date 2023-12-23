#ifndef I_GAMEOBJECT_H
#define I_GAMEOBJECT_H
#include <Base/NativeGameObject.h>
#include <EngineLibrary/BaseObject.h>
ref class Component;
#include <EngineLibrary/Component.h>


//----- GameObject 宣言
namespace EtherEngine {
    // ゲームオブジェクト
    public ref class GameObject : public BaseObject {
    internal:
        // コンストラクタ
        GameObject(void);

    public:
        // デストラクタ
        ~GameObject(void);
        // ファイナライザ
        !GameObject(void);

        // コンポーネントを追加する
        // @ Temp : 追加するコンポーネント
        // @ Ret  : 取得したコンポーネント
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        ComponentType AddComponent(void) {
            //----- コンポーネントを追加する
            auto ret = gcnew ComponentType();
            ret->ParentGameObject = this;
            m_componentList->Add(ret);
            return ret;
        }
        // コンポーネントを取得する
        // @ Temp : 取得するコンポーネント
        // @ Ret  : 取得したコンポーネント
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        ComponentType GetComponent(void) {
            //----- コンポーネント総なめ
            for each (auto it in m_componentList) {
                auto cast = dynamic_cast<ComponentType>(it);
                if (cast != nullptr) {
                    return cast;
                }
            }

            //----- ない。
            return nullptr;
        }
        // コンポーネントを取得する
        // @ Temp : 取得するコンポーネント
        // @ Ret  : 取得したコンポーネント
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        System::Collections::Generic::List<ComponentType>^ GetComponents(void) {
            //----- 返却変数宣言
            System::Collections::Generic::List<ComponentType>^ ret = gcnew System::Collections::Generic::List<ComponentType>(0);

            //----- コンポーネント総なめ
            for each (auto it in m_componentList) {
                auto cast = dynamic_cast<ComponentType>(it);
                if (cast != nullptr) {
                    ret->Add(cast);
                }
            }

            //----- 返却
            return ret;
        }
        // コンポーネントを削除する
        // @ Temp : 削除コンポーネント
        // @ Ret  : 削除が行われたか
        generic <typename ComponentType> where ComponentType : Component, gcnew()
        bool DeleteComponent(void) {
            //----- コンポーネント総なめ
            for (int i = 0; i < m_componentList->Count; i++) {
                auto cast = dynamic_cast<ComponentType>(m_componentList[i]);
                if (cast != nullptr) {
                    m_componentList->RemoveAt(i);
                    return true;
                }
            }

            return false;
        }

    private:
        System::Collections::Generic::List<Component^>^ m_componentList;
        Handle<NativeGameObject>* m_handle;
    };
}


#endif // !I_GAMEOBJECT_H
