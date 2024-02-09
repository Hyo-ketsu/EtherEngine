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
    /// SeparateLabelContents.xaml の相互作用ロジック
    /// </summary>
    public partial class SeparateLabelContents : UserControl {
        public SeparateLabelContents() {
            InitializeComponent();
        }


        /// <summary>ラベルの表示名</summary>
        public string Text { 
            set {
                var label = new Label();
                label.Content = value;
                LabelGrid.Children.Clear();
                LabelGrid.Children.Add(label);
            }
        }
        /// <summary>ラベルの表示物</summary>
        public UIElement LabelContents {
            set {
                LabelGrid.Children.Clear();
                LabelGrid.Children.Add(value);
            }
        }


        /// <summary>表示するコンテンツ</summary>
        public UIElement Contents {
            set {
                ContentsGrid.Children.Clear();
                ContentsGrid.Children.Add(value); 
            }
        }
    }
}
