#include "Estudiante.h"
#include <iostream>
#include <fstream>
#include <windows.h>  // Para Sleep()
#include <cstdlib>    // Para remove() y rename()
#include <string>
using namespace std;

// Implementación de la clase Estudiante


Estudiante::Estudiante() : nombre(""), edad(0), calificacion(0.0f) {}

Estudiante::Estudiante(const string& nombre, int edad, float calificacion)
	: nombre(nombre), edad(edad), calificacion(calificacion) {
}

string Estudiante::getNombre() const {
	return nombre;
}

int Estudiante::getEdad() const {
	return edad;
}

float Estudiante::getCalificacion() const {
	return calificacion;
}

void Estudiante::setNombre(const string& nombre) {
	this->nombre = nombre;
}

void Estudiante::setEdad(int edad) {
	this->edad = edad;
}

void Estudiante::setCalificacion(float calificacion) {
	this->calificacion = calificacion;
}

string Estudiante::toString() const {
	// Retorna la línea en formato: nombre,edad,calificacion
	return nombre + "," + to_string(edad) + "," + to_string(calificacion);
}

// Implementación de la clase EstudianteManager

void EstudianteManager::menu() {
	cout << "1. Agregar Estudiante" << endl;
	cout << "2. Mostrar Estudiantes" << endl;
	cout << "3. Calcular promedio de calificaciones" << endl;
	cout << "4. Buscar Estudiante" << endl;
	cout << "5. Eliminar Estudiante" << endl;
	cout << "6. Modificar Estudiante" << endl;
	cout << "7. Mostrar el contenido de un archivo" << endl;
	cout << "8. Salir" << endl;
	cout << "Opcion: ";
}

void EstudianteManager::addStudent() {
	Estudiante nuevo;
	cout << "Ingrese el nombre del estudiante: ";
	string nombre;
	getline(cin, nombre);
	nuevo.setNombre(nombre);

	int edad;
	do {
		cout << "Ingrese la edad del estudiante: ";
		cin >> edad;
		if (cin.fail() || edad <= 0) {
			cout << "Error: La edad debe ser un numero entero positivo." << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
	} while (edad <= 0);
	nuevo.setEdad(edad);

	float calificacion;
	do {
		cout << "Ingrese la calificacion del estudiante: ";
		cin >> calificacion;
		if (cin.fail() || calificacion < 0 || calificacion > 100) {
			cout << "Error: La calificacion debe estar entre 0 y 100." << endl;
			cin.clear();
			cin.ignore(100, '\n');
		}
	} while (calificacion < 0 || calificacion > 100);
	nuevo.setCalificacion(calificacion);
	cin.ignore();  // Limpiar el buffer

	// Agregar el registro al final del archivo
	ofstream file("\\\\192.168.146.197\\archivos\\estudiantes-Brayan-Fredy.txt", ios::app);
	if (file.is_open()) {
		file << nuevo.getNombre() << ","
			<< nuevo.getEdad() << ","
			<< nuevo.getCalificacion() << "\n";
		file.close();
		cout << "Estudiante agregado exitosamente." << endl;
	}
	else {
		cout << "Error al abrir el archivo." << endl;
	}
	cout << "Presione enter para continuar...";
	cin.get();
}

void EstudianteManager::showStudents() {
	ifstream file("\\\\192.168.146.197\\archivos\\estudiantes-Brayan-Fredy.txt");
	if (!file.is_open()) {
		cout << "No se pudo abrir el archivo." << endl;
		cout << "Presione enter para continuar...";
		cin.get();
		return;
	}

	// Salida básica sin i/o manipuladores
	cout << "ID    Nombre                 Edad    Calificacion" << endl;
	cout << "-----------------------------------------------------" << endl;
	int id = 1;
	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			// Parsear manualmente la línea usando find y substr
			size_t pos1 = line.find(',');
			size_t pos2 = line.find(',', pos1 + 1);
			if (pos1 == string::npos || pos2 == string::npos) continue;  // Formato incorrecto
			string nombre = line.substr(0, pos1);
			int edad = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
			float calificacion = stof(line.substr(pos2 + 1));

			// Impresión simple con espacios para la alineación (ajustable según el tamaño de la cadena)
			cout << id << "     " << nombre;
			int espacios = 20 - nombre.size();
			for (int i = 0; i < espacios; i++)
				cout << " ";
			cout << edad << "      " << calificacion << endl;
			id++;
		}
	}
	file.close();
	cout << "Presione enter para continuar...";
	cin.get();
}

void EstudianteManager::averageStudents() {
	ifstream file("\\\\192.168.146.197\\archivos\\estudiantes-Brayan-Fredy.txt");
	if (!file.is_open()) {
		cout << "No se pudo abrir el archivo." << endl;
		cout << "Presione enter para continuar...";
		cin.get();
		return;
	}
	float suma = 0;
	int count = 0;
	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			size_t pos1 = line.find(',');
			size_t pos2 = line.find(',', pos1 + 1);
			if (pos1 == string::npos || pos2 == string::npos) continue;
			float calificacion = stof(line.substr(pos2 + 1));
			suma += calificacion;
			count++;
		}
	}
	file.close();
	if (count > 0)
		cout << "Promedio de calificaciones: " << (suma / count) << endl;
	else
		cout << "No hay estudiantes registrados." << endl;
	cout << "Presione enter para continuar...";
	cin.get();
}

