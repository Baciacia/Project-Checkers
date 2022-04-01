#include <graphics.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include <MMsystem.h>

using namespace std;
int a[9][9],maxx,maxy,contoralbe,contornegre,cinemuta,language; /// 0-engleza 1-romana 2-franceza DEFAULT:ENGLEZA

bool paused=false;
struct chess{int x1; int y1; int x2; int y2;}chessCoord[9][9];

char* wordChoose(char *s)
{
if(strcmp(s,"START GAME")==0)
    switch(language)
        {case 0: return "START GAME";
        break;
        case 1: return "START JOC";
        break;
        case 2: return "DÉMARRER JEU";
        break;
        }
    else if(strcmp(s,"RESUME")==0)
        switch(language)
        {case 0: return "RESUME";
        break;
        case 1: return "CONTINUA";
        break;
        case 2: return "CONTINUER";
        break;
        }
        else    if(strcmp(s,"SETTINGS")==0)
            switch(language)
            {case 0: return "SETTINGS";
            break;
            case 1: return "SETARI";
            break;
            case 2: return "RÉGLAGES";
            break;
            }
                else     if(strcmp(s,"EXIT GAME")==0)
                switch(language)
                {case 0: return "EXIT GAME";
                break;
                case 1: return "IESIRE JOC";
                break;
                case 2: return "QUITTER LE JEU";
                break;
                }       else if(strcmp(s,"RESOLUTION")==0)
                            switch(language)
                            {case 0: return "RESOLUTION";
                            break;
                            case 1: return "REZOLUTIE";
                            break;
                            case 2: return "RÉSOLUTION";
                            break;
                            }   else    if(strcmp(s,"MUSIC")==0)
                                        switch(language)
                                        {case 0: return "MUSIC";
                                        break;
                                        case 1: return "MUZICA";
                                        break;
                                        case 2: return "MUSIQUE";
                                        break;}
                                        else  if(strcmp(s,"LANGUAGE")==0)
                                                switch(language)
                                                {case 0: return "LANGUAGE";
                                                break;
                                                case 1: return "LIMBA";
                                                break;
                                                case 2: return "LANGUE";
                                                break;}
                                                else        if(strcmp(s,"BLACK MOVES")==0)
                                                            switch(language)
                                                            {case 0: return "BLACK MOVES";
                                                            break;
                                                            case 1: return "NEGRU MUTA";
                                                            break;
                                                            case 2: return "TOUR NOIR";
                                                            break;} else        if(strcmp(s,"WHITE MOVES")==0)
                                                                                switch(language)
                                                                                {case 0: return "WHITE MOVES";
                                                                                break;
                                                                                case 1: return "ALB MUTA";
                                                                                break;
                                                                                case 2: return "TOUR BLANC";
                                                                                break;} else      if(strcmp(s,"WHITE WINS")==0)
                                                                                                    switch(language)
                                                                                                    {case 0: return "WHITE WINS";
                                                                                                    break;
                                                                                                    case 1: return "ALB CASTIGA";
                                                                                                    break;
                                                                                                    case 2: return "BLANC GAGNE";
                                                                                                    break;} else      if(strcmp(s,"BLACK WINS")==0)
                                                                                                                        switch(language)
                                                                                                                        {case 0: return "BLACK WINS";
                                                                                                                        break;
                                                                                                                        case 1: return "NEGRU CASTIGA";
                                                                                                                        break;
                                                                                                                        case 2: return "NOIR GAGNE";
                                                                                                                        break;}
}
void addBlackPiece(int i, int j)
{
    setcolor(DARKGRAY);
    setfillstyle(1,BLACK);
   fillellipse((chessCoord[i][j].x1+chessCoord[i][j].x2)/2,(chessCoord[i][j].y1+chessCoord[i][j].y2)/2,getmaxx()/32,getmaxx()/32);
    a[i][j]=2;
}
void backButton(int x1, int y1, int x2, int y2)
{
                                                                                                        ///PATRAT MARE
    setcolor(WHITE);
    setfillstyle(1,LIGHTGRAY);
    rectangle(x1,y1,x2,y2);
    floodfill((x1+x2)/2,(y1+y2)/2,WHITE);
                                                                                                        ///PATRAT MIC
    setcolor(RGB(204, 102, 0));
    rectangle((x2-x1)*1/3+x1,(y2-y1)*1/3+y1,(x2-x1)*9/10+x1,(y2-y1)*2/3+y1);
    setfillstyle(1,RGB(204, 102, 0));
    floodfill(((x2-x1)*1/3+x1 + (x2-x1)*9/10+x1)/2,((y2-y1)*1/3+y1 + (y2-y1)*2/3+y1)/2,RGB(204, 102, 0));
                                                                                                        ///TRIUNGHI
    int arr[8]={(x2-x1)*1/10+x1,((y2-y1)*1/3+y1 + (y2-y1)*2/3+y1)/2, (x2-x1)*1/3+x1,(y2-y1)*1/5+y1 ,(x2-x1)*1/3+x1, (y2-y1)*4/5+y1,(x2-x1)*1/10+x1,((y2-y1)*1/3+y1 + (y2-y1)*2/3+y1)/2};
    drawpoly(4,arr);
    floodfill( ((x2-x1)*1/10+x1+(x2-x1)*1/3+x1)/2  , ((y2-y1)*1/3+y1 + (y2-y1)*2/3+y1)/2 ,RGB(204, 102, 0));
}
void surrenderButton()
{
    readimagefile("flag.jpg", maxx/1.23,maxy/38, maxx/1.02, maxy/8);
    rectangle(maxx/1.23 , maxy / 38 , maxx / 1.02, maxy/8);
}
void addWhitePiece(int i, int j)
{
    setcolor(DARKGRAY);
    setfillstyle(1,WHITE);
    fillellipse((chessCoord[i][j].x1+chessCoord[i][j].x2)/2,(chessCoord[i][j].y1+chessCoord[i][j].y2)/2,getmaxx()/32,getmaxx()/32);
    a[i][j]=1;
}
void removePiece(int i, int j)
{
    setcolor(RGB(204, 102, 0));
    setfillstyle(1,RGB(204, 102, 0));
    bar(chessCoord[i][j].x1,chessCoord[i][j].y1,chessCoord[i][j].x2,chessCoord[i][j].y2);
    a[i][j]=0;
}
void afisNrPiese()
{
char a[2]={contoralbe+'0','\0'},b[2]={contornegre+'0','\0'};
setbkcolor(LIGHTGRAY);
setcolor(RED);
///ALBE MANCATE
outtextxy(maxx/1.07,maxy/4.35,a);
///NEGRE MANCATE
outtextxy(maxx/1.07,maxy/1.20,b);
setcolor(DARKGRAY);
setbkcolor(RGB(204, 102, 0));
}
void loadPos()
{
ifstream f("stats.in");
int x;
f>>x; f>>x;
for(int i=0;i<8;i++)
    for(int j=0;j<8;j++)
        {f>>x;
        a[i][j]=x;
        }
f>>x;
contoralbe=x;
f>>x;
contornegre=x;
}
void savePos()
{
ofstream g("stats.in");
g << 1 <<  " " << cinemuta << endl;
    for(int i=0;i<8;i++)
        {for(int j=0;j<8;j++)
            g << a[i][j] << " " ;
            g << endl;}
g << contoralbe << " " << contornegre << " " << language;

}
void defaultPos()
{
ofstream g("stats.in");
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            {a[i][j]=0;
                if((i+j)%2)
                if(i==0 || i==1)
                    a[i][j]=2;
                else
                    if(i==6 || i==7)
                        a[i][j]=1;}
contoralbe=0;
contornegre=0;

}
void DrawBoard()
{
                                                                                                    ///o bucata pt tabla si una pt statistici
                                                                                                    ///DESENARE SEPARARE TABLA/STATISTICI
    cleardevice();
    setcolor(WHITE);
    floodfill(2,2,WHITE);
    setfillstyle(SOLID_FILL,LIGHTGRAY);
    bar(maxx*4/5,0,maxx,maxy);
    line(maxx*4/5,0,maxx*4/5,maxy);
    setcolor(WHITE);
                                                                                                    ///DESENARE TABLA SAH + PIESE START
///Piese mancate fr
        ///SETARI TEXT
        settextstyle(6,HORIZ_DIR,getmaxx()/200+1);
        setbkcolor(LIGHTGRAY);
    ///ALBE
setcolor(DARKGRAY);
setfillstyle(1,WHITE);
fillellipse(maxx/1.16,maxy/5.03,maxx/32,maxx/32);

    ///NEGRE
 setcolor(DARKGRAY);
setfillstyle(1,BLACK);
fillellipse(maxx/1.16,maxy/1.25,maxx/32,maxx/32);

setfillstyle(LTSLASH_FILL,RED);
setbkcolor(WHITE);
fillellipse(maxx/1.16,maxy/5.03,maxx/32,maxx/32);
setbkcolor(BLACK);
fillellipse(maxx/1.16,maxy/1.25,maxx/32,maxx/32);

    ///READUCERE LA NORMAL SETARILE
setfillstyle(SOLID_FILL,LIGHTGRAY);
setbkcolor(RGB(204, 102, 0));
settextstyle(8, HORIZ_DIR,3);
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
        {
            chessCoord[i][j].x1=j*maxx*4/5/8;
            chessCoord[i][j].y1=i*maxy/8;
            chessCoord[i][j].x2=(j+1)*maxx*4/5/8;
            chessCoord[i][j].y2=(i+1)*maxy/8;

        if((i+j)%2)
            setfillstyle(1,RGB(204, 102, 0));
        else
            setfillstyle(1,LIGHTGRAY);
        bar(chessCoord[i][j].x1,chessCoord[i][j].y1,chessCoord[i][j].x2,chessCoord[i][j].y2);
        }
                                                                                                ///INITIALIZARE PIESE PENTRU START BACKEND

                                                                                                    ///AFISARE PIESE START FRONTEND
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            if(a[i][j]==1)
                addWhitePiece(i,j);
            else
                if(a[i][j]==2)
                    addBlackPiece(i,j);

                                                                                    ///AFISARE BACKBUTTON
    backButton(maxx/1.23,maxy/1.1,maxx/1.02,maxy/1.02);
    surrenderButton();

                                                                                    ///AFISARE MATRICE BACKEND
    cout << "Matrice Backend" << endl;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
            cout << a[i][j] << " ";
        cout << endl;
    }



}

