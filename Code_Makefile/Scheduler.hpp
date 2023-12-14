#ifndef SCHEDULER_H
#define SCHEDULER_H
using namespace std;
#include <iostream>
#include <thread>
#include <vector>
#include <sensor.hpp> 
#include <Server.hpp>

#include <chrono>



/**
 * @brief Classe représentant un planificateur de capteurs.
 *
 * Cette classe permet de gérer et de planifier les tâches de différents capteurs en parallèle.
 */
class Scheduler {
private:
bool stopFlag = false;
bool stateFlag = true;
vector<TemperatureSensor<float>> temperatureSensors;
vector<LightSensor<bool>> lightSensors;
vector<SoundSensor<int>> soundSensors;
vector<HumiditySensor<float>> humiditySensors;
Server server;

/**
 * @brief Tâche exécutée en parallèle pour un capteur donné.
 *
 * Cette méthode est exécutée en parallèle pour un capteur donné. Elle récupère les données du capteur,
 * les écrit dans la console et dans un fichier, puis attend pendant un certain intervalle avant de répéter
 * le processus. La tâche continue de s'exécuter tant que le drapeau d'arrêt n'est pas activé et que l'état
 * des tâches est actif.
 *
 * @param sensor Référence vers le capteur sur lequel la tâche est exécutée.
 * @tparam T Type de données du capteur.
 */
template <typename T>
void sensorTask(Sensor<T>& sensor) {

while (!shouldStop())
{
       while (stateThread()) {
        
        {
            server.consoleWrite(sensor.getSensorType(), sensor.getData(), sensor.getSensorId());
            std::cout << std::endl;
        }
        
        {
            server.fileWrite(sensor.getSensorType(), sensor.getData(), sensor.getSensorId());
        }
        sensor.aleaGenVal();
        std::this_thread::sleep_for(std::chrono::milliseconds(sensor.getSensorInterval())); // Attendre avant de vérifier à nouveau
    } 
}
}



public:

    /**
     * @brief Constructeur de la classe Scheduler.
     *
     * @param sizeTemperatureVector Nombre de capteurs de température à créer.
     * @param sizeLightVector Nombre de capteurs de lumière à créer.
     * @param sizeSoundVector Nombre de capteurs de son à créer.
     * @param sizeHumidityVector Nombre de capteurs d'humidité à créer.
     * @param intervalTemperature Intervalle de mise à jour pour les capteurs de température (en millisecondes).
     * @param intervalLight Intervalle de mise à jour pour les capteurs de lumière (en millisecondes).
     * @param intervalSound Intervalle de mise à jour pour les capteurs de son (en millisecondes).
     * @param intervalHumidity Intervalle de mise à jour pour les capteurs d'humidité (en millisecondes).
     */
Scheduler(int sizeTemperatureVector, int sizeLightVector, int sizeSoundVector, int sizeHumidityVector ,int intervalTemperature = 2000,  
int intervalLight = 2500,        
int intervalSound = 3000,        
int intervalHumidity = 4000 ) {

        while (sizeTemperatureVector > 0 || sizeLightVector > 0 || sizeSoundVector > 0 || sizeHumidityVector > 0) {

            if (sizeTemperatureVector > 0) {
                TemperatureSensor<float> temperatureSensor(intervalTemperature);
                temperatureSensors.push_back(temperatureSensor); // Ajouter le capteur au vecteur
                sizeTemperatureVector--;
            }
            if (sizeLightVector > 0) {
                LightSensor<bool> lightSensor(intervalLight);
                lightSensors.push_back(lightSensor); // Ajouter le capteur au vecteur
                sizeLightVector--;
            }
            if (sizeSoundVector > 0) {
                SoundSensor<int> soundSensor(intervalSound);
                soundSensors.push_back(soundSensor); // Ajouter le capteur au vecteur
                sizeSoundVector--;
            }
            if (sizeHumidityVector > 0) {
                HumiditySensor<float> humiditySensor(intervalHumidity);
                humiditySensors.push_back(humiditySensor); // Ajout capteur au vecteur
                sizeHumidityVector--;
            }
        }
        
    }
        

