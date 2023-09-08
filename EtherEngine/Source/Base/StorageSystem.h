#ifndef I_STORAGESYSTEM_H
#define I_STORAGESYSTEM_H
#include <Base/Singleton.h>
#include <Base/IDClass.h>


//----- その他宣言
namespace EtherEngine {
    // StorageSystemのコンセプト
    template <typename T>
    concept StorageSystemConcept = std::is_class_v<T>;
}


//----- StorageID 宣言
namespace EtherEngine {
    // StorageSystemで使用するID
    template <StorageSystemConcept DataType>
    class StorageID {
    public:
        // コンストラクタ
        // @ Arg1 : ID
        StorageID(std::weak_ptr<IDClass> id = nullptr);
        // デストラクタ
        ~StorageID(void);


        // 有効な shared_ptr をさしているか
        bool GetEnable(void) const;
        // 有効な shared_ptr をさしているか
        operator bool(void) const;
        // IDの取得
        IDClass GetId(void) const;
        // IDの取得
        operator IDClass(void) const;

    private:
        std::weak_ptr<IDClass> m_id;        // 保持しているID
    };
}


//----- StorageSystem 宣言
namespace EtherEngine {
    // IDでポインタを管理するクラス
    template <StorageSystemConcept DataType>
    class StorageSystem : public Singleton<StorageSystem<DataType>> {
    public:
        // デストラクタ
        ~StorageSystem(void) {}


        // データを追加する
        // @ Ret  : ID
        // @ Arg1 : 追加するデータ(参照)
        [[nodiscard]] StorageID<DataType> AddData(DataType& data);
        // データを削除する
        // @ Arg1 : ID
        void DeleteData(const StorageID<DataType>& id);


        // 指定したIDのデータが存在するか
        // @ Arg1 : 指定ID
        bool IsIDToData(const IDClass& id);


        // データを取得する
        // @ Arg1 : 指定ID
        DataType* const GetData(const IDClass& id);

    private:
        // コンストラクタ
        StorageSystem(void) {}

        friend class Singleton<StorageSystem<DataType>>;

        std::vector<std::tuple<std::shared_ptr<IDClass>, DataType*>> m_datas;   // 保持しているデータ
    };
}




//----- StorageID 定義
namespace EtherEngine {
    // コンストラクタ
    template <StorageSystemConcept DataType>
    StorageID<DataType>::StorageID(std::weak_ptr<IDClass> id)
        : m_id(id) {
    }
    template <StorageSystemConcept DataType>
    // デストラクタ
    StorageID<DataType>::~StorageID(void) {
        if (m_id.expired() == false) {
            StorageSystem<DataType>::Get()->DeleteData(*this);
        }
    }


    // 有効な shared_ptr をさしているか
    template <StorageSystemConcept DataType>
    bool StorageID<DataType>::GetEnable(void) const {
        return !(m_id.expired());   // expiredは「寿命が切れてたら true」なので反転
    }
    // 有効な shared_ptr をさしているか
    template <StorageSystemConcept DataType>
    StorageID<DataType>::operator bool(void) const {
        return GetEnable();
    }
    // IDの取得
    template <StorageSystemConcept DataType>
    IDClass StorageID<DataType>::GetId(void) const {
        return *m_id.lock();
    }
    // IDの取得
    template <StorageSystemConcept DataType>
    StorageID<DataType>::operator IDClass(void) const {
        return GetId();
    }
}




//----- StorageSystem 定義
namespace EtherEngine {
    // データを追加する
    // @ Ret  : ID
    // @ Arg1 : 追加するデータ(参照)
    template <StorageSystemConcept DataType>
    [[nodiscard]] StorageID<DataType> StorageSystem<DataType>::AddData(DataType& data) {
        //----- IDの作成と追加
        auto ptr = std::make_shared<IDClass>(IDClass());
        m_datas.emplace_back(std::move(ptr), &data);

        //----- 返却
        return StorageID<DataType>(std::weak_ptr<IDClass>(std::get<0>(m_datas.back())));
    }
    // データを削除する
    // @ Arg1 : ID
    template <StorageSystemConcept DataType>
    void StorageSystem<DataType>::DeleteData(const StorageID<DataType>& id) {
        if (m_datas.size() == 0) return;
        for (auto it = m_datas.begin(); it != m_datas.end(); it++) {
            if (*std::get<0>(*it) == id.GetId()) {
                //----- 削除
                m_datas.erase(it);
                break;
            }
        }
    }


    // 指定したIDのデータが存在するか
    // @ Arg1 : 指定ID
    template <StorageSystemConcept DataType>
    bool StorageSystem<DataType>::IsIDToData(const IDClass& id) {
        //----- IDで取得する
        for (auto&& it : m_datas) {
            if (*std::get<0>(it) == id) {
                return true;
            }
        }

        return false;
    }


    // データを取得する
    // @ Arg1 : 指定ID
    template <StorageSystemConcept DataType>
    DataType* const StorageSystem<DataType>::GetData(const IDClass& id) {
        //----- IDで取得する
        for (auto&& it : m_datas) {
            if (*std::get<0>(it) == id) {
                return std::get<1>(it);
            }
        }

        //----- 返却
        return nullptr;
    }
}


#endif // !I_STORAGESYSTEM_H
