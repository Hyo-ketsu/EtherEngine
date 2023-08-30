#include <EtherEngine/ProjectMediation.h>

namespace EtherEngine {
    // コンストラクタ
    ProjectMediation::ProjectMediation(void) {
    }
    // デストラクタ
    ProjectMediation::~ProjectMediation(void) {
    }


    // 初期化処理
    void ProjectMediation::Init(const PathClass& sln, const PathClass& vcxproj) {
        //----- 入力ファイルcheck
        if (sln.IsExists() == false && sln.GetExtension() != ".sln") {
            throw std::exception("Error! Non Solution File");
        }
        if (vcxproj.IsExists() == false && vcxproj.GetExtension() != ".vcxproj") {
            throw std::exception("Error! Non Project File");
        }

        //----- 入力
        m_sln = sln;
        m_vcxproj = vcxproj;
    }
    // 終了処理
    void ProjectMediation::Uninit(void) {
    }


    // .hや.cpp等をプロジェクトに追加する
    bool ProjectMediation::AddSource(const PathClass& source) {
        //----- 宣言
        tinyxml2::XMLDocument vcxprojXml;

        //----- プロジェクトファイルを読み取る
        if (vcxprojXml.LoadFile(m_vcxproj.Get().c_str()) != tinyxml2::XML_SUCCESS) {
            //----- 失敗。例外を送出
            throw std::exception("Error! Project file non");
        }

        //----- 各要素を取得
        auto projectElement = vcxprojXml.FirstChildElement("Project");
        auto itemGroupElement = projectElement->FirstChildElement("ItemGroup");

        //----- プロジェクトのソース追加のItemGroupが存在するか
        // @ MEMO : 2つ目の<ItemGroup>を想定して書いています
        int itemGroupCount = 0;
        for (; itemGroupElement; itemGroupCount++) {
            //----- 次の<ItemGroup>を探す
            itemGroupElement = itemGroupElement->NextSiblingElement("ItemGroup");
        }
        itemGroupElement = projectElement->FirstChildElement("ItemGroup");
        if (itemGroupCount < 2) {
            //----- 1行も無ければエラー
            if (itemGroupCount == 0) throw std::exception("Error!");

            //----- 2行未満。存在しないと判定して作成
            auto newItemGroupElement = vcxprojXml.NewElement("ItemGroup");
            projectElement->InsertAfterChild(projectElement->FirstChildElement("ItemGroup"), newItemGroupElement);
        }

        //----- プロジェクトにファイルを追加する
        // @ MEMO : 2つ目の<ItemGroup>を想定して書いています
        for (int i = 0; itemGroupElement; i++) {
            //----- 2つ目の<ItemGroup>を取得
            if (i == 1) {
                //----- その要素が存在するか判定
                auto clCompileElement = itemGroupElement->FirstChildElement("ClCompile");
                for (; clCompileElement; clCompileElement = clCompileElement->NextSiblingElement("ClCompile")) {
                    //----- XMLの属性取得
                    auto attribute = clCompileElement->FindAttribute("Include");

                    //----- 既に同じファイルが含まれているか判定
                    if (attribute != nullptr) {
                        if (strcmp(attribute->Value(), source.Get().c_str()) == 0) {
                            //----- 同じファイルのが含まれていた。このItemGroupでの追加を終了
                            goto END;
                        }
                    }
                };

                //----- 新しい<ClCompile>要素を作成
                clCompileElement = itemGroupElement->InsertNewChildElement("ClCompile");
                clCompileElement->SetAttribute("Include", source.Get().c_str());

                //----- <ItemGroup>の中に新しい<ClCompile>要素を追加
                itemGroupElement->InsertEndChild(clCompileElement);

                //----- XML文書を保存
                vcxprojXml.SaveFile(m_vcxproj.Get().c_str());

                return true;
            }
            END: {}

            //----- 次の<ItemGroup>を探す
            itemGroupElement = itemGroupElement->NextSiblingElement("ItemGroup");
        }

        return false;
    }
    // .hや.cpp等をプロジェクトから削除する
    bool ProjectMediation::DeleteSource(const PathClass& source) {
        //----- 宣言
        tinyxml2::XMLDocument vcxprojXml;

        //----- プロジェクトファイルを読み取る
        if (vcxprojXml.LoadFile(m_vcxproj.Get().c_str()) != tinyxml2::XML_SUCCESS) {
            //----- 失敗。例外を送出
            throw std::exception("Error! Project file non");
        }

        //----- 各要素を取得
        auto projectElement = vcxprojXml.FirstChildElement("Project");
        auto itemGroupElement = projectElement->FirstChildElement("ItemGroup");

        //----- プロジェクトにファイルを追加する
        // @ MEMO : 2つ目の<ItemGroup>を想定して書いています
        for (int i = 0; itemGroupElement; i++) {
            //----- 2つ目の<ItemGroup>を取得
            if (i == 1) {
                //----- その要素が存在するか判定
                auto clCompileElement = itemGroupElement->FirstChildElement("ClCompile");
                for (; clCompileElement; clCompileElement = clCompileElement->NextSiblingElement("ClCompile")) {
                    //----- XMLの属性取得
                    auto attribute = clCompileElement->FindAttribute("Include");

                    //----- 既に同じファイルが含まれているか判定
                    if (attribute != nullptr) {
                        if (strcmp(attribute->Value(), source.Get().c_str()) == 0) {
                            //----- 同じファイルのが含まれていた。削除・終了
                            itemGroupElement->DeleteChild(clCompileElement);

                            //----- XML文書を保存
                            vcxprojXml.SaveFile(m_vcxproj.Get().c_str());

                            return true;
                        }
                    }
                };

                break;
            }

            //----- 次の<ItemGroup>を探す
            itemGroupElement = itemGroupElement->NextSiblingElement("ItemGroup");
        }

        return false;
    }
}
