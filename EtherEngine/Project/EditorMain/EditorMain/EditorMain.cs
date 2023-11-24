using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using EditorUI;


namespace EditorMain {
    /// <summary>エディターのエントリーポイント</summary>
    internal class EditorMain {
        [STAThread]
        static public void Main() {
#if _DEBUG
            try {
                //----- アプリケーションを始動
                var application = new EditorUI.EtherEngineApplication(EtherEngine.EtherEngineMainFunction.MainFunction);
                application.Run();
            }
            catch (System.Runtime.InteropServices.SEHException exception) { // エディターを開始出来ない例外をキャッチ
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
                var exceptionWindow = new ExceptionPopupWindow(message);
                exceptionWindow.ShowDialog();
            }
#else
            //----- アプリケーションを始動
            var application = new EditorUI.EtherEngineApplication(EtherEngine.EtherEngineMainFunction.MainFunction);
            application.Run();
#endif
        }
    }
}
