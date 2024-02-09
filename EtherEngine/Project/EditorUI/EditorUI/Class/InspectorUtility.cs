using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using EtherEngine;


namespace EditorUI {
    /// <summary>インスペクターで使用する関数</summary>
    public static class InspectorUtility {
        /// <summary>「m_変数名」,「_変数名」を取り除き、名前をアッパーキャメルに変更します</summary>
        /// <param name="fieldName">修正前のフィールド名</param>
        /// <returns></returns>
        public static string GetNonDecorationFieldName(in string fieldName) {
            //----- 変数宣言
            string ret = fieldName;

            //----- 頭の「m_変数名」,「_変数名」の削除
            if (ret[0] == '_') {
                ret = ret.Remove(0, 1);
            }
            if (ret[0] == 'm' && ret[1] == '_') {
                ret = ret.Remove(0, 2);
            }

            //----- 頭の小文字を大文字にする
            if (char.IsLower(ret[0])) {
                var copyText = ret.Remove(0, 1);
                var upperChar = char.ToUpper(ret[0]);
                ret = upperChar + copyText;
            }

            return ret;
        }


        /// <summary>
        /// <para>TypeからInspectorに追加するコントロールを取得する</para>
        /// <para>@ Memo : Inspectorの構成は以下になっています(GameObejct想定)</para>
        /// <para>         BaseObject Header   (スーパークラス)</para>
        /// <para>         BaseObject TypeShow (スーパークラス)</para>
        /// <para>         GameObject Header   (サブクラス)</para>
        /// <para>         GameObject TypeShow (サブクラス)</para>
        /// <para>         GameObject BackShow (サブクラス)</para>
        /// <para>         BaseObject BackShow (スーパークラス)</para>
        /// </summary>
        /// <param name="baseObject"></param>
        /// <returns></returns>
        public static UIElement GetControl(BaseObject baseObject) {
            //----- 変数宣言
            // @ MEMO : セパレートかましたいからGrid?
            var showInspector = new StackPanel();   // 表示用のスタックパネル作成
            var backShows = new List<UIElement>();  // BackShow表示用リスト

            //----- 追加用ラムダ宣言(後に変更するのを見越しています)
            var addInspector = (UIElement add) => {
                showInspector.Children.Add(add);
            };

            var type = baseObject.GetType();
            while (type != typeof(object) && type != null) {
                //----- 型の情報取得
                var classDatas = ClassLoader.GetClassData(type, GetClassDataOption.Editor);

                //----- Header表示
                var header = InspectorTypeHeaderAttribute.GetInspectorExtension(type, baseObject);
                if (header != null) {
                    //----- Headerを取得して追加する
                    addInspector(header);
                }

                //----- 型表示
                var typeShow = InspectorTypeTypeShowAttribute.GetInspectorExtension(type, baseObject);
                if (typeShow != null) {
                    //----- 特殊表示
                    addInspector(typeShow);
                }
                else {
                    //----- デフォルト表示。それぞれの型に対応したコントロールを追加
                    foreach (var classData in classDatas) {
                        //----- BaseObject       
                        if (classData.FieldType == typeof(BaseObject)) {
                            continue;
                            if (false) {
                                //----- 非参照。再帰して表示
                            }
                            else {
                                //----- 参照。参照用を表示
                                var objectReference = new ObjectReference();
                                objectReference.Object = classData.GetValue(baseObject) as BaseObject;

                                //----- stackパネルに追加
                                showInspector.Children.Add(objectReference);
                            }

                            continue;
                        }
                        //----- 数値型
                        if (classData.FieldType == typeof(int) || classData.FieldType == typeof(short) || classData.FieldType == typeof(long) ||
                            classData.FieldType == typeof(uint) || classData.FieldType == typeof(ushort) || classData.FieldType == typeof(ulong) ||
                            classData.FieldType == typeof(float)) {
                            //----- コントロール生成
                            var numberInput = new NumberInput();
                            var contents = new SeparateLabelContents();

                            //----- 各コントロール設定
                            contents.Text = GetNonDecorationFieldName(classData.Name);
                            contents.Contents = numberInput;
                            numberInput.NumberType = classData.FieldType;
                            numberInput.SetNumber(classData.GetValue(baseObject));

                            //----- stackパネルに追加
                            showInspector.Children.Add(contents);

                            continue;
                        }
                        //----- 文字列
                        if (classData.FieldType == typeof(string)) {
                            //----- コントロール生成
                            var contents = new SeparateLabelContents();
                            var textBox = new TextBox();

                            //----- 各コントロール設定
                            contents.Text = GetNonDecorationFieldName(classData.Name);
                            contents.Contents = textBox;

                            //----- テキストボックスの修正
                            textBox.Text = classData.GetValue(baseObject) as string;
                            textBox.TextChanged += (_, _) => {
                                classData.SetValue(baseObject, textBox.Text);
                                baseObject.UpdateEventIgnition(EventArgs.Empty);
                            };

                            //----- stackパネルに追加
                            showInspector.Children.Add(contents);

                            continue;
                        }
                    }
                }

                //----- 終端表示
                var backShow = InspectorTypeFooterAttribute.GetInspectorExtension(type, baseObject);
                if (backShow != null) {
                    //----- BackShowリストに追加
                    backShows.Add(backShow);    // ここだけ HeaderとTypeShowと違います
                }

                //----- スーパークラスを取得
                type = type.BaseType;
            }

            //----- 終端表示を追加する
            backShows.Reverse();    // スーパークラス、サブクラスの順で追加されているため逆転させる
            foreach (var backShow in backShows) {
                addInspector(backShow);
            }

            //----- 返却
            return showInspector;
        }
    }
}
