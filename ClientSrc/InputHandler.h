#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <QKeyEvent>
#include "Snake.h"

class IInputHandler
{
public:
    virtual ~IInputHandler() = default;
    virtual void handleKeyPress(QKeyEvent* event, Snake* snake) = 0;
};

class DefaultInputHandler : public IInputHandler{
    void handleKeyPress(QKeyEvent* event, Snake* snake) override;
};

#endif // INPUTHANDLER_H
