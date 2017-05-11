/*
 * Copyright (c) 2013, NLNet Labs, Verisign, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the names of the copyright holders nor the
 *   names of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Verisign, Inc. BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _check_getdns_context_set_upstream_recursive_servers_h_
#define _check_getdns_context_set_upstream_recursive_servers_h_

    /*
     ******************************************************************************************
     *                                                                                        *
     *  T E S T S  F O R  G E T D N S _ C O N T E X T _ S E T _ S T U B _ R E S O L U T I O N *
     *                                                                                        *
     ******************************************************************************************
    */

    START_TEST (getdns_context_set_upstream_recursive_servers_1)
    {
     /*
      *  context is NULL
      *  expect:  GETDNS_RETURN_INVALID_PARAMETER
      */

      struct getdns_context *context = NULL;
      struct getdns_list    *upstream_list = NULL;
     
      LIST_CREATE(upstream_list);
      
      ASSERT_RC(getdns_context_set_upstream_recursive_servers(context, upstream_list),
        GETDNS_RETURN_INVALID_PARAMETER, "Return code from getdns_context_set_upstream_recursive_servers()");

            LIST_DESTROY(upstream_list);
    }
    END_TEST

    START_TEST (getdns_context_set_upstream_recursive_servers_2)
    {
     /*
      *  upstream_list  is NULL
      *  expect: GETDNS_RETURN_INVALID_PARAMETER
      */

      struct getdns_context *context = NULL;
      CONTEXT_CREATE(TRUE);

      ASSERT_RC(getdns_context_set_upstream_recursive_servers(context, NULL),
        GETDNS_RETURN_INVALID_PARAMETER, "Return code from getdns_context_set_upstream_recursive_servers()");


      CONTEXT_DESTROY;        
    }
    END_TEST

    START_TEST (getdns_context_set_upstream_recursive_servers_3)
    {
     /*
      *  create upstream_list 
      *  create context
      * a dict in upstream_list does not contain getdns_bindata
      */

      struct getdns_context *context = NULL;
      struct getdns_list    *upstream_list = NULL;
      struct getdns_dict *dict = NULL;
      size_t index = 0;

      CONTEXT_CREATE(TRUE);
      LIST_CREATE(upstream_list);
      DICT_CREATE(dict);

      ASSERT_RC(getdns_list_set_dict(upstream_list, index, dict), GETDNS_RETURN_GOOD,
        "Return code from getdns_list_set_dict()");


      ASSERT_RC(getdns_context_set_upstream_recursive_servers(context, upstream_list),
        GETDNS_RETURN_CONTEXT_UPDATE_FAIL, "Return code from getdns_context_set_upstream_recursive_servers()");

      CONTEXT_DESTROY;  
      LIST_DESTROY(upstream_list);
      DICT_DESTROY(dict);      
    }
    END_TEST

    START_TEST (getdns_context_set_upstream_recursive_servers_4)
    {
     /*
      *  create upstream_list 
      *  create context
      * a dict in upstream_list does not contain two names
      */

      struct getdns_context *context = NULL;
      struct getdns_list    *upstream_list = NULL;
      struct getdns_dict *dict = NULL;
      struct getdns_bindata address_type = { 5, (void *) "IPv4" };
      size_t index = 0;

      CONTEXT_CREATE(TRUE);
      LIST_CREATE(upstream_list);
      DICT_CREATE(dict);

      ASSERT_RC(getdns_list_set_dict(upstream_list, index, dict), GETDNS_RETURN_GOOD,
        "Return code from getdns_list_set_dict()");

      ASSERT_RC(getdns_dict_set_bindata(dict, "address_type", &address_type),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");


      ASSERT_RC(getdns_context_set_upstream_recursive_servers(context, upstream_list),
        GETDNS_RETURN_CONTEXT_UPDATE_FAIL, "Return code from getdns_context_set_upstream_recursive_servers()");

      CONTEXT_DESTROY;  
      LIST_DESTROY(upstream_list);
      DICT_DESTROY(dict);      
    }
    END_TEST

    START_TEST (getdns_context_set_upstream_recursive_servers_5)
    {
     /*
      *  create upstream_list 
      *  create context
      * a dict in upstream_list contains names other than address_type , 
         address_data, and port
      */

      struct getdns_context *context = NULL;
      struct getdns_list    *upstream_list = NULL;
      struct getdns_dict *dict = NULL;
      struct getdns_bindata address_data = { 4, (void *)"\x08\x08\x08\x08" };
      size_t index = 0;

      CONTEXT_CREATE(TRUE);
      LIST_CREATE(upstream_list);
      DICT_CREATE(dict);

      ASSERT_RC(getdns_list_set_dict(upstream_list, index, dict), GETDNS_RETURN_GOOD,
        "Return code from getdns_list_set_dict()");

     ASSERT_RC(getdns_dict_set_int(dict, "not_address_type", 100),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_int()");

       ASSERT_RC(getdns_dict_set_bindata(dict, "not_address_data", &address_data),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

      ASSERT_RC(getdns_context_set_upstream_recursive_servers(context, upstream_list),
        GETDNS_RETURN_CONTEXT_UPDATE_FAIL, "Return code from getdns_context_set_upstream_recursive_servers()");

      CONTEXT_DESTROY;  
      LIST_DESTROY(upstream_list);
      DICT_DESTROY(dict);      
    }
    END_TEST

    START_TEST (getdns_context_set_upstream_recursive_servers_6)
    {
     /*
      *  create upstream_list 
      *  create context
      * a dict in upstream_list contains invalid address_ type (not “IPv4” or “IPv6”)
      */

      struct getdns_context *context = NULL;
      struct getdns_list    *upstream_list = NULL;
      struct getdns_dict *dict = NULL;
      struct getdns_bindata address_type = { 5, (void *)"IPv5" };
       struct getdns_bindata address_data = { 4, (void *)"\x08\x08\x08\x08" };
      size_t index = 0;

      CONTEXT_CREATE(TRUE);
      LIST_CREATE(upstream_list);
      DICT_CREATE(dict);

      ASSERT_RC(getdns_list_set_dict(upstream_list, index, dict), GETDNS_RETURN_GOOD,
        "Return code from getdns_list_set_dict()");

     ASSERT_RC(getdns_dict_set_bindata(dict, "address_type", &address_type),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");
       ASSERT_RC(getdns_dict_set_bindata(dict, "address_data", &address_data),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

      ASSERT_RC(getdns_context_set_upstream_recursive_servers(context, upstream_list),
        GETDNS_RETURN_CONTEXT_UPDATE_FAIL, "Return code from getdns_context_set_upstream_recursive_servers()");

      CONTEXT_DESTROY;  
      LIST_DESTROY(upstream_list);
      DICT_DESTROY(dict);      
    }
    END_TEST

    START_TEST (getdns_context_set_upstream_recursive_servers_7)
    {
     /*
      *  create upstream_list 
      *  create context
      * a dict in upstream_list contains named address_type and 
         address_data but the data type isn’t bindata
      */

      struct getdns_context *context = NULL;
      struct getdns_list    *upstream_list = NULL;
      struct getdns_dict *dict = NULL;
      size_t index = 0;

      CONTEXT_CREATE(TRUE);
      LIST_CREATE(upstream_list);
      DICT_CREATE(dict);

     ASSERT_RC(getdns_list_set_dict(upstream_list, index, dict), GETDNS_RETURN_GOOD,
        "Return code from getdns_list_set_dict()"); 

     ASSERT_RC(getdns_dict_set_int(dict, "address_type", 100),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_int()");

       ASSERT_RC(getdns_dict_set_int(dict, "address_data", 200),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_int()");

      ASSERT_RC(getdns_context_set_upstream_recursive_servers(context, upstream_list),
        GETDNS_RETURN_CONTEXT_UPDATE_FAIL, "Return code from getdns_context_set_upstream_recursive_servers()");

      CONTEXT_DESTROY;  
      LIST_DESTROY(upstream_list);
      DICT_DESTROY(dict);      
    }
    END_TEST

    START_TEST (getdns_context_set_upstream_recursive_servers_8)
    {
     /*
      *  create upstream_list 
      *  create context
      *  a dict in upstream_list contains invalid address_data
      */

      struct getdns_context *context = NULL;
      struct getdns_list    *upstream_list = NULL;
      struct getdns_dict *dict = NULL;
      struct getdns_bindata address_type = { 5, (void *)"IPv5" };
      struct getdns_bindata address_data = { 4, (void *)"\x08\x08\x08\x08" };
      size_t index = 0;

      CONTEXT_CREATE(TRUE);
      LIST_CREATE(upstream_list);
      DICT_CREATE(dict);

     ASSERT_RC(getdns_list_set_dict(upstream_list, index, dict), GETDNS_RETURN_GOOD,
        "Return code from getdns_list_set_dict()"); 

     ASSERT_RC(getdns_dict_set_bindata(dict, "address_type", &address_type),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");
       ASSERT_RC(getdns_dict_set_bindata(dict, "address_data", &address_data),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

      ASSERT_RC(getdns_context_set_upstream_recursive_servers(context, upstream_list),
        GETDNS_RETURN_CONTEXT_UPDATE_FAIL, "Return code from getdns_context_set_upstream_recursive_servers()");

      CONTEXT_DESTROY;  
      LIST_DESTROY(upstream_list);
      DICT_DESTROY(dict);      
    }
    END_TEST

    START_TEST (getdns_context_set_upstream_recursive_servers_9)
    {
     /*
      *  create context
      *  Call getdns_list_create() to create a list
      *  Call getdns_dict_create() to create a list
      *  Create bindata containing “IPv4” 
      */

      struct getdns_context *context = NULL;
      struct getdns_list    *upstream_list = NULL;
      struct getdns_dict *dict = NULL;
      struct getdns_dict *response = NULL;
      struct getdns_bindata address_type = { 4, (void *)"IPv4" };
      struct getdns_bindata address_data = { 4, (void *)"\x08\x08\x08\x08" };
      size_t index = 0;

      CONTEXT_CREATE(TRUE);
      LIST_CREATE(upstream_list);
      DICT_CREATE(dict);

      ASSERT_RC(getdns_dict_set_bindata(dict, "address_type", &address_type),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

      ASSERT_RC(getdns_dict_set_bindata(dict, "address_data", &address_data),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

      ASSERT_RC(getdns_list_set_dict(upstream_list, index, dict), GETDNS_RETURN_GOOD,
        "Return code from getdns_list_set_dict()"); 


      ASSERT_RC(getdns_context_set_upstream_recursive_servers(context, upstream_list),
        GETDNS_RETURN_GOOD, "Return code from getdns_context_set_upstream_recursive_servers()");

      ASSERT_RC(getdns_general_sync(context, "google.com", GETDNS_RRTYPE_A, NULL, &response), 
         GETDNS_RETURN_GOOD, "Return code from getdns_general_sync()");


      EXTRACT_RESPONSE;

       assert_noerror(&ex_response);
       assert_address_in_answer(&ex_response, TRUE, FALSE);

      CONTEXT_DESTROY;  
      LIST_DESTROY(upstream_list);
      DICT_DESTROY(dict);
      DICT_DESTROY(response);
    }
    END_TEST

/* This test disabled because travis does not support IPv6 in their
 * container based infrastructure!
 */
#if 0
    START_TEST (getdns_context_set_upstream_recursive_servers_10)
    {
     /*
      *  create context
      *  Call getdns_list_create() to create a list
      * Call getdns_dict_create() to create a list
      * Create bindata containing “IPv6” 
      */

      struct getdns_context *context = NULL;
      struct getdns_list    *upstream_list = NULL;
      struct getdns_dict *dict = NULL;
      struct getdns_dict *response = NULL;
      struct getdns_bindata address_type = { 5, (void *)"IPv6" };
      struct getdns_bindata address_data = { 16, (void *)"\x26\x20\x00\x74\x00\x1b\x00\x00\x00\x00\x00\x00\x00\x01\x00\x01" };
      size_t index = 0;

      CONTEXT_CREATE(TRUE);
      LIST_CREATE(upstream_list);
      DICT_CREATE(dict);

      ASSERT_RC(getdns_dict_set_bindata(dict, "address_type", &address_type),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

      ASSERT_RC(getdns_dict_set_bindata(dict, "address_data", &address_data),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

      ASSERT_RC(getdns_list_set_dict(upstream_list, index, dict), GETDNS_RETURN_GOOD,
        "Return code from getdns_list_set_dict()"); 


      ASSERT_RC(getdns_context_set_upstream_recursive_servers(context, upstream_list),
        GETDNS_RETURN_GOOD, "Return code from getdns_context_set_upstream_recursive_servers()");

      ASSERT_RC(getdns_general_sync(context, "google.com", GETDNS_RRTYPE_A, NULL, &response), 
         GETDNS_RETURN_GOOD, "Return code from getdns_general_sync()");

      EXTRACT_RESPONSE;

       assert_noerror(&ex_response);
       assert_address_in_answer(&ex_response, TRUE, FALSE);

      CONTEXT_DESTROY;  
      LIST_DESTROY(upstream_list);
      DICT_DESTROY(dict);
      DICT_DESTROY(response);
    }
    END_TEST
#endif
    START_TEST (getdns_context_set_upstream_recursive_servers_11)
    {
     /*
      *  create context
      *  Call getdns_list_create() to create a list
      *  Call getdns_dict_create() to create a list
      *  Create bindata containing “IPv4” 
      */

      struct getdns_context *context = NULL;
      struct getdns_list    *upstream_list = NULL;
      struct getdns_dict *dict = NULL;
      struct getdns_dict *response = NULL;
      struct getdns_bindata address_type = { 4, (void *)"IPv4" };
      struct getdns_bindata address_data = { 4, (void *)"\x08\x08\x08\x08" };
      struct getdns_bindata port = { 3, (void *)"53" };
      size_t index = 0;

      CONTEXT_CREATE(TRUE);
      LIST_CREATE(upstream_list);
      DICT_CREATE(dict);

      ASSERT_RC(getdns_dict_set_bindata(dict, "address_type", &address_type),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

      ASSERT_RC(getdns_dict_set_bindata(dict, "address_data", &address_data),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

      ASSERT_RC(getdns_dict_set_bindata(dict, "53", &port),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

      ASSERT_RC(getdns_list_set_dict(upstream_list, index, dict), GETDNS_RETURN_GOOD,
        "Return code from getdns_list_set_dict()"); 


      ASSERT_RC(getdns_context_set_upstream_recursive_servers(context, upstream_list),
        GETDNS_RETURN_GOOD, "Return code from getdns_context_set_upstream_recursive_servers()");

      ASSERT_RC(getdns_general_sync(context, "google.com", GETDNS_RRTYPE_A, NULL, &response), 
         GETDNS_RETURN_GOOD, "Return code from getdns_general_sync()");


      EXTRACT_RESPONSE;
      printf("the resp is %s\n", getdns_pretty_print_dict(response));


       assert_noerror(&ex_response);
       assert_address_in_answer(&ex_response, TRUE, FALSE);

      CONTEXT_DESTROY;  
      LIST_DESTROY(upstream_list);
      DICT_DESTROY(dict);
      DICT_DESTROY(response);
    }
    END_TEST

    START_TEST (getdns_context_set_upstream_recursive_servers_12)
    {
<<<<<<< Updated upstream
     /*
      */

      struct getdns_context *context = NULL;
      struct getdns_context *context_pin = NULL;
      struct getdns_context *context_pin_set = NULL;
      struct getdns_list    *upstream_list = NULL;
      struct getdns_list    *errorlist = NULL;
      struct getdns_list  *pubkey_pinset = NULL;
      struct getdns_dict *dict = NULL;
      struct getdns_dict *pubkey_pin = NULL;
      struct getdns_dict *response = NULL;
      struct getdns_bindata address_type = { 4, (void *)"IPv4" };
      struct getdns_bindata address_data = { 4, (void *)"\x91\x64\xb9\x0f" };
      struct getdns_bindata port = { 3, (void *)"53" };
      struct getdns_bindata digest = {sizeof("sha256") - 1, (void*) "sha256"};
      struct getdns_bindata value = {32, (void*)"\xeb\x69\x4a\xbb\xd1\xec\x0d\x56\xf2\x88\xf7\xa7\x02\x99\xdc\xc7\xe6\x49\x84\xc7\x39\x57\xc5\x80\xbd\xe9\xc8\x1f\x9c\x04\xbe"};
      struct getdns_bindata tls_auth_name = {sizeof("dnsovertls.sinodun.com") - 1, (void*) "dnsovertls.sinodun.com"};
      char *tls_name = "dnsovertls.sinodun.com";
//      sha256_pin_t *tls_pubkey_pinset;
  //    tls_pubkey_pinset ->pin = "62lKu9HsDVbyiPenApnc4sfmSYTHOVfFgL3pyB+cBL4=";
    //  tls_pubkey_pinset ->next = NULL;
=======
     /* DNS OVER TLS
      * resolution_type: GETDNS_RESOLUTION_STUB
      * dns_transport_list: GETDNS_TRANSPORT_TLS 
      * tls_authentication: GETDNS_AUTHENTICATION_REQUIRED
      * upstream_recursive_servers: 
      *    address_data: 145.100.185.15
      *    tls_auth_name: "dnsovertls.sinodun.com"
      *    tls_pubkey_pinset:
      *      digest: "sha256"
      *      value: 62lKu9HsDVbyiPenApnc4sfmSYTHOVfFgL3pyB+cBL4=
      */
      struct getdns_context    *context = NULL;
      struct getdns_list       *upstream_list = NULL;
      struct getdns_list       *errorlist = NULL;
      struct getdns_list       *pubkey_pinset = NULL;
      struct getdns_dict       *dict = NULL;
      struct getdns_dict       *pubkey_pin = NULL;
      struct getdns_dict       *response = NULL;
      getdns_transport_list_t  transport_list[1];
      getdns_transport_list_t  *transport_list2;
      getdns_list              *upstreams_r = NULL;
      getdns_tls_authentication_t auth;
      size_t count;
      uint16_t backoff;
      uint16_t retries;

      struct getdns_bindata address_type = { 4, (void *)"IPv4" };
      struct getdns_bindata address_data = { 4, (void *)"\x91\x64\xb9\x0f" };
      struct getdns_bindata digest = {sizeof("sha256") - 1, (void*) "sha256"};
      struct getdns_bindata value = {32, (void *)"\xeb\x69\x4a\xbb\xd1\xec\x0d\x56\xf2\x88\xf7\xa7\x02\x99\xdc\xc7\xe6\x49\x84\xc7\x39\x57\xc5\x80\xbd\xe9\xc8\x1f\x9c\x04\xbe"};
      struct getdns_bindata tls_auth_name = {sizeof("dnsovertls.sinodun.com") - 1, (void *) "dnsovertls.sinodun.com"};
      size_t index = 0;

      CONTEXT_CREATE(TRUE);
      LIST_CREATE(upstream_list);
      LIST_CREATE(errorlist);
      LIST_CREATE(pubkey_pinset);
      LIST_CREATE(upstreams_r);
      DICT_CREATE(dict);
      DICT_CREATE(pubkey_pin);


      ASSERT_RC(getdns_dict_set_bindata(dict, "address_type", &address_type),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

      ASSERT_RC(getdns_dict_set_bindata(dict, "address_data", &address_data),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

      ASSERT_RC(getdns_dict_set_bindata(pubkey_pin, "digest", &digest),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

 ASSERT_RC(getdns_dict_set_bindata(pubkey_pin, "value", &value),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");
ASSERT_RC(getdns_dict_set_bindata(dict, "tls_auth_name", &tls_auth_name),
	GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

     /* ASSERT_RC(getdns_dict_util_set_string(dict, "tls_auth_name", tls_name),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_util_set_string"); 
      
      ASSERT_RC(getdns_dict_util_set_string(dict, "tsig_name", "62lKu9HsDVbyiPenApnc4sfmSYTHOVfFgL3pyB+cBL4="),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_util_set_string");
      ASSERT_RC(getdns_dict_util_set_string(dict, "tsig_algorithm", "sha256"),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_util_set_string");*/
     pubkey_pinset = getdns_list_create_with_context(context_pin_set);
      int pincount = 0;
      getdns_list_set_dict(pubkey_pinset, pincount++, pubkey_pin);
      getdns_dict_set_list(dict, "tls_pubkey_pinset", pubkey_pinset);

 ASSERT_RC(getdns_pubkey_pinset_sanity_check(pubkey_pinset, errorlist),
         GETDNS_RETURN_GOOD, "Return code from getdns_pubkey_pinset_sanity_check()");

      ASSERT_RC(getdns_dict_set_bindata(dict, "tls_auth_name", &tls_auth_name),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

/*      ASSERT_RC(getdns_dict_util_set_string(dict, "tls_auth_name", "dnsovertls.sinodun.com"),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_util_set_string()");*/

      ASSERT_RC(getdns_dict_set_bindata(pubkey_pin, "digest", &digest),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

      ASSERT_RC(getdns_dict_set_bindata(pubkey_pin, "value", &value),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

/*      pubkey_pin = getdns_pubkey_pin_create_from_string (NULL, "pin-sha256=\"62lKu9HsDVbyiPenApnc4sfmSYTHOVfFgL3pyB+cBL4=\"");
      ck_assert_msg(pubkey_pin != NULL, "pubkey_pin creation failed");*/

    /*  ASSERT_RC(getdns_dict_util_set_string(dict, "tsig_name", ""),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_util_set_string");
      ASSERT_RC(getdns_dict_util_set_string(dict, "tsig_algorithm", ""),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_util_set_string");*/

      getdns_list_set_dict(pubkey_pinset, 0, pubkey_pin);
      getdns_dict_set_list(dict, "tls_pubkey_pinset", pubkey_pinset);
      printf("Hodaa pins %s\n", getdns_pretty_print_list(pubkey_pinset));

     /* ASSERT_RC(getdns_pubkey_pinset_sanity_check(pubkey_pinset, errorlist),
         GETDNS_RETURN_GOOD, "Return code from getdns_pubkey_pinset_sanity_check()");*/

      ASSERT_RC(getdns_list_set_dict(upstream_list, index, dict), GETDNS_RETURN_GOOD,
        "Return code from getdns_list_set_dict()");


//printf("Hodaa %s\n", getdns_pretty_print_list(errorlist));

      getdns_transport_list_t transport_list[1];
      transport_list[0] = GETDNS_TRANSPORT_TLS;
     ASSERT_RC(getdns_context_set_resolution_type(context, GETDNS_RESOLUTION_STUB),
         GETDNS_RETURN_GOOD, "Return code from getdns_context_set_resolution_type()");
 
      ASSERT_RC(getdns_context_set_dns_transport_list(context, 1, transport_list),
	GETDNS_RETURN_GOOD, "Return code from getdns_context_set_dns_transport_list()");
      getdns_transport_list_t *transport_list2;
      size_t count;
      ASSERT_RC(getdns_context_get_dns_transport_list(context, &count, &transport_list2),
        GETDNS_RETURN_GOOD, "Return code from getdns_context_get_dns_transport_list()");
      ck_assert_msg(transport_list2[0] == GETDNS_TRANSPORT_TLS, "transport_list should be 1202 but got %d", (int) transport_list2[0]);
      ASSERT_RC(getdns_context_set_tls_authentication(context, GETDNS_AUTHENTICATION_REQUIRED),
	GETDNS_RETURN_GOOD, "Return cond from getdns_context_set_tls_authentication()");
      getdns_tls_authentication_t auth;
      ASSERT_RC(getdns_context_get_tls_authentication(context, &auth),
	GETDNS_RETURN_GOOD, "Return code from getdns_context_get_tls_authentication()");
      ck_assert_msg(auth == 1301, "tls_authentication should be 1301, but got %d", (int) auth);
      ASSERT_RC(getdns_context_set_tls_backoff_time(context, 1000), 
	GETDNS_RETURN_GOOD, "Return code from getdns_context_set_tls_backoff_time()");
      uint16_t backoff;
      ASSERT_RC(getdns_context_set_resolution_type(context, GETDNS_RESOLUTION_STUB),
         GETDNS_RETURN_GOOD, "Return code from getdns_context_set_resolution_type()");

      transport_list[0] = GETDNS_TRANSPORT_TLS;
      ASSERT_RC(getdns_context_set_dns_transport_list(context, 1, transport_list),
	GETDNS_RETURN_GOOD, "Return code from getdns_context_set_dns_transport_list()");
      ASSERT_RC(getdns_context_get_dns_transport_list(context, &count, &transport_list2),
        GETDNS_RETURN_GOOD, "Return code from getdns_context_get_dns_transport_list()");
      ck_assert_msg(transport_list2[0] == GETDNS_TRANSPORT_TLS, "transport_list should be 1202 but got %d", (int) transport_list2[0]);

      ASSERT_RC(getdns_context_set_tls_authentication(context, GETDNS_AUTHENTICATION_REQUIRED),
	GETDNS_RETURN_GOOD, "Return cond from getdns_context_set_tls_authentication()");
      ASSERT_RC(getdns_context_get_tls_authentication(context, &auth),
	GETDNS_RETURN_GOOD, "Return code from getdns_context_get_tls_authentication()");
      ck_assert_msg(auth == 1301, "tls_authentication should be 1301, but got %d", (int) auth);

      ASSERT_RC(getdns_context_set_tls_backoff_time(context, 1000), 
	GETDNS_RETURN_GOOD, "Return code from getdns_context_set_tls_backoff_time()");
      ASSERT_RC(getdns_context_get_tls_backoff_time(context, &backoff),
        GETDNS_RETURN_GOOD, "Return code from getdns_context_get_tls_backoff_time()");
      ck_assert_msg(backoff == 1000, "backoff should be 1000, but got %d", (int) backoff);

      ASSERT_RC(getdns_context_set_tls_connection_retries(context, 5),
	GETDNS_RETURN_GOOD, "Return code from getdns_context_set_tls_connection_retries()");
      uint16_t retries;
      ASSERT_RC(getdns_context_get_tls_connection_retries(context, &retries),
	GETDNS_RETURN_GOOD, "Return code from getdns_context_get_tls_connection_retries()");
      ck_assert_msg(retries == 5, "retries should be 5 but got %d", (int) retries);

//      ck_assert_msg(0, "Nedaaaa %s\n", getdns_pretty_print_list(upstream_list));
//printf("Hoda upstream_list is %s\n", getdns_pretty_print_list(upstream_list));
printf("Hoda upstream_list is %s\n", getdns_pretty_print_list(upstream_list));
//fflush(stdout);
      ASSERT_RC(getdns_context_set_upstream_recursive_servers(context, upstream_list),
        GETDNS_RETURN_GOOD, "Return code from getdns_context_set_upstream_recursive_servers()");

 /*     ASSERT_RC(getdns_general_sync(context, "google.com", GETDNS_RRTYPE_A, NULL, &response),
         GETDNS_RETURN_GOOD, "Return code from getdns_general_sync()");


      EXTRACT_RESPONSE;
      printf("the resp is %s\n", getdns_pretty_print_dict(response));


       assert_noerror(&ex_response);
       assert_address_in_answer(&ex_response, TRUE, FALSE);
      ASSERT_RC(getdns_context_get_upstream_recursive_servers(context, &upstreams_r),
        GETDNS_RETURN_GOOD, "Return code from getdns_context_get_upstream_recursive_servers()");

      ASSERT_RC(getdns_general_sync(context, "google.com", GETDNS_RRTYPE_A, NULL, &response),
        GETDNS_RETURN_GOOD, "Return code from getdns_general_sync()");
      EXTRACT_RESPONSE;
      printf("the resp is %s\n", getdns_pretty_print_dict(response));
      fflush(stdout);
      assert_noerror(&ex_response);
      assert_address_in_answer(&ex_response, TRUE, FALSE);
*/
      CONTEXT_DESTROY;
      LIST_DESTROY(upstream_list);
      DICT_DESTROY(dict);
      DICT_DESTROY(response);
    }
    END_TEST

    
    START_TEST (getdns_context_set_upstream_recursive_servers_13)
    {
     /* DNS OVER TLS
      * resolution_type: GETDNS_RESOLUTION_STUB
      * dns_transport_list: GETDNS_TRANSPORT_TLS 
      * tls_authentication: GETDNS_AUTHENTICATION_REQUIRED
      * upstream_recursive_servers: 
      *    address_data: 185.49.141.37
      *    tsig_name: hmac-md5.tsigs.getdnsapi.net. 
      *    tsig_algorithm: hmac-md5.sig-alg.reg.int.
      *    tsig_secret: 16G69OTeXW6xSQ==
      */
      struct getdns_context    *context = NULL;
      struct getdns_list       *upstream_list = NULL;
      struct getdns_dict       *dict = NULL;
      struct getdns_dict       *response = NULL;
      getdns_transport_list_t  transport_list[1];
      getdns_list              *upstreams_r = NULL;

      struct getdns_bindata address_type = { 4, (void *)"IPv4" };
      struct getdns_bindata address_data = { 16, (void *)"\xB9\x31\x8D\x25" };

      CONTEXT_CREATE(TRUE);
      LIST_CREATE(upstream_list);
      LIST_CREATE(upstreams_r);
      DICT_CREATE(dict);

      ASSERT_RC(getdns_dict_set_bindata(dict, "address_type", &address_type),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");

      ASSERT_RC(getdns_dict_set_bindata(dict, "address_data", &address_data),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_set_bindata()");


      ASSERT_RC(getdns_dict_util_set_string(dict, "tsig_name", "hmac-md5.tsigs.getdnsapi.net"),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_util_set_string");
      //ASSERT_RC(getdns_dict_util_set_string(dict, "tsig_algorithm", "hmac-md5.sig-alg.reg.int"),
       //  GETDNS_RETURN_GOOD, "Return code from getdns_dict_util_set_string");
      ASSERT_RC(getdns_dict_util_set_string(dict, "tsig_secret", "16G69OTeXW6xSQ=="),
         GETDNS_RETURN_GOOD, "Return code from getdns_dict_util_set_string");


      ASSERT_RC(getdns_list_set_dict(upstream_list, 0, dict), GETDNS_RETURN_GOOD,
        "Return code from getdns_list_set_dict()");

      ASSERT_RC(getdns_context_set_resolution_type(context, GETDNS_RESOLUTION_STUB),
         GETDNS_RETURN_GOOD, "Return code from getdns_context_set_resolution_type()");

  //    transport_list[0] = GETDNS_TRANSPORT_TLS;
   //   ASSERT_RC(getdns_context_set_dns_transport_list(context, 1, transport_list),
//	GETDNS_RETURN_GOOD, "Return code from getdns_context_set_dns_transport_list()");

  //    ASSERT_RC(getdns_context_set_tls_authentication(context, GETDNS_AUTHENTICATION_REQUIRED),
//	GETDNS_RETURN_GOOD, "Return cond from getdns_context_set_tls_authentication()");

      printf("Hoda upstream_list is %s\n", getdns_pretty_print_list(upstream_list));

      ASSERT_RC(getdns_context_set_upstream_recursive_servers(context, upstream_list),
        GETDNS_RETURN_GOOD, "Return code from getdns_context_set_upstream_recursive_servers()");
      ASSERT_RC(getdns_context_get_upstream_recursive_servers(context, &upstreams_r),
        GETDNS_RETURN_GOOD, "Return code from getdns_context_get_upstream_recursive_servers()");


      ASSERT_RC(getdns_general_sync(context, "google.com", GETDNS_RRTYPE_A, NULL, &response),
        GETDNS_RETURN_GOOD, "Return code from getdns_general_sync()");
      EXTRACT_RESPONSE;
      printf("the resp is %s\n", getdns_pretty_print_dict(response));
      assert_noerror(&ex_response);
      assert_address_in_answer(&ex_response, TRUE, FALSE);

      CONTEXT_DESTROY;
      LIST_DESTROY(upstream_list);
      DICT_DESTROY(dict);
      DICT_DESTROY(response);
    }
    END_TEST
 
    
    
    Suite *
    getdns_context_set_upstream_recursive_servers_suite (void)
    {
      Suite *s = suite_create ("getdns_context_set_upstream_recursive_servers()");
    
      /* Negative test caseis */
  /*    TCase *tc_neg = tcase_create("Negative");
      tcase_add_test(tc_neg, getdns_context_set_upstream_recursive_servers_1);
      tcase_add_test(tc_neg, getdns_context_set_upstream_recursive_servers_2);
      tcase_add_test(tc_neg, getdns_context_set_upstream_recursive_servers_3);
      tcase_add_test(tc_neg, getdns_context_set_upstream_recursive_servers_4);
      tcase_add_test(tc_neg, getdns_context_set_upstream_recursive_servers_5);
      tcase_add_test(tc_neg, getdns_context_set_upstream_recursive_servers_6);
      tcase_add_test(tc_neg, getdns_context_set_upstream_recursive_servers_7);
      tcase_add_test(tc_neg, getdns_context_set_upstream_recursive_servers_8);

      suite_add_tcase(s, tc_neg);
    */
      /* Positive test cases */
       TCase *tc_pos = tcase_create("Positive");
      // tcase_add_test(tc_pos, getdns_context_set_upstream_recursive_servers_9);
/***** tcase_add_test(tc_pos, getdns_context_set_upstream_recursive_servers_10); *****/
       tcase_add_test(tc_pos, getdns_context_set_upstream_recursive_servers_11);
       tcase_add_test(tc_pos, getdns_context_set_upstream_recursive_servers_12);
       tcase_add_test(tc_pos, getdns_context_set_upstream_recursive_servers_13);
      
       suite_add_tcase(s, tc_pos);

       return s;

    }

#endif
