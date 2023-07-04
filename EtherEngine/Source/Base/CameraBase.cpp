#include <Base/CameraBase.h>
#include <Base/BaseDefines.h>
#include <Base/MathUtility.h>
#include <Base/Converter.h>
#include <Base/CameraStorage.h>


//----- CameraData定義
namespace EtherEngine {
    // コンストラクタ
    // @ Arg1 : 座標
    // @ Arg2 : 注視点
    CameraData::CameraData(const Eigen::Vector3f& pos, const Eigen::Vector3f& look) 
        : m_pos(pos)
        , m_look(look)
        , m_up(CameraDefine::UP)
        , m_fovy(CameraDefine::FOVY)
        , m_aspect(CameraDefine::ASPECT)
        , m_near(CameraDefine::NEAR_)
        , m_far(CameraDefine::FAR_) {
        SetPos(pos);
        SetLook(look);
    }


    // 座標セッター
    void CameraData::SetPos(const Eigen::Vector3f& in) {
        m_pos = in;
        CheckPosLookPosition();
    }
    // 注視点セッター
    void CameraData::SetLook(const Eigen::Vector3f& in) {
        m_look = in;
        CheckPosLookPosition();
    }
    // 視野角セッター
    void CameraData::SetFovy(const float in) {
        m_fovy = fabsf(in);
        if (MathUtility::FloatEqual(m_fovy)) m_fovy = DirectX::XMConvertToRadians(1);
    }
    // 画面アスペクト比率セッター
    void CameraData::SetAspect(const float in) {
        m_aspect = fabsf(in);
        if (MathUtility::FloatEqual(m_aspect)) m_aspect = DirectX::XMConvertToRadians(1);
    }
    // 最短クリップ距離セッター
    void CameraData::SetNear(const float in) {
        m_near = in;
        // 一定値以下にすると弊害があるようなら付けます
        // if (m_near < 1.0f) m_near = 1.0f;
        if (m_near > m_far) m_near = m_far;
    }
    // 最長クリップ距離セッター
    void CameraData::SetFar(const float in) {
        m_far = in;
        // 一定値以上にすると弊害があるようなら付けます
        // if (m_far > 1000.0f) m_far = 1000.0f;
        if (m_far < m_near) m_far = m_near;
    }


    // 座標と注視点が同座標の場合に例外を出力します
    void CameraData::CheckPosLookPosition(void) const {
        if (MathUtility::FloatEqual(m_pos.x(), m_look.x()) &&
            MathUtility::FloatEqual(m_pos.y(), m_look.y()) &&
            MathUtility::FloatEqual(m_pos.z(), m_look.z()) 
            ) {
            throw std::exception("Exception! pos and look are the same coordinates.");
        }
    }
}


//----- CameraBase定義
namespace EtherEngine {
    // コンストラクタ
    CameraBase::CameraBase(const Eigen::Vector3f& pos, const Eigen::Vector3f& look)
        : CameraBase(CameraData(pos,look)) {
    }
    // コンストラクタ
    CameraBase::CameraBase(const CameraData& data) 
        : m_cameraData(data)
        , m_id(CameraStorage::Get()->AddData(*this)) {
    }
    // デストラクタ
    CameraBase::~CameraBase(void) {
    }


    // ビュー行列を取得する
    Eigen::Matrix4f CameraBase::GetView(const bool isTranspose) const {
        //----- 変数宣言
        DirectX::XMFLOAT3 pos;
        DirectX::XMFLOAT3 look;
        DirectX::XMFLOAT3 up;
        Eigen::Matrix4f ret;

        //----- 初期化
        MathConverter::EigenToDX(m_cameraData.GetPos(), &pos);
        MathConverter::EigenToDX(m_cameraData.GetLook(), &look);
        MathConverter::EigenToDX(m_cameraData.GetUp(), &up);

        //----- ビュー行列計算
        auto view = DirectX::XMMatrixLookAtLH(
            DirectX::XMLoadFloat3(&pos), DirectX::XMLoadFloat3(&look), DirectX::XMLoadFloat3(&up)
        );

        //----- 転置
        if (isTranspose) view = DirectX::XMMatrixTranspose(view);
        
        //----- 変換
        MathConverter::DXToEigen(view, &ret);

        //----- 返却
        return ret;
    }
    // プロジェクション行列を取得する
    Eigen::Matrix4f CameraBase::GetProjection(const bool isTranspose) const {
        //----- 変数宣言
        Eigen::Matrix4f ret;

        //----- プロジェクション行列計算
        auto projection = DirectX::XMMatrixPerspectiveFovLH(m_cameraData.GetFovy(), m_cameraData.GetAspect(), m_cameraData.GetNear(), m_cameraData.GetFar());

        //----- 転置
        if (isTranspose) projection = DirectX::XMMatrixTranspose(projection);

        //----- 変換
        MathConverter::DXToEigen(projection, &ret);

        //----- 返却
        return ret;
    }
}
