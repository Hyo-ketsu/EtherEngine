#include <EtherEngine/ProjectMediation.h>
#include <C++CLI/AssemblyHolder.h>
#include <EtherEngine/EditorAssemblyRefresh.h>
#include <EtherEngine/EditorDefine.h>


//----- �\�[�X�t�@�C�����܂܂�Ă��鑮���擾
namespace EtherEngine {
    // �\�[�X�t�@�C�����܂܂�Ă���<ItemGroup>���擾����
    // @ Ret  : �\�[�X�t�@�C�����܂܂�Ă���<ItemGroup>(null���e)
    // @ Arg1 : �z����<ItemGroup>�����鑮��
    tinyxml2::XMLElement* GetSourceFileElement(tinyxml2::XMLElement* element) {
        //----- null�`�F�b�N
        if (element == nullptr) throw std::exception(R"(Error! Arg "element" is nullptr)");

        //----- �����擾
        auto itemGroup = element->FirstChildElement("ItemGroup");

        //----- �����̂Ȃ�<ItemGroup>�݂̂��擾
        for (; itemGroup->NextSiblingElement("ItemGroup"); itemGroup = itemGroup->NextSiblingElement("ItemGroup")) {
            //----- ���炩�̑��������݂��邩
            if (itemGroup->FirstAttribute() == nullptr) {   // �ŏ��̑������Ȃ� = �����������Ȃ�
                //----- ���������݂��Ȃ��B
                return itemGroup;
            }
        }

        //----- �\�[�X�t�@�C�����܂܂�Ă���<ItemGroup>���擾�ł��Ȃ�����
        return nullptr;
    }
}


namespace EtherEngine {
    // �R���X�g���N�^
    ProjectMediation::ProjectMediation(void) {
    }
    // �f�X�g���N�^
    ProjectMediation::~ProjectMediation(void) {
    }


    // ����������
    // @ MEMO : ���݂̓G���W���N�����͋����I�Ɂu�X�V����Ă���v���̂Ƃ��܂��i�̂��ɂ��̃t�@�C���󋵂��G�N�X�|�[�g�ł���悤�ɂ���H�j
    void ProjectMediation::Init(const PathClass& sln, const PathClass& vcxproj) {
        //----- ���̓t�@�C��check
        if (sln.IsExists() == false && sln.GetExtension() != ".sln") {
            throw std::exception("Error! Non Solution File");
        }
        if (vcxproj.IsExists() == false && vcxproj.GetExtension() != ".vcxproj") {
            throw std::exception("Error! Non Project File");
        }

        //----- ����
        m_sln = sln;
        m_vcxproj = vcxproj;
        this->FileUpdateDataUpdate();
        m_isUpdateFile = true;
    }
    // �I������
    void ProjectMediation::Uninit(void) {
    }


