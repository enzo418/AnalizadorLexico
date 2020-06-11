#pragma once

#include <fstream>
#include "tipos.h"
#include <vector>
#include <map>

template <typename F>
bool TemplateAutomata(std::ifstream& fuente, ulong& control, std::string& lexema,
					  F CarASimbolo, Delta delta, 
					  std::vector<ushort> finales, ushort estadoInicial, ushort estadoMuerto);

bool EsIdentificador(std::ifstream& fuente, ulong& control, std::string& lexema);
bool EsConstanteReal(std::ifstream& fuente, ulong& control, std::string& lexema);
bool EsConstanteEntera(std::ifstream& fuente, ulong& control, std::string& lexema);
bool EsSimboloEspecial(std::ifstream& fuente, ulong& control, std::string& lexema, ComponenteLexico& complex);
