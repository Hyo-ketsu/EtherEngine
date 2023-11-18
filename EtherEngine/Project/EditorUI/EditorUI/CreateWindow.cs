using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace EditorUI {
    /// <summary>エンジン側からウィンドウを追加するクラス</summary>
    public static class CreateWindow {
        /// <summary>ウィンドウを追加する</summary>
        /// <param name="window">UIに追加したいウィンドウ</param>
        /// <returns>追加したウィンドウへのアクセス</returns>
        public static AtomicData<Window> AddCreateWindow(Window window) {
            lock (ms_lockObject) {
                //----- 生成して追加する
                var createWindow = new AtomicData<Window>(window);
                ms_createWindows.Add(createWindow);
                return createWindow;
            }
        }


        /// <summary>追加されたウィンドウを取得する</summary>
        /// <returns></returns>
        public static AtomicData<Window>? GetCreateWindow() {
            lock (ms_lockObject) {
                //----- 
                if (ms_createWindows.Count == 0) { return null; }

                //----- ウィンドウを1つ取得する
                var window = ms_createWindows[0];
                ms_createWindows.RemoveAt(0);
                return window;
            }
        }


        /// <summary>ロックオブジェクト</summary>
        private static object ms_lockObject = new();
        /// <summary>保持しているウィンドウ</summary>
        private static List<AtomicData<Window>> ms_createWindows = new();
    }


    /// <summary>UI側からのウィンドウを取得するクラス</summary>
    public static class GetWindow {
        /// <summary>ウィンドウを追加する</summary>
        /// <param name="window">UIに追加したいウィンドウ</param>
        /// <returns>追加したウィンドウへのアクセス</returns>
        internal static AtomicData<Window> AddCreateWindow(Window window) {
            lock (ms_lockObject) {
                //----- 生成して追加する
                var createWindow = new AtomicData<Window>(window);
                ms_createWindows.Add(createWindow);
                return createWindow;
            }
        }


        /// <summary>追加されたウィンドウの名前のリストを取得する</summary>
        /// <returns>追加されたウィンドウのリスト</returns>
        public static List<string> GetCreateWindowCount() {
            //----- 変数宣言
            List<string> ret = new();

            //----- window名を全て舐める
            foreach (var window in ms_createWindows) {
                ret.Add(window.GetUILock().Item2.Name);
            }

            //----- 返却
            return ret;
        }
        /// <summary>追加されたウィンドウを取得する</summary>
        /// <param name="windowType">取得するウィンドウの型</param>
        /// <returns></returns>
        public static AtomicData<WindowType>? GetCreateWindow<WindowType>() where WindowType : Window {
            //----- リストから windowType に合致したものを返却
            lock (ms_lockObject) {
                foreach (var createWindow in ms_createWindows) {
                    if (createWindow.GetType() == typeof(WindowType)) {
                        return createWindow.GetCast<WindowType>();
                    }
                }
            }

            return null;
        }


        /// <summary>ロックオブジェクト</summary>
        private static object ms_lockObject = new();
        /// <summary>保持しているウィンドウ</summary>
        private static List<AtomicData<Window>> ms_createWindows = new();
    }
}
