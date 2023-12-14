using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace EditorUI {
    /// <summary>ユーザーコントロールが削除された際の処理</summary>
    internal interface IUserControlClose {
        public void CloseEvent(object? sender, EventArgs e);
    }
}
