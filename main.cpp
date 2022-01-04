#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <numeric>
#include <fstream>
#include <regex>
#include <sstream>
#include <algorithm>
#include <chrono>

using namespace std;

class studentai {
  public:     
    vector <string> vardas;
    vector <string> pavarde;
    vector <vector <int>> pazymiai;
    vector <float> egzaminas;
    vector <float> vidurkis;
    vector <float> mediana;

    // vector <string> vardas_daugiau;
    // vector <string> pavarde_daugiau;
    // vector <vector <int>> pazymiai_daugiau;
    // vector <float> egzaminas_daugiau;
    // vector <float> vidurkis_daugiau;
    // vector <float> mediana_daugiau;

    studentai()
    {
        vardas = {};
        pavarde = {};
        pazymiai = {};
        egzaminas = {};
        vidurkis = {};
        mediana = {};
        // vardas_daugiau = {};
        // pavarde_daugiau = {};
        // pazymiai_daugiau = {};
        // egzaminas_daugiau = {};
        // vidurkis_daugiau = {};
        // mediana_daugiau = {};
        cout << "Įrašai sukurti " << "\n";
    }

    ~studentai(){
        cout << "Įrašai ištrinti " << "\n";
    }

    studentai(const studentai& other) = delete;

    studentai& operator=(const studentai&) = delete; 

    void print_result(int budas)
    {
        vector <int> paz;
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
                cout << setprecision(2) << fixed << egzaminas[i] << "\n";
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

    void perkelti_studenta(int i, studentai &kiti){
        kiti.vardas.push_back(vardas[i]);
        kiti.pavarde.push_back(pavarde[i]);
        kiti.pazymiai.push_back(pazymiai[i]);
        kiti.egzaminas.push_back(egzaminas[i]);
        kiti.vidurkis.push_back(vidurkis[i]);
        kiti.mediana.push_back(mediana[i]);
    }

    void skirstymas(int pagal, studentai &blogi, studentai &geri){
        int senas_indeksas;
        if (pagal == 0){
            for (int i = vardas.size()-1; i >= 0; i--){
                if (vidurkis[i]>=5){
                    perkelti_studenta(i, geri);
                }
                else{
                    perkelti_studenta(i, blogi);
                }
            }
        }
        else{
            for (int i = vardas.size()-1; i >= 0; i--){
                if (mediana[i]>=5){
                    perkelti_studenta(i, geri);
                }
                else{
                    perkelti_studenta(i, blogi);
                }
            }
        }
    }

    // void irasyti_gerus_stud(string pavadinimas){
    //     string eilute = "";
    //     vector <int> paz = {};
    //     ofstream myfile;
    //     for (int i = 0; i < vardas_daugiau.size(); i++){
    //         eilute += vardas_daugiau[i] + "," + pavarde_daugiau[i] + ",";
    //         paz = pazymiai_daugiau[i];
    //         for (int j = 0; j < paz.size(); j++){
    //             eilute += to_string(paz[j]) + ",";
    //         }
    //         eilute += to_string(egzaminas_daugiau[i]) + " \n" ;
    //     }
    //     myfile.open(pavadinimas, ofstream::trunc);
    //     myfile << eilute;
    //     myfile.close();
    // }

    void irasyti_likusius_stud(string pavadinimas){
        string eilute = "";
        vector <int> paz = {};
        ofstream myfile;
        for (int i = 0; i < vardas.size(); i++){
            eilute += vardas[i] + "," + pavarde[i] + ",";
            paz = pazymiai[i];
            for (int j = 0; j < paz.size(); j++){
                eilute += to_string(paz[j]) + ",";
            }
            eilute += to_string(egzaminas[i]) + " \n" ;
        }
        myfile.open(pavadinimas, ofstream::trunc);
        myfile << eilute;
        myfile.close();
    }

void SplitString(string s, vector<string> &v){
	
	string temp = "";
	for(int i=0;i<s.length();++i){
		
		if(s[i]==','){
			v.push_back(temp);
			temp = "";
		}
		else{
			temp.push_back(s[i]);
		}
		
	}
	v.push_back(temp);
	
}

void nuskaityti_is_failo(string pavadinimas){
    string eilute, tmp;
    vector <string> irasai;
    vector <int> pazim;
    ifstream rezultatai(pavadinimas);
    stringstream ss(eilute);
    float vid, med;
    int a, j;
    while (getline(rezultatai, eilute)){
        SplitString(eilute, irasai);
        a = stoi(irasai.back());
        egzaminas.push_back(a);
        vardas.push_back(irasai[0]);
        pavarde.push_back(irasai[1]);
        for(int i=2;i<(irasai.size()-1);++i){
            j = stoi(irasai[i]); 
            pazim.push_back(j);
            }
        pazymiai.push_back(pazim);

        vid = (float)accumulate(pazim.begin(), pazim.end(),0.0);
        vid = (float)vid / (float)pazim.size();
        vid = (float)vid * 0.4 + 0.6 * (float)egzaminas.back();

        med = gauti_mediana();
        med = (float)med * 0.4 + 0.6 * (float)egzaminas.back();

        vidurkis.push_back(vid);
        mediana.push_back(vid);

        irasai = {};
        pazim = {};

        }
    }

    void istrinti_irasus(){
        vardas = {};
        pavarde = {};
        pazymiai = {};
        egzaminas = {};
        vidurkis = {};
        mediana = {};
        // vardas_daugiau = {};
        // pavarde_daugiau = {};
        // pazymiai_daugiau = {};
        // egzaminas_daugiau = {};
        // vidurkis_daugiau = {};
        // mediana_daugiau = {};
    }
    

};

int main(){
    studentai grupe; 
    grupe.generuoti_studentus(1000, 4);
    grupe.print_result(0);
    // negalimas priskyrimas:
    // grupe = grupe2;
    return 0;
}