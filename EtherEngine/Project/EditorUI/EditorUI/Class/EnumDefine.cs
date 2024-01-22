using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace EditorUI {
    /// <summary>メッセージの種類を指定する</summary>
    public enum MessageType {
        /// <summary>特に何も指定しない</summary>
        None = 0,
        /// <summary>何かのメッセージ</summary>
        Info,
        /// <summary>警告</summary>
        Warning,
        /// <summary>エラー</summary>
        Error,
        /// <summary>ビルド時の出力(警告やエラーではないもの)</summary>
        BuildMessage,
        /// <summary>使用ユーザーが発するメッセージ</summary>
        UserMessage,
    }


    /// <summary>ビルド種類</summary>
    public enum BuildConfiguration {
        /// <summary>完全デバッグ</summary>
        Debug = 0,
        /// <summary>製品リリース</summary>
        Release,
    }
}
