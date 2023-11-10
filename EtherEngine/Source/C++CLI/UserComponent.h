#ifndef I_USERCOMPONENT_H
#define I_USERCOMPONENT_H
// @ MEMO : 実際にユーザーが記述するためのもととなるクラス
#include <C++CLI/ComponentInterface.h>
#include <C++CLI/C++CLIUtility.h>
#include <ImGUI/ImGUIWrapFunction.h>
#include <Base/GameObject.h>


//----- UseBaseComponent 宣言
namespace EtherEngine {
#ifndef CPPCLI_CPPCLI_CLASS_DECLARATION
    public ref class UserBaseComponent : public Serializer, public IInspectorDrawer {
    public:
        // コンストラクタ
        // @ MEMO : 仮措置
        UserBaseComponent(void)
            : m_gameObject(nullptr) {
        }


        // 親ゲームオブジェクトゲッター
        GameObject* const GetGameObject(void) { return m_gameObject; }
        // 親ゲームオブジェクトセッター
        void SetGameObject(GameObject* in) { m_gameObject = in; }


        // 開始処理
        virtual void Start(void) {}
        // 更新処理
        virtual void Update(void) {}
        // 削除時処理
        virtual void Delete(void) {}
        // 衝突開始処理
        virtual void CollisionStart(void) {}
        // 衝突終了処理
        virtual void CollisionEnd(void) {}
        // 衝突処理
        virtual void CollisionHit(void) {}


        // Inspector表示
        void DrawInspector(void) override {
            using namespace System::Reflection;

            //----- 変数宣言
            System::Type^ thisType = GetType();

            //----- 名前入力欄とアクティブcheck



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

                //----- 公開するのであればInspector表示
                // @ MEMO : 後で関数化
                do {
                    // int
                    if (field->GetType() == int::typeid) {
                        auto number = safe_cast<int>(field->GetValue(nullptr));
                        ImGuiFunction::ShowNumber<int>(number, ManageToUn(field->Name));
                        field->SetValue(nullptr, number);
                        break;
                    }
                    // uint
                    if (field->GetType() == uint::typeid) {
                        auto number = safe_cast<uint>(field->GetValue(nullptr));
                        ImGuiFunction::ShowNumber<uint>(number, ManageToUn(field->Name));
                        field->SetValue(nullptr, number);
                        break;
                    }
                    // ullint
                    if (field->GetType() == ullint::typeid) {
                        auto number = safe_cast<ullint>(field->GetValue(nullptr));
                        ImGuiFunction::ShowNumber<ullint>(number, ManageToUn(field->Name));
                        field->SetValue(nullptr, number);
                        break;
                    }
                    // float
                    if (field->GetType() == float::typeid) {
                        auto number = safe_cast<float>(field->GetValue(nullptr));
                        ImGuiFunction::ShowNumber<float>(number, ManageToUn(field->Name));
                        field->SetValue(nullptr, number);
                        break;
                    }
                    // double
                    if (field->GetType() == double::typeid) {
                        auto number = safe_cast<double>(field->GetValue(nullptr));
                        ImGuiFunction::ShowNumber<double>(number, ManageToUn(field->Name));
                        field->SetValue(nullptr, number);
                        break;
                    }
                    // string
                    // @ MEMO : 複数行使用属性対応予定
                    if (field->GetType() == System::String::typeid) {
                        auto str = ManageToUn(safe_cast<System::String^>(field->GetValue(nullptr)));
                        ImGuiFunction::ImGuiShow<std::string>(str, ManageToUn(field->Name));
                        field->SetValue(nullptr, UnToManage(str));
                        break;
                    }
                    // Array
                    // @ MEMO : 後回し
                    if (field->GetType() == System::Array::typeid) {

                    }
                } while (false);
            }
        }

    private:
        GameObject* m_gameObject; // 自身を保持しているゲームオブジェクト
    };
#endif
}


#endif // !I_USERCOMPONENT_H
