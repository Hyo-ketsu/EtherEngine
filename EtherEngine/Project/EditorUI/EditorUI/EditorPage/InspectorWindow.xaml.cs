using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using AvalonDock.Layout;
using MahApps.Metro.Controls;


namespace EditorUI {
    /// <summary>
    /// InspectorWindow.xaml の相互作用ロジック
    /// </summary>
    [CreatedWindow(en: "Inspector", jp: "詳細")]
    public partial class InspectorWindow : UserControl {
        public InspectorWindow() {
            InitializeComponent();

            InspectorVM.InspectoObject.Subscribe(baseObject => {
                if (baseObject != null) {
                    CreateInspectorItem(baseObject);
                }
                else {
                    Inspector.Children.Clear();
                }
            });
        }


        /// <summary>インスペクター用のUIを生成する</summary>
        public void CreateInspectorItem(EtherEngine.BaseObject baseObject) {
            //----- まずはClearする
            Inspector.Children.Clear();

            //----- 型の情報取得
            var classDatas = EtherEngine.ClassLoader.GetClassData(baseObject, typeof(EtherEngine.BaseObject));

            //----- それぞれの型に対応したコントロールを追加
            foreach (var classData in classDatas) {
                //----- それぞれの型に対応したコントロール表示
                if (classData.FieldType == typeof(EtherEngine.BaseObject)) {
                    var objectReference = new EditorUI.ObjectReference();
                    objectReference.Object = classData.GetValue(baseObject) as EtherEngine.BaseObject;
                    Inspector.Children.Add(objectReference);

                    continue;
                }
                if (classData.FieldType == typeof(int) || classData.FieldType == typeof(short) || classData.FieldType == typeof(long) ||
                    classData.FieldType == typeof(uint) || classData.FieldType == typeof(ushort) || classData.FieldType == typeof(ulong) ||
                    classData.FieldType == typeof(float)) {
                    var numberInput = new EditorUI.NumberInput();
                    numberInput.NumberType = classData.FieldType;
                    // @ MEMO : 後回し
                    //numberInput.SetValue(classData.GetValue(baseObject) as );
                    Inspector.Children.Add(numberInput);
                }
                if (classData.FieldType == typeof(string)) {
                    var textBox = new TextBox();
                    textBox.Text = classData.GetValue(baseObject) as string;
                    Inspector.Children.Add(textBox);
                }
            }
        }
    }
}