void moveDisplay(int i) /// 1- white, 2- black
{
settextstyle(3,HORIZ_DIR,2);
    if(i==1)
    {   setcolor(BLACK);
        setfillstyle(1,WHITE);
        setbkcolor(WHITE);
        bar(maxx/1.23,maxy/2.25,maxx/1.01,maxy/2.04);
          outtextxy((maxx/1.21+maxx/1.02)/2,(maxy/2.40+maxy/1.85)/2,wordChoose("WHITE MOVES"));
    }
    else if(i==2)
    {
    setcolor(WHITE);
    setfillstyle(1,BLACK);
    setbkcolor(BLACK);
    bar(maxx/1.23,maxy/2.25,maxx/1.01,maxy/2.04);
    outtextxy((maxx/1.21+maxx/1.02)/2,(maxy/2.40+maxy/1.85)/2,wordChoose("BLACK MOVES"));
    }
settextstyle(8, HORIZ_DIR,3);
}

void displayWinner(int i)
{
settextstyle(3,HORIZ_DIR,2);
    if(i==1)
    {   setcolor(BLACK);
        setfillstyle(1,WHITE);
        setbkcolor(WHITE);
        bar(maxx/1.23,maxy/2.25,maxx/1.01,maxy/2.04);
          outtextxy((maxx/1.21+maxx/1.02)/2,(maxy/2.40+maxy/1.85)/2,wordChoose("WHITE WINS"));
    }
    else if(i==2)
    {
    setcolor(WHITE);
    setfillstyle(1,BLACK);
    setbkcolor(BLACK);
    bar(maxx/1.23,maxy/2.25,maxx/1.01,maxy/2.04);
    outtextxy((maxx/1.21+maxx/1.02)/2,(maxy/2.40+maxy/1.85)/2,wordChoose("BLACK WINS"));
    }
settextstyle(8, HORIZ_DIR,3);
}

