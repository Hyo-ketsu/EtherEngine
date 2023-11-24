#ifndef I_CPPCLIUTILITY_H
#define I_CPPCLIUTILITY_H
#include <Base/ConceptUtility.h>
#include <Base/BaseDefines.h>
#include <Base/EditorException.h>
#include <EngineLibrary/ConvertManage.h>


//----- インタフェース定義
namespace EtherEngine {
#ifdef _ENGINELIBRARY
    // Serialize, DeserializeInterface
    public interface class ISerializer {
    public:
        // 外部出力する
        std::string Serialize(void);
        // 外部入力する
        void Deserialize(const std::string& input);
    };


    // Inspector表示Interface
    public interface class IInspectorDrawer {
    public:
        // 表示する
        void DrawInspector(void);
    };
#endif
}




//----- 完全修飾名取得関数 定義
namespace EtherEngine {
    // 完全修飾名を取得する
    // @ Exce : クラス名が存在しない
    // @ Ret  : 完全修飾名(Hoge.Fuga)
    // @ Arg1 : クラス名
    // @ Arg2 : 何番名の名前空間を採用するか(Default : 0)。例として"Foo.Hoge", "Bar.Hoge"を、0番を指定すると"Foo.Hoge"を取得する
    // @ Arg3 : System名前空間を含めるか(Default : 含めない。false)
    std::string GetFullName(const std::string& className, const uint index = 0, const bool isSystem = false);
    // 完全修飾名を取得する
    // @ Exce : クラス名が存在しない
    // @ Ret  : 完全修飾名(Hoge.Fuga)
    // @ Arg1 : クラス名
    // @ Arg2 : 何番名の名前空間を採用するか(Default : 0)。例として"Foo.Hoge", "Bar.Hoge"を、0番を指定すると"Foo.Hoge"を取得する
    // @ Arg3 : System名前空間を含めるか(Default : 含めない。false)
    System::String^ GetFullName(System::String^ className, const uint index = 0, const bool isSystem = false);
}




#ifdef _ENGINELIBRARY
//----- Serializer 宣言
namespace EtherEngine {
    // Serialize, Deserialize自体を行うクラス
    public ref class Serializer : public ISerializer {
    public:
        // 外部出力する
        std::string Serialize(void) override {
            using namespace System::Reflection;

            //----- 変数宣言
            nlohmann::json serialize;   // 出力するJson文字列
            System::Type^ thisType = GetType();

            //----- 全てのFieldを取得、出力する
            auto fields = thisType->GetFields(BindingFlags::NonPublic | BindingFlags::Public | BindingFlags::DeclaredOnly);

            //----- 出力するフィールドを判定する
            for each (auto field in fields) {
                //----- 出力フラグ宣言
                bool isOutput = false;

                //----- 公開しているかを代入
                isOutput = field->IsPublic;

                //----- 指定の属性が取得できるか
                auto attributes = field->GetCustomAttributes(true);
                for each (auto attribute in attributes) {
                    if (isOutput) {
                        //----- Public時。非公開属性か
                        if (attribute->GetType() == System::Type::GetType("EtherEngineNonSerializeAttribute")) {
                            //----- 定義されている。このループを終了
                            isOutput = false;
                            break;
                        }
                    }
                    else {
                        //----- 非Public時。公開属性か
                        if (attribute->GetType() == System::Type::GetType("EtherEngineSerializeAttribute")) {
                            //----- 定義されている。このループを終了
                            isOutput = true;
                            break;
                        }
                    }
                }

                //----- 公開するのであればJson出力
                Serializer^ iSerialize = dynamic_cast<Serializer^>(field->GetValue(this));
                if (iSerialize != nullptr) {
                    serialize[ManageToUnmanage::String(thisType->Name)][ManageToUnmanage::String(field->Name)] = iSerialize->Serialize();
                }
                else {
                    serialize[ManageToUnmanage::String(thisType->Name)][ManageToUnmanage::String(field->Name)] = ManageToUnmanage::String(field->ToString());
                }
            }

            //----- 返却
            return serialize.dump(FileDefine::JSON_DUMP_NUMBER_OF_STAGES);
        }
        // 外部入力する
        void Deserialize(const std::string& input) override {
            using namespace System::Reflection;

            //----- 変数宣言
            nlohmann::json serialize = nlohmann::json::parse(input);   // 入力するJson文字列
            System::Type^ thisType = GetType();

            //----- 全てのFieldを取得、出力する
            auto fields = thisType->GetFields(BindingFlags::NonPublic | BindingFlags::Public | BindingFlags::Instance);

            //----- そもそも自コンポーネントが存在しなければ入力しない
            if (serialize.contains(ManageToUnmanage::String(thisType->Name)) == false) return;

            //----- 全てのFieldに対し入力する
            for each (auto field in fields) {
                //----- そのFieldが存在するか
                if (serialize.contains(ManageToUnmanage::String(field->Name)) == false) continue;

                //----- 代入
                Serializer^ iSerialize = dynamic_cast<Serializer^>(field->GetValue(this));
                if (iSerialize != nullptr) {
                    iSerialize->Deserialize(serialize[ManageToUnmanage::String(thisType->Name)][ManageToUnmanage::String(field->Name)]);
                }
                else {
                    try {
                        //field->SetValue(this, System::Convert::ChangeType(UnmanageToManage::String(serialize[ManageToUnmanage::String(thisType->Name)][ManageToUnmanage::String(field->Name)]), field->FieldType));
                    }
                    catch (System::InvalidCastException^) {
                    }
                }
            }
        }
    };
}
#endif




