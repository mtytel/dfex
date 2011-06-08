#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include <jack/jack.h>
#include <curses.h>

#include "Series.h"
#include "Parallel.h"
#include "Stutter.h"
#include "Tremolo.h"

#define SR 44000

using namespace std;

jack_port_t *input_port;
jack_port_t *output_port;
Stutter *e1, *e2, *e3;
Parallel *par1, *par2;
Tremolo *trem;
Effect *e;

jack_nframes_t sr;

int process (jack_nframes_t nframes, void *arg){
    sample_t *in, *out;
        
    in = (sample_t*)jack_port_get_buffer(input_port, nframes);
    out = (sample_t*)jack_port_get_buffer(output_port, nframes);

    e->process(in, out, nframes);

    return 0;      
}

int srate (jack_nframes_t nframes, void *arg){
    printf ("the sample rate is now %lu/sec\n", (long)nframes);
    sr = nframes;
    return 0;
}

void error (const char *desc){
    fprintf (stderr, "JACK error: %s\n", desc);
}

void jack_shutdown (void *arg){
    exit (1);
}

int main (int argc, char *argv[]){
    jack_client_t *client;
    const char **ports;

    e1 = new Stutter();
    e1->setFPC(SR / 9);
    e1->setNumStutter(3);

    e2 = new Stutter();
    e2->setFPC(SR / 25);
    e2->setNumStutter(5);
    e2->setOffset(5422);

    e3 = new Stutter();
    e3->setFPC(SR / 100);
    e3->setNumStutter(10);
    e2->setOffset(39300);

    trem = new Tremolo();
    trem->setWave(10000, WaveMaker::kSquare);

    par1 = new Parallel();
    par1->setLeft(e1);
    par1->setRight(e2);

    e = par2 = new Parallel();
    par2->setLeft(par1);
    par2->setRight(e3);


    if (argc < 2) {
        fprintf (stderr, "usage: controller config_file \n");
        return 1;
    }

    jack_set_error_function(error);

    if ((client = jack_client_open ("controller", 
            (jack_options_t)(JackNullOption | JackNoStartServer), NULL)) == 0) {
        fprintf (stderr, "jack server not running?\n");
        return 1;
    }

    jack_set_process_callback (client, process, 0);
    jack_set_sample_rate_callback (client, srate, 0);
    jack_on_shutdown (client, jack_shutdown, 0);

    printf ("engine sample rate: %lu\n", (long)jack_get_sample_rate (client));

    sr=jack_get_sample_rate (client);

    input_port = jack_port_register(client, "input",
            JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);

    output_port = jack_port_register (client, "output", 
            JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

    if ((input_port == NULL) || (output_port == NULL)) {
        fprintf(stderr, "no more JACK ports available\n");
        exit (1);
    }

    if (jack_activate (client)) {
        fprintf (stderr, "cannot activate client");
        return 1;
    }

    ports = jack_get_ports (client, NULL, NULL,
             JackPortIsPhysical|JackPortIsOutput);

    if (ports == NULL) {
        fprintf(stderr, "no physical capture ports\n");
        exit (1);
    }

    if (jack_connect (client, ports[0], jack_port_name (input_port))) {
        fprintf (stderr, "cannot connect input ports\n");
    }

    if ((ports = jack_get_ports (client, NULL, NULL, 
                    JackPortIsPhysical|JackPortIsInput)) == NULL) {
        fprintf(stderr, "Cannot find any physical playback ports\n");
        exit(1);
    }

    for(int i = 0; ports[i]; i++){
        if (jack_connect (client, jack_port_name (output_port), ports[i])) {
            fprintf (stderr, "cannot connect output ports\n");
        }
    }

    free (ports);

    initscr(); 
    keypad(stdscr, TRUE);
    noecho();

    char c;
    while(1) {
        c = getch();
        if (e == par2)
            e = trem;
        else
            e = par2;
    }

    free(e1);
    free(e2);
    jack_client_close (client);

    exit (0);
}

