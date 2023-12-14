#ifndef SENSORS_H
#define SENSORS_H


#include <string>
#include <random>




/**
 * @brief Classe générique représentant un capteur.
 *
 * Cette classe générique représente un capteur avec une valeur de type T, un type de capteur et un intervalle
 * de mesure. Elle expose des méthodes pour récupérer les données du capteur, son type et son intervalle, et
 * permet de définir un nouvel intervalle.
 *
 * @tparam T Type de données du capteur.
 */
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
    /**
     * @brief Constructeur par défaut d'un capteur.
     * @param type Type du capteur.
     * @param intervalleSensor Intervalle de capture des données.
     */
    Sensor(const std::string& type = "",const int intervalleSensor=0) : sensorType(type),intervalle(intervalleSensor) {
        id = ++nextId;
    }

    /**
     * @brief Récupère les données du capteur.
     * @return Les données du capteur.
     */
    T getData() const {
        return this->valSense;
    }
    /**
     * @brief Récupère le type de capteur.
     * @return Le type de capteur.
     */
    std::string getSensorType() const {
        return this->sensorType;
    }
    /**
     * @brief Récupère l'intervalle de mesure du capteur.
     * @return L'intervalle de mesure du capteur.
     */
    int getSensorInterval() const {
        return this->intervalle;
    }
    /**
     * @brief Récupère l'identifiant unique du capteur.
     * @return L'identifiant unique du capteur.
     */
    int getSensorId() const{
            return this->id;
        }
    /**
     * @brief Définit un nouvel intervalle de mesure pour le capteur.
     * @param interval Nouvel intervalle de mesure.
     */
    void setSensorInterval(int interval) {
        this->intervalle = interval;
    }
    /**
     * @brief Méthode virtuelle pure pour générer une valeur aléatoire du capteur.
     */
    virtual void aleaGenVal() = 0;
};


/**
 * @brief Classe représentant un capteur de température.
 *
 * Cette classe représente un capteur de température 
 *
 * @tparam T Type de données du capteur.
 */
template <typename T>
class TemperatureSensor : public Sensor<float> {
private:
static int nextTempId;
public:
    // Constructeur par défaut qui icrémente un id commun à chaque type de sensor pour que le prochain sensor temperature creer prenne l'id du sensor actuel + 1
    TemperatureSensor(int interval) : Sensor<float>("Temperature",interval) {
        aleaGenVal();
        id = ++nextTempId;
    }

    /**
     *  @brief Méthode qui génère des valeurs aléatoires dans l'intervalle [-20.0f, 75.0f].*/

    void aleaGenVal() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(-20.0f, 75.0f);
        valSense = dis(gen);
    }
};


/**
 * @brief Classe représentant un capteur de lumière.
 *
 * Cette classe représente un capteur de lumière
 *
 * @tparam T Type de données du capteur.
 */

template <typename T>
class LightSensor : public Sensor<bool> {
private:
static int nextTempId;
public:
     // Constructeur par défaut qui icrémente un id commun à chaque type de sensor pour que le prochain sensor temperature creer prenne l'id du sensor actuel + 1
    LightSensor(int interval) : Sensor<bool>("Light",interval) {
        aleaGenVal();
        id = ++nextTempId;
    }

    /**
     *  @brief Méthode qui génère des valeurs aléatoires dans l'intervalle [0,1].*/

    void aleaGenVal() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 1);
        valSense = dis(gen) == 1;
    }
};


/**
 * @brief Classe représentant un capteur de son.
 *
 * Cette classe représente un capteur de son .
 *
 * @tparam T Type de données du capteur.
 */

template <typename T>
class SoundSensor : public Sensor<int> {
private:
static int nextTempId;
public:
    // Constructeur par défaut qui icrémente un id commun à chaque type de sensor pour que le prochain sensor temperature creer prenne l'id du sensor actuel + 1
    SoundSensor(int interval) : Sensor<int>("Sound",interval) {
        aleaGenVal();
        id = ++nextTempId;
    }

    /**
     *  @brief Méthode qui génère des valeurs aléatoires dans l'intervalle [0,1].*/
    void aleaGenVal() override {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(0, 200);
        valSense = dis(gen);
    }
};

/**
 * @brief Classe représentant un capteur d'humidité.
 *
 * Cette classe représente un capteur d'humidité qui génère des valeurs aléatoires dans l'intervalle [0.0f, 100.0f].
 *
 * @tparam T Type de données du capteur.
 */

template <typename T>
class HumiditySensor : public Sensor<float> {
private:
static int nextTempId;
public:
    // Constructeur par défaut...
    HumiditySensor(int interval) : Sensor<float>("Humidity",interval) {
        id = ++nextTempId;
        aleaGenVal();
    }

    // Méthode pour générer une valeur aléatoire...
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