#include <iostream>
#include "tipos.h"

void AgregarEnTablaSimbolos(std::string& lexema, ComponenteLexico& complex, TablaSimbolos& ts) {
	ElementoTabla el;
	el.complex = complex;
	el.lexema = lexema;

	ts.push_back(el);
}

std::string ComplexAString(ComponenteLexico& complex) {
	std::string out = "";
	switch (complex) {
		case ComponenteLexico::Identificador:
			out = "Identificador";
			break;
		case ComponenteLexico::ConstanteCaracter:
			out = "cadena";
			break;
		case ComponenteLexico::ConstanteEntera:
			out = "constante entera";
			break;
		case ComponenteLexico::ConstanteReal:
			out = "constante real";
			break;
		case ComponenteLexico::PuntoComa:
			out = "punto y coma";
			break;
		case ComponenteLexico::ErrorLexico:
			out = "error lexico";
			break;
		case ComponenteLexico::Mayor:
			out = "mayor";
			break;
		case ComponenteLexico::Menor:
			out = "Menor";
			break;
		case ComponenteLexico::Igual:
			out = "Igual";
			break;
		case ComponenteLexico::Mas:
			out = "Mas";
			break;
		case ComponenteLexico::Menos:
			out = "Menos";
			break;
		case ComponenteLexico::BarraInclinada:
			out = "BarraInclinada";
			break;
		case ComponenteLexico::Punto:
			out = "Punto";
			break;
		case ComponenteLexico::DosPuntos:
			out = "Dos Puntos";
			break;
		case ComponenteLexico::Coma:
			out = "Coma";
			break;
		case ComponenteLexico::LlavesA:
			out = "Llaves Abierta";
			break;
		case ComponenteLexico::LlavesC:
			out = "Llaves Cerrada";
			break;
		case ComponenteLexico::ParantesisA:
			out = "Parantesis Abierto";
			break;
		case ComponenteLexico::ParentesisC:
			out = "Parantesis Cerrado";
			break;
		case ComponenteLexico::Pesos:
			out = "Signo Pesos";
			break;
		case ComponenteLexico::Asterisco:
			out = "Asterisco";
			break;
		default:
			break;
	}
	return out;
}