void EstudianteManager::searchStudent() {
	cout << "Ingrese el nombre del estudiante a buscar: ";
	string searchName;
	getline(cin, searchName);
	ifstream file("\\\\192.168.146.197\\archivos\\estudiantes-Brayan-Fredy.txt");
	if (!file.is_open()) {
		cout << "No se pudo abrir el archivo." << endl;
		cout << "Presione enter para continuar...";
		cin.get();
		return;
	}
	bool found = false;
	int id = 1;
	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			size_t pos1 = line.find(',');
			size_t pos2 = line.find(',', pos1 + 1);
			if (pos1 == string::npos || pos2 == string::npos) continue;
			string nombre = line.substr(0, pos1);
			int edad = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
			float calificacion = stof(line.substr(pos2 + 1));
			if (nombre == searchName) {
				cout << "Estudiante encontrado:" << endl;
				cout << "ID: " << id << endl;
				cout << "Nombre: " << nombre << endl;
				cout << "Edad: " << edad << endl;
				cout << "Calificacion: " << calificacion << endl;
				found = true;
				break;
			}
			id++;
		}
	}
	file.close();
	if (!found)
		cout << "No se encontro el estudiante." << endl;
	cout << "Presione enter para continuar...";
	cin.get();
}

void EstudianteManager::deleteStudent() {
	cout << "Ingrese el nombre del estudiante a eliminar: ";
	string searchName;
	getline(cin, searchName);
	ifstream file("\\\\192.168.146.197\\archivos\\estudiantes-Brayan-Fredy.txt");
	if (!file.is_open()) {
		cout << "No se pudo abrir el archivo." << endl;
		cout << "Presione enter para continuar...";
		cin.get();
		return;
	}
	ofstream tempFile("\\\\192.168.146.197\\archivos\\temp.txt");
	bool found = false;
	string line;
	while (getline(file, line)) {
		if (!line.empty()) {
			size_t pos1 = line.find(',');
			size_t pos2 = line.find(',', pos1 + 1);
			if (pos1 == string::npos || pos2 == string::npos) continue;
			string nombre = line.substr(0, pos1);
			if (nombre == searchName) {
				found = true;
				continue;
			}
			else {
				tempFile << line << "\n";
			}
		}
	}
	file.close();
	tempFile.close();
	if (found) {
		remove("\\\\192.168.146.197\\archivos\\estudiantes-Brayan-Fredy.txt");
		rename("\\\\192.168.146.197\\archivos\\temp.txt", "\\\\192.168.146.197\\archivos\\estudiantes-Brayan-Fredy.txt");
		cout << "Estudiante eliminado exitosamente." << endl;
	}
	else {
		cout << "No se encontro el estudiante." << endl;
		remove("\\\\192.168.146.197\\archivos\\temp.txt");
	}
	cout << "Presione enter para continuar...";
	cin.get();
}

void EstudianteManager::modifyStudent() {
	cout << "Ingrese el nombre del estudiante a modificar: ";
	string searchName;
	getline(cin, searchName);

	ifstream file("\\\\192.168.146.197\\archivos\\estudiantes-Brayan-Fredy.txt");
	if (!file.is_open()) {
		cout << "No se pudo abrir el archivo." << endl;
		cout << "Presione enter para continuar...";
		cin.get();
		return;
	}

	ofstream tempFile("\\\\192.168.146.197\\archivos\\temp.txt");
	bool found = false;
	string line;
	while (getline(file, line)) {
		if (line.empty())
			continue;

		// Parsear la línea usando find y substr sin sstream
		size_t pos1 = line.find(',');
		size_t pos2 = line.find(',', pos1 + 1);
		if (pos1 == string::npos || pos2 == string::npos)
			continue;

		string nombre = line.substr(0, pos1);

		// Si se encuentra el estudiante a modificar
		if (nombre == searchName) {
			found = true;
			cout << "Estudiante encontrado. Ingrese los nuevos datos." << endl;

			cout << "Nuevo nombre: ";
			string newName;
			getline(cin, newName);

			int newAge;
			do {
				cout << "Nueva edad: ";
				cin >> newAge;
				if (cin.fail() || newAge <= 0) {
					cout << "Error: La edad debe ser un numero entero positivo." << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}
			} while (newAge <= 0);

			float newCalificacion;
			do {
				cout << "Nueva calificacion: ";
				cin >> newCalificacion;
				if (cin.fail() || newCalificacion < 0 || newCalificacion > 100) {
					cout << "Error: La calificacion debe estar entre 0 y 100." << endl;
					cin.clear();
					cin.ignore(100, '\n');
				}
			} while (newCalificacion < 0 || newCalificacion > 100);
			cin.ignore(); // Limpiar el buffer

			// Construir el nuevo registro en formato CSV
			string newRecord = newName + "," + to_string(newAge) + "," + to_string(newCalificacion);
			tempFile << newRecord << "\n";
		}
		else {
			// Escribir la línea sin cambios
			tempFile << line << "\n";
		}
	}
	file.close();
	tempFile.close();

	if (found) {
		remove("\\\\192.168.146.197\\archivos\\estudiantes-Brayan-Fredy.txt");
		rename("\\\\192.168.146.197\\archivos\\temp.txt", "\\\\192.168.146.197\\archivos\\estudiantes-Brayan-Fredy.txt");

		cout << "Estudiante modificado exitosamente." << endl;
	}
	else {
		cout << "No se encontro el estudiante." << endl;
		remove("\\\\192.168.146.197\\archivos\\temp.txt");
	}
	cout << "Presione enter para continuar...";
	cin.get();
}

void EstudianteManager::displayFileContent(string filePath) {
	ifstream file(filePath);
	if (!file.is_open()) {
		cout << "No se pudo abrir el archivo: " << filePath << endl;
		cout << "Presion ENTER para continuar...";
		cin.get();
		return;
	}

	string line;
	cout << "\n--- Contenido de " << filePath << " ---\n";
	while (getline(file, line)) {
		cout << line << "\n";
	}
	cout << "\n--- Fin del archivo ---\n";
	file.close();
	cout << "Presione ENTER para continuar...";
	cin.get();
}