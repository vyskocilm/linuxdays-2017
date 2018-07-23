/*
 *
 * Small testing of Docker build environment
 *
 * Michal Vyskocil 2018
 *
 * released under public domain
 *
 */
#include <czmq.h>

int main ()
{
    int major, minor, micro;
    char *hostname = zsys_hostname ();

    zsys_init ();
    zsys_version (&major, &minor, &micro);
    zsys_info ("Hello from zsys(%d.%d.%d)@%s", major, minor, micro, hostname);
    zstr_free (&hostname);
    exit (EXIT_SUCCESS);
}
