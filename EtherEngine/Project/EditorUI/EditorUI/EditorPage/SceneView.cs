using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using System.Windows;


namespace EditorUI {
    /// <summary>送受信メッセージ</summary>
    public enum SceneViewMessageType : byte { 
        Add = 0,
        Delete,
    }


    /// <summary>ViewModel</summary>
    public class SceneViewVM : INotifyCollectionChanged, IUserControlClose {
        public event NotifyCollectionChangedEventHandler? CollectionChanged;


        /// <summary>コンストラクタ</summary>
        /// <param name="sceneView">シーンビューのハンドル</param>
        /// <param name="size">初期シーンビューサイズ</param>
        public SceneViewVM(IntPtr sceneView, Vector2 size) {
            //----- 代入
            SceneViewTarget = sceneView; 

            //----- 生成時は即サイズが変更されたものとする
            NewWindowSize = new Vector2(size.X, size.Y);

            //----- 自身をメッセージとして送信
            EditorMessageQue<SceneViewMessageType, EditorAtomic<SceneViewVM>>.AddEngineMessage(new(SceneViewMessageType.Add, new(this, LockObject)));
        }
        /// <summary>削除時処理</summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        public void CloseEvent(object? sender, EventArgs e) {
            lock (LockObject) {
                EditorMessageQue<SceneViewMessageType, EditorAtomic<SceneViewVM>>.AddEngineMessage(new(SceneViewMessageType.Delete, new(this, LockObject)));
            }
        }


        /// <summary>ウィンドウの実際の描画部分</summary>
        public IntPtr SceneViewTarget { get; private set; }


        /// <summary>新しく設定されたサイズ</summary>
        public Vector2? NewWindowSize {
            get {
                var ret = m_newWindowSize;
                m_newWindowSize = null;
                return m_newWindowSize;
            }
            internal set {
                if (m_newWindowSize != value) {
                    m_newWindowSize = value;
                }
            }
        }


        /// <summary>保持しているID</summary>
        public EditorIDClass ID { get; private set; } = new();
        /// <summary>新しいウィンドウのサイズ</summary>
        private Vector2? m_newWindowSize = null;
        /// <summary>排他処理用オブジェクト</summary>
        private object LockObject { get; set; } = new();
    }
}
