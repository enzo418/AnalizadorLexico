#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "tipos.h"
#include "automatas.h"
#include "utiles.h"
#include <iomanip>

using namespace std;

// ============= Funciones

bool ObtenerSiguienteComplex(ifstream& fuente, ulong& control,
	ComponenteLexico& complex, string& lexema, TablaSimbolos& ts) {

	// -- Quitar los caracteres no necesarios	
	while (fuente.peek() <= 32 && !fuente.eof()) {
		fuente.get();
		control++;
	}

	if (fuente.eof()) return false; // Se termino el archivo... volver.

	control = fuente.tellg();

	if (EsIdentificador(fuente, control, lexema)) {
		complex = ComponenteLexico::Identificador;
		AgregarEnTablaSimbolos(lexema, complex, ts);
	} else if (EsConstanteReal(fuente, control, lexema)) {
		complex = ComponenteLexico::ConstanteReal;
	} else if (EsConstanteEntera(fuente, control, lexema)) {
		complex = ComponenteLexico::ConstanteEntera;
	} else if (!EsSimboloEspecial(fuente, control, lexema, complex)) {
		complex = ComponenteLexico::ErrorLexico;
	}

	return true;
}

int main(void) {
	ulong control = 0;
	string lexema;
	ComponenteLexico complex;	

	TablaSimbolos ts;
	
	// -- Abrimos el archivo para lectura
	ifstream fuente("./input.txt");

	while(!fuente.eof()){
		if (ObtenerSiguienteComplex(fuente, control, complex, lexema, ts)) {
			cout << "Control			= " << control << endl;
			cout << "Lexema			= " << lexema << endl;
			cout << setw(24) << left << "TipoComplex " << "= "+ComplexAString(complex) << endl;
			cout << endl;

			//cout << setw(25) << left << "<"+ComplexAString(complex)+">" << lexema << endl;
		}
	}

	fuente.close();

	//system("pause");	

	return 0;
}
