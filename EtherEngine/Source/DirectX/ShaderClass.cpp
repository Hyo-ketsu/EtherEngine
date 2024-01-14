#include <DirectX/ShaderClass.h>


//----- ShaderBase定義
namespace EtherEngine {
    // コンストラクタ
    ShaderBase::ShaderBase(const Handle<DirectXRender>& directxRender, ShaderType shaderType, const std::string& loadFile)
        : m_directxRender(directxRender.GetHandle())
        , m_shaderType(shaderType) {
        if (loadFile != "") {
            this->LoadFile(loadFile.c_str());
        }
    }
    // デストラクタ
    ShaderBase::~ShaderBase(void) {

    }
    // コピーコンストラクタ
    ShaderBase::ShaderBase(const ShaderBase& copy) 
        : m_directxRender(copy.m_directxRender.GetHandle())
        , m_shaderType(copy.m_shaderType) {
        m_buffers.resize(copy.m_buffers.size());
        std::copy(copy.m_buffers.begin(), copy.m_buffers.end(), m_buffers.begin());
    }
    // コピー代入
    ShaderBase& ShaderBase::operator =(const ShaderBase& copy) {
        m_directxRender = copy.m_directxRender.GetHandle();
        m_shaderType = copy.m_shaderType;
        m_buffers.resize(copy.m_buffers.size());
        std::copy(copy.m_buffers.begin(), copy.m_buffers.end(), m_buffers.begin());
        
        return *this;
    }


    // シェーダファイル(.cso)読み込み処理
    // @ Ret  : 読み込みに成功したか
    // @ Arg1 : 読み込みたいcsoファイル名
    HRESULT ShaderBase::LoadFile(const char* fileName) {
        //----- 変数宣言
        HRESULT hr = E_FAIL;    // 成功したか

        //----- ファイルを読み込む
        FILE* file;
        fopen_s(&file, fileName, "rb");
        if (!file) return hr;

        //----- ファイルのサイズを取得する
        int fileSize = 0;
        fseek(file, 0, SEEK_END);
        fileSize = ftell(file);

        //------ メモリに読み込む
        fseek(file, 0, SEEK_SET);
        char* data = new char[fileSize];
        fread(data, fileSize, 1, file);
        fclose(file);

        //----- シェーダ作成
        hr = Make(data, fileSize);

        //----- 終了処理
        delete[] data;
        return hr;
    }
    // 文字列からシェーダをコンパイルする処理
    HRESULT ShaderBase::LoadCompile(const char* code) {
        //----- ターゲット指定
        const char* target = nullptr;
        switch (m_shaderType) {
        case EtherEngine::ShaderType::Vertex:
            target = "vs_5_0";
            break;
        case EtherEngine::ShaderType::Pixel:
            target = "ps_5_0";
            break;
        }

        //----- 変数宣言
        HRESULT hr; // 成功したか
        ID3DBlob* blob;
        ID3DBlob* error;
        uint compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
        hr = D3DCompile(code, strlen(code), nullptr, nullptr, nullptr,
            "main", target, compileFlag, 0, &blob, &error);
        if (FAILED(hr)) return hr;

        //----- シェーダ作成
        hr = Make(blob->GetBufferPointer(), (uint)blob->GetBufferSize());
        delete blob;
        delete error;

        return hr;
    }


    // 定数の書き込みを行う
    // @ Arg1 : 書き込むシェーダのスロット
    // @ Arg2 : 書き込むデータ
    void ShaderBase::WriteBuffer(uint slot, void* data) {
        if (slot < m_buffers.size() && m_directxRender.IsEnable()) {
            m_directxRender.GetAtomicData().GetContext()->UpdateSubresource(m_buffers[slot], 0, nullptr, data, 0, 0);
        }
    }
    // テクスチャーの設定を行う
    // @ Arg1 : 書き込むシェーダのスロット
    // @ Arg2 : 書き込むテクスチャー情報
    void ShaderBase::SetTexture(uint slot, Texture* texture) {
        //----- 引数がnullptrではないか
        if (texture == nullptr) return;

        //----- シェーダーリソース取得
        ID3D11ShaderResourceView* shaderResourceView = texture->GetResource();

        //----- シェーダーにテクスチャーをセットする
        switch (m_shaderType) {
        case ShaderType::Vertex:
            m_directxRender.GetData().GetContext()->VSSetShaderResources(slot, 1, &shaderResourceView);
            break;
        case ShaderType::Pixel:
            m_directxRender.GetAtomicData().GetContext()->PSSetShaderResources(slot, 1, &shaderResourceView);
            break;
        }
    }


