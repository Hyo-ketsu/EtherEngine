#include <Base/Converter.h>


//----- XMMATRIX��XMFLOAT4X4�ϊ�
namespace MathConverter {
    // XMMATRIX��XMFLOAT4X4�ɕϊ�����
    // @ Ret  : �ϊ����ꂽXMFLOAT4X4
    // @ Arg1 : XMMATRIX
    DirectX::XMFLOAT4X4 MatrixToFloat4x4(const DirectX::XMMATRIX& mat) {
        DirectX::XMFLOAT4X4 ret;
        DirectX::XMStoreFloat4x4(&ret, mat);
        return std::move(ret);
    }
}