void VerificareMancarePiesa(int a[9][9],int i,int j)
{
    if(a[i+1][j-1] && a[i][j-2] && a[i+2][j-2] && a[i+2][j])                                        ///DREAPTA JOS
    {
        if(a[i-1][j-1]==1)
            {contoralbe++;
            afisNrPiese();}
        else
            {contornegre++;
            afisNrPiese();}

        removePiece(i-1,j-1);
    }
    if(a[i+1][j+1] && a[i][j+2] && a[i+2][j] && a[i+2][j+2])                                        ///STANGA SUS
    {
        if(a[i+1][j+1]==1)
            {contoralbe++;
            afisNrPiese();}
        else   {contornegre++;
            afisNrPiese();}

        removePiece(i+1,j+1);
    }
    if(a[i-1][j+1] && a[i-2][j] && a[i-2][j+2] && a[i][j+2])                                        ///STANGA JOS
    {
        if(a[i-1][j+1]==1)
               {contoralbe++;
            afisNrPiese();}
        else {contornegre++;
            afisNrPiese();}

        removePiece(i-1,j+1);
    }
    if(a[i-1][j-1] && a[i][j-2] && a[i-2][j] && a[i-2][j-2])                                        ///DREAPTA SUS
    {
        if(a[i+1][j-1]==1)
             {contoralbe++;
            afisNrPiese();}
        else  {contornegre++;
            afisNrPiese();}

        removePiece(i+1,j-1);
    }
}