    // .h��.cpp�����v���W�F�N�g�ɒǉ�����
    bool ProjectMediation::AddSource(const PathClass& source) {
        //----- �錾
        tinyxml2::XMLDocument vcxprojXml;

        //----- �v���W�F�N�g�t�@�C����ǂݎ��
        if (vcxprojXml.LoadFile(m_vcxproj.Get().c_str()) != tinyxml2::XML_SUCCESS) {
            //----- ���s�B��O�𑗏o
            throw std::exception("Error! Project file non");
        }

        //----- �e�v�f���擾
        auto projectElement = vcxprojXml.FirstChildElement("Project");
        auto itemGroupElement = projectElement->FirstChildElement("ItemGroup");

        //----- �v���W�F�N�g�̃\�[�X�ǉ���ItemGroup�����݂��邩
        // @ MEMO : 2�ڂ�<ItemGroup>��z�肵�ď����Ă��܂�
        int itemGroupCount = 0;
        for (; itemGroupElement; itemGroupCount++) {
            //----- ����<ItemGroup>��T��
            itemGroupElement = itemGroupElement->NextSiblingElement("ItemGroup");
        }
        itemGroupElement = projectElement->FirstChildElement("ItemGroup");
        if (GetSourceFileElement(projectElement)) {
            //----- <ItemGroup>�����݂��Ȃ��B����
            auto newItemGroupElement = vcxprojXml.NewElement("ItemGroup");
            projectElement->InsertAfterChild(projectElement->FirstChildElement("ItemGroup"), newItemGroupElement);
        }

        //----- �v���W�F�N�g�Ƀt�@�C����ǉ�����
        itemGroupElement = GetSourceFileElement(projectElement);
        if (itemGroupElement == nullptr) throw std::exception("Error! itemGroupElement == null");

        //----- ���̗v�f�����݂��邩����
        auto clCompileElement = itemGroupElement->FirstChildElement("ClCompile");
        for (; clCompileElement; clCompileElement = clCompileElement->NextSiblingElement("ClCompile")) {
            //----- XML�̑����擾
            auto attribute = clCompileElement->FindAttribute("Include");

            //----- ���ɓ����t�@�C�����܂܂�Ă��邩����
            if (attribute != nullptr) {
                if (strcmp(attribute->Value(), source.Get().c_str()) == 0) {
                    //----- �����̃t�@�C�������݂��Ă����B�I��
                    return false;
                }
            }
        };

        //----- �V����<ClCompile>�v�f���쐬
        clCompileElement = itemGroupElement->InsertNewChildElement("ClCompile");
        clCompileElement->SetAttribute("Include", source.Get().c_str());

        //----- <ItemGroup>�̒��ɐV����<ClCompile>�v�f��ǉ�
        itemGroupElement->InsertEndChild(clCompileElement);

        //----- XML������ۑ�
        vcxprojXml.SaveFile(m_vcxproj.Get().c_str());

        return true;
    }
    // .h��.cpp�����v���W�F�N�g����폜����
    bool ProjectMediation::DeleteSource(const PathClass& source) {
        //----- �錾
        tinyxml2::XMLDocument vcxprojXml;

        //----- �v���W�F�N�g�t�@�C����ǂݎ��
        if (vcxprojXml.LoadFile(m_vcxproj.Get().c_str()) != tinyxml2::XML_SUCCESS) {
            //----- ���s�B��O�𑗏o
            throw std::exception("Error! Project file non");
        }

        //----- �e�v�f���擾
        auto projectElement = vcxprojXml.FirstChildElement("Project");
        auto itemGroupElement = GetSourceFileElement(projectElement);
        if (itemGroupElement == nullptr) throw std::exception("Error! itemGroupElement == nullptr");

        //----- �v���W�F�N�g�Ƀt�@�C����ǉ�����
        auto clCompileElement = itemGroupElement->FirstChildElement("ClCompile");
        for (; clCompileElement; clCompileElement = clCompileElement->NextSiblingElement("ClCompile")) {
            //----- XML�̑����擾
            auto attribute = clCompileElement->FindAttribute("Include");

            //----- ���ɓ����t�@�C�����܂܂�Ă��邩����
            if (attribute != nullptr) {
                if (strcmp(attribute->Value(), source.Get().c_str()) == 0) {
                    //----- �����t�@�C�����܂܂�Ă����B�폜�E�I��
                    itemGroupElement->DeleteChild(clCompileElement);

                    //----- XML������ۑ�
                    vcxprojXml.SaveFile(m_vcxproj.Get().c_str());

                    return true;
                }
            }
        };

        //----- �����t�@�C�����Ȃ������B���ɍ폜����Ă����Ƃ��Ĕ��肷��
        return false;
    }


    // �A�Z���u�������t���b�V������
    bool ProjectMediation::RefreshAssembly(void) {
        //----- �X�V���ꂽ�����肵�Ă���Refresh
        if (GetIsUpdateFile()) {
            return CoercionRefreshAssembly();
        }
    }
    // �A�Z���u�����������t���b�V������
    bool ProjectMediation::CoercionRefreshAssembly(void) {
        //----- Refresh�����s����
        if (Refresh::AssemblyRefresh() == Refresh::RefreshStateType::Ok) {
            //----- ���t���b�V���������B�A�Z���u�����i�[ 
            AssemblyHolder::LoadAssembly(GetVcxproj().GetDirectory() / EditorFileDefine::Directory::EDITOR_MIDDLE_DATA / GetVcxproj().GetFileName() + ".dll");
            return true;
        }
        else {
            return false;
        }
    }


