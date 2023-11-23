#include <EngineLibrary/ConvertManage.h>


namespace EtherEngine {
    // ������ϊ�
    std::string ManageToUnmanage::String(System::String^ manage) {
        //----- �錾�E�擾
        std::string ret;
        auto wchars = manage->ToCharArray();

        //----- �m��
        ret.reserve(wchars->Length);

        //----- �ϊ�
        for (int i = 0; i < wchars->Length; i++) {
            ret.push_back(static_cast<char>(wchars[i]));
        }

        return ret;
    }

    // �p�X�ϊ�
    PathClass ManageToUnmanage::Path(PathString^ manage) {
        return PathClass(String(manage));
    }
}
