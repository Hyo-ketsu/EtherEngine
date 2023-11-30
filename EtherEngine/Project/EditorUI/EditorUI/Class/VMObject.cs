using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace EditorUI {
    /// <summary>ロックを保持しながらVMにアクセスするためのクラス</summary>
    /// <typeparam name="ViewModelType"></typeparam>
    public class VMObject<ViewModelType> where ViewModelType : class {
        /// <summary>コンストラクタ</summary>
        /// <param name="data">保持するロック付きオブジェクト</param>
        public VMObject(AtomicData<ViewModelType> data) {
            Data = data;
        }
        public VMObject(ViewModelType vm) {
            Data = GetEditorWindow.AddCreateWindow<ViewModelType>(vm);
        }


        /// <summary>ロックを取得しながらアクセスする</summary>
        public ViewModelType Get { 
            get {
                var lockObject = Data.GetUILock();
                using (lockObject.Item1) {
                    return lockObject.Item2;
                }
            } 
            set {
                var lockObject = Data.GetUILock();
                using (lockObject.Item1) {
                    lockObject.Item2 = value;
                }
            }
        }
        /// <summary>ロックしないで取得</summary>
        public ViewModelType NoLockGet {
            get { return Data.NoLock; }
            set { Data.NoLock = value; }
        }
        /// <summary>保持しているViewModel</summary>
        private AtomicData<ViewModelType> Data { get; set; }
    }
}
