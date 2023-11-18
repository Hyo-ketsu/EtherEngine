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
    public partial class SceneView : Window {
        public SceneView() {
            //----- 初期化
            InitializeComponent();

            //----- エディター側で必要なのでメッセージとして追加
            GetWindow(this);

            //----- 生成時は即サイズが変更されたものとする
            m_newWindowSize = new Vector2(this.SceneViewWindowForms.Width, this.SceneViewWindowForms.Height);
        }


        /// <summary>ウィンドウの実際の描画部分</summary>
        public IntPtr SceneViewTarget { get { return SceneViewWindowForms.Handle; } }


        /// <summary>新しく設定されたサイズ</summary>
        public Vector2? NewWindowSize { 
            get {
                var ret = m_newWindowSize;
                m_newWindowSize = null;
                return m_newWindowSize;
            } 
        }


        /// <summary>シーン描画箇所のサイズが変更された際のイベント</summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void WindowsFormsHost_SizeChanged(object sender, SizeChangedEventArgs e) {
            var windowsFormsHostPanel = (System.Windows.Forms.Panel)sender;
            if (windowsFormsHostPanel != null) { throw new Exception(); }

            //----- 現在のサイズを取得
            m_newWindowSize = new Vector2((float)e.NewSize.Width, (float)e.NewSize.Height);
        }


        /// <summary>新しいウィンドウのサイズ</summary>
        private Vector2? m_newWindowSize = null;   
    }
}
