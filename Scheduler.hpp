#ifndef SCHEDULER_H
#define SCHEDULER_H
using namespace std;
#include <iostream>
#include <thread>
#include <vector>
#include <sensor.hpp> 
#include <Server.hpp>
#include <mutex>
#include <chrono>
#include <ctime>



class Scheduler {
private:
bool stopFlag = false;
bool stateFlag = true;
vector<TemperatureSensor<float>> temperatureSensors;
vector<LightSensor<bool>> lightSensors;
vector<SoundSensor<int>> soundSensors;
vector<HumiditySensor<float>> humiditySensors;
Server server;
std::mutex inputMutex;

template <typename T>
void sensorTask(Sensor<T>& sensor) {
// faire une boucle pour stopper et une boucle pour changer l'etat donc deux flag un etat un stop boucle sup pour le stop qui est changé dans la fontion stop et boucle inf qui a pour condition state
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
        

    // Constructeur par copie
    Scheduler(const Scheduler &other) {
        temperatureSensors = other.temperatureSensors;
        lightSensors = other.lightSensors;
        soundSensors = other.soundSensors;
        humiditySensors = other.humiditySensors;
        server = other.server;
    }

    // Opérateur d'affectation
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

    // Destructeur
    ~Scheduler() {}



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

    void changeStateThread() {
        stateFlag = !stateFlag;
    }
    bool stateThread(){
        return this->stateFlag;
    }
    void stopThread() {
        stopFlag = true;
    }
    bool shouldStop() const {
        return this->stopFlag;
    }


    };


#endif // SCHEDULER_H

// class SensorTask {
// public:
//     SensorTask(Server& server) : server(server) {}

//     template <typename T>
//     void operator()(Sensor<T>& sensor) {
//         // Envoyer les données au serveur
//         server.consoleWrite(sensor.getData());
//     }

// private:
//     Server& server;
// };

    // template <typename Function, typename... Args>
    // void Scheduler::ScheduleTask(int interval, Function&& func, Args&&... args) {
    //     std::thread([interval, func, args...] {
    //         while (true) {
    //             std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    //             (std::forward<Function>(func))(std::forward<Args>(args)...);
    //         }
    //     }).detach();
    // }