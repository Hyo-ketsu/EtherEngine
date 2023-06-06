#ifndef I_SHADERCLASS_H
#define I_SHADERCLASS_H
#include <Base/Handle.h>
#include <DirectX/ComPointer.h>
#include <DirectX/Texture.h>
#include <DirectX/DirectX.h>


//----- ShaderBase宣言
namespace EtherEngine {
    // どの種類のシェーダかの列挙体
    enum class ShaderType {
        Vertex = 0,
        Pixel,
    };


    // シェーダの基本抽象クラス
    class ShaderBase {
    public:
        // デストラクタ
        virtual ~ShaderBase(void);


        // シェーダファイル(.cso)読み込み処理
        // @ Ret  : 読み込みに成功したか
        // @ Arg1 : 読み込みたいcsoファイル名
        HRESULT LoadFile(const char* fileName);
        // 文字列からシェーダをコンパイルする処理
        HRESULT LoadCompile(const char* code);


        // 定数の書き込みを行う
        // @ Arg1 : 書き込むシェーダのスロット
        // @ Arg2 : 書き込むデータ
        void WriteBuffer(uint slot, void* data);
        // テクスチャーの設定を行う
        // @ Arg1 : 書き込むシェーダのスロット
        // @ Arg2 : 書き込むテクスチャー情報
        void SetTexture(uint slot, Texture* texture);
        // シェーダを描画に使用する
        virtual void Bind(void) = 0;

    protected:
        // コンストラクタ
        // @ Arg1 : DirectX
        // @ Arg2 : シェーダの種類
        ShaderBase(const BaseHandle<DirectXRender>& directxRender, ShaderType shaderType);


        // シェーダファイルの読み込み後、シェーダの種類別に処理を行う
        virtual HRESULT MakeShader(void* data, uint size) = 0;


        std::vector<ID3D11Buffer*> m_buffers;   // 保持しているバッファー

    protected:
        //
        HRESULT Make(void* data, uint size);


        BaseHandle<DirectXRender> m_directxRender;  // 保持しているDirectX
        ShaderType m_shaderType;  // このシェーダーの種類
    };
}


//----- VertexShader宣言
namespace EtherEngine {
    // 頂点シェーダ
    class VertexShader : public ShaderBase {
    public:
        // コンストラクタ
        // @ Arg1 : DirectX
        VertexShader(const BaseHandle<DirectXRender>& directxRender);
        // デストラクタ
        ~VertexShader(void) override;


        // シェーダを使用する
        void Bind(void) override;

    protected:
        HRESULT MakeShader(void* data, uint size) override;

    private:
        ID3D11VertexShader* m_vertexShader; // 保持している頂点シェーダ
        ID3D11InputLayout* m_inputLayout;   //
    };
}


//----- PixelShader宣言
namespace EtherEngine {
    // ピクセルシェーダ
    class PixelShader : public ShaderBase {
    public:
        // コンストラクタ
        // @ Arg1 : DirectX
        PixelShader(const BaseHandle<DirectXRender>& directxRender);
        // デストラクタ
        ~PixelShader(void) override;


        // シェーダを使用する
        void Bind(void) override;

    protected:
        HRESULT MakeShader(void* data, uint size);

    private:
        ID3D11PixelShader* m_pixelShader;   // 保持しているピクセルシェーダ
    };
}


#endif // !I_SHADERCLASS_H
