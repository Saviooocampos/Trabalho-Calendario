#include <iostream>
#include <fstream>

using namespace std;

void diaSemana (int dia, int mes, int ano, int &ds) {
	int f;

	f = ano + dia + 3 * ( mes - 1 ) - 1;

	if (mes < 3)
		ano = ano-1;
	if (mes>=3)
		f = f - int ( 0.4 * mes + 2.3 );

	f= f + (ano / 4) - int (( ano / 100 +1 ) * 0.75 );
	f=f % 7;
	
	ds = f;
}

bool ehBissexto(int ano) {
    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        return true;  // O ano é bissexto
    } else {
        return false; // O ano não é bissexto
    }
}

int diasNoMes(int mes, int ano) {
    if (mes < 1 || mes > 12) {
        return -1; // Mês inválido
    }

    switch (mes) {
        case 4: case 6: case 9: case 11:
            return 30; // Meses com 30 dias
        case 2:
            if (ehBissexto(ano)) {
                return 29; // Fevereiro em ano bissexto
            } else {
                return 28; // Fevereiro em ano não bissexto
            }
        default:
            return 31; // Meses com 31 dias (janeiro e os demais)
    }
}

void Gerar_Html (int mes, int ano){
    
    cout << " CALENDÁRIO DE " << ano;
    cout << endl << endl;
    
    int calendario [6][7];
    
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 7; j++){
            calendario[i][j] = 0; 
        }
    }

    int ds;
    int d = 1;
    diaSemana(1,mes,ano,ds);
    int dia_mes = diasNoMes(mes,ano);

     //preencehe 1 linha
    for (int i = ds; i < 7;i++){
        calendario [0][i] = d;
        d++;        
    }
    //preenche a partir da segunda linha 
    for (int i = 1; i < 6;i++){
        for (int j = 0; j < 7; j++){
            if ( d <= dia_mes) {
                calendario [i][j] = d;
                d++;
            }   
            
        }
    }

    ofstream fout;

    fout.open ("calendariomes.html");
    if (!fout){
        cout << "Erro de criacao ";
    }

    fout << "<html lang=\"PT-BR\">" ;
    
	fout << "<head>";
 
    fout << "<title>";
    fout << " CALENDARIO " << endl;
    fout << "</title>";
    
	fout << "</head>";
    
    fout << "<body>";
    
    fout << "<h1 style = \"font-size: 120%; color: red;\">" ;
    
	fout << " CALENDARIO DO MES  " << mes;
    
    fout << " DE " << ano << endl;
   
    fout << "</h1>";


    fout << "<table align= \"center\" border=3 cellpadding=2>";

    fout << "<tr>";

    fout << " <th>DOM <th>SEG <th>TER <th>QUA <th>QUI <th>SEX <th>SAB ";
    
    fout << "</tr>";
    

    for (int i = 0; i < 6;i++){
    	fout << "<tr>" << endl;
        for (int j = 0; j < 7; j++){
            if (calendario [i][j] != 0 ){
                fout << "<td>" << calendario [i][j] << "</td>" << endl;
            }
            else {
                fout << "<td>" << "\n" << "</td>";
            }
        }
        fout << "</tr>" << endl;    
    }

    fout << "</table>";

    fout << "</body>";
    
	fout << "</html>";

    fout.close ();
    
    system ("calendariomes.html");
}

int main (){
   
   int mes, ano;
    
    cout << "INSIRA UM MES: ";
    cin >> mes; 
    cout << "INSIRA UM ANO: ";
    cin >> ano;

    Gerar_Html(mes,ano);
    
    return 0;
}
