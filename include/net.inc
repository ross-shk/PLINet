 
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

 dcl net_new entry (
   like conncb, 
   fixed bin(31), 
   fixed bin(31), 
   fixed bin(31));
 
 dcl net_dial entry (
   like conncb,
   char(*) varying,
   port_t
 );

 dcl net_send entry (
   like conncb,
   char(*) varying,
   flags_t
 ) returns(size_t);

 dcl net_write entry (
   like conncb,
   char(*) varying
 ) returns(size_t);
 
 dcl net_receive entry (
   like conncb,
   char(*),  
   flags_t
 ) returns(size_t);

 dcl net_read entry (
   like conncb,
   char(*)
 ) returns(size_t);

 dcl net_close entry (
   like conncb
 ) returns(fixed bin(31));

 dcl net_shutdown entry (
   like conncb,
   shut_how_t  /* 0=read, 1=write, 2=both */
 ) returns(fixed bin(31));

 dcl net_resolve entry (
   like conncb,
   char(*) varying
 );
  