/// SA NU BUGGUIASCA LA STERGEREA UNEI PIESE CU 4X ALBE/ NEGRE;
/// LA FUNCTIA DE STERGERE E CEVA AIUREA

/// MUZICA;


int startGame()
{int x;
ifstream f("stats.in");
f>>x;
if(x)
    { f>>x;
    cinemuta=x;
    loadPos(); }
else
    cinemuta=1;



    int gameOver=0;
    DrawBoard();                                        ///ASTEPTARE INPUT

    int mx=0,my=0,culoarepiesa=0;
    int rand=0;                                         /// SA TIN MINTE CAND TRE SA STERG SI CAND SA DESENEZ;
    int coordx,coordy;                                  /// PENTRU MEMORAREA COORDONATELOR PIESEI STERSE /// O SA VEZI MAI JOS DE CE AM NEVOIE;
    int mutaregresita=1;                                /// SA NU PERMIT MUTAREA UNEI PIESE AIUREA
   //cinemuta=1;                                                      /// SA VAD A CUI ESTE RANDUL
    moveDisplay(cinemuta);
    int PrimaMutare=0;
    int contoralbe=0,contornegre=0;
    afisNrPiese();

    bool exitPage=0;
    while(!exitPage)
    {
        if(contoralbe==8) // DEEEEEEEEEEEE CEEEEEEEEEEE NU     MMMMMMMMMMMEEEEEEEEEEEERRRRRGGGGGEEEEEEEEEEEEE
    {displayWinner(2);
    Sleep(3000);
    exitPage=1;
    break;}
    else if(contornegre==8)
    {
    displayWinner(1);
    Sleep(3000);
    exitPage=1;
    break;
    }

        while(!ismouseclick(WM_LBUTTONDOWN))
            delay(50);

        getmouseclick(WM_LBUTTONDOWN,mx,my);
        cout << "poz:" <<  getmaxx()*1.00 / mx << " " << getmaxy()*1.00/my << endl;
        {
            int i=my/(maxy/8);                                                                       ///COORDONATE LINIE
            int j=mx/(maxx/10);                                                                      ///COORDONATE COLOANA

            if(rand)                                                                                 ///VERIFICAM DACA TREBUIE SA STERGEM SAU SA DESENAM
            {
                if(culoarepiesa==1 && cinemuta==1)                                                   ///DACA ESTE ALBA SI DACA ALBUL ESTE LA MUTARE
                    if(a[i][j]==0)                                                                   /// VERIFICAM DACA PATRATICA NU ESTE OCUPATA
                        if((coordx-i==1 || i-coordx==1) && (coordy-j==1 || j-coordy==1))             ///DACA ESTE PE DIAGONALA SI VECINA;
                        {
                            addWhitePiece(i,j);
                            VerificareMancarePiesa(a,i,j);                    ///VERIFICAM DACA PIESA MUTATA POATE INCHIDE VREO PIESA
                            cinemuta=2;
                            moveDisplay(2);
                            mutaregresita=0;
                            PrimaMutare=1;                                                           ///CAZ SPECIAL PENTRU PRIMA MUTARE;
                        }
                        else mutaregresita=1;
                    else;

                else                                                                                ///DACA ESTE AFRO-AMERICANA :3
                if(culoarepiesa==2 && cinemuta==2)
                    if(a[i][j]==0)
                        if((coordx-i==1 || i-coordx==1) && (coordy-j==1 || j-coordy==1))
                        {
                            addBlackPiece(i,j);
                            VerificareMancarePiesa(a,i,j);                   ///VERIFICAM DACA PIESA MUTATA POATE INCHIDE VREO PIESA
                            mutaregresita=0;
                            cinemuta=1;
                            moveDisplay(1);
                        }

                        else mutaregresita=1;
                    else;
                if(mutaregresita==0)                                                               ///DACA MUTAREA ESTE ACCEPTATA
                    rand=0;
                mutaregresita=1;
            }


            else
                if(a[i][j])                                                                      /// DACA E VREO PIESA PE COORDONATELE ALEA;
                    if(PrimaMutare)
                    {
                        if(a[i][j]==1)                                                           /// DACA E PIESA ALBA;
                            culoarepiesa=1;                                                      ///SALVAM CULOAREA;
                        else culoarepiesa=2;

                        if(culoarepiesa==1 && cinemuta==1)
                        {

                            removePiece(i,j);                                                        ///STERGEM PIESA DE PE POZ RESPECTIVA
                            rand=1;
                            coordx=i;                                                                ///SALVAM I UL PIESEI STERSE;
                            coordy=j;                                                                ///SALVAM J UL PIESEI STERSE
                        }
                        else
                            if(culoarepiesa==2 && cinemuta==2)
                            {
                                removePiece(i,j);
                                rand=1;
                                coordx=i;
                                coordy=j;
                            }
                    }
                    else
                        if(a[i][j]==1)
                        {
                            culoarepiesa=1;
                            removePiece(i,j);
                            rand=1;
                            coordx=i;
                            coordy=j;
                        }
                        else;


    if(mx > maxx/1.23 && mx < maxx/1.02 && my > maxy/1.1&& my< maxy/1.02)
    {
        savePos();
        paused=true;
        exitPage=1;}
        else if(mx > maxx/1.23 && my > maxy / 38 && mx < maxx / 1.02 && my < maxy/8) ///SURRENDER
                {paused=0;
                if(cinemuta==1)
                    displayWinner(2);
                    else
                    displayWinner(1);
                    defaultPos();
                Sleep(3000);
                exitPage=1;
                }
        }
    }
}


