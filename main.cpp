#include "Estudiante.h"
#include <iostream>
#include <cstdlib>    // Para system("cls")
#include <windows.h>  // Para Sleep()
using namespace std;

int main() {
    int opcion;
    EstudianteManager manager;
    do {
        system("cls");
        manager.menu();
        cin >> opcion;
        cin.ignore();  // Limpiar el buffer de entrada
        switch (opcion) {
        case 1:
            system("cls");
            manager.addStudent();
            break;
        case 2:
            system("cls");
            manager.showStudents();
            break;
        case 3:
            system("cls");
            manager.averageStudents();
            break;
        case 4:
            system("cls");
            manager.searchStudent();
            break;
        case 5:
            system("cls");
            manager.deleteStudent();
            break;
        case 6:
            system("cls");
            manager.modificarEstudiante();
            break;
        case 7:
            system("cls");
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion invalida. Intente de nuevo." << endl;
            Sleep(1500);
            break;
        }
    } while (opcion != 7);
    return 0;
}
