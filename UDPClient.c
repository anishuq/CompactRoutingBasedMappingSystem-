    /**
    * Send map register message and receive map notify packet.
    *
    * @brief This function will send map registration message to the
    * server in chunks ( the size of chunk depends on the choosen MTU)
    * and it will receive map notify packet for each of the map
    * register packets.
    * @author A. M. Anisul Huq
    * @param
    * @retval 0
    *
    */

     int main ( int arg , char * argv[] )
     {
        //!a global variable declared in the header file has to be
        //! initialized inside a function.
        udp_cli_program_cycle = 0;
        //! udp_cli_program_cycle initialized

        int sockfd ;
        struct sockaddr_in server_addr;
        struct map_register_pkt* map_register_packet ;
        struct map_notify_pkt* recved_map_notify_packet ;
        struct node * starting_point ;
        double number_of_loops;
        int i;
        num_of_mapping = 0; // global variable initialization.

        so kfd = so ket ( AF_INET , SOCK_DGRAM ,0);
        if( sockfd < 0)
        {
            perror (" Socket error : " );
            exit (1);
        }

        xx1 = 0; //! for test purposes.
        // initialize the addresses
        bzero (&server_addr , sizeof ( server_addr ));
        // assign values to the so kaddr_in type stru ture
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons ( SERVER_PORT );
        inet_pton( AF_INET , SERVER_IP ,& server_addr. sin_addr );

        /** Read the file and aquire the data dynami ally. */
        starting_point = access_file_insert_data ();
        // printf ("\ npossible error site .3");
        position = starting_point;

        /** Depending on the MTU (i. e. OPTIMAL_RECORD_NUMBER ) we calculate how many packets ( i.e. map_register_packet )
        need to be transmitted to the server.
        */
        number_of_loops = ceil ( ( double )( num_of_mapping )/ OPTIMAL_RECORD_NUMBER );
        //! the dividend must be in double format to get a correct
        //! output .
        /** The number of pa kets needed to be transmitted is
        " number_of_loops ". */

        for(i = 0; i < ( int) number_of_loops ; i ++)
        {
            int current_turn_recs ;
            if (( num_of_mapping - ( i * OPTIMAL_RECORD_NUMBER )) >= OPTIMAL_RECORD_NUMBER )
                 current_turn_recs = OPTIMAL_RECORD_NUMBER ;
            else
                 current_turn_recs = num_of_mapping - (i * OPTIMAL_RECORD_NUMBER );

            /**
            In the last iteration , there might not be " OPTIMAL_RECORD_NUMBER " number of records left .
            'current_turn_recs ' determines how many records an be included in a map_register_packet .
            */

            udp_cli_program_cycle++;
            //! ounting the number of y les for omplexity analysis.
            map_register_packet = map_register_packet_initialization ( map_register_packet, position , current_turn_recs );
            /**
            The " map_register_packet " is a structure that has an element called "rec"; which in turn is an array of
            type "structure map_register_record". The "structure map_register_record" has an element
            "char eid_prefix[ EID_PREFIX_SIZE]" which holds the eid prefix.
            It also has an element called " struct map_register_rlocloc" which holds the RLOC value.
            */
            // send to the server
            if( sendto ( sockfd , map_register_packet , sizeof ( struct map_register_pkt ) ,0 ,( struct sockaddr *)& server_addr , sizeof ( server_addr )) == -1)
            {
                perror (" sendto () error : " );
                exit (1);
            }
             //! now we receive notification packet .
            recved_map_notify_pa ket = map_notify_packet_initialization( recved_map_notify_packet );

            recved_map_notify_packet = get_map_notify_packet ( sockfd, recved_map_notify_packet );

            printf ("\ nnumber of records in the packet : %d" ,recved_map_notify_pa ket->record_count );

            printf ("\n TCP server address: %s " , recved_map_notify_packet - > server_ip_address ); // ! new

            tcp_server_access_main ( recved_map_notify_packet -> server_ip_address );

          }
          printf ("\ nTotal number of program cycles in UDP client : % ld : \ n" ,  udp_cli_program_cycle );
          return 0;
     }
