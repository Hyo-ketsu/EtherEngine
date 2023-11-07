#include <EtherEngine/ProjectMediation.h>
#include <C++CLI/AssemblyHolder.h>
#include <EtherEngine/EditorAssemblyRefresh.h>
#include <EtherEngine/EditorDefine.h>


//----- ソースファイルが含まれている属性取得
namespace EtherEngine {
    // ソースファイルが含まれている<ItemGroup>を取得する
    // @ Ret  : ソースファイルが含まれている<ItemGroup>(null許容)
    // @ Arg1 : 配下に<ItemGroup>がある属性
    tinyxml2::XMLElement* GetSourceFileElement(tinyxml2::XMLElement* element) {
        //----- nullチェック
        if (element == nullptr) throw std::exception(R"(Error! Arg "element" is nullptr)");

        //----- 属性取得
        auto itemGroup = element->FirstChildElement("ItemGroup");

        //----- 属性のない<ItemGroup>のみを取得
        for (; itemGroup->NextSiblingElement("ItemGroup"); itemGroup = itemGroup->NextSiblingElement("ItemGroup")) {
            //----- 何らかの属性が存在するか
            if (itemGroup->FirstAttribute() == nullptr) {   // 最初の属性がない = 何も属性がない
                //----- 属性が存在しない。
                return itemGroup;
            }
        }

        //----- ソースファイルが含まれている<ItemGroup>を取得できなかった
        return nullptr;
    }
}


namespace EtherEngine {
    // コンストラクタ
    ProjectMediation::ProjectMediation(void) {
    }
    // デストラクタ
    ProjectMediation::~ProjectMediation(void) {
    }


    // 初期化処理
    // @ MEMO : 現在はエンジン起動時は強制的に「更新されている」ものとします（のちにこのファイル状況をエクスポートできるようにする？）
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
        this->FileUpdateDataUpdate();
        m_isUpdateFile = true;
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
        if (GetSourceFileElement(projectElement)) {
            //----- <ItemGroup>が存在しない。生成
            auto newItemGroupElement = vcxprojXml.NewElement("ItemGroup");
            projectElement->InsertAfterChild(projectElement->FirstChildElement("ItemGroup"), newItemGroupElement);
        }

        //----- プロジェクトにファイルを追加する
        itemGroupElement = GetSourceFileElement(projectElement);
        if (itemGroupElement == nullptr) throw std::exception("Error! itemGroupElement == null");

