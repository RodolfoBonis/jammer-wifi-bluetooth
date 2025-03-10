
#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include "config.h"
#include "mode_controller.h"

class ButtonHandler {
private:
    ModeController* modeController;
    unsigned long lastButtonPressTime;

public:
    ButtonHandler();
    void init();
    void setModeController(ModeController* modeCtrl);
    void update();
    bool checkButtonsDebounced();
};

#endif // BUTTON_HANDLER_H