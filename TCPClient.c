
      /**
      * Extraction of BGP's Aggregator and Community Attribute.
      * @brief    Extra t Aggregator and Community attribute
      *           from Quagga's advertisement.
      * @author   A. M. Anisul Huq
      * @param    vtysh_output      Quagga's advertisement in
      *                             the form of a char array .
      * @param
      * @retval   none
      *
      */

      void LMID_extraction ( char * vtysh_output )
      {
         int r ;
         regex_t* myregex = calloc(1 , sizeof ( regex_t ));

          //! Compile the regular expression
          r = regcomp( myregex ," [[: digit :]]{1 ,3}\\.[[:digit :]]{1 ,3}\\.[[:digit :]]{1 ,3}\\.[[: digit :]]{1 ,3}" , REG_EXTENDED );

          regmatch_t pm ;
          int j;
          char * extracted_ip = ( char *) malloc( STANDARD_IP_LENGTH + 1);
          memset( extracted_ip , ' \0 ' , STANDARD_IP_LENGTH + 1);
          char * temp_storage = ( char *) malloc( STATIC_ARRAY_SIZE + 1 );
          //! "+1" is for NULL hara ter.
          memset ( temp_storage , ' \0 ' , STATIC_ARRAY_SIZE + 1);

          char* to = ( char *) malloc( STATIC_ARRAY_SIZE + 1 );
          memset (to , ' \0 ' , STATIC_ARRAY_SIZE + 1);
          strcpy ( temp_storage , vtysh_output );

          j = regexec( myregex , temp_storage ,1 ,&pm ,0);
          //! make the first mat h !

          strncpy( extracted_ip , ( temp_storage+ pm . rm_so ) , ( pm.rm_eo - pm.rm_so ) );
         // is_aggregator( extra ted_ip );
         //! Test if aggregator attribute is there or not.

         extract_rloc_community_attribute ( extracted_ip );
         //! fun tion all that does pattern mat hing and
         //! extra ts RLOC and Community value .

         //! printf (" he he :%s \n" , extra ted_ip );
         memset ( extracted_ip , ' \0 ' , STANDARD_IP_LENGTH );
         memset ( temp_storage , ' \0 ' , STATIC_ARRAY_SIZE + 1);

         strncpy(to , ( vtysh_output+ pm.rm_eo ) , ( strlen ( vtysh_output) - pm.rm_eo ) );

         while (1)
         {
             j = regexec( myregex ,to ,1 ,&pm , REG_NOTBOL );

             if( j !=0)
             {
                    tcp_cli_program_cycle ++;
                    // !counting the number of cycles
                    // ! for complexity analysis.
                    break ;
             }

             strcpy ( temp_storage , to );
             strncpy( extracted_ip , ( temp_storage+ pm . rm_so ) ,( pm . rm_eo - pm . rm_so ) );
             extract_rloc_community_attribute ( extracted_ip );
             memset ( extracted_ip , '\0 ' , STANDARD_IP_LENGTH + 1);
             memset ( temp_storage , '\0 ' , STATIC_ARRAY_SIZE + 1);

             //! extract string and then compare( start )
             strncpy( temp_storage , ( to + pm . rm_eo ) , ( strlen ( to ) - pm . rm_eo ) );
             //! put the substring extracted from " to "
             //! into " temp_storage ".

             //! This is done for temporary storage!
             memset (to , '\0 ' , STATIC_ARRAY_SIZE + 1);
             // !" to" is now filled with NULL .

             str py (to , temp_storage );
             //! Now " to " has the extra ted string .

             memset ( temp_storage , '\0 ' , STATIC_ARRAY_SIZE + 1);
             //! Now we fill " temp_storage" with NULL so that
             // ! it an be used in the next iteration.
        }

         //! Garbage collection ( start )
         free ( extracted_ip );
         free ( temp_storage );
         free ( to );
         //! Garbage collection ( end)
     }
