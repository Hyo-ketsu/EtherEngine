using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Threading;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Runtime.CompilerServices;
using System.Threading;


namespace EditorUI {
    /// <summary>エンジン側からウィンドウを追加するクラス</summary>
    public static class CreateEditorWindow {
        /// <summary>型を与えて生成する</summary>
        /// <typeparam name="WindowType">作成するWindowの型</typeparam>
        /// <param name="isDialog">Dialogで表示を行うか(Default : false)</param>
        public static void AddCreateWindow<WindowType>(bool isDialog = false) where WindowType : Window, new() {
            AddCreateWindow(() => { return new WindowType(); }, isDialog);
        }
        /// <summary>ラムダを与えて生成する</summary>
        /// <param name="windowCreate">生成に使用するデリゲーター</param>
        /// <param name="isDialog">Dialogで表示を行うか(Default : false)</param>
        public static void AddCreateWindow(Func<Window> windowCreate, bool isDialog = false) {
            Application.Current.Dispatcher.Invoke(() => {
                var createWindow = windowCreate();

                //----- 生成して表示する
                if (isDialog) {
                    createWindow.ShowDialog();
                }
                else {
                    createWindow.Show();
                }
            });
        }
        /// <summary>
        /// <para>型を与えて生成する</para>
        /// <para>@ Memo : ウィンドウの生成が完了するまで待機します</para>
        /// </summary>
        /// <typeparam name="ViWindowTypeewModelType">作成するWindowの型</typeparam>
        /// <typeparam name="ViewModelType">取得するViewModelの型</typeparam>
        /// <param name="isDialog">Dialogで表示を行うか(Default : false)</param>
        /// <returns>取得したViewModel</returns>
        public static AtomicData<ViewModelType>? AddCreateWindow<WindowType, ViewModelType>(bool isDialog = false) 
            where WindowType : Window, new() 
            where ViewModelType : class {
            return AddCreateWindow<ViewModelType>(() => { return new WindowType(); });
        }
        /// <summary>
        /// <para>ラムダを与えて生成する</para>
        /// <para>@ Memo : ウィンドウの生成が完了するまで待機します</para>
        /// </summary>
        /// <typeparam name="ViewModelType">生成するウィンドウの型</typeparam>
        /// <param name="windowCreate">生成に使用するデリゲーター</param>
        /// <param name="isDialog">Dialogで表示を行うか(Default : false)</param>
        /// <returns>取得したViewModel</returns>
        public static AtomicData<ViewModelType>? AddCreateWindow<ViewModelType>(Func<Window> windowCreate, bool isDialog = false) 
            where ViewModelType : class {
            //----- 変数宣言
            AtomicData<ViewModelType>? ret = null;
            bool isLock = true;

            //----- ウィンドウ生成
            Application.Current.Dispatcher.Invoke(() => {
                var createWindow = windowCreate();

                //----- 生成して表示する
                if (isDialog) {
                    createWindow.ShowDialog();
                }
                else {
                    createWindow.Show();
                }

                //----- ViewModel取得
                ret = GetEditorWindow.GetCreateWindow<ViewModelType>();

                isLock = false;
            });

            //----- 生成待ち
            while (isLock) { }

            //----- 返却
            return ret;
        }
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
        /// <summary>ViewModelを追加する</summary>
        /// <typeparam name="ViewModelType">追加するViewModelの型</typeparam>
        /// <param name="viewModel">UIに追加したいViewModel</param>
        /// <returns>追加したViewModelへのアクセス</returns>
        internal static AtomicData<ViewModelType> AddCreateWindow<ViewModelType>(ViewModelType viewModel) where ViewModelType : class {
            lock (ms_lockObject) {
                //----- 生成して追加する
                var createViewModel = new AtomicData<object>(viewModel);
                ms_createViewModel.Add(createViewModel);
                return createViewModel.GetCast<ViewModelType>();
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
        /// <summary>
        /// <para>追加されたViewModelを取得する</para>
        /// <para>@ Memo : 新しく追加されたものから取得します</para>
        /// </summary>
        /// <typeparam name="ViewModelType">取得するViewModelの型</typeparam>
        /// <returns></returns>
        public static AtomicData<ViewModelType>? GetCreateWindow<ViewModelType>() where ViewModelType : class {
            //----- 変数宣言
            AtomicData<ViewModelType> ret = null;

            //----- リストから ViewModelType に合致したものを返却
            lock (ms_lockObject) {
                //----- 変数宣言
                int i = ms_createViewModel.Count - 1;

                //----- リストを全て逆から参照
                for (; i >= 0; i--) {
                    var viewModel = ms_createViewModel[i].GetCast<ViewModelType>();
                    if (viewModel != null) {
                        ret = viewModel;
                        break;
                    }
                }

                //----- 既に参照した要素の削除
                if (ret != null) {
                    ms_createViewModel.RemoveAt(i);
                }
            }

            //----- 返却
            return ret;
        }


        /// <summary>ロックオブジェクト</summary>
        private static object ms_lockObject = new();
        /// <summary>保持しているViewModel</summary>
        private static List<AtomicData<object>> ms_createViewModel = new();
    }
}
