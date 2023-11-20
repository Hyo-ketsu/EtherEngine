using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EditorUI;


namespace EditorMain {
    /// <summary>エディターのエントリーポイント</summary>
    internal class EditorMain {
        [STAThread]
        static public void Main() {
#if DEBUG
            try {
                //----- アプリケーションを始動
                var application = new EditorUI.EtherEngineApplication(EtherEngine.EtherEngineMainFunction.MainFunction);
                application.Run();
            }
            catch (System.Runtime.InteropServices.SEHException exception) {
                //----- エディターを開始出来ない例外をキャッチ
                var exceptionWindow = new ExceptionPopupWindow(exception.ToString());
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
