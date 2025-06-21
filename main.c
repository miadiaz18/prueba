#include <stdio.h>  // Sirve para entrada y salida estándar (input/output) y funciones comunes.
#include <stdint.h> // Define tipos de datos con tamaño exacto.
#include <stdlib.h> // Contiene funciones de utilidad general(para vec dinamicos).
#include <math.h>   // Funciones matemáticas avanzadas.
#include"audio_player.h"

/*
struct encabezado
{
    uint32_t SampleRate :4;
    uint32_t SampleCount : 28;
};

struct elementos {
    struct encabezado sample;
    float *audio;
};

int main(){
    FILE *f = fopen ("audio_list.raw","rb");
    
    if( f == NULL){
        printf("file error");
        return -1;
    }

    struct elementos *v;
    int cont=0;
    v=malloc(sizeof(struct elementos));
    

    while ( fread(&v[0].sample, sizeof(struct encabezado), 1, f)!=0)
    {
        fseek(f, v[0].sample.SampleCount*sizeof(float), SEEK_CUR);
        cont++;
    }
    free(v);
    printf("En total hay %d elementos", cont);


    v=malloc(cont*sizeof(struct elementos));

    fseek(f,0,SEEK_SET);
    for (int i=0; i < cont; i++)
    {
        fread(&v[i].sample, sizeof(struct encabezado), 1, f);
        v[i].audio=malloc(sizeof(float)*v[i].sample.SampleCount);
        fread(v[i].audio, sizeof(float), v[i].sample.SampleCount, f);
    }

    int pista_a_reproducir;
    printf("\nIngrese la pista que quiere reproducir");
    scanf("%d", &pista_a_reproducir);

    uint32_t rate;
    if (v[pista_a_reproducir].sample.SampleRate == 0){
        rate = 32000;
    }else if(v[pista_a_reproducir].sample.SampleRate == 1){
        rate = 44100;
    }else if (v[pista_a_reproducir].sample.SampleRate == 2){
        rate = 48000; 
    }else if(v[pista_a_reproducir].sample.SampleRate == 3){
        rate = 88200;
    }
    
    play_audio(rate, v[pista_a_reproducir].sample.SampleCount, v[pista_a_reproducir].audio);
    
    for (int i=0; i<cont ; i++){
        free(v[i].audio);
    }

    fclose(f);

    return 0;
}
*/

/*-	El archivo audio_list.raw contiene varias pistas de audio. Cada pista tiene una duración y una velocidad de 
reproducción particular, es decir, las pistas no duran el mismo tiempo ni se reproducen a la misma velocidad.
El formato del archivo es simple, consiste de un encabezado de 32 bits seguido de las muestras de audio. 
(Las muestras en todos los casos es tipo float.)
La velocidad de reproducción se indica en el campo SampleRate (0: 32000Hz, 1: 44100Hz, 2: 48000Hz, 3: 88200Hz) 
y la cantidad de muestras de audio que contiene esa pista es Sample Count.
*/

struct encabezado{
    uint32_t velocidad : 4;
    uint32_t cantidad : 28;
};

struct pista
{
    struct encabezado samples;
    float *audio;
};

int main(){

    FILE *f = fopen("audio_list.raw","rb");
    if ( f == NULL){
        printf("ERROR opening the file\n");
        return -1;
    }

    int cont = 0;
    struct pista *v;
    v = malloc(sizeof(struct pista));

    while (fread(&(v->samples) ,sizeof(struct encabezado) , 1, f)!=0)
    {
        fseek(f, v->samples.cantidad * sizeof(float), SEEK_CUR); // salteo la cantidad de floats q hay para llegar al otro encabezado
        cont++;
    }
    fseek(f, 0, SEEK_SET);
    printf("La cantidad de pistas es: %d",cont);
    free(v);
    v = malloc(sizeof(struct pista)*cont);
    
    for(int i = 0; i<cont; i++){
        fread(&v[i].samples, sizeof(struct encabezado), 1 ,f);
        v[i].audio = malloc(v[i].samples.cantidad*sizeof(float));
        fread(v[i].audio, sizeof(float), v[i].samples.cantidad, f); //leo la cantidad de muestras (v[i].samples.cantidad)
    }

    printf("\nIngrese la pista q quiere escuchar: ");
    int track;
    scanf("%d", &track);

    int rate;
    if (v[track].samples.velocidad == 0){
        rate = 32000;
    }else if(v[track].samples.velocidad == 1){
        rate = 44100;
    }else if(v[track].samples.velocidad == 2){
        rate = 48000;
    }else if(v[track].samples.velocidad == 3){
        rate = 88200;
    }

    play_audio(rate, v[track].samples.cantidad, v[track].audio);

    for (int i=0; i<cont ; i++){
        free(v[i].audio);
    }
    free(v);

    fclose(f);
    return 0;
}