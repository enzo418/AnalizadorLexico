#pragma once

#include <iostream>
#include "tipos.h"

void AgregarEnTablaSimbolos(std::string& lexema, ComponenteLexico& complex, TablaSimbolos& ts);
std::string ComplexAString(ComponenteLexico& complex);