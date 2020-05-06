#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "tipos.h"
#include "automatas.h"

using namespace std;

bool EsIdentificador(ifstream& fuente, ulong& control, string& lexema) {
	// -- Definimos el alfabeto de entrada, especial = _
	typedef enum Sigma { Letra, Digito, Especial, Otro };

	auto CarASimbolo = [](auto& c) {
		Sigma t = Otro;

		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
			t = Letra;
		}
		else if (c >= '0' && c <= '9') {
			t = Digito;
		}
		else if (c == '_') {
			t = Especial;
		}

		return t;
	};

	// -- Definimos Delta
	std::map<tuple<ushort, Sigma>, ushort> delta = {
		//		 q	 x	simbolo	 ->	q
			{	{0,		Letra	},	1},
			{	{0,		Digito	},	2},
			{	{0,		Especial},	2},
			{	{0,		Otro	},	2},

			{	{1,		Letra	},	1},
			{	{1,		Digito	},	1},
			{	{1,		Especial},	1},
			{	{1,		Otro	},	3},

			{	{2,		Letra	},	2},
			{	{2,		Digito	},	2},
			{	{2,		Especial},	2},
			{	{2,		Otro	},	2},
	};

	// -- Definimos los estados finales, invalidos y el inicial
	const ushort estadoTerminal = 3;
	const ushort estadoMuerto = 2 ;
	const ushort q0 = 0;

	bool esIdentificador = false;

	lexema = "";

	// ==== Buscamos por un identificador
	ushort estadoActual = q0;
	char c = '\0';

	// -- Verificamos que el estado en el cual estamos no sea invalido y no sea el fin del archivo
	while ((estadoMuerto != estadoActual && estadoTerminal != estadoActual) && !fuente.eof()) {
		fuente.get(c);

		estadoActual = delta[{estadoActual, CarASimbolo(c)}];

		if (estadoActual == 1)
			lexema += c;		
	}

	// -- Si llegamos al final del archivo limpiar el bit de EOF, asi poder utilizar seekg si es necesario
	if (fuente.eof()) fuente.clear();

	// -- Si el estado actual es final
	if (estadoActual == estadoTerminal) {
		//control = fuente.tellg(); control--; // Actualizamos la posicion del control a la actual
		control += lexema.size();
		fuente.seekg(control);
		esIdentificador = true;
	}
	else { // -- Sino movemos el cursor a donde estaba
		fuente.seekg(control);
	}

	return esIdentificador;
}

bool EsConstanteReal(std::ifstream& fuente, ulong& control, std::string& lexema) {
	// -- Definimos el alfabeto de entrada, especial = _
	typedef enum Sigma {
		Digito, Signo, Punto, Exponente, Otro
	};

	auto CarASimbolo = [](auto& c) {
		Sigma t = Sigma::Otro;

		if (c == 'e' || c == 'E') {
			t = Sigma::Exponente;
		} else if (c >= '0' && c <= '9') {
			t = Sigma::Digito;
		} else if (c == '-' || c == '+') {
			t = Sigma::Signo;
		} else if (c == '.') {
			t = Sigma::Punto;
		}

		return t;
	};

	// -- Definimos Delta
	std::map<tuple<ushort, Sigma>, ushort> delta = {
		//		 q	 x	simbolo		->	q
			{	{0,		Exponente	},	7},
			{	{0,		Digito		},	2},
			{	{0,		Signo		},	1},
			{	{0,		Punto		},	7},
			{	{0,		Otro		},	7},

			{	{1,		Exponente	},	7},
			{	{1,		Digito		},	2},
			{	{1,		Signo		},	7},
			{	{1,		Punto		},	7},
			{	{1,		Otro		},	7},

			{	{2,		Exponente	},	5},
			{	{2,		Digito		},	2},
			{	{2,		Signo		},	7},
			{	{2,		Punto		},	3},
			{	{2,		Otro		},	7},

			{	{3,		Exponente	},	5},
			{	{3,		Digito		},	4},
			{	{3,		Signo		},	7},
			{	{3,		Punto		},	7},
			{	{3,		Otro		},	7},

			{	{4,		Exponente	},	5},
			{	{4,		Digito		},	4},
			{	{4,		Signo		},	7},
			{	{4,		Punto		},	7},
			{	{4,		Otro		},	7},

			{	{5,		Exponente	},	7},
			{	{5,		Digito		},  8},
			{	{5,		Signo		},	6},
			{	{5,		Punto		},	7},
			{	{5,		Otro		},	7},

			{	{6,		Exponente	},	7},
			{	{6,		Digito		},	8},
			{	{6,		Signo		},	7},
			{	{6,		Punto		},	7},
			{	{6,		Otro		},	7},

			{	{7,		Exponente	},	7},
			{	{7,		Digito		},	7},
			{	{7,		Signo		},	7},
			{	{7,		Punto		},	7},
			{	{7,		Otro		},	7},

			{	{8,		Exponente	},	7},
			{	{8,		Digito		},	8},
			{	{8,		Signo		},	7},
			{	{8,		Punto		},	7},
			{	{8,		Otro		},	7},
	};

	// -- Definimos los estados finales, invalidos y el inicial
	const ushort finales[] = { 3,4,8 };
	const ushort estadoMuerto = 7;
	const ushort q0 = 0;
	bool esConstReal = false;

	lexema = "";

	// ==== Buscamos un identificador
	ushort estadoActual = q0;
	ushort ultimoEstado = q0;
	
	char c = '\0';

	fuente.get(c);
	// -- Verificamos que el estado en el cual estamos no sea invalido y no sea el fin del archivo
	while (estadoMuerto != estadoActual && !fuente.eof()) {
		Sigma simb = CarASimbolo(c);
		estadoActual = delta[{estadoActual, simb}];

		if (estadoActual != estadoMuerto) {
			lexema += c;
			ultimoEstado = estadoActual;
		}

		fuente.get(c);
	}

	// -- Si llegamos al final del archivo limpiar el bit de EOF, asi poder utilizar seekg si es necesario
	if (fuente.eof()) fuente.clear();

	// -- Si el estado actual es final
	if (find(begin(finales), end(finales), ultimoEstado) != end(finales)) {
		//control = fuente.tellg(); control--; // Actualizamos la posicion del control a la actual
		control += lexema.size();
		fuente.seekg(control);
		esConstReal = true;
	} else { // -- Sino movemos el cursor a donde estaba
		fuente.seekg(control);
	}

	return esConstReal;
}

