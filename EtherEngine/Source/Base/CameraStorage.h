#ifndef I_CAMERASTORAGE_H
#define I_CAMERASTORAGE_H
#include <Base/Singleton.h>
#include <Base/CameraBase.h>
#include <Base/IDClass.h>


//----- CameraSystem 宣言
namespace EtherEngine {
    // カメラを管理するクラス
    class CameraSystem : public Singleton<CameraSystem> {
    public:
        // デストラクタ
        ~CameraSystem(void) {}


        // カメラを追加する
        // @ Ret  : ID
        // @ Arg1 : 追加するカメラ
        // @ Arg2 : 優先順位 (Default : 0)
        [[nodiscard]] IDClass AddData(std::weak_ptr<CameraData> data, int priority = 0);
        // カメラを削除する
        // @ Arg1 : ID
        void DeleteData(const IDClass& id);


        // カメラを取得する
        // @ Ret  : 取得したカメラ情報
        // @ Arg1 : 指定ID
        std::optional<CameraData> GetData(const IDClass& id);
        // メインカメラを取得する
        // @ Ret  : 取得したカメラ情報
        std::optional<CameraData> GetMainData(void);

    private:
        // コンストラクタ
        CameraSystem(void) {}

        friend class Singleton<CameraSystem>;

        std::vector<std::tuple<IDClass, std::weak_ptr<CameraData>, int>> m_datas;   // 保持しているデータ
    };
}


#endif // !I_CAMERASTORAGE_H
