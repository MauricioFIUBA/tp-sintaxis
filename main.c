#include <stdio.h>
#include <stdlib.h>

#define cantidadFilas 8
#define cantidadColumnas 14
#define cantidadEstadosFinales 2
#define NUL 0

const char tabla_transiciones[cantidadFilas][cantidadColumnas] = {
	{NUL, '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'F', '.', '\t'},
	{'0', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '6', '6', '6'}, 
	{'1', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '3', '4', '6'},
	{'2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '2', '3', '6', '6'},
	{'3', '6', '6', '6', '6', '6', '6', '6', '6', '6', '6', '6', '6', '6'},
	{'4', '5', '6', '6', '6', '6', '6', '6', '6', '6', '6', '6', '6', '6'},
	{'5', '6', '3', '6', '6', '6', '6', '6', '6', '6', '6', '6', '6', '6'},
	{'6', '6', '6', '6', '6', '6', '6', '6', '6', '6', '6', '6', '6', '6'},
};

const char estados_finales[cantidadEstadosFinales] = {'3', '4'};
const char centinela = '#';
const char fdt = '\n';
const char caracterFueraDelAlfabeto = '\t';

char siguienteEstado(char estado, char caracter){
	int posicionFilaEstado, posicionColumnaCaracter;
	int caracterEncontrado = 0;
	char estadoSiguiente;
	
	unsigned i;	
	for(i = 0; i < cantidadFilas; i++) {		
    	if (tabla_transiciones[i][0] == estado) {
        	posicionFilaEstado = i;
    	}    	
	}
	
	for(i = 0; i < cantidadColumnas; i++){
		if (tabla_transiciones[0][i] == caracter){
    		posicionColumnaCaracter = i;
    		caracterEncontrado = 1;
		}
	}
	
	if(caracterEncontrado){
		estadoSiguiente = tabla_transiciones[posicionFilaEstado][posicionColumnaCaracter];
	} else {
		int columnaCaracterFueraDelAlfabeto;
		unsigned i;
		for(i = 0; i < cantidadColumnas; i++){
			if(tabla_transiciones[0][i] == caracterFueraDelAlfabeto){
				columnaCaracterFueraDelAlfabeto = i;
			}
		}
		
		estadoSiguiente = tabla_transiciones[posicionFilaEstado][columnaCaracterFueraDelAlfabeto];
	}
	
	return estadoSiguiente;
}

int esEstadoFinal(char estado){
	int encontrado = 0;
	
	unsigned i;
	for (i = 0; i < cantidadEstadosFinales; i++){
		if(estados_finales[i] == estado){
			encontrado = 1;
		}
	}
	
	return encontrado;
}

int main(int argc, char *argv[]) {

  printf("Introducir una cadena:");
   
  char* palabra = 0;
  char* palabrasAceptadas = 0;
  int tamanioPalabra = 0;
  int tamanioPalabrasAceptadas = 0;
  char caracterActual = getchar();
  char estadoActual = tabla_transiciones[0][1];  
  int cantidadPalabrasAceptadas = 0;
  int cantidadPalabras = 0;
  
  while(caracterActual != fdt){  	
  	palabra = (char*)realloc(palabra, tamanioPalabra + 1);  	
  	
  	while(caracterActual != centinela && caracterActual != fdt){
  		estadoActual = siguienteEstado(estadoActual, caracterActual);
  		palabra[tamanioPalabra] = caracterActual;
  		tamanioPalabra++;
  		//Lee siguiente caracter
  		caracterActual = getchar();
	}
	
	if(esEstadoFinal(estadoActual)){
	    //Guarda palabra en la siguiente posición de palabrasAceptadas
		tamanioPalabrasAceptadas += tamanioPalabra + 1;
		palabrasAceptadas = (char*)realloc(palabrasAceptadas, tamanioPalabrasAceptadas);
		unsigned i;
		for (i = 0; i < tamanioPalabra; i++){
			palabrasAceptadas[tamanioPalabrasAceptadas - tamanioPalabra + i - 1] = palabra[i];	
		}
		palabrasAceptadas[tamanioPalabrasAceptadas - 1] = '#';
		cantidadPalabras++;
	}
	
	//Reinicializa todo para leer la siguiente palabra (deja palabra sin elementos y otras cosas propias del autómata).
	if(caracterActual == fdt){
	    break;
	}
	
	palabra = 0;
	tamanioPalabra = 0;
	caracterActual = getchar();
	estadoActual = tabla_transiciones[0][1];
  }
  
  //Muestra las palabras aceptadas listadas.
  printf("Cantidad de palabras aceptadas: %d\n", cantidadPalabras);
  
  if (tamanioPalabrasAceptadas > 0){
  	printf("Palabras aceptadas: ");
  	unsigned i;
  	for (i = 0; i < tamanioPalabrasAceptadas; i++){
  		if (palabrasAceptadas[i] == '#'){
  			printf("\n");
		} else {
			printf("%c", palabrasAceptadas[i]);
		}
	}
  }
  
  
  free(palabra);
  free(palabrasAceptadas);

   return 0;
}
