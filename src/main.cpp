/* 
 * Copyright 2011 Matthew Tytel
 *
 * dfex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dfex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dfex.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include <jack/jack.h>
#include <curses.h>
#include <iostream>
#include <fstream>

#include "Processor.h"
#include "Keyboard.h"
#include "rapidxml.hpp"
#include <fftw3.h>

using namespace std;

jack_port_t *input_port;
jack_port_t *output_port;
Processor *p;

jack_nframes_t sr;

int process (jack_nframes_t nframes, void *arg){
  sample_t *in, *out;

  in = (sample_t*)jack_port_get_buffer(input_port, nframes);
  out = (sample_t*)jack_port_get_buffer(output_port, nframes);

  p->process(in, out, nframes);

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

void read_xml(const char* fileName, rapidxml::xml_document<> *doc) {
  ifstream config(fileName);

  if (!config.is_open()) {
    fprintf(stderr, "Cannot open configuration file \n");
    exit(1);
  }

  config.seekg(0, ios::end);
  int size = (int)config.tellg();
  config.seekg(0, ios::beg);
  char *data = (char*)malloc((size + 1) * sizeof(char));
  config.read(data, size);
  data[size] = 0;

  doc->parse<rapidxml::parse_no_data_nodes>(data);
}

int main (int argc, char *argv[]){
  jack_client_t *client;
  const char **ports;

  if (argc < 2) {
    fprintf(stderr, "usage: controller config_file \n");
    return 1;
  }

  rapidxml::xml_document<> doc;
  read_xml(argv[1], &doc);
  p = Processor::readProcessor(*doc.first_node());

  jack_set_error_function(error);

  if ((client = jack_client_open ("controller", 
          (jack_options_t)(JackNullOption | JackNoStartServer), NULL)) == 0) {
    fprintf(stderr, "jack server not running?\n");
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
    fprintf(stderr, "cannot activate client");
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
  noecho();
  cbreak();

  KeyboardStream::stream();

  jack_client_close (client);

  exit (0);
}
