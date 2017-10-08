/*  
    zauth - A PoC for zauth/CureZMQ

@header
    zauth - A PoC for zauth/CureZMQ
@discuss
@end
*/

#include <czmq.h>

int main (int argc, char *argv [])
{

    zsys_init ();

    char *private_file = NULL;
    char *server_public_file = NULL;
    char *endpoint = "ipc://@/zauth";
    bool verbose = false;
    int argn;
    bool server = false;
    for (argn = 1; argn < argc; argn++) {
        if (streq (argv [argn], "--help")
        ||  streq (argv [argn], "-h")) {
            puts ("zauth [options] ...");
            puts ("  --endpoint / -e        endpoint to connect to");
            puts ("  --server / -s          act as server");
            puts ("  --client / -s          act as client (default)");
            puts ("  --private / -p         path to private certificate");
            puts ("  --public / -P          path to server public certificate (for client only)");
            puts ("  --verbose / -v         verbose test output");
            puts ("  --help / -h            this information");
            return 0;
        }
        else
        if (streq (argv [argn], "--endpoint")
        ||  streq (argv [argn], "-e")) {
            if (argc == argn + 1) {
                printf ("-e/--endpoint option expected argument");
                return 1;
            }
            argn++;
            endpoint = argv [argn];
        }
        else
        if (streq (argv [argn], "--private")
        ||  streq (argv [argn], "-p")) {
            if (argc == argn + 1) {
                printf ("-p/--private option expected argument");
                return 1;
            }
            argn++;
            private_file = argv [argn];
        }
        else
        if (streq (argv [argn], "--public")
        ||  streq (argv [argn], "-P")) {
            if (argc == argn + 1) {
                printf ("-P/--public option expected argument");
                return 1;
            }
            argn++;
            server_public_file = argv [argn];
        }
        else
        if (streq (argv [argn], "--server")
        ||  streq (argv [argn], "-s"))
            server = true;
        else
        if (streq (argv [argn], "--client")
        ||  streq (argv [argn], "-c"))
            server = false;
        else
        if (streq (argv [argn], "--verbose")
        ||  streq (argv [argn], "-v"))
            verbose = true;
        else {
            printf ("Unknown option: %s\n", argv [argn]);
            return 1;
        }
    }

    // check arguments
    if (!server) {
        if ((private_file && !server_public_file)
        ||  (!private_file && server_public_file)) {
            zsys_error ("both --private and --server-public are mandatory for --client");
            exit (EXIT_FAILURE);
        }
    }

    //  Insert main code here
    if (verbose)
        zsys_info ("zauth - An experiment with zauth/CureMQ, connecting as %s on %s", server ? "server" : "client", endpoint);

    //  Insert authentication
    
    zsock_t *sock = NULL;
    if (server)
        sock = zsock_new (ZMQ_ROUTER);
    else
        sock = zsock_new (ZMQ_DEALER);
    assert (sock);


    //  Load key(s)
    zcert_t *cert = NULL;               // private certificate
    char *server_key = NULL;      // (server) public key
    zactor_t *auth = NULL;

    if (private_file) {
        if (server) {
            cert = zcert_load (private_file);
            server_key = strdup (zcert_public_txt (cert));
        }
        else {
            cert = zcert_load (server_public_file);
            server_key = strdup (zcert_public_txt (cert));
            zcert_destroy (&cert);
            cert = zcert_load (private_file);
        }

        auth = zactor_new (zauth, NULL);
        assert (auth);
        //if (verbose) {
            zstr_sendx (auth, "VERBOSE", NULL);
            zsock_wait (auth);
        //}

        //  Apply private certificate on socket
        zcert_apply (cert, sock);
        if (server)
            zsock_set_curve_server (sock, 1);
        else
            zsock_set_curve_serverkey (sock, server_key);

        //  Enable CURVE!!
        zstr_sendx (auth, "CURVE", "./certs", NULL);
        zsock_wait (auth);
    }

    // try to bind/connect to the endpoint
    if (server) {
        int rc = zsock_bind (sock, "%s", endpoint);
        assert (rc != -1);
    }
    else {
        int rc = zsock_connect (sock, "%s", endpoint);
        assert (rc != 1);
        zclock_sleep (1500);
    }
    
    //  Main loop
    if (server) {
        while (!zsys_interrupted) {
            char *str = zstr_recv (sock);
            zsys_debug ("server recv=%s", str);
            zstr_free (&str);
        }
    }
    else {
        while (!zsys_interrupted) {
            zstr_send (sock, "HELLO");
            zsys_debug ("client sent=%s", "HELLO");
            zclock_sleep (2500);
        }
    }

    zactor_destroy (&auth);
    zstr_free (&server_key);
    zcert_destroy (&cert);

    zsock_destroy (&sock);

    zactor_destroy (&auth);
    return 0;
}
