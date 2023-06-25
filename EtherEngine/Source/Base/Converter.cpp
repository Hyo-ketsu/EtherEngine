#include <Base/Converter.h>


//----- XMMATRIX‚ÆXMFLOAT4X4•ÏŠ·
namespace MathConverter {
    // XMMATRIX‚ðXMFLOAT4X4‚É•ÏŠ·‚·‚é
    // @ Ret  : •ÏŠ·‚³‚ê‚½XMFLOAT4X4
    // @ Arg1 : XMMATRIX
    DirectX::XMFLOAT4X4 MatrixToFloat4x4(const DirectX::XMMATRIX& mat) {
        DirectX::XMFLOAT4X4 ret;
        DirectX::XMStoreFloat4x4(&ret, mat);
        return std::move(ret);
    }
}
