using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;


namespace EditorUI {
    /// <summary>エンジン側からウィンドウを追加するクラス</summary>
    public static class CreateEditorWindow {
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


    /// <summary>UI側からのViewModelを取得するクラス</summary>
    public static class GetEditorWindow {
        /// <summary>ViewModelを追加する</summary>
        /// <param name="viewModel">UIに追加したいViewModel</param>
        /// <returns>追加したViewModelへのアクセス</returns>
        internal static AtomicData<object> AddCreateWindow(object viewModel) {
            lock (ms_lockObject) {
                //----- 生成して追加する
                var createViewModel = new AtomicData<object>(viewModel);
                ms_createViewModel.Add(createViewModel);
                return createViewModel;
            }
        }


        /// <summary>追加されたViewModelの名前のリストを取得する</summary>
        /// <returns>追加されたViewModelのリスト</returns>
        public static List<string> GetCreateWindowCount() {
            //----- 変数宣言
            List<string> ret = new();

            //----- ViewModel名を全て舐める
            foreach (var viewModel in ms_createViewModel) {
                ret.Add(viewModel.GetUILock().Item2.GetType().Name);
            }

            //----- 返却
            return ret;
        }
        /// <summary>追加されたViewModelを取得する</summary>
        /// <typeparam name="ViewModelType">取得するViewModelの型</typeparam>
        /// <returns></returns>
        public static AtomicData<ViewModelType>? GetCreateWindow<ViewModelType>() where ViewModelType : class {
            //----- リストから ViewModelType に合致したものを返却
            lock (ms_lockObject) {
                foreach (var createViewModel in ms_createViewModel) {
                    if (createViewModel.GetType() == typeof(ViewModelType)) {
                        return createViewModel.GetCast<ViewModelType>();
                    }
                }
            }

            return null;
        }


        /// <summary>ロックオブジェクト</summary>
        private static object ms_lockObject = new();
        /// <summary>保持しているViewModel</summary>
        private static List<AtomicData<object>> ms_createViewModel = new();
    }
}
