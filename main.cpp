#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

using namespace std;

void clrscr(){
  printf("\033[2J"); // Czyści ekran
  printf("\033[0;0f"); // Ustawia kursor w lewym, górnym rogu
}

int get_opt(){
    string key;
    while(true){
       cin >>key;
       if(key=="0") return 0;
       if(key=="1") return 1;
       cout << "Wprowadziłeś zły znak, spróbuj ponownie:\n";
    }
}

void error_with_file(string path){
    cout << path << endl<< "Podałeś złą ścieżkę bądź Twój plik jest niepoprawny" << endl;
}
void args_error(){
    cout << "Źle podałeś argumenty przy wywołaniu"<< endl << "Przykład: ./game --not not.txt --or or.txt --and and.txt --impl impl.txt"<<endl;
}

void good_answer(){
    cout << "Brawo, poprawna odpowiedź, zmierzasz w dobrym kierunku :)\n\n";
}

void bad_answer(){
    cout << "Przykro mi, zła odpowiedź :(\n\n";
}

void info(){
    cout << "Witam Cię w Logicznym Labiryncie!!\n"
            "Twoim zadaniem jest rozwiązywanie zdań logicznych dzięki którym będziesz\nwiedział jaką drogą przejść przez labirynt.\n"
            "Za każdym razem musisz stwierdzić, czy podane zdanie logiczne jest prawdziwe,\nfałszywe bądź nie można stwierdzić czy jest to prawda czy fałsz.\n"
            "Stwierdzenie, że podane zdanie jest logiczną prawdą oznacza, że idziemy \nw prawo, fałszem, że idziemy w lewo a jeśli nie można stwierdzić\nto idziemy prosto.\n"
            "Wartość logiczną podanych zdań podajemy jako:\n"
            " Fałsz         :   0\n"
            " Prawda       :   1\n"
            " Nie wiadomo :   2\n\n"
            "Zaczynamy, powodzenia!!!\n\n";
}

void sentences(int option,int x){
    if(option==0&&x==0) cout << "nie w lewo ";
    if(option==1&&x==0) cout << "nie w prawo ";
    if(option==0&&x==1) cout << "w lewo ";
    if(option==1&&x==1) cout << "w prawo ";
    if(option==0&&x==-1)cout << "nie wiem czy w lewo ";
    if(option==1&&x==-1)cout << "nie wiem czy w prawo ";
}

int get(){ //wprowadzanie odpowiedzi
    string key;
    while(true){
       cin >>key;
       if(key=="0") return 0;
       if(key=="1") return 1;
       if(key=="2") return -1;
       cout << "Wprowadziłeś zły znak, spróbuj ponownie:\n";
    }

}

int check(int **t, int x1, int x2){
    for(int i=0;i<9;i++){
        if(t[i][0]==x1&&t[i][1]==x2) return t[i][2];
    }
    return -2;
}

int check_not(int ** not_tab, int ** tab, int x1, int x2){
    int tmp=check(tab,x1,x2);
    for(int i=0;i<3;i++){
        if(not_tab[i][0]==tmp) return not_tab[i][1];
    }
    return -2;
}

