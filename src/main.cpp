#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include <jack/jack.h>
#include <curses.h>

#include "Series.h"
#include "Parallel.h"
#include "Stutter.h"
#include "Tremolo.h"

using namespace std;

jack_port_t *input_port;
jack_port_t *output_port;
Effect *e, *e1, *e2, *ser, *par;

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

    e1 = new Stutter(10000, 10);
    e2 = new Tremolo(10000, WaveMaker::kSquare);

    e = ser = new Series(e1, e2, 1);
    par = new Parallel(e1, e2, 1);

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
        if (e == ser)
            e = par;
        else
            e = ser;
    }

    free(e1);
    free(e2);
    jack_client_close (client);

    exit (0);
}

