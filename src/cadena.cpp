
#include "../include/cadena.h"
#include "../include/info.h"
#include "../include/utils.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct nodoCadena {
  TInfo dato;
  TLocalizador anterior;
  TLocalizador siguiente;
};

struct _rep_cadena {
  TLocalizador inicio;
  TLocalizador final;
};

bool esLocalizador(TLocalizador loc) { return loc != NULL; }

TCadena crearCadena() {
  TCadena res = new _rep_cadena;
  res->inicio = res->final = NULL;
  return res;
}

void liberarCadena(TCadena cad) {
  while (cad->inicio) {
    TLocalizador borrar = cad->inicio;
    cad->inicio = cad->inicio->siguiente;
    liberarInfo(borrar -> dato);
    delete borrar;
  }
  delete cad->final;
  delete cad;
}

bool esVaciaCadena(TCadena cad) {
  return !cad || cad->inicio == NULL;
}

TLocalizador inicioCadena(TCadena cad) {
  TLocalizador res;
  if (esVaciaCadena(cad)) {
    res = NULL;
  } else {
    res = cad->inicio;
  }
  return res;
}

TLocalizador finalCadena(TCadena cad) {
  TLocalizador res;
  if (esVaciaCadena(cad)) {
    res = NULL;
  } else {
    res = cad->final;
  }
  return res;
}

TInfo infoCadena(TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
  return loc->dato;
}

TLocalizador siguiente(TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
  return loc->siguiente;
}

TLocalizador anterior(TLocalizador loc, TCadena cad) {
  assert(localizadorEnCadena(loc, cad));
  return loc->anterior;
}

bool esFinalCadena(TLocalizador loc, TCadena cad) {
  return (!esVaciaCadena(cad)) && (loc == finalCadena(cad));
}

bool esInicioCadena(TLocalizador loc, TCadena cad) {
  if (esVaciaCadena(cad)) return false;
  return loc->anterior == NULL;
}

TCadena insertarAlFinal(TInfo i, TCadena cad) {
  TLocalizador nuevoNodo = new nodoCadena;
  nuevoNodo->dato = i;
  nuevoNodo->anterior = cad->final;
  nuevoNodo->siguiente = NULL;
  if (cad->final) {
    cad->final->siguiente = nuevoNodo;
  }
  if (esVaciaCadena(cad)) {
    cad->inicio = nuevoNodo;
  }
  cad->final = nuevoNodo;
  return cad;
}

TCadena insertarAntes(TInfo i, TLocalizador loc, TCadena cad) {
  TLocalizador nuevoNodo = new nodoCadena;
  nuevoNodo->dato = i;
  nuevoNodo->siguiente = loc;
  nuevoNodo->anterior = loc->anterior;
  
  if (loc->anterior) {
    loc->anterior->siguiente = nuevoNodo;
  }

  loc->anterior = nuevoNodo;
  return cad;
}

TCadena removerDeCadena(TLocalizador loc, TCadena cad) {
  if (loc->anterior) {
    loc->anterior->siguiente = loc->siguiente;
  }
  if (loc->siguiente) {
    loc->siguiente->anterior = loc->anterior;
  }
  delete loc;
  loc = NULL;

  return cad;
}

void imprimirCadena(TCadena cad) {
  TLocalizador actual = cad->inicio;
  while (actual) {
    /* printf (actual->dato.n); */
    actual = actual->siguiente;
  }
  /* printf endline; */
}

TLocalizador kesimo(nat k, TCadena cad) {
  if (k<=0) return NULL;
  TLocalizador head = cad->inicio;
  nat contador = 1;
  while (head != NULL && contador != k) {
    head = head->siguiente;
    contador++;
  }
  return head;
}

TCadena insertarSegmentoDespues(TCadena sgm, TLocalizador loc, TCadena cad) {
  loc->siguiente = sgm->inicio;
  sgm->inicio->anterior = loc;
  if (loc->siguiente) {
    loc->siguiente->anterior = sgm->final;
  }
  sgm->final->siguiente = loc->siguiente;
  return cad;
}

TCadena copiarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  TCadena resultado = crearCadena();
  TLocalizador aux = desde;
  while (aux != hasta) {
    insertarAlFinal(aux->dato, resultado);
    aux = aux->siguiente;
  }
  return resultado;
} 

TCadena borrarSegmento(TLocalizador desde, TLocalizador hasta, TCadena cad) {
  TLocalizador aux = desde;
  while (aux != hasta) {
    removerDeCadena(aux, cad);
    aux = aux->siguiente;
  }
  return cad;
}

TCadena cambiarEnCadena(TInfo i, TLocalizador loc, TCadena cad) {
  loc->dato = i;
  return cad;
}

TCadena intercambiar(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  TInfo aux = loc1->dato;
  loc1->dato = loc2->dato;
  loc2->dato = aux;
  return cad;
}

bool localizadorEnCadena(TLocalizador loc, TCadena cad) {
  if (esVaciaCadena(cad)) return false;
  TLocalizador aux = cad->inicio;
  while (aux != loc || aux != NULL) {
    aux = aux->siguiente;
  }
  return aux == loc;
}

bool precedeEnCadena(TLocalizador loc1, TLocalizador loc2, TCadena cad) {
  if (esVaciaCadena(cad)) return false;
  TLocalizador aux = loc1;
  while (aux != loc2 || aux != NULL) {
    aux = aux->siguiente;
  }
  return aux == loc2;
}

TLocalizador siguienteClave(nat clave, TLocalizador loc, TCadena cad) {
  TLocalizador aux = loc;
  while (aux != NULL || natInfo(aux->dato) != clave) {
    aux = aux->siguiente;
  }
  return aux;
}

TLocalizador anteriorClave(nat clave, TLocalizador loc, TCadena cad) {
  TLocalizador aux = loc;
  while (aux != NULL || natInfo(aux->dato) != clave) {
    aux = aux->anterior;
  }
  return aux;
}

TLocalizador menorEnCadena(TLocalizador loc, TCadena cad) {
  TLocalizador menor = loc;
  TLocalizador aux = loc;
  while (aux != NULL) {
    if (natInfo(aux->dato) < natInfo(menor->dato)) {
      menor = aux;
    }
    aux = aux->siguiente;
  }
  return menor;
}
