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
        /// <summary>コンストラクタ</summary>
        public SeparateLabelContents() {
            InitializeComponent();

            //----- テキスト変更時の処理
            m_text.Subscribe(value => {
                if (value != null) {
                    var label = new Label();
                    label.Content = value;
                    LabelGrid.Children.Clear();
                    LabelGrid.Children.Add(label);
                }
            });
            //----- ラベルにContentsを追加した際の処理
            m_labelContents.Subscribe(value => {
                if (value != null) {
                    LabelGrid.Children.Clear();
                    LabelGrid.Children.Add(value);
                }
            });
            //----- Contents領域にContentsを追加した際の処理
            m_contentsProperty.Subscribe(value => {
                if (value != null) {
                    ContentsGrid.Children.Clear();
                    ContentsGrid.Children.Add(value);
                }
            });
        }


        /// <summary>ラベルの表示名</summary>
        public string Text {
            get { return m_text.Value; }
            set { m_text.Value = value; }
        }
        /// <summary>ラベルの表示物</summary>
        public UIElement LabelContents {
            get { return m_labelContents.Value; }
            set { m_labelContents.Value = value;}
        }
        /// <summary>表示するコンテンツ</summary>
        public UIElement Contents {
            get { return m_contentsProperty.Value; }
            set { m_contentsProperty.Value = value; }
        }


        /// <summary>ラベルの表示名</summary>
        public ReactiveProperty<string> m_text { get; private set; } = new();
        /// <summary>ラベルの表示物</summary>
        public ReactiveProperty<UIElement> m_labelContents { get; private set; } = new();
        /// <summary>表示するコンテンツ</summary>
        public ReactiveProperty<UIElement> m_contentsProperty { get; private set; } = new();
    }
}
