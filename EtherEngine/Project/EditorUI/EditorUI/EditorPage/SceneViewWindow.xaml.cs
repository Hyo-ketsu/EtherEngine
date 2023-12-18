using System;
using System.Collections.Generic;
using System.Drawing.Printing;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Forms;
using System.Windows.Forms.Integration;
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
        public SceneViewWindow() {
            //----- 初期化
            InitializeComponent();

            WindowsFormsHost.Loaded += (_, _) => {
                lock (m_lockObject) {
                    //----- ViewModel追加
                    var windowSize = m_windowSize;
                    windowSize ??= new Vector2(SceneViewWindowForms.Width, SceneViewWindowForms.Height);
                    DataContext = new SceneViewVM(SceneViewWindowForms.Handle, windowSize.Value);
                }
            };
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
            lock (m_lockObject) {
                //----- VM取得
                var vm = DataContext as SceneViewVM;

                //----- 
                var windowSize = new Vector2((float)e.NewSize.Width, (float)e.NewSize.Height);

                //----- 設定処理
                if (vm != null) {
                    //----- VMがある。初期化
                    vm.NewWindowSize = windowSize;
                }
                else {
                    //----- VMがない。フィールドに保持
                    m_windowSize = windowSize;
                }
            }
        }


        /// <summary>保持しているウィンドウサイズ</summary>
        private Vector2? m_windowSize = null;
        /// <summary>WindowSizeのロックオブジェクト</summary>
        private object m_lockObject = new();
    }
}
