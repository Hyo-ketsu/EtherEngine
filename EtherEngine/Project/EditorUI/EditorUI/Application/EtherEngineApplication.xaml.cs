using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
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
using EtherEngine;
using Microsoft.Build.Locator;


namespace EditorUI {
    /// <summary>エディターを表現するApplication</summary>
    public partial class EtherEngineApplication : Application {
        public delegate void EtherEngineMainFunction(string cmdLine, int nShowCmd);


        /// <summary>コンストラクタ </summary>
        public EtherEngineApplication() {
            InitializeComponent();
        }


        /// <summary>初期化を行う</summary>
        /// <param name="mainFunction">呼び出すメイン関数</param>
        public void Init(EtherEngineMainFunction mainFunction) {
            //----- MSBuildのランタイム登録
            MSBuildLocator.RegisterDefaults();

            //----- 変数宣言
            MainWindow? mainWindow = null;

            //----- エディターのカレントディレクトリ設定
            EditorDirectory.Directory = System.IO.Directory.GetCurrentDirectory();

            //----- UI関連処理
            Dispatcher.Invoke(() => {
                //----- 内部的なメインウィンドウ立ち上げ
                mainWindow = new MainWindow();

                //----- スタートアップ
                var startupWindow = new StartupWindow();
                startupWindow.ShowDialog();

                //----- キャンセルだったら終了する
                if (IsCancelStartup) {
                    mainWindow.Close(); return; 
                }

                //----- エディターのメインウィンドウ立ち上げ
                mainWindow.Show();
            });

            //----- メイン関数スレッド立ち上げ
            var startFunction = new ThreadStart(() => {
                try {
                    //----- メインウィンドウが立ち上がったら続行、キャンセルされたら終了
                    while (mainWindow == null && IsCancelStartup == false) { }
                    if (IsCancelStartup) return;

                    //----- 初期化
                    EditorExtensionInit.Init(Assembly.GetExecutingAssembly());

                    //----- 初期シーン作成
                    SceneLoader.Get.MoveScene(new EditorDefaultScene(""));

                    //----- メイン関数の実行
                    mainFunction("", 0);
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
            m_thread = new(startFunction);
            m_thread.Name = "Engine Main Thread";
            m_thread.Start();
        }


        /// <summary>Startupせずに終了したか</summary>
        public bool IsCancelStartup { get { return m_isCancelStartup; } set { m_isCancelStartup = value; } }
        private volatile bool m_isCancelStartup = false;
        /// <summary>保持しているエンジンスレッド</summary>
        private Thread? m_thread;
    }
}
