#include <DirectX/Model.h>


namespace EtherEngine {
    // �R���X�g���N�^
    Model::Model(const std::string& file, const BaseHandle<DirectXRender>& directX, VertexShader* const vertexShader, PixelShader* const pixelShader,
        const float scale, const bool isFlip) 
        : m_textureSlot(0) 
        , m_vertexShader(vertexShader)
        , m_pixelShader(pixelShader){
        //----- ���f���ǂݍ���
        Load(file, directX, scale, isFlip);
    }
    // �f�X�g���N�^
    Model::~Model(void) {
    }


    // �`��
    void Model::DrawModel(const Eigen::Matrix4f& world, const Eigen::Matrix4f& view, const Eigen::Matrix4f& projection) {
        //----- ���_�V�F�[�_�[
        Eigen::Matrix4f matrix[3] = { world, view.transpose(), projection.transpose() };
        m_vertexShader->WriteBuffer(0, &matrix);
        m_vertexShader->Bind();

        //----- �s�N�Z���V�F�[�_�[
        m_pixelShader->Bind();

        //----- �`��
        for (auto&& it : m_meshes) {
            if (m_textureSlot >= 0) {
                m_pixelShader->SetTexture(m_textureSlot, m_materials[it.materialID].texture.get());
            }
            it.mesh->Draw();
        }
    }


    // ���f����ǂݍ���
    void Model::Load(const std::string& file, const BaseHandle<DirectXRender>& directX, const float scale, const bool isFlip) {
        //----- assimp�̐ݒ�
        Assimp::Importer importer;
        int flag = 0;
        flag |= aiProcess_Triangulate;
        flag |= aiProcess_JoinIdenticalVertices;
        flag |= aiProcess_FlipUVs;
        flag |= aiProcess_PreTransformVertices;
        if (isFlip) flag |= aiProcess_MakeLeftHanded;

        //----- assimp�œǂݍ���
        auto scene = importer.ReadFile(file, flag);
        if (!scene) {
            throw std::exception((importer.GetErrorString() + std::string(" Don't Created")).c_str());
        }

        //----- ���b�V���̍쐬
        aiVector3D zero(0.0f, 0.0f, 0.0f);
        for (uint i = 0; i < scene->mNumMeshes; i++) {
            //----- �ϐ��錾
            Mesh mesh = decltype(mesh)();

            //----- ���_�̍쐬
            mesh.vertexs.resize(scene->mMeshes[i]->mNumVertices);
            for (uint j = 0; j < mesh.vertexs.size(); j++) {
                //----- �l�̋z�o��
                aiVector3D pos = scene->mMeshes[i]->mVertices[j];
                aiVector3D uv = scene->mMeshes[i]->HasTextureCoords(0) ? scene->mMeshes[i]->mTextureCoords[0][j] : zero;
                aiVector3D normal = scene->mMeshes[i]->HasNormals() ? scene->mMeshes[i]->mNormals[j] : zero;

                //----- �l��ݒ�
                mesh.vertexs[j].pos    = Eigen::Vector3f(pos.x * scale, pos.y * scale, pos.z * scale);
                mesh.vertexs[j].normal = Eigen::Vector3f(normal.x, normal.y, normal.z);
                mesh.vertexs[j].uv     = Eigen::Vector2f(uv.x, uv.y);
            }

            //----- �C���f�b�N�X�̍쐬
            mesh.indexs.resize(scene->mMeshes[i]->mNumFaces * 3); // face�̓|���S���̐���\��(1�|���S����3�C���f�b�N�X
            for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; j++) {
                aiFace face = scene->mMeshes[i]->mFaces[j];
                int idx = j * 3;
                mesh.indexs[idx + 0] = face.mIndices[0];
                mesh.indexs[idx + 1] = face.mIndices[1];
                mesh.indexs[idx + 2] = face.mIndices[2];
            }

            //----- �}�e���A���̊��蓖��
            mesh.materialID = scene->mMeshes[i]->mMaterialIndex;

            //----- ���b�V�������ɒ��_�o�b�t�@�쐬
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

            // ���b�V���ǉ�
            m_meshes.push_back(mesh);
        }

        //----- �}�e���A���̍쐬
        // �t�@�C���̒T��
        std::string dir = file;
        dir = dir.substr(0, dir.find_last_of('/') + 1);
        //----- �}�e���A��
        aiColor3D color(0.0f, 0.0f, 0.0f);
        Eigen::Vector4f diffuse(1.0f, 1.0f, 1.0f, 1.0f);
        Eigen::Vector4f ambient(0.3f, 0.3f, 0.3f, 1.0f);
        for (uint i = 0; i < scene->mNumMaterials; i++) {
            Material material = decltype(material)();

            //----- �e��p�����[�^�[
            float shininess;
            material.diffuse = scene->mMaterials[i]->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS ?
                Eigen::Vector4f(color.r, color.g, color.b, 1.0f) : diffuse;
            material.ambient = scene->mMaterials[i]->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS ?
                Eigen::Vector4f(color.r, color.g, color.b, 1.0f) : ambient;
            shininess = scene->mMaterials[i]->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS ? shininess : 0.0f;
            material.specular = scene->mMaterials[i]->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS ?
                Eigen::Vector4f(color.r, color.g, color.b, shininess) : Eigen::Vector4f(0.0f, 0.0f, 0.0f, shininess);

            //----- �e�N�X�`��
            HRESULT hr;
            aiString path;
            if (scene->mMaterials[i]->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS) {
                //----- ���̂܂ܒT��
                material.texture = std::make_unique<Texture>();
                hr = material.texture->Create(directX, std::string(path.C_Str()));
                //----- ���f���Ɠ����K�w��T��
                if (FAILED(hr)) {
                    std::string file = dir;
                    file += path.C_Str();
                    hr = material.texture->Create(directX, file.c_str());
                }
                //----- �t�@�C�����݂̂ŒT��
                if (FAILED(hr)) {
                    std::string file = path.C_Str();
                    size_t idx = file.find_last_of('\\');
                    if (idx != std::string::npos) {
                        file = file.substr(idx + 1);
                        file = dir + file;
                        hr = material.texture->Create(directX, file.c_str());
                    }
                }
                //----- ���s���Ă������O��f��
                if (FAILED(hr)) {
                    throw std::exception((std::string(path.C_Str()) + "No Texture").c_str());
                }
            }
            else {
                material.texture = nullptr;
            }

            //----- �}�e���A���ǉ�
            m_materials.push_back(std::move(material));
        }
    }
}
