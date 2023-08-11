#include <DirectX/Model.h>
#include <Base/BaseDefines.h>


namespace EtherEngine {
    // コンストラクタ
    Model::Model(void) 
        : m_isLoad(false)
        , m_isFlip(false)
        , m_scale(1.0f)
        , m_loadModel("")
        , m_textureSlot(0) {
    }
    // デストラクタ
    Model::~Model(void) {
    }


    // 描画
    bool Model::DrawModel(const Eigen::Matrix4f& world, const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection, PixelShader* pixelShader) {
        //----- 読み込みが行われていなければ例外送出
        if (m_isLoad == false) return false;

        //----- 頂点シェーダー
        Eigen::Matrix4f matrix[3] = { world, view.transpose(), projection.transpose() };

        //----- 描画
        for (auto&& it : m_meshes) {
            if (m_textureSlot >= 0) {
                pixelShader->SetTexture(m_textureSlot, m_materials[it.materialID].texture.get());
            }
            it.mesh->Draw();
        }

        return true;
    }


    // モデルを読み込む
    void Model::Load(const std::string& file, const BaseHandle<DirectXRender>& directX, const float scale, const bool isFlip) {
        //----- assimpの設定
        Assimp::Importer importer;
        int flag = 0;
        flag |= aiProcess_Triangulate;
        flag |= aiProcess_JoinIdenticalVertices;
        flag |= aiProcess_FlipUVs;
        flag |= aiProcess_PreTransformVertices;
        if (isFlip) flag |= aiProcess_MakeLeftHanded;

        //----- assimpで読み込み
        auto scene = importer.ReadFile(file, flag);
        if (!scene) {
            throw std::exception((importer.GetErrorString() + std::string(" Don't Created")).c_str());
        }

        //----- メッシュの作成
        aiVector3D zero(0.0f, 0.0f, 0.0f);
        for (uint i = 0; i < scene->mNumMeshes; i++) {
            //----- 変数宣言
            Mesh mesh = decltype(mesh)();

            //----- 頂点の作成
            mesh.vertexs.resize(scene->mMeshes[i]->mNumVertices);
            for (uint j = 0; j < mesh.vertexs.size(); j++) {
                //----- 値の吸出し
                aiVector3D pos = scene->mMeshes[i]->mVertices[j];
                aiVector3D uv = scene->mMeshes[i]->HasTextureCoords(0) ? scene->mMeshes[i]->mTextureCoords[0][j] : zero;
                aiVector3D normal = scene->mMeshes[i]->HasNormals() ? scene->mMeshes[i]->mNormals[j] : zero;

                //----- 値を設定
                mesh.vertexs[j].pos    = Eigen::Vector3f(pos.x * scale, pos.y * scale, pos.z * scale);
                mesh.vertexs[j].normal = Eigen::Vector3f(normal.x, normal.y, normal.z);
                mesh.vertexs[j].uv     = Eigen::Vector2f(uv.x, uv.y);
            }

            //----- インデックスの作成
            mesh.indexs.resize(scene->mMeshes[i]->mNumFaces * 3); // faceはポリゴンの数を表す(1ポリゴンで3インデックス
            for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++) {
                aiFace face = scene->mMeshes[i]->mFaces[j];
                int idx = j * 3;
                mesh.indexs[idx + 0] = face.mIndices[0];
                mesh.indexs[idx + 1] = face.mIndices[1];
                mesh.indexs[idx + 2] = face.mIndices[2];
            }

            //----- マテリアルの割り当て
            mesh.materialID = scene->mMeshes[i]->mMaterialIndex;

            //----- メッシュを元に頂点バッファ作成
            MeshBuffer::Description desc = decltype(desc)(
                directX,
                mesh.vertexs.data(),
                sizeof(Vertex),
                static_cast<uint>(mesh.vertexs.size()),
                false,
                mesh.indexs.data(),
                sizeof(uint),
                static_cast<uint>(mesh.indexs.size()),
                D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
                );
            mesh.mesh = std::make_shared<MeshBuffer>(desc);

            // メッシュ追加
            m_meshes.push_back(mesh);
        }

        //----- マテリアルの作成
        // ファイルの探索
        std::string dir = file;
        dir = dir.substr(0, dir.find_last_of('/') + 1);
        //----- マテリアル
        aiColor3D color(0.0f, 0.0f, 0.0f);
        Eigen::Vector4f diffuse(1.0f, 1.0f, 1.0f, 1.0f);
        Eigen::Vector4f ambient(0.3f, 0.3f, 0.3f, 1.0f);
        for (uint i = 0; i < scene->mNumMaterials; i++) {
            Material material = decltype(material)();

            //----- 各種パラメーター
            float shininess;
            material.diffuse = scene->mMaterials[i]->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS ?
                Eigen::Vector4f(color.r, color.g, color.b, 1.0f) : diffuse;
            material.ambient = scene->mMaterials[i]->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS ?
                Eigen::Vector4f(color.r, color.g, color.b, 1.0f) : ambient;
            shininess = scene->mMaterials[i]->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS ? shininess : 0.0f;
            material.specular = scene->mMaterials[i]->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS ?
                Eigen::Vector4f(color.r, color.g, color.b, shininess) : Eigen::Vector4f(0.0f, 0.0f, 0.0f, shininess);

            //----- テクスチャ
            HRESULT hr;
            aiString path;
            if (scene->mMaterials[i]->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS) {
                //----- そのまま探索
                material.texture = std::make_unique<Texture>();
                hr = material.texture->Create(directX, std::string(path.C_Str()));
                //----- モデルと同じ階層を探索
                if (FAILED(hr)) {
                    std::string file = dir;
                    file += path.C_Str();
                    hr = material.texture->Create(directX, file.c_str());
                }
                //----- ファイル名のみで探索
                if (FAILED(hr)) {
                    std::string file = path.C_Str();
                    size_t idx = file.find_last_of('\\');
                    if (idx != std::string::npos) {
                        file = file.substr(idx + 1);
                        file = dir + file;
                        hr = material.texture->Create(directX, file.c_str());
                    }
                }
                //----- 失敗していたら例外を吐く
                if (FAILED(hr)) {
                    throw std::exception((std::string(path.C_Str()) + "No Texture").c_str());
                }
            }
            else {
                material.texture = nullptr;
            }

            //----- マテリアル追加
            m_materials.push_back(std::move(material));
        }

        //----- 読込ステータス保持
        m_isFlip = isFlip;
        m_scale = scale;
        m_loadModel = file;

        //----- 読込フラグを立てる
        m_isLoad = true;
    }


    // 外部出力
    std::string Model::Output(void) {
        nlohmann::json json;

        json["Model"]["LoadFile"] = m_loadModel;
        json["Model"]["Filp"] = m_isFlip;
        json["Model"]["Scale"] = m_scale;

        return json.dump(FileDefine::JSON_DUMP_NUMBER_OF_STAGES);
    }
    // 外部入力
    void Model::Input(const std::string& input) {
        nlohmann::json json = nlohmann::json::parse(input);

        m_loadModel = json["Model"]["LoadFile"];
        m_isFlip = json["Model"]["Filp"];
        m_scale = json["Model"]["Scale"];
    }
}
