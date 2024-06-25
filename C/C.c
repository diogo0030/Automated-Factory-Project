#include "IO.c"
#define DEBUG
#ifdef DEBUG
uint64_t cycle_counter;
#endif



    typedef struct {
    bool on;
    uint64_t time;
} timerBlock;

    timerBlock timer1, timer2, timer3, timer4, timer5, timer6, timer7; 

    // G1
    #define MAX_ETAPAS_G1 5
    #define MAX_TRASICOES_G1 6
    bool G1[MAX_ETAPAS_G1];
    bool T1[MAX_TRASICOES_G1];


    // G2
    #define MAX_ETAPAS_G2 11 
    #define MAX_TRASICOES_G2 12
    bool G2[MAX_ETAPAS_G2];
    bool T2[MAX_TRASICOES_G2];

    // G3
    #define MAX_ETAPAS_G3 3
    #define MAX_TRASICOES_G3 3
    bool G3[MAX_ETAPAS_G3];
    bool T3[MAX_TRASICOES_G3];

    // G4
    #define MAX_ETAPAS_G4 8
    #define MAX_TRASICOES_G4 8
    bool G4[MAX_ETAPAS_G4];
    bool T4[MAX_TRASICOES_G4];

    // G5
    #define MAX_ETAPAS_G5 2
    #define MAX_TRASICOES_G5 2
    bool G5[MAX_ETAPAS_G5];
    bool T5[MAX_TRASICOES_G5];

    // G6
    #define MAX_ETAPAS_G6 3
    #define MAX_TRASICOES_G6 3
    bool G6[MAX_ETAPAS_G6];
    bool T6[MAX_TRASICOES_G6];

    // G7
    #define MAX_ETAPAS_G7 3
    #define MAX_TRASICOES_G7 4
    bool G7[MAX_ETAPAS_G7];
    bool T7[MAX_TRASICOES_G7];

    
    bool RE_G22_1;
    bool OLD_G22_1;
    bool RE_G22_2;
    bool OLD_G22_2;
    bool RE_G22_3;
    bool OLD_G22_3;
    bool RE_G22_4;
    bool OLD_G22_4;
    bool RE_G33_1;
    bool OLD_G33_1;
    bool RE_G66_1;
    bool OLD_G66_1;
    bool RE_G66_2;
    bool OLD_G66_2;
    bool RE_G77_1;
    bool OLD_G77_1;
    bool RE_G77_2;
    bool OLD_G77_2;
    bool FE_S6;
    bool OLD_S6;
    



uint64_t start_time=0, end_time=0, cycle_time=0;

void update_timers() {
    // Calcula o tempo de ciclo
    end_time = get_time();
    if (start_time == 0)
    cycle_time = 0;
    else
    cycle_time = end_time - start_time;
    // o fim do ciclo atual é o inicio do próximo
    start_time = end_time;
    // Atualiza temporizadores
    if (timer1.on)
    timer1.time = timer1.time + cycle_time;
    if (timer2.on)
    timer2.time = timer2.time + cycle_time;
    if (timer3.on)
    timer3.time = timer3.time + cycle_time;
    if (timer4.on)
    timer4.time = timer4.time + cycle_time;
    if (timer5.on)
    timer5.time = timer5.time + cycle_time;
    if (timer6.on)
    timer6.time = timer6.time + cycle_time;
    if (timer7.on)
    timer7.time = timer7.time + cycle_time;
    }


void start_timer(timerBlock* t) {
    t->on = true;
    t->time = 0;
}
void stop_timer(timerBlock* t) {
    t->on = false;
    t->time = 0;
}

