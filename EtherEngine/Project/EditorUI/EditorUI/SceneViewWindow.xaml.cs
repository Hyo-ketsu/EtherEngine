using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
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


namespace EditorUI {
    /// <summary>
    /// SceneView.xaml の相互作用ロジック
    /// </summary>
    public partial class SceneViewWindow : Window {
        /// <summary>コンストラクタ</summary>
        public SceneViewWindow() {
            //----- 初期化
            InitializeComponent();

            //----- ViewModel初期化
            m_vm = new(SceneViewWindowForms.Handle, new Vector2(SceneViewWindowForms.Width, SceneViewWindowForms.Height));

            //----- エディター側で必要なのでメッセージとして追加
            GetEditorWindow.AddCreateWindow(m_vm);
        }


        /// <summary>サイズ変更時の処理</summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        /// <exception cref="Exception"></exception>
        public void WindowsFormsHostSizeChanged(object sender, SizeChangedEventArgs e) {
            var windowsFormsHostPanel = (System.Windows.Forms.Panel)sender;
            if (windowsFormsHostPanel != null) { throw new Exception(); }

            //----- 現在のサイズを取得
            m_vm.NewWindowSize = new Vector2((float)e.NewSize.Width, (float)e.NewSize.Height);
        }


        /// <summary>保持しているViewModel</summary>
        SceneViewVM m_vm;
    }
}
