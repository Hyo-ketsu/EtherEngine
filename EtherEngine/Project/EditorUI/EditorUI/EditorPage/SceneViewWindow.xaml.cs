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
using System.Windows.Forms;
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
    [CreatedWindow("Scene View", "シーン ビュー")]
    public partial class SceneViewWindow : System.Windows.Controls.UserControl, IUserControlClose {
        /// <summary>コンストラクタ</summary>
        internal SceneViewWindow() {
            //----- 初期化
            InitializeComponent();

            //----- ViewModel追加
            DataContext = new SceneViewVM(SceneViewWindowForms.Handle, new Vector2(SceneViewWindowForms.Width, SceneViewWindowForms.Height));
        }
        /// <summary>削除時処理</summary>
        public void CloseEvent(object? sender, EventArgs e) {
            var vm = DataContext as SceneViewVM;
            vm.CloseEvent(sender, e);
        }


        /// <summary>サイズ変更時の処理</summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        /// <exception cref="Exception"></exception>
        public void WindowsFormsHostSizeChanged(object sender, SizeChangedEventArgs e) {
            var windowsFormsHostPanel = (System.Windows.Forms.Panel)sender;
            if (windowsFormsHostPanel != null) { throw new Exception(); }

            //----- 現在のサイズを取得
            var vm = DataContext as SceneViewVM;
            vm.NewWindowSize = new Vector2((float)e.NewSize.Width, (float)e.NewSize.Height);
        }
    }
}
