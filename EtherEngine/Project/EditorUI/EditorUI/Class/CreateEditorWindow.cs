using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Runtime.CompilerServices;
using System.Threading;


namespace EditorUI {
    /// <summary>エンジン側からウィンドウを追加するクラス</summary>
    public static class CreateEditorWindow {
        /// <summary>型を与えて生成する</summary>
        /// <typeparam name="WindowType">作成するWindowの型</typeparam>
        /// <param name="isDialog">Dialogで表示を行うか(Default : false)</param>
        public static void AddCreateWindow<WindowType>(bool isDialog = false) where WindowType : Window, new() {
            AddCreateWindow(() => { return new WindowType(); }, isDialog);
        }
        /// <summary>ラムダを与えて生成する</summary>
        /// <param name="windowCreate">生成に使用するデリゲーター</param>
        /// <param name="isDialog">Dialogで表示を行うか(Default : false)</param>
        public static void AddCreateWindow(Func<Window> windowCreate, bool isDialog = false) {
            Application.Current.Dispatcher.Invoke(() => {
                var createWindow = windowCreate();

                //----- 生成して表示する
                if (isDialog) {
                    createWindow.ShowDialog();
                }
                else {
                    createWindow.Show();
                }
            });
        }
    }
}
