#include "stdafx.h"
#include "HormigaStates.h"
#include "Tablero.h"
#include "utils.h"
State_Hormiga_Deambular*  State_Hormiga_Deambular::Instance(){
		static State_Hormiga_Deambular instance;
		return &instance;
}


/////////////////////////////////////////////////////////////////////////////
//Deambular
/////////////////////////////////////////////////////////////////////////////

void State_Hormiga_Deambular::Enter(Hormiga* hormiga) {


}

void State_Hormiga_Deambular::Execute(Hormiga* hormiga) {

	//Calculamos si hay que cambiar de estado
	Tablero* t = hormiga->GetTablero();

	//vemos si hay una hormiga cerca 
	Comida* g = t->GetNearestVisibleFood(hormiga);
	Matador* m = t->GetNearestVisibleMtador(hormiga);

	if (g != NULL) {
		float dist = Utils::GetVecDistance(g->GetPosition(), hormiga->GetPosition());
		if (dist < DISTANCIAVISTA)//cambiamos al estado buscar comida
			hormiga->GetFSM()->ChangeState(State_Hormiga_Bcomida::Instance());
	}

	if (m != NULL) {
		float dist = Utils::GetVecDistance(m->GetPosition(), hormiga->GetPosition());
		if (dist < 80)//cambiamos al estado escapar
			hormiga->GetFSM()->ChangeState(State_Hormiga_Escapar::Instance());
	}

	//calculamos si vamos a cambiar de dirección
	if (Utils::GetRandomIntValue(0, 100) == 0) {
		hormiga->ChangeDirection();
	}

	hormiga->Move();


}

void State_Hormiga_Deambular::Exit(Hormiga* hormiga) {


}

char* State_Hormiga_Deambular::GetStateName() {
	return "Deambular";
}

State_Hormiga_Escapar* State_Hormiga_Escapar::Instance() {
	static State_Hormiga_Escapar instance;
	return &instance;
}

/////////////////////////////////////////////////////////////////////////////
//Escapar
/////////////////////////////////////////////////////////////////////////////

void State_Hormiga_Escapar::Enter(Hormiga* hormiga) {



}

void State_Hormiga_Escapar::Execute(Hormiga* hormiga) {


	//Escapamos del matador mas cercano
	Tablero* t = hormiga->GetTablero();
	Matador* g = t->GetNearestVisibleMtador(hormiga);

	//guardamos el objetivo en el objeto matador
	if (g != NULL)
		hormiga->SetTargetM(g);
	else
		hormiga->GetFSM()->ChangeState(State_Hormiga_Deambular::Instance());

	//si estamos muy cerca escapamos
	float dist = Utils::GetVecDistance(hormiga->GetPosition(), hormiga->GetTargetM()->GetPosition());
	if (dist < 80) {
		hormiga->GetFSM()->ChangeState(State_Hormiga_Escapar::Instance());
	}
	//lo pierde de vista
	if (dist > DISTANCIAVISTA) {
		hormiga->GetFSM()->ChangeState(State_Hormiga_Deambular::Instance());
	}

	


	//Update chase direction
	hormiga->ChaseScape();
	//move
	hormiga->Move();


}

void State_Hormiga_Escapar::Exit(Hormiga* matador) {


}

char* State_Hormiga_Escapar::GetStateName() {
	return "Escapar";
}


State_Hormiga_Bcomida* State_Hormiga_Bcomida::Instance() {
	static State_Hormiga_Bcomida instance;
	return &instance;
}


/////////////////////////////////////////////////////////////////////////////
//BuscarComida
/////////////////////////////////////////////////////////////////////////////

void State_Hormiga_Bcomida::Enter(Hormiga* hormiga) {



}

void State_Hormiga_Bcomida::Execute(Hormiga* hormiga) {


	//buscamos la hormiga mas cercana
	Tablero* t = hormiga->GetTablero();
	Comida* g = t->GetNearestVisibleFood(hormiga);
	//guardamos el objetivo en el objeto matador
	if (g != NULL)
		hormiga->SetTarget(g);
	else
		hormiga->GetFSM()->ChangeState(State_Hormiga_Deambular::Instance());

	//si estamos muy cerca lo comemos

	float dist = Utils::GetVecDistance(hormiga->GetPosition(), hormiga->GetTarget()->GetPosition());
	if (dist < EATDIST) {
		hormiga->GetTablero()->KillComida(hormiga->GetTarget());
		hormiga->GetFSM()->ChangeState(State_Hormiga_Deambular::Instance());
	}
	//lo pierde de vista
	if (dist > DISTANCIAVISTA) {
		hormiga->GetFSM()->ChangeState(State_Hormiga_Deambular::Instance());
	}


	//Update chase direction
	hormiga->Chase();
	//move
	hormiga->Move();


}

void State_Hormiga_Bcomida::Exit(Hormiga* matador) {


}

char* State_Hormiga_Bcomida::GetStateName() {
	return "Buscar Comida";
}