    // 入力された文字列からシェーダーをコンパイルする
    const HRESULT ShaderBase::Compile(const char* code) {
        const char* target = nullptr;
        switch (m_shaderType) {
        case EtherEngine::ShaderType::Vertex:
            target = "vs_5_0";
            break;
        case EtherEngine::ShaderType::Pixel:
            target = "ps_5_0";
            break;
        }

        HRESULT hr;
        ID3DBlob* blob;
        ID3DBlob* error;
        UINT compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
        hr = D3DCompile(code, strlen(code), nullptr, nullptr, nullptr,
            "main", target, compileFlag, 0, &blob, &error);
        if (FAILED(hr)) { return hr; }

        //----- シェーダ作成
        hr = Make(blob->GetBufferPointer(), (UINT)blob->GetBufferSize());
        if (blob != nullptr) blob->Release();
        if (error != nullptr) error->Release();
        return hr;
    }


    //
    HRESULT ShaderBase::Make(void* data, uint size) {
        //----- 変数宣言
        HRESULT hr;

        //----- 解析用のリフレクション作成
        ID3D11ShaderReflection* reflection;
        hr = D3DReflect(data, size, IID_PPV_ARGS(&reflection));
        if (FAILED(hr)) { return hr; }

        //----- 定数バッファ作成
        D3D11_SHADER_DESC shaderDesc;
        reflection->GetDesc(&shaderDesc);
        m_buffers.resize(shaderDesc.ConstantBuffers, nullptr);
        for (uint i = 0; i < shaderDesc.ConstantBuffers; i++) {
            //----- シェーダーの定数バッファの情報を取得
            D3D11_SHADER_BUFFER_DESC shaderBufDesc;
            ID3D11ShaderReflectionConstantBuffer* cbuf = reflection->GetConstantBufferByIndex(i);
            cbuf->GetDesc(&shaderBufDesc);

            // 作成するバッファの情報
            D3D11_BUFFER_DESC bufDesc = {};
            bufDesc.ByteWidth = shaderBufDesc.Size;
            bufDesc.Usage = D3D11_USAGE_DEFAULT;
            bufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

            // バッファの作成
            hr = m_directxRender.GetAtomicData().GetDevice()->CreateBuffer(&bufDesc, nullptr, &m_buffers[i]);
            if (FAILED(hr)) { return hr; }
        }

        //----- 返却
        return MakeShader(data, size);
    }
}


//----- VertexShader定義
namespace EtherEngine {
    // コンストラクタ
    VertexShader::VertexShader(const Handle<DirectXRender>& directxRender, const std::string& loadFile)
        : ShaderBase(directxRender, ShaderType::Vertex, loadFile) {
    }
    // デストラクタ
    VertexShader::~VertexShader(void) {
    }


    // シェーダを使用する
    void VertexShader::Bind(void) {
        auto dxRender = m_directxRender.GetAtomicItem();
        dxRender.GetData().GetContext()->VSSetShader(m_vertexShader, nullptr, 0);
        dxRender.GetData().GetContext()->IASetInputLayout(m_inputLayout);
        for (int i = 0; i < m_buffers.size(); i++) {
            dxRender.GetData().GetContext()->VSSetConstantBuffers(i, 1, &m_buffers[i]);
        }
    }