bool game(int ** not_tab,int ** and_tab,int ** or_tab,int ** impl_tab){
    cout<<  "Witaj w grze\n"
            "Przed Tobą 20 zdań\n"
            "Jeśli na którekolwiek z nich odpowiesz nieprawidłowo gra zakończy się\n"
            " Fałsz(lewo)         :   0\n"
            " Prawda(prawo)       :   1\n"
            " Nie wiadomo(prosto) :   2\n\n"
            "START!!\n\n";
    //zmienne sterujace pojawiajacymi sie wyrazeniami
    int opt1=1;
    int opt2=0;


    int sentence_number=1;
    int answer;

    cout << sentence_number << ". ";
    sentence_number++;
    sentences(opt1,0);
    cout << "i " ;
    sentences(opt2,1);
    cout << endl;
    answer=get();
    if(answer==check(and_tab,0,1)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=0;
    opt2=1;
    cout << sentence_number << ". ";
    sentence_number++;
    cout << "Bzdura, że ";
    sentences(opt1,-1);
    cout << "i " ;
    sentences(opt2,1);
    cout << endl;
    answer=get();
    if(answer==check_not(not_tab,and_tab,-1,1)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=0;
    opt2=1;
    cout << sentence_number << ". ";
    sentence_number++;
    sentences(opt1,0);
    cout << "lub " ;
    sentences(opt2,1);
    cout << endl;
    answer=get();
    if(answer==check(or_tab,0,1)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }
    opt1=0;
    opt2=1;
    cout << sentence_number << ". ";
    sentence_number++;
    cout << "Jeśli ";
    sentences(opt1,-1);
    cout << "to " ;
    sentences(opt2,1);
    cout << endl;
    answer=get();
    if(answer==check(impl_tab,-1,1)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=1;
    opt2=0;
    cout << sentence_number << ". ";
    sentence_number++;
    cout << "Bzdura, że ";
    sentences(opt1,0);
    cout << "lub " ;
    sentences(opt2,0);
    cout << endl;
    answer=get();
    if(answer==check_not(not_tab,or_tab,0,0)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=1;
    opt2=1;
    cout << sentence_number << ". ";
    sentence_number++;
    sentences(opt1,-1);
    cout << "i " ;
    sentences(opt2,0);
    cout << endl;
    answer=get();
    if(answer==check(and_tab,-1,0)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=0;
    opt2=1;
    cout << sentence_number << ". ";
    sentence_number++;
    sentences(opt1,1);
    cout << "lub " ;
    sentences(opt2,-1);
    cout << endl;
    answer=get();
    if(answer==check(or_tab,1,-1)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=0;
    opt2=1;
    cout << sentence_number << ". ";
    sentence_number++;
    cout << "Jeśli ";
    sentences(opt1,0);
    cout << "to " ;
    sentences(opt2,0);
    cout << endl;
    answer=get();
    if(answer==check(impl_tab,0,0)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=1;
    opt2=0;
    cout << sentence_number << ". ";
    sentence_number++;
    cout << "Bzdura, że ";
    sentences(opt1,-1);
    cout << "i " ;
    sentences(opt2,-1);
    cout << endl;
    answer=get();
    if(answer==check_not(not_tab,and_tab,-1,-1)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=0;
    opt2=0;
    cout << sentence_number << ". ";
    sentence_number++;
    cout << "Jeśli ";
    sentences(opt1,-1);
    cout << "to " ;
    sentences(opt2,0);
    cout << endl;
    answer=get();
    if(answer==check(impl_tab,-1,0)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=1;
    opt2=1;
    cout << sentence_number << ". ";
    sentence_number++;
    sentences(opt1,0);
    cout << "lub " ;
    sentences(opt2,0);
    cout << endl;
    answer=get();
    if(answer==check(or_tab,0,0)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=0;
    opt2=1;
    cout << sentence_number << ". ";
    sentence_number++;
    cout << "Jeśli ";
    sentences(opt1,0);
    cout << "to " ;
    sentences(opt2,-1);
    cout << endl;
    answer=get();
    if(answer==check(impl_tab,0,-1)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=1;
    opt2=0;
    cout << sentence_number << ". ";
    sentence_number++;
    cout << "Bzdura, że ";
    cout << "jeśli ";
    sentences(opt1,-1);
    cout << "to " ;
    sentences(opt2,1);
    cout << endl;
    answer=get();
    if(answer==check_not(not_tab,impl_tab,-1,1)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=0;
    opt2=1;
    cout << sentence_number << ". ";
    sentence_number++;
    sentences(opt1,-1);
    cout << "i " ;
    sentences(opt2,1);
    cout << endl;
    answer=get();
    if(answer==check(and_tab,-1,1)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=1;
    opt2=1;
    cout << sentence_number << ". ";
    sentence_number++;
    sentences(opt1,-1);
    cout << "lub " ;
    sentences(opt2,-1);
    cout << endl;
    answer=get();
    if(answer==check(or_tab,-1,-1)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=0;
    opt2=1;
    cout << sentence_number << ". ";
    sentence_number++;
    cout << "Bzdura, że ";
    sentences(opt1,-1);
    cout << "lub " ;
    sentences(opt2,1);
    cout << endl;
    answer=get();
    if(answer==check_not(not_tab,or_tab,-1,1)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=0;
    opt2=0;
    cout << sentence_number << ". ";
    sentence_number++;
    sentences(opt1,-1);
    cout << "i " ;
    sentences(opt2,-1);
    cout << endl;
    answer=get();
    if(answer==check(and_tab,-1,-1)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=0;
    opt2=1;
    cout << sentence_number << ". ";
    sentence_number++;
    cout << "Bzdura, że ";
    cout << "jeśli ";
    sentences(opt1,0);
    cout << "to " ;
    sentences(opt2,-1);
    cout << endl;
    answer=get();
    if(answer==check_not(not_tab,impl_tab,0,-1)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=1;
    opt2=0;
    cout << sentence_number << ". ";
    sentence_number++;
    sentences(opt1,-1);
    cout << "lub " ;
    sentences(opt2,-1);
    cout << endl;
    answer=get();
    if(answer==check(or_tab,-1,-1)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    opt1=1;
    opt2=1;
    cout << sentence_number << ". ";
    sentence_number++;
    cout << "Bzdura, że ";
    sentences(opt1,0);
    cout << "i " ;
    sentences(opt2,0);
    cout << endl;
    answer=get();
    if(answer==check_not(not_tab,and_tab,0,0)){
        good_answer();
    }
    else{
        bad_answer();
        return false;
    }

    return true;
}

bool open_file(string path, int **tab,int m,int n){

    char val;
    ifstream file;
    file.open(path.c_str() );
    if(!file.good()) error_with_file(path);
    else{
        for(int i=0;i<n;i++){

            for(int j=0;j<m;j++) {
                if(!file.eof()){
                    file >> val;
                    if (val != '0' && val != '1') tab[i][j]=-1;
                    else tab[i][j]=(int)val-48;
                }
                else{
                    error_with_file(path);
                    file.close();
                    return false;
                    }
            }
        }
    }
    file.close();
    return true;
}

int ** create( int n, int m ){
 //alokowanie pamięci dla tablic
    int ** tab=new int*[n];
    for(int i=0;i<n;i++) tab[i]=new int[m];
    return tab;
}

void clean(int ** tab, int n){ //czyszczenie pamieci zaalokowanej dla konkretnej tablicy
    for(int i=0;i<n;i++) delete tab[i];
    delete tab;
}
void clean_memory(int ** not_tab,int ** and_tab,int ** or_tab,int ** impl_tab){ //czyszczenie pamieci
    clean(not_tab,3);
    clean(and_tab,9);
    clean(or_tab,9);
    clean(impl_tab,9);
}


int main(int argc, char **argv){

    if(argc<9){
        args_error();
        return 0;
    }
    else{
        string tmp;
        bool f1=false,f2=false,f3=false,f4=false; //flagi do sprawdzenia poprawnosci wczytania plikow

        int **not_tab=create(3,2);

        int **and_tab=create(9,3);

        int **or_tab=create(9,3);

        int **impl_tab=create(9,3);

        for(int i=1;i<argc;i=i+2){
            tmp=argv[i];
            if(tmp=="--not"&&!f1) f1=open_file(argv[i+1],not_tab,2,3);
            if(tmp=="--and"&&!f2) f2=open_file(argv[i+1],and_tab,3,9);
            if(tmp=="--or"&&!f3) f3=open_file(argv[i+1],or_tab,3,9);
            if(tmp=="--impl"&&!f4) f4=open_file(argv[i+1],impl_tab,3,9);
        }
        double highscore=0.0;
        while(true){
            if(f1&&f2&&f3&&f4){ //jesli ktoras z flag okaze sie false czyli plik zostal zle wczytany gra nie rozpocznie sie
                clrscr();
                info();
                cout << "Wprowadź 1 jeśli chcesz rozpocząć grę, 0 jeśli chcesz zakończyć\n";
                int opt=get_opt();
                clrscr();
                if(opt==1) {
                    std::chrono::time_point<std::chrono::system_clock> start,endd; //deklaracja zmiennych sluzacych do pomiaru czasu
                    start = std::chrono::system_clock::now(); //zapisanie czasu przed startem gry
                    bool test=game(not_tab,and_tab,or_tab,impl_tab);
                    endd = std::chrono::system_clock::now(); //zapisanie czasu po zakończeniu gry
                    std::chrono::duration<double> elapsed_seconds = endd-start; //czas gry w sekundach

                    if(test){
                        cout << "Gratulacje, przeszedłeś cały labirynt w: " << elapsed_seconds.count() << " sekundy!!" << endl;
                        if(highscore==0) highscore=(double)elapsed_seconds.count();
                        if((double)elapsed_seconds.count()<highscore){
                            cout << "Jest to nowy najlepszy wynik!!!\n";
                            highscore=(double)elapsed_seconds.count();
                        }
                        else if(highscore!=(double)elapsed_seconds.count()) cout << "Highscore: " << highscore << endl;
                    }
                    else{
                        cout << "Niestety, zabłądziłeś :(" << endl;
                    }
                    getchar();
                    while (getchar() != '\n'); //oczekiwanie na enter
                    }
                if(opt==0){
                    clean_memory(not_tab,and_tab,or_tab,impl_tab);
                    return 0;
                }
            }
            else{
                args_error();
                clean_memory(not_tab,and_tab,or_tab,impl_tab);
                return 0;
            }
        }
    }
}