    /**
     * @brief Constructeur de copie de la classe Scheduler.
     *
     * @param other Objet Scheduler à copier.
     */
    Scheduler(const Scheduler &other) {
        temperatureSensors = other.temperatureSensors;
        lightSensors = other.lightSensors;
        soundSensors = other.soundSensors;
        humiditySensors = other.humiditySensors;
        server = other.server;
    }

    /**
     * @brief Opérateur d'affectation de la classe Scheduler.
     *
     * @param other Objet Scheduler à copier.
     * @return Référence vers l'objet actuel après l'affectation.
     */
    Scheduler &operator=(const Scheduler &other) {
        if (this != &other) {
            temperatureSensors = other.temperatureSensors;
            lightSensors = other.lightSensors;
            soundSensors = other.soundSensors;
            humiditySensors = other.humiditySensors;
            server = other.server;
        }
        return *this;
    }

    /**
     * @brief Destructeur de la classe Scheduler.
     */
    ~Scheduler() {}


    /**
     * @brief Définit les intervalles de mise à jour des capteurs.
     *
     * @param temperatureInterval Intervalle de mise à jour pour les capteurs de température (en millisecondes).
     * @param lightInterval Intervalle de mise à jour pour les capteurs de lumière (en millisecondes).
     * @param soundInterval Intervalle de mise à jour pour les capteurs de son (en millisecondes).
     * @param humidityInterval Intervalle de mise à jour pour les capteurs d'humidité (en millisecondes).
     */
    void setSensorIntervals(int temperatureInterval, int lightInterval, int soundInterval, int humidityInterval) {
        for(auto& sensor : temperatureSensors) {
            sensor.setSensorInterval(temperatureInterval);
        }

        for(auto& sensor : lightSensors) {
            sensor.setSensorInterval(lightInterval);
        }

        for(auto& sensor : soundSensors) {
            sensor.setSensorInterval(soundInterval);
        }

        for(auto& sensor : humiditySensors) {
            sensor.setSensorInterval(humidityInterval);
        }
    }


    /**
     * @brief Démarre les tâches des capteurs.
     *
     * Cette méthode lance les tâches des capteurs en parallèle.
     */

    void startTasks() {

     std::vector<std::thread> threads;

     for (auto& temperatureSensor : temperatureSensors) {
        threads.emplace_back([&](){this->sensorTask(temperatureSensor);} );
     }

     for (auto& lightSensor : lightSensors) {
        threads.emplace_back([&](){this->sensorTask(lightSensor);} );
     }

     for (auto& soundSensor : soundSensors) {
         threads.emplace_back([&](){this->sensorTask(soundSensor);} );
     }

     for (auto& humiditySensor : humiditySensors) {
         threads.emplace_back([&](){this->sensorTask(humiditySensor);} );
     }

     // Joindre tous les threads
     for (auto& thread : threads) {
         thread.join();
     }
    }

    /**
     * @brief Change l'état des tâches des capteurs.
     *
     * Cette méthode permet de changer l'état des tâches des capteurs (actif ou inactif).
     */
    void changeStateThread() {
        stateFlag = !stateFlag;
    }

    /**
     * @brief Vérifie l'état des tâches des capteurs.
     *
     * @return true si les tâches des capteurs sont actives, false sinon.
     */
    bool stateThread(){
        return this->stateFlag;
    }
    /**
     * @brief Arrête les tâches des capteurs.
     *
     * Cette méthode permet d'arrêter toutes les tâches des capteurs.
     */
    void stopThread() {
        stopFlag = true;
    }
    /**
     * @brief Vérifie si les tâches des capteurs doivent s'arrêter.
     *
     * @return true si les tâches des capteurs doivent s'arrêter, false sinon.
     */
    bool shouldStop() const {
        return this->stopFlag;
    }


    };


#endif // SCHEDULER_H

