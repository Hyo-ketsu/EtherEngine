#include <Base/CameraBase.h>
#include <Base/MathUtility.h>
#include <Base/BaseDefines.h>
#include <Base/Converter.h>
#include <Base/CameraStorage.h>
#include <Base/EditorException.h>


//----- CameraData定義
namespace EtherEngine {
    // コンストラクタ
    CameraData::CameraData(const IDNumberType& id, const Eigen::Vector3f& pos, const Eigen::Vector3f& look)
        : m_id(id)
        , m_pos(pos)
        , m_look(look)
        , m_up(CameraDefine::UP)
        , m_fovy(CameraDefine::FOVY)
        , m_aspect(CameraDefine::ASPECT)
        , m_near(CameraDefine::NEAR_)
        , m_far(CameraDefine::FAR_) {
        SetPos(pos);
        SetLook(look);
    }
    // Jsonコンストラクタ
    CameraData::CameraData(const std::string& json) {
        this->Input(json);
    }


    // 座標ゲッター
    Eigen::Vector3f CameraData::GetPos(void) const {
        CheckPosLookPosition();
        return m_pos;
    }
    // 座標セッター
    void CameraData::SetPos(const Eigen::Vector3f& in) {
        m_pos = in;
    }
    // 注視点ゲッター
    Eigen::Vector3f CameraData::GetLook(void) const {
        CheckPosLookPosition();
        return m_look;
    }
    // 注視点セッター
    void CameraData::SetLook(const Eigen::Vector3f& in) {
        m_look = in;
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
        // @ MEMO : 一定値以下にすると弊害があるようなら付けます
        // if (m_near < 1.0f) m_near = 1.0f;
        if (m_near > m_far) m_near = m_far;
    }
    // 最長クリップ距離セッター
    void CameraData::SetFar(const float in) {
        m_far = in;
        // @ MEMO : 一定値以上にすると弊害があるようなら付けます
        // if (m_far > 1000.0f) m_far = 1000.0f;
        if (m_far < m_near) m_far = m_near;
    }


    // 外部出力する
    Json CameraData::Output(void) {
        nlohmann::json json;

        json["CameraData"]["id"] = m_pos.x();
        json["CameraData"]["posX"] = m_pos.x();
        json["CameraData"]["posY"] = m_pos.y();
        json["CameraData"]["posZ"] = m_pos.z();
        json["CameraData"]["lookX"] = m_look.x();
        json["CameraData"]["lookY"] = m_look.y();
        json["CameraData"]["lookZ"] = m_look.z();
        json["CameraData"]["upX"] = m_up.x();
        json["CameraData"]["upZ"] = m_up.z();
        json["CameraData"]["upY"] = m_up.y();
        json["CameraData"]["priority"] = m_priority;
        json["CameraData"]["fovy"]     = m_fovy;
        json["CameraData"]["aspect"]   = m_aspect;
        json["CameraData"]["near"]     = m_near;
        json["CameraData"]["far"]      = m_far;

        return json;
    }
    // 外部入力する
    void CameraData::Input(const Json& input) {
        auto& cameraData = input["CameraData"];
        m_id = cameraData["id"];
        m_pos.x() = cameraData["posX"];
        m_pos.y() = cameraData["posY"];
        m_pos.z() = cameraData["posZ"];
        m_look.x() = cameraData["lookX"];
        m_look.y() = cameraData["lookY"];
        m_look.z() = cameraData["lookZ"];
        m_up.x() = cameraData["upX"];
        m_up.z() = cameraData["upZ"];
        m_up.y() = cameraData["upY"];
        m_priority = cameraData["priority"];
        m_fovy     = cameraData["fovy"];
        m_aspect   = cameraData["aspect"];
        m_near     = cameraData["near"];
        m_far      = cameraData["far"];
    }


    // 座標と注視点が同座標の場合に例外を出力します
    void CameraData::CheckPosLookPosition(void) const {
        if (MathUtility::FloatEqual(m_pos.x(), m_look.x()) &&
            MathUtility::FloatEqual(m_pos.y(), m_look.y()) &&
            MathUtility::FloatEqual(m_pos.z(), m_look.z()) 
            ) {
            throw EditorException("Exception! pos and look are the same coordinates.");
        }
    }


    // ビュー行列を取得する
    Eigen::Matrix4f CameraData::GetView(const bool isTranspose) const {
        //----- 変数宣言
        DirectX::XMFLOAT3 pos;
        DirectX::XMFLOAT3 look;
        DirectX::XMFLOAT3 up;
        Eigen::Matrix4f ret;

        //----- 初期化
        MathConverter::EigenToDX(GetPos(), &pos);
        MathConverter::EigenToDX(GetLook(), &look);
        MathConverter::EigenToDX(GetUp(), &up);

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
    Eigen::Matrix4f CameraData::GetProjection(const bool isTranspose) const {
        //----- 変数宣言
        Eigen::Matrix4f ret;

        //----- プロジェクション行列計算
        auto projection = DirectX::XMMatrixPerspectiveFovLH(GetFovy(), GetAspect(), GetNear(), GetFar());

        //----- 転置
        if (isTranspose) projection = DirectX::XMMatrixTranspose(projection);

        //----- 変換
        MathConverter::DXToEigen(projection, &ret);

        //----- 返却
        return ret;
    }
}


//----- CameraBase定義
namespace EtherEngine {
    // コンストラクタ
    CameraBase::CameraBase(const Eigen::Vector3f& pos, const Eigen::Vector3f& look, const bool isRegister, const int priority)
        : CameraBase(CameraData(m_id, pos, look), isRegister, priority) {
    }
    // コンストラクタ
    CameraBase::CameraBase(const CameraData& data, const bool isRegister, const int priority)
        : m_cameraData(std::make_shared<CameraData>(data)) {
        if (isRegister) {
            m_id = CameraSystem::Get()->AddData(std::weak_ptr<CameraData>(m_cameraData), priority);
        }
    }
    // デストラクタ
    CameraBase::~CameraBase(void) {
    }


    // ビュー行列を取得する
    Eigen::Matrix4f CameraBase::GetView(const bool isTranspose) const {
        return m_cameraData->GetView();
    }
    // プロジェクション行列を取得する
    Eigen::Matrix4f CameraBase::GetProjection(const bool isTranspose) const {
        return m_cameraData->GetProjection();
    }


    // 外部出力する
    Json CameraBase::Output(void) {
        nlohmann::json json;

        json["CameraBase"] = m_cameraData->Output();

        return json;
    }
    // 入力する
    void CameraBase::Input(const Json& input) {
        m_cameraData->Input(input["CameraBase"]);
    }
}
