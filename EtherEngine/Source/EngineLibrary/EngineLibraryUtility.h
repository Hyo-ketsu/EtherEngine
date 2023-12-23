#ifndef I_CPPCLIUTILITY_H
#define I_CPPCLIUTILITY_H
#include <Base/ConceptUtility.h>
#include <Base/BaseDefines.h>
#include <Base/EditorException.h>
#include <EngineLibrary/ConvertManageToUnmanage.h>


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




//----- UnmanageMaintainer 宣言
namespace EtherEngine {
    // Unmanage Class を value class で保持するクラス
    // @ Memo : 手動で解放処理を呼び出してください
    template <typename UnmanageType>
    public value class UnmanageMaintainer {
    public:
        // ポインタを保持するコンストラクタ
        // @ Arg1 : 対象
        UnmanageMaintainer(UnmanageType* maintainer)
            : m_maintainer(maintainer)
            , m_isNew(false) {
        }
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
        UnmanageType* m_maintainer; // 保持している対象
        bool m_isNew;               // 右辺値を受け取り構築したか
    };
}


#endif // !I_CPPCLIUtility_H
