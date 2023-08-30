#include <EtherEngine/ProjectMediation.h>

namespace EtherEngine {
    // �R���X�g���N�^
    ProjectMediation::ProjectMediation(void) {
    }
    // �f�X�g���N�^
    ProjectMediation::~ProjectMediation(void) {
    }


    // ����������
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
        if (itemGroupCount < 2) {
            //----- 1�s��������΃G���[
            if (itemGroupCount == 0) throw std::exception("Error!");

            //----- 2�s�����B���݂��Ȃ��Ɣ��肵�č쐬
            auto newItemGroupElement = vcxprojXml.NewElement("ItemGroup");
            projectElement->InsertAfterChild(projectElement->FirstChildElement("ItemGroup"), newItemGroupElement);
        }

        //----- �v���W�F�N�g�Ƀt�@�C����ǉ�����
        // @ MEMO : 2�ڂ�<ItemGroup>��z�肵�ď����Ă��܂�
        for (int i = 0; itemGroupElement; i++) {
            //----- 2�ڂ�<ItemGroup>���擾
            if (i == 1) {
                //----- ���̗v�f�����݂��邩����
                auto clCompileElement = itemGroupElement->FirstChildElement("ClCompile");
                for (; clCompileElement; clCompileElement = clCompileElement->NextSiblingElement("ClCompile")) {
                    //----- XML�̑����擾
                    auto attribute = clCompileElement->FindAttribute("Include");

                    //----- ���ɓ����t�@�C�����܂܂�Ă��邩����
                    if (attribute != nullptr) {
                        if (strcmp(attribute->Value(), source.Get().c_str()) == 0) {
                            //----- �����t�@�C���̂��܂܂�Ă����B����ItemGroup�ł̒ǉ����I��
                            goto END;
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
            END: {}

            //----- ����<ItemGroup>��T��
            itemGroupElement = itemGroupElement->NextSiblingElement("ItemGroup");
        }

        return false;
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
        auto itemGroupElement = projectElement->FirstChildElement("ItemGroup");

        //----- �v���W�F�N�g�Ƀt�@�C����ǉ�����
        // @ MEMO : 2�ڂ�<ItemGroup>��z�肵�ď����Ă��܂�
        for (int i = 0; itemGroupElement; i++) {
            //----- 2�ڂ�<ItemGroup>���擾
            if (i == 1) {
                //----- ���̗v�f�����݂��邩����
                auto clCompileElement = itemGroupElement->FirstChildElement("ClCompile");
                for (; clCompileElement; clCompileElement = clCompileElement->NextSiblingElement("ClCompile")) {
                    //----- XML�̑����擾
                    auto attribute = clCompileElement->FindAttribute("Include");

                    //----- ���ɓ����t�@�C�����܂܂�Ă��邩����
                    if (attribute != nullptr) {
                        if (strcmp(attribute->Value(), source.Get().c_str()) == 0) {
                            //----- �����t�@�C���̂��܂܂�Ă����B�폜�E�I��
                            itemGroupElement->DeleteChild(clCompileElement);

                            //----- XML������ۑ�
                            vcxprojXml.SaveFile(m_vcxproj.Get().c_str());

                            return true;
                        }
                    }
                };

                break;
            }

            //----- ����<ItemGroup>��T��
            itemGroupElement = itemGroupElement->NextSiblingElement("ItemGroup");
        }

        return false;
    }
}
