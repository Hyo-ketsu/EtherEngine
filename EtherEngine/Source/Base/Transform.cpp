#include <Base/Transform.h>
#include <Base/MathUtility.h>
#include <Base/BaseDefines.h>
#include <Base/Converter.h>


namespace EtherEngine {
    // コンストラクタ
    // @ Arg1 : 座標(デフォルト：全て0)
    // @ Arg2 : 拡縮(デフォルト：全て0)
    // @ Arg3 : 回転(デフォルト：全て1)
    Transform::Transform(Eigen::Vector3f pos, Eigen::Vector3f sca, Eigen::Vector3f rot)
        : m_postion(pos)
        , m_scale(sca)
        , m_rotation(rot) {
    }


    // ワールド行列を作成する
    Eigen::Matrix4f Transform::CreateWorld(void) const {
        auto toRad = [](float in) {return DirectX::XMConvertToRadians(in); };    // ショートカットラムダ
        Eigen::Matrix4f ret{};
        auto mat =
            DirectX::XMMatrixScaling(m_scale.x(), m_scale.y(), m_scale.z()) *
            DirectX::XMMatrixRotationX(toRad(m_rotation.x())) *
            DirectX::XMMatrixRotationY(toRad(m_rotation.y())) *
            DirectX::XMMatrixRotationZ(toRad(m_rotation.z())) *
            DirectX::XMMatrixTranslation(m_postion.x(), m_postion.y(), m_postion.z());

        MathConverter::DXToEigen(mat, &ret);
        return ret;
    }


    // 加算
    Transform Transform::operator+(const Transform& transform) {
        Transform ret = *this;
        ret.m_postion += transform.m_postion;
        ret.m_rotation += transform.m_rotation;
        ret.m_scale += transform.m_scale;
        return ret;
    }
    // 減算
    Transform Transform::operator-(const Transform& transform) {
        Transform ret = *this;
        ret.m_postion -= transform.m_postion;
        ret.m_rotation -= transform.m_rotation;
        ret.m_scale -= transform.m_scale;
        return ret;
    }
    // 代入
    Transform& Transform::operator=(const Transform& transform) {
        m_postion = transform.m_postion;
        m_rotation = transform.m_rotation;
        m_scale = transform.m_scale;
        return *this;
    }
    // 加算代入
    Transform& Transform::operator+=(const Transform& transform) {
        m_postion += transform.m_postion;
        m_rotation += transform.m_rotation;
        m_scale += transform.m_scale;
        return *this;
    }
    // 減算代入
    Transform& Transform::operator-=(const Transform& transform) {
        m_postion -= transform.m_postion;
        m_rotation -= transform.m_rotation;
        m_scale -= transform.m_scale;
        return *this;
    }


    // 外部出力
    Json Transform::Output(void) {
        nlohmann::json json;

        json["Transform"]["px"] = m_postion.x(); 
        json["Transform"]["py"] = m_postion.y(); 
        json["Transform"]["pz"] = m_postion.z(); 
        json["Transform"]["sx"] = m_scale.x(); 
        json["Transform"]["sy"] = m_scale.y(); 
        json["Transform"]["sz"] = m_scale.z(); 
        json["Transform"]["rx"] = m_rotation.x(); 
        json["Transform"]["ry"] = m_rotation.y(); 
        json["Transform"]["rz"] = m_rotation.z(); 

        return json;
    }
    // 外部入力
    void Transform::Input(const Json& input) {
        auto& transform = input["Transform"];
        m_postion.x() = transform["px"];
        m_postion.y() = transform["py"];
        m_postion.z() = transform["pz"];
        m_scale.x() = transform["sx"];
        m_scale.y() = transform["sy"];
        m_scale.z() = transform["sz"];
        m_rotation.x() = transform["rx"];
        m_rotation.y() = transform["ry"];
        m_rotation.z() = transform["rz"];
    }
}
