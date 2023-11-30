using System;
using System.Collections.Generic;
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
        public LogicLockObject() {
            lock (this) {
                if (ms_isThisThreadLock.Value == true) return;

                Monitor.Enter(ms_lockObject);
            }
        }
        /// <summary>ファイナライザー</summary>
        ~LogicLockObject() {
            Dispose();
        }
        /// <summary></summary>
        public void Dispose() {
            if (m_isDispose) return;
            lock (this) {
                //----- ロックを解除する
                var isGetLock = Monitor.TryEnter(ms_lockObject);
                if (isGetLock) Monitor.Exit(ms_lockObject);
                m_isDispose = true;
            }
        }


        private bool m_isDispose = false;
        /// <summary>ロックオブジェクト</summary>
        static protected object ms_lockObject = new();
        /// <summary>自身のスレッドでロックされているか</summary>
        static protected ThreadLocal<bool> ms_isThisThreadLock = new(false);
    }


    public class EngineLock : LogicLockObject {
    }
    internal class UILock : LogicLockObject {
    }


    /// <summary>エンジン側とUI側で使用されるオブジェクト</summary>
    /// <typeparam name="DataType">保持している型</typeparam>
    public class AtomicData<DataType> {
        /// <summary>コンストラクタ</summary>
        /// <param name="data">保持させるデータ</param>
        public AtomicData(DataType data) {
            m_data = data;
        }


        public AtomicData<CastDataType>? GetCast<CastDataType>() where CastDataType : class,DataType {
            var data = m_data as CastDataType;
            return data != null ? new(data) : null;
        }


        /// <summary>エンジン側ロックを獲得する</summary>
        /// <returns></returns>
        public (EngineLock,DataType) GetEngineLock() {
            return new(new EngineLock(), m_data);
        }
        /// <summary>UI側ロックを獲得する</summary>
        /// <returns></returns>
        internal (UILock,DataType) GetUILock() {
            return new(new UILock(), m_data);
        }
        /// <summary>ロックしないでデータを取得する</summary>
        /// <returns></returns>
        public DataType NoLock {
            get { return m_data; }
            set { m_data = value; }
        }


        /// <summary>保持しているデータ</summary>
        private DataType m_data;
    }
}