void tudo_off(){

    G1[0] = 0;
    G1[1] = 0;
    G1[2] = 0;
    G1[3] = 0;
    G1[4] = 0;
    G2[0] = 0;
    G2[1] = 0;
    G2[2] = 0;
    G2[3] = 0;
    G2[4] = 0;
    G2[5] = 0;
    G2[6] = 0;
    G2[7] = 0;
    G2[8] = 0;
    G2[9] = 0;
    G2[10] = 0;
    G3[0] = 0;
    G3[1] = 0;
    G3[2] = 0;
    G5[0] = 0;
    G5[1] = 0;
    T4M=0;
    T3M=0;
    MSTART=0;
    

}
void GRAFCET_INIT(){
    G1[0]=1;
    G2[0]=1;
    G3[0]=1;
    G5[0]=1;
    CVERDES=0;
    CAZUIS=0;
}

void G6_INIT(){
    
    G6[0]=1;
}

void G11(){
   
   // Transições habilitadas
   T1[0] = G1[0] && EM2;
   T1[1] = G1[1] && S3 && (((G2[0]==1) && (G2[3]==0)) || ((G2[0]==0) && (G2[3]==1)));
   T1[2] = G1[1] && S3 && ((G2[0]==0) && (G2[3]==0));
   T1[3] = G1[2] && S3==0;
   T1[4] = G1[3] && (G2[0]==1 || G2[3]==1 || G2[6]==1 || G2[9]==1 );
   T1[5] = G1[4] && S3==0;

   // Desativação das etapas de entrada
   if(T1[0]) G1[0]=false;
   if(T1[1]) G1[1]=false;
   if(T1[2]) G1[1]=false;
   if(T1[3]) G1[2]=false;
   if(T1[4]) G1[3]=false;
   if(T1[5]) G1[4]=false;

   // Ativação das etapas de saída
   if(T1[0]) G1[1]=true;
   if(T1[1]) G1[2]=true;
   if(T1[2]) G1[3]=true;
   if(T1[3]) G1[0]=true;
   if(T1[4]) G1[4]=true;
   if(T1[5]) G1[0]=true;

   // Execução das ações
   if(G1[1]==1 && G1[2]==0 && G1[4]==0)T3M = 1;
   if(G1[1]==0 && G1[2]==1) T3M = 1;
   if(G1[1]==0 && G1[4]==1)T3M = 1;
   if(G1[0]==1 || G1[3]==1) T3M =0;
    


}

void G22() {
     
     // Transições habilitadas
     T2[0] = G2[0] && (G1[2] || G1[4]);
     T2[1] = G2[1] && (timer1.time >= 3000);
     T2[2] = G2[2] && S4I;
     T2[3] = G2[3] && (G1[2] || G1[4]);
     T2[4] = G2[4] && (timer2.time >= 3000);
     T2[5] = G2[5] && S4I;
     T2[6] = G2[6] && (G1[2] || G1[4]);
     T2[7] = G2[7] && (timer3.time >= 3000);
     T2[8] = G2[8] && S4I;
     T2[9] = G2[9] && (G1[2] || G1[4]);
     T2[10] = G2[10] && (timer4.time >= 3000);
     T2[11] = G2[11] && S4I;

     // Desativação das etapas de entrada
     if(T2[0]) G2[0]=false;
     if(T2[1]) {G2[1]=false; stop_timer(&timer1);}
     if(T2[2]) G2[2]=false;
     if(T2[3]) G2[3]=false;
     if(T2[4]) {G2[4]=false; stop_timer(&timer2);}
     if(T2[5]) G2[5]=false;
     if(T2[6]) G2[6]=false;
     if(T2[7]) {G2[7]=false; stop_timer(&timer3);}
     if(T2[8]) G2[8]=false;
     if(T2[9]) G2[9]=false;
     if(T2[10]) {G2[10]=false; stop_timer(&timer4);}
     if(T2[11]) G2[11]=false;

     // Ativação das etapas de saída
     if(T2[0]) G2[1]=true;
     if(T2[1]) G2[2]=true;
     if(T2[2]) G2[3]=true;
     if(T2[3]) G2[4]=true;
     if(T2[4]) G2[5]=true;
     if(T2[5]) G2[6]=true;
     if(T2[6]) G2[7]=true;
     if(T2[7]) G2[8]=true;
     if(T2[8]) G2[9]=true;
     if(T2[9]) G2[10]=true;
     if(T2[10]) G2[11]=true;
     if(T2[11]) G2[0]=true;

     // Execução das ações
     if(G2[1]==1 && G2[4]==0 && G2[7]==0 && G2[10]==0) { MTP=1; MSTART = 1;}
     if(G2[1]==0 && G2[4]==1 && G2[7]==0 && G2[10]==0) { MSTART = 1; MTP =1;}
     if(G2[1]==0 && G2[4]==0 && G2[7]==1 && G2[10]==0) { MTP=0;  MSTART = 1;}
     if(G2[1]==0 && G2[4]==0 && G2[7]==0 && G2[10]==1) { MTP =0; MSTART = 1;}
     if(G2[0]==1 || G2[2]==1 || G2[3]==1 || G2[5]==1 || G2[6]==1 || G2[8]==1 || G2[9]==1 || G2[11]==1) {MSTART = 0;}




}

