#ifndef I_PARENTANDCHILDOBJECT_H
#define I_PARENTANDCHILDOBJECT_H
#include <Base/Handle.h>
#include <Base/HandleHelper.h>


//----- ParentAndChildObject宣言
namespace EtherEngine {
    // 親子関係をクラスでのみ扱うコンセプト
    // クラスかつ参照やポインタではない
    template <typename T>
    concept ParentAndChildObjectConcept = std::is_class_v<T> && 
        !(std::is_reference_v<T>) && !(std::is_pointer_v<T>);


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
        template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
        void SetParent(const Handle<Type, HandleCountType::Count>& handle);
        // 親を設定する
        // @ Arg1 : 親に設定するハンドル
        template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
        void SetParent(const Handle<Type, HandleCountType::UnCount>& handle);

        // 親へのアクセスを削除する
        void DeleteParent(void);

        // 親要素が存在するか
        bool IsParent(void) const;

        // 親を取得する
        // @ Ret  : 親要素へのハンドル
        void GetParent(void) const;


        // 子を追加する
        // @ Arg1 : 子として追加するハンドル
        template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
        void AddChild(const Handle<Type, HandleCountType::Count>& handle);
        // 子を追加する
        // @ Arg1 : 子として追加するハンドル
        template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
        void AddChild(const Handle<Type, HandleCountType::UnCount>& handle);

        // インデックスで子へのアクセスを削除する
        // @ Arg1 : インデックス
        void DeleteChild(const uint index);
        // 指定ハンドルで子へのアクセスを削除する
        template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
        void DeleteChild(const Handle<Type, HandleCountType::Count>& handle);
        // 指定ハンドルで子へのアクセスを削除する
        template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
        void DeleteChild(const Handle<Type, HandleCountType::UnCount>& handle);
        // 全ての子へのアクセスを削除する
        void DeleteChildAll(void);

        // 子要素の数
        // @ Ret  : 子要素の数
        uint GetChildCount(void) const;
        // 子要素が一つでも存在するか
        bool IsChild(void) const;

        // インデックスで子へのアクセスを取得する
        // @ Arg1 : インデックス
        void GetChild(const uint index);
        // 指定ハンドルで子へのアクセスを取得する
        template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
        void GetChild(const Handle<Type, HandleCountType::Count>& handle);
        // 指定ハンドルで子へのアクセスを取得する
        template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
        void GetChild(const Handle<Type, HandleCountType::UnCount>& handle);
        // 全ての子へのアクセスを取得する
        void GetChildAll(void);

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
    template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
    void ParentAndChildObject<Type>::SetParent(const Handle<Type, HandleCountType::Count>& handle) {
        SetParent(HandleHelper::GetRefHandle(handle));
    }
    // 親を設定する
    // @ Arg1 : 親に設定するハンドル
    template <ParentAndChildObjectConcept Type>
    template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
    void ParentAndChildObject<Type>::SetParent(const Handle<Type, HandleCountType::UnCount>& handle) {
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

    }

    // 親を取得する
    // @ Ret  : 親要素へのハンドル
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::GetParent(void) const {

    }


    // 子を追加する
    // @ Arg1 : 子として追加するハンドル
    template <ParentAndChildObjectConcept Type>
    template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
    void ParentAndChildObject<Type>::AddChild(const Handle<Type, HandleCountType::Count>& handle) {

    }
    // 子を追加する
    // @ Arg1 : 子として追加するハンドル
    template <ParentAndChildObjectConcept Type>
    template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
    void ParentAndChildObject<Type>::AddChild(const Handle<Type, HandleCountType::UnCount>& handle) {

    }

    // インデックスで子へのアクセスを削除する
    // @ Arg1 : インデックス
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::DeleteChild(const uint index) {

    }
    // 指定ハンドルで子へのアクセスを削除する
    template <ParentAndChildObjectConcept Type>
    template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
    void ParentAndChildObject<Type>::DeleteChild(const Handle<Type, HandleCountType::Count>& handle) {

    }
    // 指定ハンドルで子へのアクセスを削除する
    template <ParentAndChildObjectConcept Type>
    template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
    void ParentAndChildObject<Type>::DeleteChild(const Handle<Type, HandleCountType::UnCount>& handle) {

    }
    // 全ての子へのアクセスを削除する
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::DeleteChildAll(void) {

    }

    // 子要素の数
    // @ Ret  : 子要素の数
    template <ParentAndChildObjectConcept Type>
    uint ParentAndChildObject<Type>::GetChildCount(void) const {

    }
    // 子要素が一つでも存在するか
    template <ParentAndChildObjectConcept Type>
    bool ParentAndChildObject<Type>::IsChild(void) const {

    }

    // インデックスで子へのアクセスを取得する
    // @ Arg1 : インデックス
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::GetChild(const uint index) {

    }
    // 指定ハンドルで子へのアクセスを取得する
    template <ParentAndChildObjectConcept Type>
    template <HandleCountTypeConcept<Type, HandleCountType::Count> HandleType>
    void ParentAndChildObject<Type>::GetChild(const Handle<Type, HandleCountType::Count>& handle) {

    }
    // 指定ハンドルで子へのアクセスを取得する
    template <ParentAndChildObjectConcept Type>
    template <HandleCountTypeConcept<Type, HandleCountType::UnCount> HandleType>
    void ParentAndChildObject<Type>::GetChild(const Handle<Type, HandleCountType::UnCount>& handle) {

    }
    // 全ての子へのアクセスを取得する
    template <ParentAndChildObjectConcept Type>
    void ParentAndChildObject<Type>::GetChildAll(void) {

    }
}


#endif // !I_PARENTANDCHILDOBJECT_H
