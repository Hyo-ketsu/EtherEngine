using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;


namespace EditorUI {
    /// <summary>エディターを表現するApplication</summary>
    public partial class EtherEngineApplication : Application {
        public delegate void EtherEngineMainFunction(int windowSizeX, int windowSizeY, string cmdLine, int nShowCmd);

        public EtherEngineApplication(EtherEngineMainFunction mainFunction) {
            //----- UI関連処理
            Dispatcher.Invoke(() => {
                m_mainWindow = new MainWindow();
                m_mainWindow.Show();
            });

            //----- メイン関数スレッド立ち上げ
            var startFunction = new ThreadStart(() => {
                try {
                    while (m_mainWindow == null) { }

                    int? width = null;
                    int? height = null;
                    //----- UI関連処理
                    Dispatcher.Invoke(() => {
                        width = (int)m_mainWindow.Width;
                        height = (int)m_mainWindow.Height;
                    });
                    while (width == null || height == null) { }

                    mainFunction(width.Value, height.Value, "", 0);
                } catch (System.Runtime.InteropServices.SEHException exception) { // エディターを開始出来ない例外をキャッチ
                    //----- 変数宣言
                    string message;

                    //----- 例外表示
                    if (exception.InnerException != null) {
                        //----- 非マネージの例外
                        message = exception.InnerException.ToString();
                    }
                    else {
                        //----- マネージの例外
                        message = exception.ToString();
                    }

                    //----- 例外ウィンドウ出力
                    Dispatcher.Invoke(() => {
                        var exceptionWindow = new ExceptionPopupWindow(message);
                        exceptionWindow.ShowDialog();

                        //----- アプリケーション終了
                        Current.Shutdown();
                    });
                }
            });
            var thread = new Thread(startFunction);
            thread.Name = "Engine Main Thread";
            thread.Start();
        }


        private MainWindow m_mainWindow;
    }
}
