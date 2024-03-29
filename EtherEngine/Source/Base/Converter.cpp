#include <Base/Converter.h>


//----- XMMATRIXとXMFLOAT4X4変換
namespace MathConverter {
    // XMMATRIXをXMFLOAT4X4に変換する
    // @ Ret  : 変換されたXMFLOAT4X4
    // @ Arg1 : XMMATRIX
    DirectX::XMFLOAT4X4 MatrixToFloat4x4(const DirectX::XMMATRIX& mat) {
        DirectX::XMFLOAT4X4 ret;
        DirectX::XMStoreFloat4x4(&ret, mat);
        return std::move(ret);
    }
}
