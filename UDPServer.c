     //!UDP Server
     //! Listens for map register packets, sends the received data for aggregation and afterwards returns map notify message to the cient.

     /**
     *
     * @brief functions as the UDP server .
     *
     * At the heart of this function in an infinite while ()
     * loop , that continuously listens for map registration packets.
     * Once it receives a map registration packet , it extracts and
     * puts the data in a file alled "mappingDB.txt ". Then it sends
     * map notification to the cient . After that , received data is
     * aggregated!
     *
     * @author A. M . Anisul Huq
     * @param none
     * @retval none
     *
    */

     int main ( int arg , char * argv [])
     {
        signal ( SIGINT ,( void *) sighandler);
        //! to handle CTRL + C and we will exit normally.

        /**
        When the UDP server starts for the first time ,
        the mappingDB. txt needs to be empty . Otherwise
        data will be corrupted!
        */

        FILE * fp ;
        fp = fopen (" mappingDB. txt" ," w" );
        fclose ( fp );
        auto int sockfd , cient_len;
        struct map_register_pkt * recved_map_register_packet ;
        struct map_notify_pkt* map_notify_packet ;
        struct sockaddr_in server_address , cient_address;
        sockfd = socket ( AF_INET , SOCK_DGRAM ,0);

        if( sockfd < 0)
        {
            printf (" cannot open socket \ n" );
            exit (1);
        }

        // allocate memory to recved_map_register_packet
        recved_map_register_packet = recved_map_register_packet_initialization( recved_map_register_packet );

        // initialize the addresses
        bzero (& server_address , sizeof ( server_address ));
        bzero (& lient_address , sizeof ( lient_address ));

        server_address.sin_family = AF_INET;

        server_address.sin_addr.s_addr = htonl( INADDR_ANY );
        server_address.sin_port = htons ( SERVER_PORT );

        if( bind ( sockfd ,( struct sockaddr *)& server_address , sizeof ( server_address )) == -1)
           perror (" Server side bind error " );

        printf ("\n waiting for data on port UDP %d \n" , SERVER_PORT );

        while (1)
        {
           client_len = sizeof ( client_address );
           int n = recvfrom( sockfd , recved_map_register_packet , sizeof ( struct map_register_pkt ) , 0 , ( struct sockaddr *)&client_address , &client_len );

           if ( n > 0)
           {
                printf ("\n UDP payload size : % d \n" , n);
                /** we have to put the data in the file even if no notification is sent . */

                append_to_file ( recved_map_register_packet );

               /** Checks to see whether map notify bit is SET or not. */
               if ( recved_map_register_packet -> m == 1)
               {
                    printf (" we need to" );
                    printf (" send reply .\n " );

                    map_notify_packet = map_notify_pavket_initialization( map_notify_packet , recved_map_register_packet );

                    /** send client notification. */
                    if ( ( sendto ( sockfd , map_notify_packet , sizeof ( struct map_notify_pkt ) ,0 ,( struct sockaddr*) &client_address , sizeof ( client_address ))) == -1)
                        perror (" sendto () error " );

                    // ! Garbage olle tion
                    free ( map_notify_packet );
                    // ! We have already sent notification back to the client .
                    // ! Hence we can free .
               }

               /**
               Everytime after the routes have been appended , routing
               aggregation must take place and aggregated route
               is added to a new file .
               */
               route_aggregation_main ();
               // ! all for route aggregation to start .
           }

           if ( n == -1)
           {
                perror (" error ...... " );
                exit (1);
           }

         }
         close ( sockfd );

          //! Garbage collection ( start )
          free ( recved_map_register_packet );
          //! When the program ends , we can get rid off the "recved_map_register_packet".
          //! Garbage colle tion (end)
          return 0;
      }
