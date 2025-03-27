#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>
using namespace std;

class Estudiante {
private:
    string nombre;
    int edad;
    float calificacion;
public:
    // Constructores
    Estudiante();
    Estudiante(const string& nombre, int edad, float calificacion);

    // Getters
    string getNombre() const;
    int getEdad() const;
    float getCalificacion() const;

    // Setters
    void setNombre(const string& nombre);
    void setEdad(int edad);
    void setCalificacion(float calificacion);

    // Método para convertir el objeto a una línea de texto (formato CSV)
    string toString() const;
};

class EstudianteManager {
public:
    void menu();
    void addStudent();
    void showStudents();
    void averageStudents();
    void searchStudent();
    void deleteStudent();
    void modifyStudent();
};

#endif // ESTUDIANTE_H
