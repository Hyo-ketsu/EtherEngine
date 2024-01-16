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
using System.Windows.Navigation;
using System.Windows.Shapes;
using Reactive.Bindings;


namespace EditorUI {
    /// <summary>
    /// EditorTextControl.xaml の相互作用ロジック
    /// </summary>
    public partial class EditorTextControl : UserControl {
        public EditorTextControl() {
            //----- 初期化
            InitializeComponent();

            //----- 文字列設定
            EditorSetting.Get.Language.Subscribe(language => {
                Text.Value = EditorText.ToString();
            });

            //----- DataContextへ追加
            DataContext = this;
        }


        public ReactiveProperty<string> Text { get; private set; } = new();
        public string EN { set { 
                EditorText.EN = value; 
                Text.Value = EditorText.ToString();
            }
        }
        public string JP { set { 
                EditorText.JP = value;
                Text.Value = EditorText.ToString();
            } 
        }

        
        public EditorText EditorText { get; private set; } = new();
    }
}
