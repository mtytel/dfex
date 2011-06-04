#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>

#include <jack/jack.h>

const double PI = 3.14;

jack_port_t *input_port;
jack_port_t *output_port;

typedef jack_default_audio_sample_t sample_t;

int bitdepth;
int possible;
int zeroenabled;

int process (jack_nframes_t nframes, void *arg){
    sample_t *in, *out;
        
    in = jack_port_get_buffer(input_port, nframes);
    out = jack_port_get_buffer(output_port, nframes);

    for(jack_nframes_t i=0;i < nframes;i++){
        if (zeroenabled) {
            int val = in[i] * possible / 2 + (in[i] >= 0 ? 0.5 : -0.5);
            out[i] = val * 1.0 / possible / 2;
        }
        else {
            int val = (in[i] + 1) * possible + 1;
            out[i] = val * 1.0 / possible - 1;
        }
    }

    return 0;      
}

int srate (jack_nframes_t nframes, void *arg){
    printf ("the sample rate is now %lu/sec\n", (long)nframes);
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
    zeroenabled = 1;

    if (argc < 3) {
        fprintf (stderr, "usage: bitchomp name bitspersample [zeroenabled = 1]\n");
        return 1;
    }

    int bitdepth = atoi(argv[2]);
    possible = pow(2, bitdepth);

    if (argc > 3)
        zeroenabled = 0;

    jack_set_error_function (error);

    if ((client = jack_client_open (argv[1], JackNullOption | JackNoStartServer, NULL)) == 0) {
        fprintf (stderr, "jack server not running?\n");
        return 1;
    }

    jack_set_process_callback (client, process, 0);
    jack_set_sample_rate_callback (client, srate, 0);
    jack_on_shutdown (client, jack_shutdown, 0);

    printf ("engine sample rate: %lu\n", (long)jack_get_sample_rate (client));

    input_port = jack_port_register (client, "input",
            JACK_DEFAULT_AUDIO_TYPE,
            JackPortIsInput, 0);

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

	/*ports = jack_get_ports (client, NULL, NULL,
				JackPortIsPhysical|JackPortIsOutput);
	if (ports == NULL) {
		fprintf(stderr, "no physical capture ports\n");
		exit (1);
	}

	if (jack_connect (client, ports[0], jack_port_name (input_port))) {
		fprintf (stderr, "cannot connect input ports\n");
	}*/

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

    sleep (-1);
    jack_client_close (client);
    exit (0);
}
