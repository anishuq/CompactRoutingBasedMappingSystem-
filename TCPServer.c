     //! TCP Server
     //! C.3.1 I/O Multiplexed TCP Server to handle multiple clients simultaneously.
     int main ()
     {
        signal ( SIGINT ,( void *) sighandler);
        //! to handle CTRL + C and we will exit normally.

         int listenfd , connfd , pid , client_len;
         char buff [ BUFSIZ ], cli_data[ BUFSIZ] , send_data[ BUFSIZ ] ;
         int i , fd , n;

         fd_set active_fd_set , read_fd_set;
         struct sockaddr_in tcp_cliaddr , tcp_servaddr;

         listenfd = socket ( AF_INET , SOCK_STREAM , 0);

         if( listenfd < 0)
             printf (" Error in Socket creation! \ n" );

         bzero (& tcp_servaddr , sizeof ( tcp_servaddr ));
         bzero (& tcp_cliaddr , sizeof ( tcp_cliaddr ));

         tcp_servaddr.sin_family = AF_INET;
         tcp_servaddr.sin_addr. s_addr = htonl ( INADDR_ANY );
         tcp_servaddr.sin_port = htons ( TCP_SERVER_PORT );

         if(    bind ( listenfd , ( struct sockaddr *) & tcp_servaddr , sizeof ( tcp_servaddr ))== -1)
         {
               printf ("\ nError in binding !!!!\ n" );
               exit (0);
         }
         listen ( listenfd , LISTENQ); // MUST
         printf (" Waiting for lient on % d \n " , TCP_SERVER_PORT );

         // initialize the set of a tive so kets.
         FD_ZERO(& active_fd_set );
         FD_SET ( listenfd ,& active_fd_set );

         while (1)
         { //1
               read_fd_set = active_fd_set;

               if( select ( FD_SETSIZE ,& read_fd_set , NULL , NULL , NULL ) <0)
               {
                   perror (" select error " );
                   exit ( EXIT_FAILURE );
               }

               for( fd = 0; fd < FD_SETSIZE; fd ++)
               { // 2
                       if( FD_ISSET(fd , & read_fd_set ))
                       { //3
                             if( fd == listenfd) // ! new client wants to connect
                             { // 4
                                    client_len = sizeof ( tcp_ liaddr );
                                    connfd = accept ( listenfd ,( struct sockaddr*) & tcp_cliaddr ,& client_len );

                                    FD_SET ( connfd , & read_fd_set );
                                    //! Add the fd to the fd_set

                                    printf (" Connected from %s , port %d \n" , inet_ntop( AF_INET ,& tcp_cliaddr. sin_addr , buff , sizeof ( buff )) , ntohs ( tcp_cliaddr. sin_port ));
                               } // 4
                               else
                               { // 4
                                      //! read from the client
                                      bzero ( cli_data , BUFSIZ );
                                      n = read (fd , cli_data , BUFSIZ -1);

                                        if( n < 1 ) // ! means the client has closed .
                                        { // 5
                                             close ( fd );
                                             FD_CLR (fd ,& read_fd_set );

                                             printf (" Removing client #%d from list ." ,fd );
                                        } // 5
                                        else // ! means the lient has data .
                                        { // 5
                                               printf (" zzzz %s\ n" , cli_data );
                                               // ! Here we have to put ode to a ess the db .

                                               memset ( send_data , '\0 ', BUFSIZ );

                                               strcpy ( send_data , db_access_main( cli_data ));
                                               // ! access then MySQL database through TCPServerDB program.

                                               printf ("\ n Data sent to the client : %s \n" , send_data);
                                                 if (( write ( connfd , send_data , strlen ( send_data )) <0))
                                                       error (" ERROR writing to so ket " );
                                       } // 5
                               } // 4

                       } //3
                 } // 2
          } //1

          return 0;
     }
