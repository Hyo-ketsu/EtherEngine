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
// @ MEMO : 頻繁に使用するなら例外を取ってそこからメッセージを出すようにする


namespace EditorUI {
    /// <summary>
    /// ExceptionPopUpWindow.xaml の相互作用ロジック
    /// </summary>
    public partial class ExceptionPopupWindow : Window {
        /// <summary>コンストラクタ</summary>
        /// <param name="showText"></param>
        public ExceptionPopupWindow(string showText) {
            InitializeComponent();

            //----- テキスト追加
            m_vm.ShowText.Value = mr_editorText.Text;
            m_vm.ShowText.Value += showText;

            //----- バインディング
            DataContext = m_vm;

            //----- ウィンドウサイズ自動調整
            this.SizeToContent = SizeToContent.Height;
        }


        /// <summary>保持しているView Model</summary>
        private ExceptionPopupVM m_vm = new();

        readonly EditorText mr_editorText = new(
            en:"The following serious exception was thrown:\n\n",
            jp:"以下の重篤な例外が送出されました。\n\n"
            );
    }
}