    HRESULT VertexShader::MakeShader(void* data, uint size) {
        //----- 変数宣言
        HRESULT hr;
        auto dxRender = m_directxRender.GetAtomicItem();

        //----- シェーダー作成
        hr = dxRender.GetData().GetDevice()->CreateVertexShader(data, size, nullptr, &m_vertexShader);
        if (FAILED(hr)) { return hr; }

        ID3D11ShaderReflection* reflection;
        D3D11_SHADER_DESC shaderDesc;
        D3D11_INPUT_ELEMENT_DESC* inputDesc;
        D3D11_SIGNATURE_PARAMETER_DESC sigDesc;

        DXGI_FORMAT formats[][4] = { {
                DXGI_FORMAT_R32_UINT,
                DXGI_FORMAT_R32G32_UINT,
                DXGI_FORMAT_R32G32B32_UINT,
                DXGI_FORMAT_R32G32B32A32_UINT,
            }, {
                DXGI_FORMAT_R32_SINT,
                DXGI_FORMAT_R32G32_SINT,
                DXGI_FORMAT_R32G32B32_SINT,
                DXGI_FORMAT_R32G32B32A32_SINT,
            }, {
                DXGI_FORMAT_R32_FLOAT,
                DXGI_FORMAT_R32G32_FLOAT,
                DXGI_FORMAT_R32G32B32_FLOAT,
                DXGI_FORMAT_R32G32B32A32_FLOAT,
            },
        };

        hr = D3DReflect(data, size, IID_PPV_ARGS(&reflection));
        if (FAILED(hr)) { return hr; }

        reflection->GetDesc(&shaderDesc);
        inputDesc = new D3D11_INPUT_ELEMENT_DESC[shaderDesc.InputParameters];
        for (UINT i = 0; i < shaderDesc.InputParameters; i++) {
            reflection->GetInputParameterDesc(i, &sigDesc);
            inputDesc[i].SemanticName = sigDesc.SemanticName;
            inputDesc[i].SemanticIndex = sigDesc.SemanticIndex;

            // http://marupeke296.com/TIPS_No17_Bit.html
            BYTE elementCount = sigDesc.Mask;
            elementCount = (elementCount & 0x05) + ((elementCount >> 1) & 0x05);
            elementCount = (elementCount & 0x03) + ((elementCount >> 2) & 0x03);

            switch (sigDesc.ComponentType) {
            case D3D_REGISTER_COMPONENT_UINT32:
                inputDesc[i].Format = formats[0][elementCount - 1];
                break;
            case D3D_REGISTER_COMPONENT_SINT32:
                inputDesc[i].Format = formats[1][elementCount - 1];
                break;
            case D3D_REGISTER_COMPONENT_FLOAT32:
                inputDesc[i].Format = formats[2][elementCount - 1];
                break;
            }
            inputDesc[i].InputSlot = 0;
            inputDesc[i].AlignedByteOffset = i == 0 ? 0 : D3D11_APPEND_ALIGNED_ELEMENT;
            inputDesc[i].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
            inputDesc[i].InstanceDataStepRate = 0;
        }

        hr = dxRender.GetData().GetDevice()->CreateInputLayout(
            inputDesc, shaderDesc.InputParameters,
            data, size, &m_inputLayout
        );

        delete[] inputDesc;
        return hr;
    }
}


//----- PixelShader定義
namespace EtherEngine {
    // コンストラクタ
    PixelShader::PixelShader(const Handle<DirectXRender>& directxRender, const std::string& loadFile)
        : ShaderBase(directxRender, ShaderType::Pixel, loadFile) {
    }
    // デストラクタ
    PixelShader::~PixelShader(void) {
    }


    // シェーダを使用する
    void PixelShader::Bind(void) {
        auto dxRender = m_directxRender.GetAtomicItem();
        dxRender.GetData().GetContext()->PSSetShader(m_pixelShader, nullptr, 0);
        for (int i = 0; i < m_buffers.size(); i++)
            dxRender.GetData().GetContext()->PSSetConstantBuffers(i, 1, &m_buffers[i]);
    }


    HRESULT PixelShader::MakeShader(void* data, uint size) {
        return m_directxRender.GetAtomicData().GetDevice()->CreatePixelShader(data, size, NULL, &m_pixelShader);
    }
}