#ifdef _ENGINELIBRARY
//----- UnmanageMaintainer 宣言
namespace EtherEngine {
    // Unmanage Class を value class で保持するクラス
    // @ Memo : 手動で解放処理を呼び出してください
    template <typename UnmanageType>
    public value class UnmanageMaintainer : public ISerializer {
    public:
        // ポインタを保持するコンストラクタ
        // @ Arg1 : 対象
        UnmanageMaintainer(UnmanageType* maintainer)
            : m_maintainer(maintainer)
            , m_isNew(false) {
        }
        //// 生成を行うコンストラクタ
        //// @ Args : 初期化に必要な変数
        //template <typename ...ArgsType>
        //UnmanageMaintainer(ArgsType... args)
        //    : m_maintainer(new UnmanageType(args...))
        //    , m_isNew(true) {
        //}
        // コピーとnewを行うコンストラクタ
        // @ Arg1 : 対象
        UnmanageMaintainer(UnmanageType&& maintainer)
            : m_maintainer(new UnmanageType(maintainer))
            , m_isNew(true) {
        }
        // 解放する
        void MaintainerClear(void) {
            if (m_isNew == true) {
                delete m_maintainer;
                m_maintainer = nullptr;
            }
            m_isNew = false;
        }


        // 対象を持っているか
        // @ Ret  : 値を持っていれば true
        bool HasValue(void) {
            return m_maintainer != nullptr;
        }
        // 対象を取得する
        // @ Memo : 対象が無ければ例外を出力します
        // @ Ret  : 対象
        UnmanageType& GetValue(void) {
            if (HasValue() == false) throw EditorException("Error! Non Maintainer");
            return *m_maintainer;
        }
        // 対象を設定する
        // @ Arg1 : 対象
        void SetValue(UnmanageType* maintainer) {
            //----- 自身がポインタで保持している、かつ引数もポインタで保持しているかつ、アドレスが違う場合解放する
            if (m_maintainer != nullptr && m_maintainer != nullptr && m_maintainer != maintainer) MaintainerClear();

            //----- ポインタの保持
            m_maintainer = maintainer;
        }
        // 対象を設定する
        // @ Arg1 : 対象
        void SetValue(UnmanageType&& maintainer) {
            //----- 解放
            MaintainerClear();

            //----- 保持
            m_maintainer = new UnmanageType(maintainer);
        }


        // 外部出力する
        std::string Serialize(void) override {
            if constexpr (Concept::BaseOfConcept<UnmanageType, IInOuter>) {
                return dynamic_cast<IInOuter*>(m_maintainer)->Output();
            }
            else {
                return "";
            }
        }
        // 外部入力する
        void Deserialize(const std::string& input) override {
            if constexpr (Concept::BaseOfConcept<UnmanageType, IInOuter>) {
                dynamic_cast<IInOuter*>(m_maintainer)->InputString(input);
            }
            else {
            }
        }

    private:
        // 自動削除用クラス
        ref class Deleter {
        public:
        };


        UnmanageType* m_maintainer; // 保持している対象
        bool m_isNew;               // 右辺値を受け取り構築したか
    };
}
#endif;


#endif // !I_CPPCLIUtility_H