    // �X�V���X�V
    void ProjectMediation::FileUpdateDataUpdate(void) {
        //----- �ϐ��錾
        bool isUpdate = false;  // �X�V����Ă��邩
        tinyxml2::XMLDocument vcxprojXml;   // vcxproj��xml
        decltype(this->m_projectFile) projectFile;          // �v���W�F�N�g�t�@�C���ǉ��E�폜����p
        decltype(this->m_projectFileTime) projectFileTime;  // �v���W�F�N�g�t�@�C���X�V����p

        //----- �v���W�F�N�g�t�@�C����ǂݎ��
        if (vcxprojXml.LoadFile(m_vcxproj.Get().c_str()) != tinyxml2::XML_SUCCESS) {
            //----- ���s�B��O�𑗏o
            throw std::exception("Error! Project file non");
        }

        //----- �v���W�F�N�g�̃t�@�C�����ǉ��E�폜����Ă��邩
        do {
            //----- �e�v�f���擾
            auto projectElement = vcxprojXml.FirstChildElement("Project");
            auto itemGroupElement = GetSourceFileElement(projectElement);
            if (itemGroupElement == nullptr) throw std::exception("Error! itemGroupElement == nullptr");

            //----- �ꗗ�Ƀt�@�C������ǉ�����
            auto clCompileElement = itemGroupElement->FirstChildElement("ClCompile");
            for (; clCompileElement; clCompileElement = clCompileElement->NextSiblingElement("ClCompile")) {
                //----- XML�̑����擾
                auto attribute = clCompileElement->FindAttribute("Include");
                
                //----- �t�@�C�����ǉ�
                projectFile.push_back(attribute->Value());
            };

            //----- �t�@�C������ˍ�����
            // @ MEMO : �œK�����͂��Ƃŏd���E�������͑������s����̂ł���΍s���܂�
            // �t�@�C���ǉ�����
            for (auto& old : m_projectFile) {
                bool isEqualName = false;
                for (auto& current : projectFile) {
                    if (old == current) {
                        //----- �����t�@�C��������
                        isEqualName = true;
                        break;
                    }
                }

                if (isEqualName == false) {
                    //----- �����t�@�C�����Ȃ�(�ǉ����ꂽ)�B�X�V���ꂽ���̂Ƃ���
                    isUpdate = true;
                    break;
                }
            }
            // �t�@�C���폜����
            if (isUpdate) break;
            for (auto& current : projectFile) {
                bool isEqualName = false;
                for (auto& old : m_projectFile) {
                    if (old == current) {
                        //----- �����t�@�C��������
                        isEqualName = true;
                        break;
                    }
                }

                if (isEqualName == false) {
                    //----- �����t�@�C�����Ȃ�(�폜���ꂽ)�B�X�V���ꂽ���̂Ƃ���
                    isUpdate = true;
                    break;
                }
            }
        } while (false);

        //----- �v���W�F�N�g���̃t�@�C�����X�V����Ă��邩
        {
            //----- �e�t�@�C���^�C���X�^���v�擾
            for (const auto& it : projectFile) {
                //----- �ϐ��錾
                WIN32_FIND_DATA fileData{};
                FILETIME fileTime{};
                SYSTEMTIME updateTime{};

                //----- (�O�̂���)vcxproj����ɂ�����΃p�X�Ńt�@�C�����w��
                auto filePath = GetVcxproj().GetDirectory() / it;

                //----- �t�@�C���I�[�v��
                HANDLE fileHandle = FindFirstFile(filePath.Get().c_str(), &fileData);
                if (fileHandle != INVALID_HANDLE_VALUE) {
                    //----- �t�@�C��������ɊJ���Ă���B�^�C���X�^���v���擾
                    FindClose(fileHandle);
                    FileTimeToSystemTime(&fileTime, &updateTime);

                    //----- �ǉ�
                    projectFileTime.emplace(it, updateTime);
                }
            }

            //----- �ŏI�X�V���Ԃ�ˍ�����
            for (const auto& it : projectFile) {
                //----- ����
                auto current = projectFileTime.find(it);
                auto old = m_projectFileTime.find(it);

                //----- �ˍ�����
                if (current != projectFileTime.end() && old != m_projectFileTime.end()) {
                    //----- �����t�@�C�������݂���B����Ɏ��Ԃ��r
                    // �ϐ��錾
                    FILETIME currentFileTime{}; 
                    FILETIME oldFileTime{};
                    // SYSTEMTIME��FILETIME�ɕϊ�
                    SystemTimeToFileTime(&current->second, &currentFileTime);
                    SystemTimeToFileTime(&old->second, &oldFileTime);
                    // FILETIME��64�r�b�g�����ɕϊ�
                    ULARGE_INTEGER current64bitInteger{};
                    ULARGE_INTEGER old64bitInteger{};
                    current64bitInteger.LowPart = currentFileTime.dwLowDateTime;
                    current64bitInteger.HighPart = currentFileTime.dwHighDateTime;
                    old64bitInteger.LowPart = oldFileTime.dwLowDateTime;
                    old64bitInteger.HighPart = oldFileTime.dwHighDateTime;
                    if (current64bitInteger.QuadPart != old64bitInteger.QuadPart) {
                        //----- �������łȂ��B�X�V���ꂽ���̂Ƃ���
                        isUpdate = true;
                        break;
                    }
                }
            }
        } 

        //----- �擾�������������o�[�ɕۑ�
        m_isUpdateFile = isUpdate;
        m_projectFile = projectFile;
        m_projectFileTime = projectFileTime;
    }
}
