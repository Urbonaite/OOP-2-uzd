#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <numeric>
#include <fstream>
#include <regex>

using namespace std;

class studentai {
  public:     
    vector <string> vardas = {};
    vector <string> pavarde = {};
    vector <vector <int>> pazymiai = {};
    vector <float> egzaminas = {};
    vector <float> vidurkis = {};
    vector <float> mediana = {};


    vector <string> vardas_daugiau = {};
    vector <string> pavarde_daugiau = {};
    vector <vector <int>> pazymiai_daugiau = {};
    vector <float> egzaminas_daugiau = {};
    vector <float> vidurkis_daugiau = {};
    vector <float> mediana_daugiau = {};

    void print_result(int budas)
    {
        cout << "\n";
        cout << "Vardas ";
        cout << "Pavarde ";
        cout << "Rezultatas \n";
        for (int i = 0; i < vardas.size(); i++)
        {
            cout << vardas[i] << " ";
            cout << pavarde[i] << " ";
            if (budas == 0){
                cout << setprecision(2) << fixed << vidurkis[i] << "\n";
            }
            else{
                cout << setprecision(2) << fixed << mediana[i] << "\n";
            }
    }
    cout << "\n";
    }

    double gauti_mediana()
    {
        vector <int> paz = pazymiai.back();
        int size = paz.size();
        if (size == 0){
            return 0;
            }
        else{
            sort(paz.begin(), paz.end());
            if (size % 2 == 0){
                return ((float)paz[size / 2 - 1] + (float)paz[size / 2]) / 2;
                }
            else {
                return paz[size / 2];
                }
            }
    }

    int ats_paz(){
        // srand(time(NULL));
        return rand() % 10 + 1;
    }

    void generuoti_studenta(int paz_kiekis){
        float vid;
        float med;
        string vard, pavard;
        vector <int> paz;
        egzaminas.push_back(ats_paz());
        for (int i = 0; i < paz_kiekis; i++){
            paz.push_back(ats_paz());
        }
        pazymiai.push_back(paz);
        vid = (float)accumulate(paz.begin(), paz.end(),0.0);
        vid = (float)vid / (float)paz.size();
        vid = (float)vid * 0.4 + 0.6 * (float)egzaminas.back();

        med = gauti_mediana();
        med = (float)med * 0.4 + 0.6 * (float)egzaminas.back();

        vidurkis.push_back(vid);
        mediana.push_back(vid);

        vard = "Vardas" + to_string(vardas.size());
        pavard = "Pavarde" + to_string(vardas.size());

        vardas.push_back(vard);
        pavarde.push_back(pavard);
    }

    void generuoti_studentus(int stud_kiekis, int paz_kiekis){
        for (int i = 0; i < stud_kiekis; i++){
            generuoti_studenta(paz_kiekis);
        }
    }

    void perkelti_studenta(int i){
        vardas_daugiau.push_back(vardas[i]);
        pavarde_daugiau.push_back(pavarde[i]);
        pazymiai_daugiau.push_back(pazymiai[i]);
        egzaminas_daugiau.push_back(egzaminas[i]);
        vidurkis_daugiau.push_back(vidurkis[i]);
        mediana_daugiau.push_back(mediana[i]);
        cout << vidurkis[i] << " ";

        vardas.erase(vardas.begin() + i);
        pavarde.erase(pavarde.begin() + i);
        pazymiai.erase(pazymiai.begin() + i);
        egzaminas.erase(egzaminas.begin() + i);
        vidurkis.erase(vidurkis.begin() + i);
        mediana.erase(mediana.begin() + i);
    }

    void skirstymas(int pagal){
        int senas_indeksas;
        if (pagal == 0){
            for (int i = vardas.size(); i >= 0; i--){
                if (vidurkis[i]>=5){
                    perkelti_studenta(i);
                }
            }
        }
        else{
            for (int i = vardas.size(); i >= 0; i--){
                if (mediana[i]>=5){
                    perkelti_studenta(i);
                }
            }
        }
    }

    void irasyti_gerus_stud(){
        string eilute = "";
        vector <int> paz = {};
        ofstream myfile;
        cout << vardas_daugiau.size();
        for (int i = 0; i < vardas_daugiau.size(); i++){
            eilute = eilute + vardas_daugiau[i] + ", " + pavarde_daugiau[i] + ", ";
            paz = pazymiai_daugiau[i];
            for (int j = 0; j < paz.size(); j++){
                eilute = eilute + to_string(paz[j]) + ", ";
                }
            eilute = eilute + to_string(egzaminas_daugiau[i]) + " \n " ;
        myfile.open ("geri_studentai.txt");
        myfile << eilute;
        myfile.close();
    }
}

    void irasyti_likusius_stud(){
        string eilute = "";
        vector <int> paz = {};
        ofstream myfile;
        cout << vardas.size();
        for (int i = 0; i < vardas.size(); i++){
            eilute = eilute + vardas[i] + ", " + pavarde[i] + ", ";
            paz = pazymiai[i];
            for (int j = 0; j < paz.size(); j++){
                eilute = eilute + to_string(paz[j]) + ", ";
                }
            eilute = eilute + to_string(egzaminas[i]) + " \n " ;
        myfile.open ("like_studentai.txt");
        myfile << eilute;
        myfile.close();
    }
}

};



int main(){
    studentai grupe;
    grupe.generuoti_studentus(500, 20);
    grupe.skirstymas(0);
    grupe.print_result(0);
    grupe.irasyti_gerus_stud();
    grupe.irasyti_likusius_stud();
    return 0;
}