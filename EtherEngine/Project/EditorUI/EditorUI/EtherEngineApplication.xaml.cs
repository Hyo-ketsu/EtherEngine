using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
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
        public delegate void EtherEngineMainFunction(IntPtr hInstance, int windowSizeX, int windowSizeY, string cmdLine, int nShowCmd);

        public EtherEngineApplication(EtherEngineMainFunction mainFunction) {
            //----- UI関連処理
            Dispatcher.Invoke(() => {
                m_mainWindow = new MainWindow();
                m_mainWindow.Show();
            });

            //----- メイン関数
            Dispatcher.Invoke(() => {
                while (m_mainWindow == null) { }

                var interopHelper = new WindowInteropHelper(Current.MainWindow);
                mainFunction(interopHelper.Handle, (int)m_mainWindow.Width, (int)m_mainWindow.Height, "", 0);
            });
        }


        private MainWindow m_mainWindow;
    }
}
