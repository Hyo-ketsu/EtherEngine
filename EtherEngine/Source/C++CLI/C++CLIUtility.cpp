#include <C++CLI/C++CLIUtility.h>
// @ MEMO : w_cahr����char�ɂ��Ă���̂ŃG���[�N��������
     

//----- ������ϊ��֐�
namespace EtherEngine {
    // .NET�������C++������ɕϊ�����
    std::string ManageToUn(String^ manage) {
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
    // C++�������.NET������ɕϊ�����
    String^ UnToManage(const std::string& un) {
        //----- �錾
        String^ ret;

        //----- �ϊ�
        ret = gcnew String(un.c_str());

        //----- �ԋp
        return ret;
    }
}
