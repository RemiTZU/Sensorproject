#ifndef SENSORS_H
#define SENSORS_H

#include <iostream>
#include <string>
#include <random>
#include <typeinfo>

template <typename T>
class Sensor {
private:
static int nextId;
protected:
    T valSense;
    std::string sensorType;
    int intervalle;
    int id;

public:
    // Constructeur par défaut
    Sensor(const std::string& type = "",const int intervalleSensor=0) : sensorType(type),intervalle(intervalleSensor) {
        id = ++nextId;
    }

    // Méthode pour envoyer les données au serveur
    T getData() const {
        return this->valSense;
    }
// Méthode pour envoyer le type de sensor au serveur
    std::string getSensorType() const {
        return this->sensorType;
    }
// Méthode pour envoyer l'intervalle de sensor au serveur
    int getSensorInterval() const {
        return this->intervalle;
    }
    int getSensorId() const{
            return this->id;
        }
    void setSensorInterval(int interval) {
        this->intervalle = interval;
    }
    // Méthode pour générer une valeur aléatoire (virtuelle pure)
    virtual void aleaGenVal() = 0;
};

template <typename T>
class TemperatureSensor : public Sensor<float> {
private:
static int nextTempId;
public:
    // Constructeur par défaut
    TemperatureSensor(int interval) : Sensor<float>("Temperature",interval) {
        aleaGenVal();
        id = ++nextTempId;
    }

    // Méthode pour générer une valeur aléatoire
    void aleaGenVal() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-20.0f, 75.0f);
        valSense = dis(gen);
    }
};

template <typename T>
class LightSensor : public Sensor<bool> {
private:
static int nextTempId;
public:
    // Constructeur par défaut
    LightSensor(int interval) : Sensor<bool>("Light",interval) {
        aleaGenVal();
        id = ++nextTempId;
    }

    // Méthode pour générer une valeur aléatoire
    void aleaGenVal() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 1);
        valSense = dis(gen) == 1;
    }
};

template <typename T>
class SoundSensor : public Sensor<int> {
private:
static int nextTempId;
public:
    // Constructeur par défaut
    SoundSensor(int interval) : Sensor<int>("Sound",interval) {
        aleaGenVal();
        id = ++nextTempId;
    }

    // Méthode pour générer une valeur aléatoire
    void aleaGenVal() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 200);
        valSense = dis(gen);
    }
};

template <typename T>
class HumiditySensor : public Sensor<float> {
private:
static int nextTempId;
public:
    // Constructeur par défaut
    HumiditySensor(int interval) : Sensor<float>("Humidity",interval) {
        id = ++nextTempId;
        aleaGenVal();
    }

    // Méthode pour générer une valeur aléatoire
    void aleaGenVal() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(0.0f, 100.0f);
        valSense = dis(gen);
    }
};

template <typename T>
int Sensor<T>::nextId = 0;

template <typename T>
int TemperatureSensor<T>::nextTempId = 0;

template <typename T>
int HumiditySensor<T>::nextTempId = 0;


template <typename T>
int LightSensor<T>::nextTempId = 0;

template <typename T>
int SoundSensor<T>::nextTempId = 0;

#endif // SENSORS_H