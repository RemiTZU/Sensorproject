#include <iostream>
#include <fstream>
#include <string>
#include <Scheduler.hpp>
#include <Server.hpp>
#include <sensor.hpp>
#include <thread>
#include<chrono>
using namespace std;



int main(int argc, char *argv[]) {

    if (argc<4) {
        std::cout << "Erreur : Veuillez entrer le nombre de sensor pour chaque type de sensor en arguments." << std::endl;
        std::cout << "premier argument : nombre de sensor Humidity" << std::endl;
        std::cout << "deuxième argument : nombre de sensor Sound" << std::endl;
        std::cout << "troisième argument : nombre de sensor Light" << std::endl;
        std::cout << "quatrième argument : nombre de sensor Temperature" << std::endl;
        cout << "Par exemple : ./votre_programme 2 1 3 4" << endl;
        return 1;
    }
    cout << "Bienvenue dans notre programme de surveillance sensorielle!" << endl;
    cout << "Ce programme surveille divers capteurs (humidité, son, lumière, température)" << endl;
    cout << "et enregistre les données dans des fichiers texte." << endl;
    cout << "Utilisez les arguments en ligne de commande pour spécifier le nombre de capteurs de chaque type." << endl;
    cout << "Par exemple : ./votre_programme 2 1 3 4" << endl;
    cout << "Cela signifie 2 capteurs d'humidité, 1 capteur de son, 3 capteurs de lumière et 4 capteurs de température." << endl;
    cout << "Tapez 'f' à tout moment pour arrêter l'envoi des données." << endl;
    cout << "Tapez 'o' pour reprendre l'envoie"<<endl;
    std::cout << "Tapez 'q' pour arrêter le programme "<<endl;
    
    std::string programActivation;
    std::cout << "Tapez 's' pour lancer le programme ou 'quit' pour le stopper "<<endl;
    std::cin >> programActivation;

    while (programActivation!="s" && programActivation!="q")
    {
        std::cerr << "Commande non reconnue tapez 'start' pour lancer le programme ou 'quit' pour le stopper "<<endl;
        std::cin >> programActivation;
    }
    

    if (programActivation == "s")
    {

        int numberOfHumiditySensor = std::atoi(argv[1]);
        int numberOfSoundSensor = std::atoi(argv[2]);
        int numberOfLightSensor = std::atoi(argv[3]);
        int numberOfTemperatureSensor = std::atoi(argv[4]);
        int humidityInterval = 0;
        int soundInterval = 0;
        int lightInterval = 0;
        int temperatureInterval = 0;
        std::string input = "";
        Scheduler scheduler(numberOfTemperatureSensor, numberOfLightSensor, numberOfSoundSensor, numberOfHumiditySensor);
        cout<<"Voulez-vous définir des intervalles de temps pour vos capteurs ? : Y/N"<<endl;
        cin>>input;        
        if (input == "Y" || input == "y")
        {
            cout<<"intervalle d'humidité"<<endl;
            cin>>humidityInterval;
            cout<<"intervalle de son"<<endl;
            cin>>soundInterval;            
            cout<<"intervalle de lumière"<<endl;
            cin>>lightInterval;            
            cout<<"intervalle de temperature"<<endl;
            cin>>temperatureInterval;
            scheduler.setSensorIntervals(temperatureInterval,lightInterval,soundInterval,humidityInterval);

            
        }if (input == "N" || input =="n")
        {
            cout<<"Intervalles définie par défaut"<<endl;
        }
        
        thread tasksThread([&]() {
            scheduler.startTasks();
        });
            cout<<"suite du programme"<<endl;
        
        input = "o";
        while (true) {
            
            cin>>input;
            if (input == "f" && scheduler.stateThread() == true) {
                cout<<"STOP L'ENVOIE DES DONNÉES"<<endl;
                cout<<scheduler.stateThread()<<endl;
                scheduler.changeStateThread();
                cout<<scheduler.stateThread()<<endl;
            }else if (input == "o" && scheduler.stateThread()==false)
            {
                cout<<"ENVOIE DES DONNÉES"<<endl;
                cout<<scheduler.stateThread()<<endl;
                scheduler.changeStateThread();
                cout<<scheduler.stateThread()<<endl;
            }else if(input=="e"){

                //extract in csv date id data
            }
            else if(input == "q")
            {
                if (scheduler.stateThread() == true)
                {
                    scheduler.changeStateThread();
                }
                scheduler.stopThread();
                break;
            }else if ((input == "o" && scheduler.stateThread()==true)||(input == "f" && scheduler.stateThread() ==false))
            {
                if (input == "o")
                {
                    scheduler.changeStateThread();
                }
                cout<<"Votre commande ne coincide pas avec l'etat de l'affichage --> pour activer l'affichage ce dernier doit être en pause. "<<endl;
                cout<<"Tapez 'f' pour arrêter l'envoie des données"<<endl;
                cout<<"Tapez 'o' pour reprendre l'envoie des données"<<endl;
                cout<<"Tapez 'q' pour quitter le programme"<<endl;
                
                if (input == "o")
                {
                    std::this_thread::sleep_for(std::chrono::seconds(7));
                    scheduler.changeStateThread();
                }
                
                
                
            }else if (input.empty()){}
            else {
                std::cout << "Commande invalide. Veuillez taper 'f' pour arrêter l'envoi des données 'o' pour reprendre l'envoie des données et 'q' pour quitter le programme";
                
                
            }
            input = "";
        }
        tasksThread.join();

    }else
    {
        std::cout << "Fin du programme.";
        return 0;
    }
    
    
    
    

    std::cout << "Fin du programme." << std::endl;
    // ajouts...
    // Attendre que les tâches des capteurs se terminent (optionnel)
    

    return 0; 
}
