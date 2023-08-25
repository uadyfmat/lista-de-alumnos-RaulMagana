#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Alumno {
	char nombreCompleto[100];
	int creditosAprobados;
	int semestreEquivalente;
};

struct Nodo {
	struct Alumno alumno;
	struct Nodo* siguiente;
};

struct Alumno* crearAlumno(const char* nombre, int creditos, int semestre) {
	struct Alumno* alumno = (struct Alumno*)malloc(sizeof(struct Alumno));
	if (alumno != NULL) {
		strcpy(alumno->nombreCompleto, nombre);
		alumno->creditosAprobados = creditos;
		alumno->semestreEquivalente = semestre;
	}
	return alumno;
}

void imprimirAlumno(struct Alumno* alumno) {
	printf("Nombre: %s, Créditos: %d, Semestre: %d\n", alumno->nombreCompleto, alumno->creditosAprobados, alumno->semestreEquivalente);
}

struct Nodo* crearNodo(struct Alumno* alumno) {
	struct Nodo* nodo = (struct Nodo*)malloc(sizeof(struct Nodo));
	if (nodo != NULL) {
		nodo->alumno = *alumno;
		nodo->siguiente = NULL;
	}
	return nodo;
	
}

int insertarNodosPorCreditos(struct Nodo** lista, struct Nodo* nuevoNodo) {
	if (*lista == NULL || nuevoNodo->alumno.creditosAprobados >= (*lista)->alumno.creditosAprobados) {
		nuevoNodo->siguiente = *lista;
		*lista = nuevoNodo;
		return 0;
	}
	struct Nodo* actual = *lista;
	while (actual->siguiente != NULL && actual->siguiente->alumno.creditosAprobados > nuevoNodo->alumno.creditosAprobados) {
		actual = actual->siguiente;
	}
	nuevoNodo->siguiente = actual->siguiente;
	actual->siguiente = nuevoNodo;
	return 0;
}

void imprimirLista(struct Nodo* lista) {
	struct Nodo* actual = lista;
	while (actual != NULL) {
		imprimirAlumno(&(actual->alumno));
		actual = actual->siguiente;
	}
}

int main() {
	
	struct Nodo* lista = NULL;
	
	struct Alumno* alumno1 = crearAlumno("Raul Alejandro Magana Flores", 105, 5);
	struct Alumno* alumno2 = crearAlumno("Jimena Guadalupe Garcia Rios", 107, 4);
	struct Alumno* alumno3 = crearAlumno("Jesus Mateo Ortiz Chay", 126, 6);
	struct Alumno* alumno4 = crearAlumno("Josue David Torres Tec", 45, 4);
	struct Alumno* alumno5 = crearAlumno("Maria Jose Garcia Rios", 118, 5);
	
	insertarNodosPorCreditos(&lista, crearNodo(alumno1));
	insertarNodosPorCreditos(&lista, crearNodo(alumno2));
	insertarNodosPorCreditos(&lista, crearNodo(alumno3));
	insertarNodosPorCreditos(&lista, crearNodo(alumno4));
	insertarNodosPorCreditos(&lista, crearNodo(alumno5));

	imprimirLista(lista);
	
	while (lista != NULL) {
		struct Nodo* temp = lista;
		lista = lista->siguiente;
		free(temp);
	}
	return 0;
}
