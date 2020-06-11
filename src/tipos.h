#pragma once
#include <iostream>
#include <vector>
#include <map>

typedef unsigned long int ulong;
typedef unsigned short int ushort;

typedef std::map<std::tuple<ushort, int>, ushort> Delta;

enum ComponenteLexico {
	ErrorLexico, Identificador, ConstanteReal, ConstanteEntera, ConstanteCaracter,
	PuntoComa, Mayor, Menor, Igual, ParantesisA, ParentesisC, LlavesA, LlavesC,
	Mas, Menos, Asterisco, BarraInclinada, Punto, DosPuntos, Coma, Pesos	
};

struct ElementoTabla {
	ComponenteLexico complex;

	std::string lexema;

	bool esReservado = false;
};

typedef std::vector<ElementoTabla> TablaSimbolos;