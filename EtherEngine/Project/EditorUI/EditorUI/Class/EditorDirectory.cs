using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace EditorUI {
    /// <summary>エディターのカレントディレクトリを保持しておくクラス</summary>
    internal static class EditorDirectory {
        internal static string Directory { get; set; } = new("");
    }
}
