#include <Base/InitUninitPerformer.h>

using namespace EtherEngine;


// 初期化処理、終了処理の追加
void InitUninitPerformer::AddInitUninit(std::function<void(void)> init, std::function<void(void)> uninit) {
    m_init.push_front(init);
    m_uninit.push_back(uninit);
}


// 初期化処理実行
void InitUninitPerformer::Init(void) {
    for (auto& it : m_init) {
        it();
    }
}
// 終了処理実行
void InitUninitPerformer::UnInit(void) {
    for (auto& it : m_uninit) {
        it();
    }
}
