#include "automthread.h"
#include <thread>



Aglorithme_de_resolution
{
    Tant_que(Le_robot_n_est_pas_arrive)
    {

        Carte_obstacle = Camera->construireCarteObstacle();
        Relais_transporte_les_informations_vers_le_controleur;
        Carte_instruction = Controleur->calculProchainesInstructions(Informations_disponibles);
        Relais_transporte_les_informations_vers_le_robot;
        Robot_execute_instructions_et_correcteur_corrige;
    }
}


void envoisInstructions(instructions _instructions,Window* _parent)
{
    while(_instructions.size())
    {
        _parent->keyPressEvent(&(_instructions.front()));
        _instructions.pop();
    }
}

void executeInstructions(Window* _parent)
{
    QKeyEvent executeInstructionsEvent(QEvent::KeyPress,Qt::Key_Return,Qt::NoModifier);
    _parent->keyPressEvent(&(executeInstructionsEvent));
}



