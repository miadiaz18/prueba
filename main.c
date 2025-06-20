#include <stdio.h>  // Sirve para entrada y salida estándar (input/output) y funciones comunes.
#include <stdint.h> // Define tipos de datos con tamaño exacto.
#include <stdlib.h> // Contiene funciones de utilidad general(para vec dinamicos).
#include <math.h>   // Funciones matemáticas avanzadas.
#include"audio_player.h"

struct encabezado
{
    uint32_t SampleRate :4;
    uint32_t SampleCount : 28;
};

struct elementos {
    struct encabezado sample;
    float *audio;
}

int main(){
    FILE *f = fopen ("audio_list.raw","rb");
    
    if( f == NULL){
        printf("file error");
        return -1;
    }

    struct elementos *v;
    int cont=0
    v=malloc(sizeof(struct elementos));

    while ( fread(&v[0], sizeof(struct encabezado), 1, f)!=0)
    {
        fseek(audio, sizeof(float), v.SampleCount, f);
        cont++;
    }
    
    printf("En total hay %d elementos", cont);
    int pista_a_reproducir;
    printf("\nIngrese la pista que quiere reproducir");
    scanf("%d", &pista_a_reproducir);

    fseek(f,0,SEEK_SET);
    for (int i=0, i < cont, i++)
    {
        fread(v[i], sizeof(struct encabezado), 1, f);
    }
    
    printf("SampleRate:     %d\n",v.sample.SampleRate);
    printf("SampleCount:   %d\n",v.sample.SampleCount);
    
    uint32_t rate;
    if (v.sample.SampleRate == 0){
        rate = 32000;
    }else if(v.sample.SampleRate == 1){
        rate = 44100;
    }else if (v.sample.SampleRate == 2){
        rate = 48000; 
    }else if(v.sample.SampleRate == 3){
        rate = 88200;
    }
    
    fread(audio, sizeof(float), v.sample.SampleCount, f);
    play_audio(rate, v.sample.SampleCount, audio);
    
    free(audio);
    fclose(f);
    /*

    float *audio=malloc(sizeof(float)*v.SampleCount);

    fread(audio, sizeof(float), v.SampleCount, f);
    
    play_audio(rate, v.SampleCount, audio);
    
    free(audio);*/
    fclose(f);

    return 0;
}
