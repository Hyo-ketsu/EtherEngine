using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace EditorUI {
    /// <summary>非マネージのラムダをラップするインターフェース</summary>
    public interface ILambdaWrapper<LambdaType> {
        LambdaType Lambda();
    }
    /// <summary>非マネージのラムダをラップするインターフェース</summary>
    public interface ILambdaWrapper {
        void Lambda();
    }
}
