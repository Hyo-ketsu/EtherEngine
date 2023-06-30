#ifndef I_PROCEDUREGAMEWINDOW_H
#define I_PROCEDUREGAMEWINDOW_H


namespace EtherEngine {
    namespace Procedure {
        // マウス座標入力等の処理を行う
        void BaseFunction(void);
    }


    LRESULT CALLBACK WindowGameProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
}


#endif // !I_PROCEDUREGAMEWINDOW_H