bool EsConstanteEntera(std::ifstream& fuente, ulong& control, std::string& lexema) {
	// -- Definimos el alfabeto de entrada, especial = _
	typedef enum Sigma {
		Digito, Signo, Otro
	};

	auto CarASimbolo = [](auto& c) {
		Sigma t = Sigma::Otro;

		if (c == '-' || c == '+') {
			t = Sigma::Signo;
		} else if (c >= '0' && c <= '9') {
			t = Sigma::Digito;
		}

		return t;
	};

	// -- Definimos Delta
	std::map<tuple<ushort, Sigma>, ushort> delta = {
		//		 q	 x	simbolo	 ->	q
			{	{0,		Signo	},	1},
			{	{0,		Digito	},	2},
			{	{0,		Otro	},	3},

			{	{1,		Signo	},	3},
			{	{1,		Digito	},	2},
			{	{1,		Otro	},	3},

			{	{2,		Signo	},	3},
			{	{2,		Digito	},	2},
			{	{2,		Otro	},	3},

			{	{3,		Signo	},	3},
			{	{3,		Digito	},	3},
			{	{3,		Otro	},	3},
	};

	// -- Definimos los estados finales, invalidos y el inicial
	const ushort finales[] = { 2 };
	const ushort estadoMuerto = 3;
	ushort q0 = 0;
	bool esCostEntera = false;

	lexema = "";

	// ==== Buscamos por un identificador
	ushort estadoActual = q0;
	ushort ultimoEstado = q0;

	char c = '\0';

	fuente.get(c);

	// -- Verificamos que el estado en el cual estamos no sea invalido y no sea el fin del archivo
	while (estadoMuerto != estadoActual && !fuente.eof()) {
		Sigma simb = CarASimbolo(c);
		estadoActual = delta[{estadoActual, simb}];

		if (estadoActual != estadoMuerto) {
			lexema += c;
			ultimoEstado = estadoActual;
		}

		fuente.get(c);
	}

	// -- Si llegamos al final del archivo limpiar el bit de EOF, asi poder utilizar seekg si es necesario
	if (fuente.eof()) fuente.clear();

	// -- Si el estado actual es final
	if (find(begin(finales), end(finales), ultimoEstado) != end(finales)) {
		//control = fuente.tellg(); control--; // Actualizamos la posicion del control a la actual		
		control += lexema.size();
		fuente.seekg(control); // Cambiamos la posicion del cursor a la anterior a la actual (la que fallo el automata)
		esCostEntera = true;
	}
	else { // -- Sino movemos el cursor a donde estaba
		fuente.seekg(control);
	}

	return esCostEntera;
}

bool EsSimboloEspecial(std::ifstream& fuente, ulong& control, std::string& lexema, ComponenteLexico& complex) {
	char c = '\0';
	bool esSimbolo = true;
	fuente.get(c);

	switch (c) {
		case '(':
			complex = ComponenteLexico::ParantesisA;
			break;
		case ')':
			complex = ComponenteLexico::ParentesisC;
			break;
		case ';':
			complex = ComponenteLexico::PuntoComa;
			break;
		case '=':
			complex = ComponenteLexico::Igual;
			break;
		case '+':
			complex = ComponenteLexico::Mas;
			break;
		case '-':
			complex = ComponenteLexico::Menos;
			break;
		case '/':
			complex = ComponenteLexico::BarraInclinada;
			break;
		case '*':
			complex = ComponenteLexico::Asterisco;
			break;
		case '.':
			complex = ComponenteLexico::Punto;
			break;
		case ':':
			complex = ComponenteLexico::DosPuntos;
			break;
		case ',':
			complex = ComponenteLexico::Coma;
			break;
		case '{':
			complex = ComponenteLexico::LlavesA;
			break;
		case '}':
			complex = ComponenteLexico::LlavesC;
			break;
		case '<':
			complex = ComponenteLexico::Menor;
			break;
		case '>':
			complex = ComponenteLexico::Mayor;
			break;
		case '$':
			complex = ComponenteLexico::Pesos;
			break;
		default:
			esSimbolo = false;
			break;
	}

	if (!esSimbolo)
		fuente.seekg(control);
	else
		lexema = c;

	return esSimbolo;
}