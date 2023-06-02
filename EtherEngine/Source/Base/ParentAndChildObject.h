#ifndef I_PARENTANDCHILDOBJECT_H
#define I_PARENTANDCHILDOBJECT_H
#include <Base/Handle.h>
#include <Base/HandleHelper.h>


namespace EtherEngine {
    // 親子関係をクラスでのみ扱うコンセプト
    // クラスかつ参照やポインタではない
    template <typename T>
    concept ParentAndChildObjectConcept = std::is_class_v<T> && !(std::is_reference_v<T>) && !(std::is_pointer_v<T>);
}


//----- ParentAndChildObject宣言
namespace EtherEngine {
    // 親子関係をオブジェクトとして表現するためのクラス
    // @ Temp: 親子関係を表現するクラス
    template <ParentAndChildObjectConcept Type>
    class ParentAndChildObject {
    public:
        // コンストラクタ
        ParentAndChildObject(void) {}
        // デストラクタ
        virtual ~ParentAndChildObject(void) {}


        // 親を設定する
        // @ Arg1 : 親に設定するハンドル
        void SetParent(const BaseHandle<Type>& handle);

        // 親へのアクセスを削除する
        void DeleteParent(void);

        // 親要素が存在するか
        bool IsParent(void) const;

        // 親を取得する
        // @ Ret  : 親要素へのハンドル
        RefHandle<Type> GetParent(void) const;


        // 子を追加する
        // @ Arg1 : 子として追加するハンドル
        void AddChild(const BaseHandle<Type>& handle);

        // インデックスで子へのアクセスを削除する
        // @ Arg1 : インデックス
        void DeleteChild(const uint index);
        // 指定ハンドルで子へのアクセスを削除する
        void DeleteChild(const BaseHandle<Type>& handle);
        // 指定ハンドルで子へのアクセスを削除する
        void DeleteChild(const BaseHandle<Type>& handle);
        // 全ての子へのアクセスを削除する
        void DeleteChildAll(void);

        // 子要素の数
        // @ Ret  : 子要素の数
        uint GetChildCount(void) const;
        // 子要素が一つでも存在するか
        bool IsChild(void) const;

        // インデックスで子へのアクセスを取得する
        // @ Arg1 : インデックス
        RefHandle<Type> GetChild(const uint index);
        // 指定ハンドルで子へのアクセスを取得する
        RefHandle<Type> GetChild(const BaseHandle<Type>& handle);
        // 全ての子へのアクセスを取得する
        std::vector<RefHandle<Type>> GetChildAll(void);

    private:
        RefHandle<Type>              m_parent;  // 親
        std::vector<RefHandle<Type>> m_child;   // 子
    };
}


//----- ParentAndChildObject実装
namespace EtherEngine {
    // 親を設定する
    // @ Arg1 : 親に設定するハンドル
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::SetParent(const BaseHandle<Type>& handle) {
        SetParent(HandleHelper::GetRefHandle(handle));
    }
    // 親を設定する
    // @ Arg1 : 親に設定するハンドル
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::SetParent(const BaseHandle<Type>& handle) {
        m_parent = handle;
    }

    // 親へのアクセスを削除する
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::DeleteParent(void) {
        m_parent.DeleteRef();
    }

    // 親要素が存在するか
    template <ParentAndChildObjectConcept Type>
    bool ParentAndChildObject<Type>::IsParent(void) const {
        return m_parent.GetEnable();
    }

    // 親を取得する
    // @ Ret  : 親要素へのハンドル
    template <ParentAndChildObjectConcept Type>
    RefHandle<Type> ParentAndChildObject<Type>::GetParent(void) const {
        return m_parent;
    }


    // 子を追加する
    // @ Arg1 : 子として追加するハンドル
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::AddChild(const BaseHandle<Type>& handle) {
        m_child.push_back(handle);
    }

    // インデックスで子へのアクセスを削除する
    // @ Arg1 : インデックス
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::DeleteChild(const uint index) {
        m_child[index].DeleteRef();
    }
    // 指定ハンドルで子へのアクセスを削除する
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::DeleteChild(const BaseHandle<Type>& handle) {
        for (int i = 0; i < m_child.size(); i++) {
            if (m_child[index] == handle) {
                m_child[i].DeleteRef();
                return;
            }
        }
    }
    // 全ての子へのアクセスを削除する
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::DeleteChildAll(void) {
        m_child.clear();
    }

    // 子要素の数
    // @ Ret  : 子要素の数
    template <ParentAndChildObjectConcept Type>
    uint ParentAndChildObject<Type>::GetChildCount(void) const {
        return m_child.size();
    }
    // 子要素が一つでも存在するか
    template <ParentAndChildObjectConcept Type>
    bool ParentAndChildObject<Type>::IsChild(void) const {
        return m_child.size() > 0;
    }

    // インデックスで子へのアクセスを取得する
    // @ Arg1 : インデックス
    template <ParentAndChildObjectConcept Type>
    RefHandle<Type> ParentAndChildObject<Type>::GetChild(const uint index) {
        return m_child[i];
    }
    // 指定ハンドルで子へのアクセスを取得する
    template <ParentAndChildObjectConcept Type>
    RefHandle<Type> ParentAndChildObject<Type>::GetChild(const BaseHandle<Type>& handle) {
        for (int i = 0; i < m_child.size(); i++) {
            if (m_child[index] == handle) {
                return m_child[i];
            }
        }
    }
    // 全ての子へのアクセスを取得する
    template <ParentAndChildObjectConcept Type>
    std::vector<RefHandle<Type>> ParentAndChildObject<Type>::GetChildAll(void) {
        return m_child;
    }
}


#endif // !I_PARENTANDCHILDOBJECT_H
