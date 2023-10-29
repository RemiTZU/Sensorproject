#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <sstream>
#include <map>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Server {
public:
    // Constructeur par défaut
    Server();

    // Constructeur de copie
    Server(const Server& other);

    // Opérateur d'affectation
    Server& operator=(const Server& other);

    // Destructeur
    ~Server();

// Fonction pour afficher les données dans la console

    template<typename T>
    void consoleWrite(const std::string& typeofsensor, T data,int id) {
        std::lock_guard<std::mutex>lock(this->consoleMutex);
        std::cout << typeofsensor << id << " : " << data << std::endl;
    }

     
    template<typename T>
    void fileWrite(const std::string& sensorName, const T data, int id) {
        std::lock_guard<std::mutex> lock(fileMutex); // Verrouillage du mutex du fichier

        std::ofstream file(sensorName + ".csv",std::ios::app);
        if (file.is_open()) {
            file << id << ";" << data << std::endl;
            file.close();
        } else {
            std::cerr << "Impossible d'ouvrir le fichier pour le capteur : " << sensorName << std::endl;
        }
    }


    // bool fileExists(const std::string& fileName) {
    //     std::ifstream file(fileName);
    //     return file.good();
    // }

    // void csvWrite(const std::string& sensorName, int id) {
    //     std::lock_guard<std::mutex> lock(fileMutex); // Verrouillage du mutex du fichier

    //     std::vector<int> ids; // Vecteur pour stocker les IDs de la première ligne

    //     // Vérifier si le fichier existe, le créer s'il n'existe pas
    //     if (!fileExists(sensorName + ".csv")) {
    //         std::ofstream createFile(sensorName + ".csv");
    //         if (createFile.is_open()) {
    //             createFile.close();
    //         } else {
    //             std::cerr << "Impossible de créer le fichier pour le capteur : " << sensorName << std::endl;
    //             return;
    //         }
    //     }


    //     // Lire la première ligne du fichier CSV et stocker les IDs dans le vecteur
    //     std::ifstream file(sensorName + ".csv");
    //     if (file.is_open()) {
    //         std::string line;
    //         std::getline(file, line);
    //         std::stringstream lineStream(line);
    //         std::string cell;
    //         while (std::getline(lineStream, cell, ',')) {
    //             int num = std::stoi(cell);
    //             ids.push_back(num);
    //         }
    //         file.close();
    //     } else {
    //         std::cerr << "Impossible d'ouvrir le fichier pour le capteur : " << sensorName << std::endl;
    //         return;
    //     }

    //     // Insérer l'ID au bon emplacement dans le vecteur
    //     if (insertNumber(ids, id)) {
    //         // Écrire la ligne mise à jour dans le fichier
    //         std::ofstream outFile(sensorName + ".csv");
    //         if (outFile.is_open()) {
    //             for (int num : ids) {
    //                 outFile << num << ",";
    //             }
    //             outFile << std::endl;
    //             outFile.close();
    //         } else {
    //             std::cerr << "Impossible de mettre à jour le fichier pour le capteur : " << sensorName << std::endl;
    //         }
    //     }

    // }

    // template<typename T>
    // void insertdata(const std::string& sensorName, const T data, int id){

    //     //Insérer la data au bon endroit
    //     // Ouvrir le fichier en mode lecture et écriture
    //     std::fstream file(sensorName + ".csv", std::ios::in | std::ios::out);

    //     if (file.is_open()) {
    //         std::string line;
    //         std::getline(file, line); // Lire la dernière ligne

    //         // Compter le nombre de virgules dans la dernière ligne
    //         int numCommas = std::count(line.begin(), line.end(), ',');

    //         // Ajouter les virgules nécessaires si le nombre de virgules est inférieur à id
    //         while (numCommas < id + 1) {
    //             file << ","; // Ajouter les virgules jusqu'à id - 1
    //             numCommas++;
    //         }

    //         // Avancer jusqu'à la virgule numéro id - 1
    //         for (int i = 0; i < id - 1; ++i) {
    //             std::getline(file, line, ',');
    //         }
    //     } else {
    //         std::cerr << "Impossible d'ouvrir le fichier pour le capteur : " << sensorName << std::endl;
    //     }
    // }

    // bool insertNumber(std::vector<int>& numbers, int num) {
    //     // Recherche binaire pour trouver la bonne position pour insérer le nombre
    //     int left = 0;
    //     int right = numbers.size() - 1;

    //     while (left <= right) {
    //         int mid = left + (right - left) / 2;

    //         if (numbers[mid] == num) {
    //             return false; // Le nombre est déjà présent, ne pas l'ajouter
    //         }

    //         if (numbers[mid] < num) {
    //             left = mid + 1;
    //         } else {
    //             right = mid - 1;
    //         }
    //     }

    //     // Insérer le nombre à la bonne position
    //     numbers.insert(numbers.begin() + left, num);
    //     return true; // Le nombre a été ajouté avec succès
    // }






    // Fonction qui reçoit une donnée d'un capteur
    void dataRcv(int dataSens);

private:
    bool consolActivation;
    std::mutex consoleMutex;
    std::mutex fileMutex;
    std::unordered_map<std::string, std::vector<std::string>> csvData;
};

// Définition des méthodes de la classe Server

// Constructeur par défaut
Server::Server() : consolActivation(true){
    
}

// Constructeur de copie
Server::Server(const Server& other) :consolActivation(other.consolActivation){}

// Opérateur d'affectation
Server& Server::operator=(const Server& other) {
    if (this != &other) {
        consolActivation = other.consolActivation;
    }
    return *this;
}

// Destructeur
Server::~Server() {
    
}



// Fonction qui reçoit une donnée d'un capteur
void Server::dataRcv(int dataSens) {
    // Code pour récupérer les données du fichier
    std::ifstream inputFile("sensor_data.txt");
    std::string data;
    if (inputFile.is_open()) {
        while (getline(inputFile, data)) {
            std::cout << "Donnée récupérée : " << data << std::endl;
        }
        inputFile.close();
    } else {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier." << std::endl;
    }
}

#endif // SERVER_H