void changeLanguage()
{int mx,my;
bool exit=false;
readimagefile("background.jpg",0,0,getmaxx(),getmaxy());
readimagefile("uk.jpg",maxx/9,maxy*1/7,maxx*4/9,maxy*3/7);
readimagefile("ro.jpg",maxx*5/9,maxy*1/7,maxx*8/9,maxy*3/7);
readimagefile("fr.jpg",maxx*3/9,maxy*4/7,maxx*6/9,maxy*6/7);
backButton(maxx/50,maxy/65,maxx/8,maxy/17);
while(!exit)
    {while(!ismouseclick(WM_LBUTTONDOWN))
            delay(50);
    getmouseclick(WM_LBUTTONDOWN,mx,my);
        if(mx > maxx/50 && mx < maxx/8 && my > maxy/65&& my< maxy/17)
                exit=true; ///BACKBUTTON
        else if(mx>maxx/9 && mx<maxx*4/9 && my>maxy*1/7 && my<maxy*3/7)
            {
            language=0;
            exit=true;
            }
            else if(mx>maxx*5/9 && mx<maxx*8/9 && my>maxy*1/7 && my<maxy*3/7)
                {
                language=1;
                exit=true;
                }
                else if (mx>maxx*3/9 && mx<maxx*6/9 && my>maxy*4/7 && my<maxy*6/7)
                        {
                        language=2;
                        exit=true;
                        }

    }

}



