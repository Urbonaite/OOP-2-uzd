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
                // paz = pazymiai[i];
                // for (int j = 0; j < paz.size(); j++){
                //     cout << setprecision(2) << fixed << paz[j] << " ";
                // }
                // cout << "\n";
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

    void irasyti_gerus_stud(string pavadinimas){
        string eilute = "";
        vector <int> paz = {};
        ofstream myfile;
        // cout << vardas_daugiau.size();
        for (int i = 0; i < vardas_daugiau.size(); i++){
            eilute += vardas_daugiau[i] + "," + pavarde_daugiau[i] + ",";
            paz = pazymiai_daugiau[i];
            for (int j = 0; j < paz.size(); j++){
                eilute += to_string(paz[j]) + ",";
            }
            eilute += to_string(egzaminas_daugiau[i]) + " \n" ;
        }
        myfile.open (pavadinimas, ofstream::trunc);
        myfile << eilute;
        myfile.close();
    }

    void irasyti_likusius_stud(string pavadinimas){
        string eilute = "";
        vector <int> paz = {};
        ofstream myfile;
        // cout << vardas.size();
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
        vardas_daugiau = {};
        pavarde_daugiau = {};
        pazymiai_daugiau = {};
        egzaminas_daugiau = {};
        vidurkis_daugiau = {};
        mediana_daugiau = {};
    }
    

};



int main(){
    studentai grupe;
    auto start_0 = chrono::high_resolution_clock::now();
    grupe.generuoti_studentus(10000, 4);
    auto end_0 = chrono::high_resolution_clock::now();
    chrono::duration<double> diff_0 = end_0 - start_0;
    cout << "100,000 studentų generavimas ir įrašymas į klasę užtruko: " << diff_0.count() << "s \n\n";

    auto start_1 = chrono::high_resolution_clock::now();
    grupe.skirstymas(1);
    auto end_1 = chrono::high_resolution_clock::now();
    chrono::duration<double> diff_1 = end_1 - start_1;
    cout << "100,000 studentų skirstymas užtruko: " << diff_1.count() << "s \n\n";

    auto start_2 = chrono::high_resolution_clock::now();
    grupe.irasyti_likusius_stud("like_studentai.txt");
    grupe.irasyti_gerus_stud("geri_studentai.txt");
    auto end_2 = chrono::high_resolution_clock::now();
    chrono::duration<double> diff_2 = end_2 - start_2;
    cout << "100,000 studentų failų įrašymas užtruko: " << diff_2.count() << "s \n\n";

    grupe.istrinti_irasus();

    auto start_3 = chrono::high_resolution_clock::now();
    grupe.nuskaityti_is_failo("like_studentai.txt");
    grupe.nuskaityti_is_failo("geri_studentai.txt");
    auto end_3 = chrono::high_resolution_clock::now();
    chrono::duration<double> diff_3 = end_3 - start_3;
    cout << "100,000 nuskaitymas iš failų užtruko: " << diff_3.count() << "s \n\n";

    // grupe.print_result(0);
    return 0;
}
