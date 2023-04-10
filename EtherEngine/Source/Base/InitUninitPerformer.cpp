#include <Base/InitUninitPerformer.h>

using namespace EtherEngine;


// �����������A�I�������̒ǉ�
void InitUninitPerformer::AddInitUninit(std::function<void(void)> init, std::function<void(void)> uninit) {
    m_init.push_front(init);
    m_uninit.push_back(uninit);
}


// �������������s
void InitUninitPerformer::Init(void) {
    for (auto& it : m_init) {
        it();
    }
}
// �I���������s
void InitUninitPerformer::UnInit(void) {
    for (auto& it : m_uninit) {
        it();
    }
}
