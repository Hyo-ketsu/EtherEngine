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


namespace EditorUI {
    /// <summary>複数言語の入力に対応したTextBlock</summary>
    public class MultiLanguageTextBlock : TextBlock {
        /// <summary>コンストラクタ</summary>
        public MultiLanguageTextBlock() {
        }


        public static readonly DependencyProperty EditorTextProperty = DependencyProperty.Register(
            "EditorText",
            typeof(EditorText),
            typeof(MultiLanguageTextBlock), 
            new PropertyMetadata(null, OnEditorTextPropertyChanged));


        /// <summary>表示するテキスト</summary>
        public EditorText EditorText {
            get {
                return (EditorText)GetValue(EditorTextProperty);
            }
            set {
                SetValue(EditorTextProperty, value);
            }
        }


        /// <summary>EditorText変更時のイベントハンドラ</summary>
        /// <param name="d"></param>
        /// <param name="e"></param>
        private static void OnEditorTextPropertyChanged(DependencyObject d, DependencyPropertyChangedEventArgs e) {
            //----- キャスト
            var textBlock = (TextBlock)d;
            var newEditorText = (EditorText)e.NewValue;

            //----- 代入
            textBlock.Text = newEditorText?.ToString();
        }


        /// <summary>保持している複数言語でのテキスト</summary>
        private EditorText m_editorText = new();
    }
}
