using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;


namespace EditorUI {
    /// <summary>UIとエンジンそれぞれでロックを行うクラス</summary>
    public abstract class LogicLockObject : IDisposable {
        public LogicLockObject() {
            //----- ロックを行う
            while (GetLock() > 0 && ms_lockObject.TryEnterWriteLock(10) == false) {
                ms_lockObject.EnterWriteLock();
            }
            AddLock(1);
        }
        /// <summary></summary>
        public void Dispose() {
            //----- ロックを解除する
            ms_lockObject.ExitWriteLock();
            AddLock(-1);
        }


        /// <summary>ロック数を加算する</summary>
        /// <param name="addValue">加算する箇所</param>
        protected abstract void AddLock(int addValue);
        /// <summary>ロック数を取得する</summary>
        /// <returns></returns>
        protected abstract int GetLock();


        /// <summary>ロックオブジェクト</summary>
        static protected ReaderWriterLockSlim ms_lockObject = new();
        /// <summary>エンジン側でのロックがされているか</summary>
        static protected int m_engineLock = 0;
        /// <summary>UI側でのロックがされているか</summary>
        static protected int m_uiLock = 0;
    }


    public class EngineLock : LogicLockObject {
        protected override void AddLock(int addValue) {
            m_engineLock += addValue;
        }
        protected override int GetLock() {
            return m_engineLock;
        }
    }
    internal class UILock : LogicLockObject {
        protected override void AddLock(int addValue) {
            m_uiLock += addValue;
        }
        protected override int GetLock() {
            return m_uiLock;
        }
    }


    /// <summary>エンジン側とUI側で使用されるオブジェクト</summary>
    /// <typeparam name="DataType">保持している型</typeparam>
    public class AtomicData<DataType> {
        /// <summary>コンストラクタ</summary>
        /// <param name="data">保持させるデータ</param>
        public AtomicData(DataType data) {
            m_data = data;
        }


        public AtomicData<CastDataType> GetCast<CastDataType>() where CastDataType : class,DataType {
            AtomicData<CastDataType> ret = new(m_data as CastDataType);
            return ret;
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


        /// <summary>保持しているデータ</summary>
        private DataType m_data;
    }
}