void selectResolution()
{
int mx,my;
readimagefile("background.jpg",0,0,getmaxx(),getmaxy());
backButton(maxx/50,maxy/65,maxx/8,maxy/17);
   bar(maxx*1/12,maxy*6/12,maxx*5/12,maxy*7/12);                                     /// Resolutie
    bar(maxx*1/12,maxy*8/12,maxx*5/12,maxy*9/12);                                     /// Muzica
    bar(maxx*1/12,maxy*10/12,maxx*5/12,maxy*11/12);
    setcolor(WHITE);
    outtextxy(maxx*1/4,maxy*13/24,"800 x 600");

    outtextxy(maxx/4,(maxy*8/12+maxy*9/12)/2,"1280 x 720");

    outtextxy(maxx/4 ,(maxy*10/12+maxy*11/12)/2,"FULLSCREEN");

    while(1)
    {
        while(!ismouseclick(WM_LBUTTONDOWN))
            delay(50);


        getmouseclick(WM_LBUTTONDOWN,mx,my);
            cout << "poz:" <<  getmaxx()*1.00 / mx << " " << getmaxy()*1.00/my << endl;


        if(mx > maxx*1/12 && mx < maxx*5/12 && my > maxy*10/12 && my< maxy*11/12)
        {
            ///FULLSCREEN
            maxx=GetSystemMetrics(SM_CXSCREEN);
            maxy=GetSystemMetrics(SM_CYSCREEN);
            closegraph();
            initwindow(maxx,maxy,"",-3,-3);
            readimagefile("background.jpg",0,0,getmaxx(),getmaxy());
            return;
        }
        else

            if(mx >= maxx*1/12 && mx <= maxx*5/12 && my >=maxy*6/12 && my<=maxy*7/12)
            {
                ///800 x 600
                closegraph();
                initwindow(800,600-30);
                readimagefile("background.jpg",0,0,getmaxx(),getmaxy());
                return;
            }

            else

                if(mx >= maxx*1/12 && mx <= maxx*5/12 && my >=maxy*8/12 && my<=maxy*9/12)
                {
                    ///1280 x 720
                 closegraph();
                 initwindow(1280,720-30);
                 readimagefile("background.jpg",0,0,getmaxx(),getmaxy());
                 return;
                }
                else
                            if(mx > maxx/50 && mx < maxx/8 && my > maxy/65&& my< maxy/17)
                            return; ///BACKBUTTON

    }
return;

}

void selectareMuzica()
{
int mx,my;
bool exit=false;
setcolor(WHITE);
readimagefile("background.jpg",0,0,getmaxx(),getmaxy());
readimagefile("uk.jpg",maxx/9,maxy*1/7,maxx*4/9,maxy*3/7);
outtextxy((maxx/9+maxx*4/9)/2,(maxy*1/7+maxy*3/7)/2,"??????");
readimagefile("ro.jpg",maxx*5/9,maxy*1/7,maxx*8/9,maxy*3/7);
outtextxy((maxx*5/9+maxx*8/9)/2,(maxy*1/7+maxy*3/7)/2,"?????");
readimagefile("fr.jpg",maxx*3/9,maxy*4/7,maxx*6/9,maxy*6/7);
outtextxy((maxx*3/9+maxx*6/9)/2,(maxy*4/7+maxy*6/7)/2,"????????");
backButton(maxx/50,maxy/65,maxx/8,maxy/17);

///REVENIRE SETARI NORMALE
setfillstyle(SOLID_FILL,LIGHTGRAY);
setbkcolor(RGB(204, 102, 0));
settextstyle(8, HORIZ_DIR,3);
setcolor(LIGHTGRAY);


while(!exit)
    {while(!ismouseclick(WM_LBUTTONDOWN))
            delay(50);
    getmouseclick(WM_LBUTTONDOWN,mx,my);
        if(mx > maxx/50 && mx < maxx/8 && my > maxy/65&& my< maxy/17)
                exit=true; ///BACKBUTTON
        else if(mx>maxx/9 && mx<maxx*4/9 && my>maxy*1/7 && my<maxy*3/7)
            {
            ///////////////////////////////////////////play muzica 1
            exit=true;
            }
            else if(mx>maxx*5/9 && mx<maxx*8/9 && my>maxy*1/7 && my<maxy*3/7)
                {
                ////////////////////////////////play muzica 2
                exit=true;
                }
                else if (mx>maxx*3/9 && mx<maxx*6/9 && my>maxy*4/7 && my<maxy*6/7)
                        {
                        /////////////////////////// play muzica 3
                        exit=true;
                        }

    }

}



