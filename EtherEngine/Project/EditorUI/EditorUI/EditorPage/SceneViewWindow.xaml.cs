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
using AvalonDock.Layout;
using MahApps.Metro.Controls;


namespace EditorUI {
    /// <summary>
    /// SceneView.xaml の相互作用ロジック
    /// </summary>
    [CreatedWindow("Scene View","シーン ビュー")]
    public partial class SceneViewWindow : UserControl {
        /// <summary>コンストラクタ</summary>
        internal SceneViewWindow() {
            //----- 初期化
            InitializeComponent();

            //----- ViewModel追加
            VM = new(new SceneViewVM(SceneViewWindowForms.Handle, new Vector2(SceneViewWindowForms.Width, SceneViewWindowForms.Height)));

            DataContext = VM;
        }


        /// <summary>サイズ変更時の処理</summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        /// <exception cref="Exception"></exception>
        public void WindowsFormsHostSizeChanged(object sender, SizeChangedEventArgs e) {
            var windowsFormsHostPanel = (System.Windows.Forms.Panel)sender;
            if (windowsFormsHostPanel != null) { throw new Exception(); }

            //----- 現在のサイズを取得
            VM.Get.NewWindowSize = new Vector2((float)e.NewSize.Width, (float)e.NewSize.Height);
        }


        /// <summary>ViewModel</summary>
        public VMObject<SceneViewVM> VM { get; private set; }
    }
}
