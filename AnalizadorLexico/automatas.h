#pragma once

#include <fstream>
#include "tipos.h"

bool EsIdentificador(std::ifstream& fuente, ulong& control, std::string& lexema);
bool EsConstanteReal(std::ifstream& fuente, ulong& control, std::string& lexema);
bool EsConstanteEntera(std::ifstream& fuente, ulong& control, std::string& lexema);
bool EsSimboloEspecial(std::ifstream& fuente, ulong& control, std::string& lexema, ComponenteLexico& complex);