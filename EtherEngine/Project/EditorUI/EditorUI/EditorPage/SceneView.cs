using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using System.Windows;


namespace EditorUI {
    /// <summary>ViewModel</summary>
    public class SceneViewVM : INotifyCollectionChanged {
        public event NotifyCollectionChangedEventHandler? CollectionChanged;


        /// <summary>コンストラクタ</summary>
        /// <param name="sceneView">シーンビューのハンドル</param>
        /// <param name="size">初期シーンビューサイズ</param>
        public SceneViewVM(IntPtr sceneView, Vector2 size) {
            //----- 代入
            SceneViewTarget = sceneView; 

            //----- 生成時は即サイズが変更されたものとする
            NewWindowSize = new Vector2(size.X, size.Y);
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


        /// <summary>新しいウィンドウのサイズ</summary>
        private Vector2? m_newWindowSize = null;
    }
}