void G33 () {

  // Transições habilitadas
  T3[0] = G3[0] && S4I;
  T3[1] = G3[1] && S4F;
  T3[2] = G3[2] && (timer5.time >= 1000);

  // Desativação das etapas de entrada
  if(T3[0]) G3[0]=false;
  if(T3[1]) G3[1]=false;
  if(T3[2]) {G3[2]=false; stop_timer(&timer5);}

  // Ativação das etapas de saída
  if(T3[0]) G3[1]=true;
  if(T3[1]) G3[2]=true;
  if(T3[2]) G3[0]=true;

  // Execução das ações
  if(G3[1]) T4M = 1;
  if(G3[2]) T4M = 1;
  if(G3[0]) T4M = 0;



}

void G44(){

   // Transições habilitadas
   T4[0] = G4[0] && BSTART;
   T4[1] = G4[1] && BSTOP && G5[1]==0;
   T4[2] = G4[1] && BSTOP && G5[1];
   T4[3] = G4[2];
   T4[4] = G4[4];
   T4[5] = G4[5] && FE_S6;
   T4[6] = (G4[6] || G4[3]) && BSTART;
   T4[7] = G4[7];

   // Desativação das etapas de entrada
   if(T4[0]) G4[0]=false;
   if(T4[1]) G4[1]=false;
   if(T4[2]) G4[1]=false;
   if(T4[3]) G4[2]=false;
   if(T4[4]) G4[4]=false;
   if(T4[5]) G4[5]=false;
   if(T4[6]) {G4[6]=false; G4[3]=false;}
   if(T4[7]) G4[7]=false;

   // Ativação das etapas de saída
   if(T4[0]) G4[1]=true;
   if(T4[1]) G4[2]=true;
   if(T4[2]) G4[4]=true;
   if(T4[3]) G4[3]=true;
   if(T4[4]) G4[5]=true;
   if(T4[5]) G4[6]=true;
   if(T4[6]) G4[7]=true;
   if(T4[7]) G4[0]=true;

   // Execução das ações
   if(G4[1]) {EM2 = 1; LSTART =1;}
   if(G4[2]) {G6_INIT(); LSTART = 0;}
   if(G4[3]) tudo_off();
   if(G4[4]) {G6_INIT();T6M=1;LSTART = 0;}
   if(G4[5]) tudo_off();
   if(G4[6]) T6M=0;
   if(G4[7]) {GRAFCET_INIT(); G6[0]=0; G6[1]=0;} 
   



}

void G55(){

    // Transições habilitadas
    T5[0] = G5[0] && S4F;
    T5[1] = G5[1] && FE_S6;

    // Desativação das etapas de entrada
    if(T5[0]) G5[0]=false;
    if(T5[1]) G5[1]=false;

    // Ativação das etapas de saída
    if(T5[0]) G5[1]=true;
    if(T5[1]) G5[0]=true;

    // Execução das ações
    if(G5[1]==1) T6M=1;
    if(G5[0]==1) T6M=0;
 
}

