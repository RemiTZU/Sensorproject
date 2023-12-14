#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>



/**
 * @brief Classe représentant un serveur pour stocker et afficher les données des capteurs.
 *
 * Cette classe gère l'affichage des données des capteurs dans la console et leur enregistrement dans un fichier CSV.
 * Elle offre également la fonction `dataRcv` pour récupérer des données à partir d'un fichier.
 */

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

    /**
     * @brief Affiche les données du capteur dans la console.
     * @tparam T Type de données à afficher.
     * @param typeofsensor Type du capteur.
     * @param data Données du capteur.
     * @param id Identifiant du capteur.
     */
    template<typename T>
    void consoleWrite(const std::string& typeofsensor, T data,int id) {
        std::lock_guard<std::mutex>lock(this->consoleMutex);
        std::cout << typeofsensor << id << " : " << data << std::endl;
    }

    /**
     * @brief Enregistre les données du capteur dans un fichier CSV.
     * @tparam T Type de données à enregistrer.
     * @param sensorName Nom du capteur.
     * @param data Données du capteur.
     * @param id Identifiant du capteur.
     */ 
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




private:
    bool consolActivation;
    std::mutex consoleMutex;
    std::mutex fileMutex;
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

#endif // SERVER_H





