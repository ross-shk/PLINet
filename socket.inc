 
/* Copyright 2026 Ross Shkurat
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

 %include type_defs;
 %include socket_errors;

 dcl new_socket entry (
   like socket_t, 
   fixed bin(31), 
   fixed bin(31), 
   fixed bin(31));
 
 dcl sock_connect entry (
   like socket_t,
   char(*) varying,
   port_t
 );

 dcl socket_send entry (
   like socket_t,
   char(*) varying,
   flags_t
 ) returns(size_t);

 dcl socket_write entry (
   like socket_t,
   char(*) varying
 ) returns(size_t);
 
 dcl socket_receive entry (
   like socket_t,
   char(*),  
   flags_t
 ) returns(size_t);

 dcl socket_read entry (
   like socket_t,
   char(*)
 ) returns(size_t);

 dcl close_socket entry (
   like socket_t
 ) returns(fixed bin(31));

 dcl shutdown_socket entry (
   like socket_t,
   shut_how_t  /* 0=read, 1=write, 2=both */
 ) returns(fixed bin(31));
  