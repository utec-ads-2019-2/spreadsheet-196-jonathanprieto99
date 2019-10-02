#include <iostream>
#include <string>
using namespace std;

int csheets;
int columnas;
int filas;

class Hoja{
    int ** solucion;
    bool ** resuelto;
    string ** celdas;
    int columnas;
    int filas;

public:
    Hoja(int columnas, int filas):columnas(columnas), filas(filas){
        //Celdas
        celdas = new string*[filas];
        //Resuelto
        resuelto = new bool*[filas];
        //Resultado
        solucion = new int*[filas];

        //Generando
        string* nceldas = new string[filas*columnas];

        bool* nresuelto = new bool[filas*columnas];

        int* nsolucion = new int[filas*columnas];


        for(int i=0; i!=filas; ++i){

            celdas[i]= &nceldas[columnas*i];

            solucion[i]= &nsolucion[columnas*i];

            resuelto[i]= &nresuelto[columnas*i];
        }
    };

    void ingresar(){
        string celda;
        for(int i=0; i!=filas; ++i){
            for(int j=0;j!=columnas;++j){
                cin>>celda;
                celdas[i][j]=celda;
                resuelto[i][j]=0;
            }
        }
    }

    int ejecutar(string formula){
        string celda;
        int resultado=0;

        for(int i=0; i<formula.size(); ++i){

            if(formula[i]!= '+'){
                celda= celda+formula[i];
            }

            else{
                resultado = recorrer(celda) + resultado;
                celda.clear();
            }
        }

        resultado= recorrer(celda) + resultado;
        return resultado;
    }
    void resolver(){
        for(int i=0; i!=filas; ++i){

            for(int j=0; j!=columnas; ++j){

                if(!resuelto[i][j]) {

                    if (celdas[i][j][0] == '=') {
                        solucion[i][j] = ejecutar(celdas[i][j].substr(1, celdas[i][j].size() - 1));
                    }

                    else {
                        solucion[i][j] = stoi(celdas[i][j]);
                    }

                    resuelto[i][j]=1;
                }
            }
        }
    }

    int recorrer(string celda){

        int filas=0;
        int columnas=0;
        int solu;
        int tamano=celda.size();

        for(int i=0; i!=tamano; ++i){
            //Rango Have Care
            if(celda[i] >= 51 and celda[i] <=105){
                //No cambiar!
                columnas= columnas*(26);
                columnas= columnas+(celda[i]-(64));
            }

            else{
                //cout<<"i="<<i<<endl;
                //cout<<"tamano="<<tamano-1<<endl;
                //cout<<celda.substr(i,tamano-i)<<endl;
                filas= std::stoi(celda.substr(i,tamano-i));
                break;
            }
        }

        filas--;
        columnas--;

        if(celdas[filas][columnas][0]=='='){
            solu=ejecutar(celdas[filas][columnas].substr(1,celdas[filas][columnas].size()-1));
        }

        else {
            solu=stoi(celdas[filas][columnas]);
        }

        solucion[filas][columnas]=solu;
        resuelto[filas][columnas]=1;
        return solu;
    }

    void imprimir(){
        for(int i=0; i!=filas; ++i){
            for(int j=0; j!=columnas; ++j){
                if(j){
                    cout << ' ';
                }
                cout << solucion[i][j];
            }
            cout << '\n';
        }
    }
};

int main() {

    cin>>csheets;
    while(cin){
        cin>>columnas>>filas;
        Hoja hoja1(columnas,filas);
        hoja1.ingresar();
        hoja1.resolver();
        hoja1.imprimir();
    }
    return 0;
}

