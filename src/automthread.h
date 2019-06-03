#ifndef AUTOMTHREAD_H
#define AUTOMTHREAD_H

#define Le_robot_n_est_pas_arrive _parent->helper.m_controller->getRobotPosition().second != 3
#define Tant_que while
#define Aglorithme_de_resolution void automThread(Window* _parent, std::shared_ptr<solver> _solver)
#define Carte_obstacle camStruct informationCamera
#define Relais_transporte_les_informations_vers_le_controleur std::this_thread::sleep_for(std::chrono::duration<double,std::milli>(_parent->helper.m_controller->getWaitTime()))
#define Relais_transporte_les_informations_vers_le_robot envoisInstructions(prochainesInstructions,_parent);std::this_thread::sleep_for(std::chrono::duration<double,std::milli>(_parent->helper.m_controller->getWaitTime()/2.0));
#define Carte_instruction instructions prochainesInstructions
#define Controleur _solver
#define Robot_execute_instructions_et_correcteur_corrige executeInstructions(_parent)
#define Camera _parent->helper.m_controller
#define Informations_disponibles informationCamera,_parent->helper.m_controller

#include "helper.h"
#include "controller.h"
#include "parcours.h"
#include "window.h"
#include "solvers.h"




void automThread(Window* parent,std::shared_ptr<solver> );

void envoisInstructions(instructions,Window*);

void executeInstructions(Window*);

#endif // AUTOMTHREAD_H