void Setari(int &volum)
{
    int mx=0,my=0;
    bool exitGame=false;
    setcolor(WHITE);
    setfillstyle(1,DARKGRAY);
    setbkcolor(RGB(204, 102, 0));
    settextstyle(8, HORIZ_DIR,3);
    settextjustify(1,1);
    setfillstyle(1,RGB(204, 102, 0));
    readimagefile("background.jpg",0,0,getmaxx(),getmaxy());
                                                                                      ///RECTANGLES
    bar(maxx*1/12,maxy*6/12,maxx*5/12,maxy*7/12);                                     /// Resolutie
    bar(maxx*1/12,maxy*8/12,maxx*5/12,maxy*9/12);                                     /// Muzica
    bar(maxx*1/12,maxy*10/12,maxx*5/12,maxy*11/12);                                   /// ????

                                                                                            ///BUTON 1
    outtextxy(maxx*1/4,maxy*13/24,wordChoose("RESOLUTION"));

                                                                                            ///BUTON 2

    outtextxy(maxx/4,(maxy*8/12+maxy*9/12)/2,wordChoose("MUSIC"));

                                                                                            ///BUTON 3
    outtextxy(maxx/4 ,(maxy*10/12+maxy*11/12)/2,wordChoose("LANGUAGE"));


    backButton(maxx/50,maxy/65,maxx/8,maxy/17);                                            ///BACKBUTTON FR

    switch(volum)                                                                          ///BUTON VOLUM
        {
        case 0:
        readimagefile("sound0.jpg",maxx/1.24,maxy/5.47,maxx/1.12,maxy/3.69);
        break;
        case 1:
        readimagefile("sound1.jpg",maxx/1.24,maxy/5.47,maxx/1.12,maxy/3.69);
        break;
        case 2:
        readimagefile("sound2.jpg",maxx/1.24,maxy/5.47,maxx/1.12,maxy/3.69);
        break;
        case 3:
        readimagefile("sound3.jpg",maxx/1.24,maxy/5.47,maxx/1.12,maxy/3.69);
        break;
        }

                                                                                            ///ASTEPTARE INPUT

    while(!exitGame)
    {
        while(!ismouseclick(WM_LBUTTONDOWN))
            delay(50);

        getmouseclick(WM_LBUTTONDOWN,mx,my);
            cout << "poz:" <<  getmaxx()*1.00 / mx << " " << getmaxy()*1.00/my << endl;

        if(mx > maxx*1/12 && mx < maxx*5/12 && my > maxy*10/12 && my< maxy*11/12)
        {
            changeLanguage();
            Setari(volum);
            ///??????
        }
        else

            if(mx >= maxx*1/12 && mx <= maxx*5/12 && my >=maxy*6/12 && my<=maxy*7/12)
            {
                selectResolution();
                maxx=getmaxx();
                maxy=getmaxy();
                Setari(volum);
            }

            else

                if(mx >= maxx*1/12 && mx <= maxx*5/12 && my >=maxy*8/12 && my<=maxy*9/12)
                {
                    selectareMuzica();
                        Setari(volum); ///MUZICA
                }
                else
                        if(mx > maxx/50 && mx < maxx/8 && my > maxy/65&& my< maxy/17)
                            return;
                        else if(mx>maxx/1.24 && mx<maxx/1.12 && my>maxy/5.47 && my < maxy/3.69)
                                { if(volum==3)
                                    volum=0;
                                    else
                                        volum++;

                                        switch(volum)
                                        {
                                        case 0:
                                        readimagefile("sound0.jpg",maxx/1.24,maxy/5.47,maxx/1.12,maxy/3.69);
                                        waveOutSetVolume(0,0x0000);
                                        break;
                                        case 1:
                                        readimagefile("sound1.jpg",maxx/1.24,maxy/5.47,maxx/1.12,maxy/3.69);
                                        waveOutSetVolume(0,0x5555);
                                        break;
                                        case 2:
                                        readimagefile("sound2.jpg",maxx/1.24,maxy/5.47,maxx/1.12,maxy/3.69);
                                        waveOutSetVolume(0,0xAAAA);
                                        break;
                                        case 3:
                                        waveOutSetVolume(0,0xFFFF);
                                        readimagefile("sound3.jpg",maxx/1.24,maxy/5.47,maxx/1.12,maxy/3.69);
                                        break;
                                        }

                                }
    }

return;

}





