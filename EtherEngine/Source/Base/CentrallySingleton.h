#ifndef I_CENTRALLYSINGLETON_H
#define I_CENTRALLYSINGLETON_H
#include <Base/Mutex.h>
#include <Base/BaseUtility.h>


//----- CentrallySingleton 宣言
namespace EtherEngine {
    // シングルトンをT::Get()で呼び出せ、かつコンストラクタが呼び出せない型を判定するコンセプト
    template <typename T>
    concept SingletonTypeConcept = requires(T t) {
        {t.Get()}-> std::same_as<T*>;
    };


    // シングルトンを一元的に保持しているクラス
    class CentrallySingleton {
    public:
        // デストラクタ
        ~CentrallySingleton(void);


        // インスタンスを取得する
        static std::shared_ptr<CentrallySingleton>& Get(void);
        // インスタンスを設定する
        static void Set(std::shared_ptr<CentrallySingleton> instance);


        // シングルトンを追加する
        // @ Temp : 追加するシングルトン
        // @ Ret  : 追加されたインスタンス
        template <SingletonTypeConcept SingletonType>
        SingletonType* AddSingleton(void);
        // シングルトンを削除する
        // @ Temp : 削除するシングルトン
        template <SingletonTypeConcept SingletonType>
        void DeleteSingleton(void);
        // シングルトンを取得する
        // @ Temp : 取得するシングルトン
        // @ Ret  : インスタンス
        template <SingletonTypeConcept SingletonType>
        SingletonType* GetSingleton(void);

    private:
        // コンストラクタ
        CentrallySingleton(void);

        static std::shared_ptr<CentrallySingleton> ms_instance; // 保持インスタンス
        static Mutex ms_mutex;
        std::unordered_map<ullint, std::pair<void*, std::function<void(void*)>>> m_instances;   // 保持しているインスタンス一覧
    };
}




//----- CentrallySingleton 定義
namespace EtherEngine {
    // シングルトンを追加する
    template <SingletonTypeConcept SingletonType>
    SingletonType* CentrallySingleton::AddSingleton(void) {
        auto ret = new SingletonType();
        auto hoge = typeid(SingletonType).hash_code();
        auto instance = std::pair<void*, std::function<void(void*)>>(static_cast<void*>(ret), [](void* instance) { 
            auto deleteInstance = static_cast<SingletonType*>(instance);
            DELETE_NULL(deleteInstance);
        });
        m_instances.emplace(typeid(SingletonType).hash_code(), instance);  // typeid.nameを用いているがクラスで一意に名前を取得できれば良いのでコンパイラ等の差異は無視する
        return ret;
    }
    // シングルトンを削除する
    template <SingletonTypeConcept SingletonType>
    void CentrallySingleton::DeleteSingleton(void) {
        auto find = m_instances.find(typeid(SingletonType).hash_code());
        if (find != m_instances.end()) {
            find->second.second(find->second.first);
            m_instances.erase(find);
        }
    }
    // シングルトンを取得する
    template <SingletonTypeConcept SingletonType>
    SingletonType* CentrallySingleton::GetSingleton(void) {
        auto find = m_instances.find(typeid(SingletonType).hash_code());
        if (find != m_instances.end()) {
            return static_cast<SingletonType*>(find->second.first);
        }
        else {
            return AddSingleton<SingletonType>();
        }
    }
}
#endif // !I_CENTRALLYSINGLETON_H
