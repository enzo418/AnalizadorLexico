#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "tipos.h"
#include "automatas.h"
#include "utiles.h"
#include <iomanip>

// ============= Funciones

bool ObtenerSiguienteComplex(std::ifstream& fuente, ulong& control,
	ComponenteLexico& complex, std::string& lexema, TablaSimbolos& ts) {

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
	std::string lexema;
	ComponenteLexico complex;	

	TablaSimbolos ts;
	
	// -- Abrimos el archivo para lectura (Linux)
	std::ifstream fuente("/input.txt");
	
	if(!fuente.good()){ // si no se pudo abrir
		fuente.open("input.txt"); // intentamos abrirlo sin / (Windows)
		if(!fuente.good()){
			std::cout << "El archivo no existe" << std::endl; 
			return 1; 
		}
	}

	// mientras no sea el fin del archivo
	while(!fuente.eof()){
		if (ObtenerSiguienteComplex(fuente, control, complex, lexema, ts)) {
			std::cout << "Control			= " << control << std::endl;
			std::cout << "Lexema			= " << lexema << std::endl;
			std::cout << std::setw(24) << std::left << "TipoComplex " << "= "+ComplexAString(complex) << std::endl;
			std::cout << std::endl;

			//cout << setw(25) << left << "<"+ComplexAString(complex)+">" << lexema << endl;
		}
	}

	fuente.close();

	//system("pause");	

	return 0;
}