int Menu()
{

    int mx=0,my=0,volum=1;
    bool exitGame=false;

    cleardevice();
    setcolor(WHITE);
    setfillstyle(1,DARKGRAY);
    readimagefile("background.jpg",0,0,getmaxx(),getmaxy());
    setbkcolor(RGB(204, 102, 0));
    settextstyle(8, HORIZ_DIR,3);
    settextjustify(1,1);
    setfillstyle(1,RGB(204, 102, 0));
                                                                                            ///RECTANGLES
    bar(maxx*1/12,maxy*6/12,maxx*5/12,maxy*7/12);                                     /// startgame
    bar(maxx*1/12,maxy*8/12,maxx*5/12,maxy*9/12);                                     /// settings
    bar(maxx*1/12,maxy*10/12,maxx*5/12,maxy*11/12);                                   ///exit game


                                                                                            ///BUTON 1
if(!paused)
    outtextxy(maxx*1/4,maxy*13/24,wordChoose("START GAME"));
else
    outtextxy(maxx*1/4,maxy*13/24,wordChoose("RESUME"));
                                                                                            ///BUTON 2

    outtextxy(maxx/4,(maxy*8/12+maxy*9/12)/2,wordChoose("SETTINGS"));

                                                                                            ///BUTON 3
    outtextxy(maxx/4 ,(maxy*10/12+maxy*11/12)/2,wordChoose("EXIT GAME"));

                                                                                            ///ASTEPTARE INPUT

    while(!exitGame)
    {
        while(!ismouseclick(WM_LBUTTONDOWN))
            delay(50);

        getmouseclick(WM_LBUTTONDOWN,mx,my);
            cout << "poz:" <<  getmaxx()*1.00 / mx << " " << getmaxy()*1.00/my << endl;

        if(mx > maxx*1/12 && mx < maxx*5/12 && my > maxy*10/12 && my < maxy*11/12)
        {
            exitGame=1;
            savePos();
            exit(1);
        }

        else

            if(mx >= maxx*1/12 && mx <= maxx*5/12 && my >=maxy*6/12 && my<=maxy*7/12)
            {
                if(!paused)
                defaultPos();
                startGame();
                Menu();
            }

            else

                if(mx >= maxx*1/12 && mx <= maxx*5/12 && my >=maxy*8/12 && my<=maxy*9/12)
                {
                    Setari(volum);
                    Menu();
                }
    }


}


int main()
{
language=0;
ifstream f("stats.in");
f >> paused;
while(!f.eof())
    f>>language;

PlaySound(TEXT("C:\\Users\\Bogdanel\\Desktop\\FACULTATE\\INTRODUCERE PROGRAMARE\\PROIECT IP\\song.wav"),NULL,SND_ASYNC);
waveOutSetVolume(0,0x5555); ///655 1% volum
    initwindow(800,600-30);
    setlinestyle(0,0,3);
    maxx=getmaxx();
    maxy=getmaxy();
    Menu();
    closegraph();
    return 0;

}
