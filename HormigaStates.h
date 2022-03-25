#pragma once
#include "StateMachine.h"
#include "Hormiga.h"
#define DISTANCIAVISTA 150
#define EATDIST		   20
class State_Hormiga_Deambular : public State<Hormiga>{

	private:

	//constructores vacios y por copia privados
	//para que nadie pueda crear la instancia
	State_Hormiga_Deambular (){}
	State_Hormiga_Deambular (const State_Hormiga_Deambular * &other){}
	State_Hormiga_Deambular & operator=(const State_Hormiga_Deambular&){}

	public:
	static State_Hormiga_Deambular * Instance();
	void Execute(Hormiga* hormiga);
	void Enter(Hormiga* hormiga);
	void Exit(Hormiga* hormiga);
	virtual char* GetStateName();

};

class State_Hormiga_Escapar : public State<Hormiga> {

private:

	//constructores vacios y por copia privados
	//para que nadie pueda crear la instancia
	State_Hormiga_Escapar() {}
	State_Hormiga_Escapar(const State_Hormiga_Escapar*& other) {}
	State_Hormiga_Escapar& operator=(const State_Hormiga_Escapar&) {}

public:
	static State_Hormiga_Escapar* Instance();
	void Execute(Hormiga* hormiga);
	void Enter(Hormiga* hormiga);
	void Exit(Hormiga* hormiga);
	virtual char* GetStateName();

};

class State_Hormiga_Bcomida : public State<Hormiga> {

private:

	//constructores vacios y por copia privados
	//para que nadie pueda crear la instancia
	State_Hormiga_Bcomida() {}
	State_Hormiga_Bcomida(const State_Hormiga_Bcomida*& other) {}
	State_Hormiga_Bcomida& operator=(const State_Hormiga_Bcomida&) {}

public:
	static State_Hormiga_Bcomida* Instance();
	void Execute(Hormiga* hormiga);
	void Enter(Hormiga* hormiga);
	void Exit(Hormiga* hormiga);
	virtual char* GetStateName();

};
