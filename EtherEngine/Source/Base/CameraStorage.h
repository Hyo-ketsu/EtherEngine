#ifndef I_CAMERASTORAGE_H
#define I_CAMERASTORAGE_H
#include <Base/Singleton.h>
#include <Base/CameraBase.h>
#include <Base/IDClass.h>


//----- CameraStorage宣言
namespace EtherEngine {
    // カメラを保持しておくクラス
    class CameraStorage : public Singleton<CameraStorage> {
    public:
        // デストラクタ
        ~CameraStorage(void) {}


        // カメラを追加する
        // @ Arg1 : 追加するカメラ
        // @ Arg2 : ID
        void AddCamera(CameraBase& camera, const IDClass& id);
        // カメラを削除する
        // @ Arg1 : ID
        void DeleteCamera(const IDClass& id);


        // 指定したIDのカメラが存在するか
        // @ Arg1 : 指定ID
        bool IsIDToCamera(const IDClass& id);


        // カメラを取得する
        // @ MEMO : ポインタを返すのくそなんで改修予定
        // @ Ret  : カメラへのポインタ(なければnullptr)
        // @ Arg1 : 優先度の順位(Default : 0)
        [[deprecated]]
        CameraBase* const GetCamera(const uint priority = 0);
        // カメラを取得する
        // @ Arg1 : 指定ID
        CameraBase* const GetCamera(const IDClass& id);


    private:
        // コンストラクタ
        CameraStorage(void) {}

        friend class Singleton<CameraStorage>;

        std::vector<std::tuple<IDClass, CameraBase*, bool>> m_cameras;   // 保持しているカメラ
    };
}


#endif // !I_CAMERASTORAGE_H
