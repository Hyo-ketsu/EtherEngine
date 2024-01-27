using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using EditorUI;
using EtherEngine;


namespace EditorMain {
    /// <summary>エディターのエントリーポイント</summary>
    internal class EditorMain {
        [STAThread]
        static public void Main() {
            //----- アプリケーションを始動
            var application = new EtherEngineApplication();
            application.Init(EtherEngineMainFunction.MainFunction);
            application.Run();

            //----- 終了処理
            EditorApplication.Get.GameEnd();
        }
    }
}
