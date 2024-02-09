using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using EtherEngine;


namespace EditorUI {
    [InspectorTypeHeaderAttribute(typeof(BaseObject), typeof(InspectorExtensionBaseObject))]
    public class InspectorExtensionBaseObject : InspectorExtension {
        public override FrameworkElement GetFramework(object showObject) {
            var baseObject = showObject as BaseObject;
            var ret = new InspectorHeaderBaseObject();
            ret.BaseObject = baseObject;

            return ret;
        }
    }
}
