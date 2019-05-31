#ifndef AUTOMTHREAD_H
#define AUTOMTHREAD_H


#include "helper.h"
#include "controller.h"
#include "parcours.h"
#include "window.h"
#include "solvers.h"




void automThread(Window* parent,std::shared_ptr<solver>);

void envoisInstructions(instructions,Window*);

void executeInstructions(Window*);

#endif // AUTOMTHREAD_H
