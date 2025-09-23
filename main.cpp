#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

const int MAX = 10; // tamaño máximo permitido por la práctica

// Llena la matriz n x n con valores aleatorios entre 1 y 100
void llenarRandom(int a[][MAX], int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            a[i][j] = rand() % 100 + 1; // 1..100
}

// Muestra la matriz con alineación
void mostrarMatriz(int a[][MAX], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << setw(4) << a[i][j];
        cout << '\n';
    }
}

// Suma todos los elementos de la matriz y devuelve la suma
int sumarElementos(int a[][MAX], int n) {
    int suma = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            suma += a[i][j];
    return suma;
}

// Cuenta pares, impares y divisibles entre 7 (pasa resultados por referencia)
void contarParImparDiv7(int a[][MAX], int n, int &pares, int &impares, int &div7) {
    pares = impares = div7 = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            if (a[i][j] % 2 == 0) ++pares;
            else ++impares;
            if (a[i][j] % 7 == 0) ++div7;
        }
}

// Calcula la matriz transpuesta: t = transpose(a)
void trasponer(int a[][MAX], int t[][MAX], int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            t[j][i] = a[i][j];
}

int main() {
    srand((unsigned) time(NULL)); // inicializa generador aleatorio

    int n;
    // Leer n validando que esté entre 1 y MAX
    do {
        cout << "Ingrese el tamano n (1-" << MAX << ") para la matriz n x n: ";
        cin >> n;
        if (!cin) { // protección contra entrada no numérica
            cin.clear();
            cin.ignore(10000, '\n');
            n = 0;
        }
        if (n < 1 || n > MAX) cout << "Valor invalido. Intente de nuevo.\n";
    } while (n < 1 || n > MAX);

    int mat[MAX][MAX], tr[MAX][MAX];

    llenarRandom(mat, n);

    cout << "\nMatriz original:\n";
    mostrarMatriz(mat, n);

    int suma = sumarElementos(mat, n);
    int pares, impares, div7;
    contarParImparDiv7(mat, n, pares, impares, div7);

    cout << "\nSuma de todos los elementos: " << suma << '\n';
    cout << "Cantidad de pares: " << pares << '\n';
    cout << "Cantidad de impares: " << impares << '\n';
    cout << "Cantidad de elementos divisibles entre 7: " << div7 << '\n';

    trasponer(mat, tr, n);
    cout << "\nMatriz transpuesta:\n";
    mostrarMatriz(tr, n);

    return 0;
}

