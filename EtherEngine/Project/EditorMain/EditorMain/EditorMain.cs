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
            //----- アプリケーションを始動
            var application = new EditorUI.EtherEngineApplication(EtherEngine.EtherEngineMainFunction.MainFunction);
            application.Run();

            //----- 終了処理
            EtherEngine.Wrapper.EditorApplication.IsGameLoop = false;
        }
    }
}
