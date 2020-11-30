   //! IP Address aggregation.
      /**
      *
      * @brief    This function determines whether a node has an
      *           ancestor or not.
      * @author   A. M . Anisul Huq
      * @param    snode             pointer to the starting node of
      *                             the linked list .
      * @retval
      *
      */

      void route_aggregate( struct node* snode )
      {
         // display( snode );
         auto int i;
         auto int match_flag = 1;

         char* node_substring ;
         char* tnode_substring ;

         struct node* cnode = snode ;
         //! node means current node
         struct node* tnode ;
         //! tnode means traversing node

          while ( cnode != NULL )
          { // loop for node ( start )
              // tnode = node - > next ;
              /**
              For every cnode , we traverse the whole linked list
              to find a possible ancestor. Thats why, the " tnode " or
              " traversing node " is always initialized to the starting
              location.
              */
              tnode = snode ;
              while ( tnode != NULL )
              { //! loop for tnode ( start )
                  if ( tnode -> mask_len < cnode -> mask_len)
                  /** tnode maybe an ancestor of node. To be a parent ,
                  tnode's mask_len must be less than node's mask_len. */
                  {
                      cnode_substring = ( char *) malloc( tnode -> mask_len + 1);
                      strncpy( code_substring , cnode -> ip_address_bi ,  tnode -> mask_len);
                      cnode_substring[ tnode -> mask_len ]= '\0 ';

                      tnode_substring = ( char *) malloc( tnode -> mask_len + 1);
                      strncpy( tnode_substring , tnode -> ip_address_bi, tnode -> mask_len);
                      tnode_substring[tnode -> mask_len] = '\0 ';

                      if ( strcmp ( tnode_substring , cnode_substring ) == 0 )
                      {
                           cnode-> ancestor_flag = 1;
                           /** we have determined that our current node or
                           node has an ancestor!
                           */
                      }
                   }
                   tnode = tnode-> next;
              } // loop for tnode ( end)

                  cnode = cnode->next;
           } // loop for cnode ( end)

           //! Garbage collection ( start )
           free ( cnode_substring ); // ! Lookout.
           free ( tnode_substring );
           //! Garbage collection ( end)
    }
