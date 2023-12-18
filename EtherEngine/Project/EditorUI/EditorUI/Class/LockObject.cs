using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Navigation;


namespace EditorUI {
    /// <summary>UIとエンジンそれぞれでロックを行うクラス</summary>
    public abstract class LogicLockObject : IDisposable {
        /// <summary>コンストラクタ</summary>
        /// <param name="lockObject">ロックに使用するオブジェクト</param>
        public LogicLockObject(object lockObject) {
            lock (this) {
                //----- フィールドの初期化
                m_lockObject = lockObject;

                //----- ロックを取得
                Monitor.Enter(m_lockObject);
            }
        }
        /// <summary>ファイナライザー</summary>
        ~LogicLockObject() {
            // @ MEMO : ファイナライザでDisposeが呼ばれる = GCが行われるまでロックしっぱなし。警告する？
            Dispose();
        }
        /// <summary></summary>
        public void Dispose() {
            if (m_isDispose) return;
            lock (this) {
                //----- ロックを解除する
                var isGetLock = Monitor.TryEnter(m_lockObject);
                if (isGetLock) Monitor.Exit(m_lockObject); Monitor.Exit(m_lockObject);  // TryEnterの分のロックを解除する
                m_isDispose = true;
            }
        }


        private bool m_isDispose = false;
        /// <summary>ロックオブジェクト</summary>
        private object m_lockObject;
    }


    /// <summary>エンジン側ロックオブジェクト</summary>
    public class EngineLock : LogicLockObject {
        /// <summary>コンストラクタ</summary>
        /// <param name="lockObject">ロックに使用するオブジェクト</param>
        public EngineLock(object lockObject)
            : base(lockObject) { 
        }
    }
    /// <summary>UI側ロックオブジェクト</summary>
    internal class UILock : LogicLockObject {
        /// <summary>コンストラクタ</summary>
        /// <param name="lockObject">ロックに使用するオブジェクト</param>
        public UILock(object lockObject)
            : base(lockObject) {
        }
    }


    /// <summary>エンジン側とUI側で使用されるオブジェクト</summary>
    /// <typeparam name="DataType">保持している型</typeparam>
    public class EditorAtomic<DataType> {
        /// <summary>コンストラクタ</summary>
        /// <param name="data">保持させるデータ</param>
        /// <param name="lockObject">ロックに使用するobject</param>
        public EditorAtomic(DataType data, object lockObject) {
            m_data = data;
            m_lockObject = lockObject;
        }


        /// <summary>データをキャストして渡す</summary>
        /// <typeparam name="CastDataType"></typeparam>
        /// <returns></returns>
        public EditorAtomic<CastDataType>? GetCast<CastDataType>() where CastDataType : class,DataType {
            var data = m_data as CastDataType;
            return data != null ? new(data, m_lockObject) : null;
        }


        /// <summary>エンジン側ロックを獲得する</summary>
        /// <returns></returns>
        public (EngineLock,DataType) GetEngineLock() {
            return new(new EngineLock(m_lockObject), m_data);
        }
        /// <summary>UI側ロックを獲得する</summary>
        /// <returns></returns>
        internal (UILock,DataType) GetUILock() {
            return new(new UILock(m_lockObject), m_data);
        }
        /// <summary>ロックしないでデータを取得する</summary>
        /// <returns></returns>
        public DataType NoLock {
            get { return m_data; }
            set { m_data = value; }
        }


        /// <summary>保持しているデータ</summary>
        private DataType m_data;
        /// <summary>ロックに使用するオブジェクト</summary>
        private object m_lockObject;
        private int m_lockCount;
    }
}