void G66(){

    // Transições habilitadas
    T6[0] = G6[0] && (timer6.time >= 2000);
    T6[1] = G6[1] && (timer7.time >= 2000);

    // Desativação das etapas de entrada 
    if(T6[0]) {G6[0]=false; stop_timer(&timer6);}
    if(T6[1]) {G6[1]=false; stop_timer(&timer7);}

    // Ativação das etapas de saída
    if(T6[0]) G6[1]=true;
    if(T6[1]) G6[0]=true;

    // Execução das ações
    if(G6[0]==1 && G6[1]==0 ) LSTOP = 1;
    if(G6[1]==1 && G6[0]==0) LSTOP = 0;
    
}

void G77(){

    // Transições habilitadas
    T7[0] = G7[0] && (SV1 == 2 || SV1 == 3);
    T7[1] = G7[0] && (SV1 == 5 || SV1 == 6);
    T7[2] = G7[1] && SV1==0;
    T7[3] = G7[2] && SV1==0;

    // Desativação das etapas de entrada
    if(T7[0]) G7[0]=false;
    if(T7[1]) G7[0]=false;
    if(T7[2]) G7[1]=false;
    if(T7[3]) G7[2]=false;

    // Ativação das etapas de saída
    if(T7[0]) G7[1]=true;
    if(T7[1]) G7[2]=true;
    if(T7[2]) G7[0]=true;
    if(T7[3]) G7[0]=true;

    // Execução das ações
    if(RE_G77_1 == 1) CAZUIS++;
    if(RE_G77_2 == 1 ) CVERDES++;
    



}
int main(){
    //INICIALIZA O G1
    G1[0]=true;
    G1[1]=false;
    G1[2]=false;
    G1[3]=false;

    //INICIALIZA O G2
    G2[0]=true;
    G2[1]=false;
    G2[2]=false;
    G2[3]=false;

    //INICIALIZA O G3
    G3[0]=true;
    G3[1]=false;
    G3[2]=false;
    G3[3]=false;

    //INICIALIZA O G4
    G4[0]=true;
    CVERDES=0;
    CAZUIS=0;

    //INICIALIZA O G5
    G5[0]=true;
    G5[1]=false;

    //INICIALIZA O G7
    G7[0]=true;

    
    while(1){
        
        update_timers();
        
        read_inputs();

        RE_G22_1 =  G2[1] && !(OLD_G22_1);
        OLD_G22_1 = G2[1];

        RE_G22_2 =  G2[4] && !(OLD_G22_2);
        OLD_G22_2 = G2[4];

        RE_G22_3 =  G2[7] && !(OLD_G22_3);
        OLD_G22_3 = G2[7];

        RE_G22_4 =  G2[10] && !(OLD_G22_4);
        OLD_G22_4 = G2[10];

        RE_G33_1 =  G3[2] && !(OLD_G33_1);
        OLD_G33_1 = G3[2];

        RE_G66_1 =  G6[0] && !(OLD_G66_1);
        OLD_G66_1 = G6[0];

        RE_G66_2 =  G6[1] && !(OLD_G66_2);
        OLD_G66_2 = G6[1];

        RE_G77_1 =  G7[1] && !(OLD_G77_1);
        OLD_G77_1 = G7[1];

        RE_G77_2 =  G7[2] && !(OLD_G77_2);
        OLD_G77_2 = G7[2];

        FE_S6 = !S6 && OLD_S6;
        OLD_S6 = S6;

        if (RE_G22_1) start_timer(&timer1);
        if (RE_G22_2) start_timer(&timer2);
        if (RE_G22_3) start_timer(&timer3);
        if (RE_G22_4) start_timer(&timer4);
        if (RE_G33_1) start_timer(&timer5);
        if (RE_G66_1) start_timer(&timer6);
        if (RE_G66_2) start_timer(&timer7);

        
        G44();
        G11();
        G22();
        G33();
        G55();
        G66();
        G77();

        write_outputs();
        
    }
}


