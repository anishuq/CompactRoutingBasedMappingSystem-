      //! Prefix length calculation for address aggregation.

      /**
      *
      * @brief This function goes through the linked list, parses it and calculates the prefix length .
      * The " struct node " has elements like , ip_address_bi and mask_ip_bi ( both r strings). As the
      * names suggest, " ip_address_bi" contains the binary version of an ip address and mask_ip_bi
      * ( or prefix IP ) contains the binary version of the prefix . Until now , these two fields
      * remained vaccant . This function fills them by first extracting all the octets ( in two steps )
      * and then by converting them to binary with the help of the function "dec_to_bi ()". This function
      * also calculates the mask length .
      *
      * @author A. M . Anisul Huq
      * @param snode              pointer to the starting node of
      *                           the linked list .
      * @retval
      *
      */

      void route_proccessing ( struct node * snode )
      // ! snode is starting node .
      {
         auto char delims [] = "/" ;
         auto char mdelims[] = ". "; // micro delimeter

          auto char * token = NULL ;
          auto char * mtoken = NULL ; // micro token
          auto char * last ;

          char * separated_token [2];
          char * mseparated_token [4];

          char * original_eid_prefix;

          auto struct node* node = snode ;
          auto int i ,j;

          /**
          we parse the eid prefix ; first on the basis of "/" ( the outer while loop )
          and then on the basis of "." ( the inner while loop ).
          */


        while ( node != NULL )
        {
           bzero ( temp_ip_address , ADDRESS_LENGTH );
           bzero ( temp_mask_ip , ADDRESS_LENGTH );
          /** temp_ip_address and temp_mask_ip ontains the
           binary version of the ip address and mask ip. */

           // store node - > temp_eid_prefix in original_eid_prefix .
           original_eid_prefix = malloc( strlen ( node - > temp_eid_prefix ) +1);
           strcpy ( original_eid_prefix , node - > temp_eid_prefix );

           i = 0;
           token = strtok ( original_eid_prefix , delims );

           while ( token != NULL )
           {
              /** the outer while loop separates on the basis of "/". */
              separated_token [i] = malloc( strlen ( token ) + 1);
              strcpy ( separated_token [i] , token );

               /** the inner while loop separates on the basis of "." */
               j = 0;
               mtoken = strtok_r( separated_token [i] , mdelims , &last );

               while ( mtoken != NULL )
               {
                  mseparated_token [j] = malloc( strlen ( mtoken ) + 1);
                  strcpy ( mseparated_token [j] , mtoken );
                  // printf ("%s " , mseparated_token [j℄ );

                  // ! onvert to binary . and also de ide the
                  // ! length of the mask ( start )
                  if (i == 0)
                    dec_to_bi( atoi ( mseparated_token[j]) , 0);

                    if (i == 1)
                    // ! we ount the mask_len only in ase of mask IP.
                         dec_to_bi( atoi ( mseparated_token [j]) , 1);
                    // ! onvert to binary . and also de ide the
                    // ! length of the mask ( end)

                    j ++;
                    mtoken = strtok_r( NULL , mdelims , &last );
               }

               if ( i == 1)
               {
                     node-> mask_len = number_of_ones;
                    /**" number_of_ones" is a global variable which is
                    used to count the mask length . */
                    number_of_ones = 0;
               }
               i ++;
               token = strtok ( NULL , delims );
           }

            strcpy ( node -> ip_address_bi , temp_ip_address );
            strcpy ( node -> mask_ip_bi , temp_mask_ip );


             node - > ancestor_flag = 0;
             // ! initially we presume that , there are no an estor
             // ! for this node .

              node = node -> next ;
          }
          //! Garbage olle tion ( start )
          free ( original_eid_prefix ); // ! Lookout.
          auto int k;

          for( k = 0; k < 2; k ++)
          {
              free ( separated_token [k]);
          }

          for( k = 0; k < 4; k ++)
          {
              free ( mseparated_token [k]);
          }
          //! Garbage olle tion ( end)
     }