        //----- その要素が存在するか判定
        auto clCompileElement = itemGroupElement->FirstChildElement("ClCompile");
        for (; clCompileElement; clCompileElement = clCompileElement->NextSiblingElement("ClCompile")) {
            //----- XMLの属性取得
            auto attribute = clCompileElement->FindAttribute("Include");

            //----- 既に同じファイルが含まれているか判定
            if (attribute != nullptr) {
                if (strcmp(attribute->Value(), source.Get().c_str()) == 0) {
                    //----- 同名のファイルが存在していた。終了
                    return false;
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
        auto itemGroupElement = GetSourceFileElement(projectElement);
        if (itemGroupElement == nullptr) throw std::exception("Error! itemGroupElement == nullptr");

        //----- プロジェクトにファイルを追加する
        auto clCompileElement = itemGroupElement->FirstChildElement("ClCompile");
        for (; clCompileElement; clCompileElement = clCompileElement->NextSiblingElement("ClCompile")) {
            //----- XMLの属性取得
            auto attribute = clCompileElement->FindAttribute("Include");

            //----- 既に同じファイルが含まれているか判定
            if (attribute != nullptr) {
                if (strcmp(attribute->Value(), source.Get().c_str()) == 0) {
                    //----- 同じファイルが含まれていた。削除・終了
                    itemGroupElement->DeleteChild(clCompileElement);

                    //----- XML文書を保存
                    vcxprojXml.SaveFile(m_vcxproj.Get().c_str());

                    return true;
                }
            }
        };

        //----- 同名ファイルがなかった。既に削除されていたとして判定する
        return false;
    }


    // アセンブリをリフレッシュする
    bool ProjectMediation::RefreshAssembly(void) {
        //----- 更新されたか判定してからRefresh
        if (GetIsUpdateFile()) {
            return CoercionRefreshAssembly();
        }
    }
    // アセンブリを強制リフレッシュする
    bool ProjectMediation::CoercionRefreshAssembly(void) {
        //----- Refreshを実行する
        if (Refresh::AssemblyRefresh() == Refresh::RefreshStateType::Ok) {
            //----- リフレッシュが完了。アセンブリを格納 
            AssemblyHolder::LoadAssembly(GetVcxproj().GetDirectory() / EditorFileDefine::Directory::EDITOR_MIDDLE_DATA / GetVcxproj().GetFileName() + ".dll");
            return true;
        }
        else {
            return false;
        }
    }


    // 更新情報更新
    void ProjectMediation::FileUpdateDataUpdate(void) {
        //----- 変数宣言
        bool isUpdate = false;  // 更新されているか
        tinyxml2::XMLDocument vcxprojXml;   // vcxprojのxml
        decltype(this->m_projectFile) projectFile;          // プロジェクトファイル追加・削除判定用
        decltype(this->m_projectFileTime) projectFileTime;  // プロジェクトファイル更新判定用

        //----- プロジェクトファイルを読み取る
        if (vcxprojXml.LoadFile(m_vcxproj.Get().c_str()) != tinyxml2::XML_SUCCESS) {
            //----- 失敗。例外を送出
            throw std::exception("Error! Project file non");
        }

        //----- プロジェクトのファイルが追加・削除されているか
        do {
            //----- 各要素を取得
            auto projectElement = vcxprojXml.FirstChildElement("Project");
            auto itemGroupElement = GetSourceFileElement(projectElement);
            if (itemGroupElement == nullptr) throw std::exception("Error! itemGroupElement == nullptr");

            //----- 一覧にファイル名を追加する
            auto clCompileElement = itemGroupElement->FirstChildElement("ClCompile");
            for (; clCompileElement; clCompileElement = clCompileElement->NextSiblingElement("ClCompile")) {
                //----- XMLの属性取得
                auto attribute = clCompileElement->FindAttribute("Include");
                
                //----- ファイル名追加
                projectFile.push_back(attribute->Value());
            };

            //----- ファイル名を突合する
            // @ MEMO : 最適化等はあとで重い・もしくは多数実行するのであれば行います
            // ファイル追加検索
            for (auto& old : m_projectFile) {
                bool isEqualName = false;
                for (auto& current : projectFile) {
                    if (old == current) {
                        //----- 同名ファイルがある
                        isEqualName = true;
                        break;
                    }
                }

                if (isEqualName == false) {
                    //----- 同名ファイルがない(追加された)。更新されたものとする
                    isUpdate = true;
                    break;
                }
            }
            // ファイル削除検索
            if (isUpdate) break;
            for (auto& current : projectFile) {
                bool isEqualName = false;
                for (auto& old : m_projectFile) {
                    if (old == current) {
                        //----- 同名ファイルがある
                        isEqualName = true;
                        break;
                    }
                }

                if (isEqualName == false) {
                    //----- 同名ファイルがない(削除された)。更新されたものとする
                    isUpdate = true;
                    break;
                }
            }
        } while (false);

        //----- プロジェクト内のファイルが更新されているか
        {
            //----- 各ファイルタイムスタンプ取得
            for (const auto& it : projectFile) {
                //----- 変数宣言
                WIN32_FIND_DATA fileData{};
                FILETIME fileTime{};
                SYSTEMTIME updateTime{};

                //----- (念のため)vcxprojを基準にした絶対パスでファイル名指定
                auto filePath = GetVcxproj().GetDirectory() / it;

                //----- ファイルオープン
                HANDLE fileHandle = FindFirstFile(filePath.Get().c_str(), &fileData);
                if (fileHandle != INVALID_HANDLE_VALUE) {
                    //----- ファイルが正常に開けている。タイムスタンプを取得
                    FindClose(fileHandle);
                    FileTimeToSystemTime(&fileTime, &updateTime);

                    //----- 追加
                    projectFileTime.emplace(it, updateTime);
                }
            }

            //----- 最終更新時間を突合する
            for (const auto& it : projectFile) {
                //----- 検索
                auto current = projectFileTime.find(it);
                auto old = m_projectFileTime.find(it);

                //----- 突合する
                if (current != projectFileTime.end() && old != m_projectFileTime.end()) {
                    //----- 同名ファイルが存在する。さらに時間を比較
                    // 変数宣言
                    FILETIME currentFileTime{}; 
                    FILETIME oldFileTime{};
                    // SYSTEMTIMEをFILETIMEに変換
                    SystemTimeToFileTime(&current->second, &currentFileTime);
                    SystemTimeToFileTime(&old->second, &oldFileTime);
                    // FILETIMEを64ビット整数に変換
                    ULARGE_INTEGER current64bitInteger{};
                    ULARGE_INTEGER old64bitInteger{};
                    current64bitInteger.LowPart = currentFileTime.dwLowDateTime;
                    current64bitInteger.HighPart = currentFileTime.dwHighDateTime;
                    old64bitInteger.LowPart = oldFileTime.dwLowDateTime;
                    old64bitInteger.HighPart = oldFileTime.dwHighDateTime;
                    if (current64bitInteger.QuadPart != old64bitInteger.QuadPart) {
                        //----- 同時刻でない。更新されたものとする
                        isUpdate = true;
                        break;
                    }
                }
            }
        } 

        //----- 取得した情報をメンバーに保存
        m_isUpdateFile = isUpdate;
        m_projectFile = projectFile;
        m_projectFileTime = projectFileTime;
    }
}
