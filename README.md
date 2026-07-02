# PL/I Networking Library

A basic networking library for PL/I

## Files

| File | Purpose |
|------|---------|
| `type_defs.inc` | Named types (`conncb`, `port_t`, `buffer_t`, etc.) and the `conncb` structure |
| `net_bridge.inc` | C function external declarations (`socket`, `bind`, `listen`, ...) |
| `net.pli` / `.inc` | Object-oriented client socket methods (`net_dial`, `net_send`, `net_receive`, `net_close`, `net_shutdown`, `socket_errno`) |
| `net_server.pli` / `.inc` | Server socket methods (`net_listen`, `net_accept`, `server_error`) |
| `net_errors.inc` | `net_error` condition and `get_errno` entry |
| `net_bridge.c` | C bridge: `default_accept`, `bind_to_port`, `connect_to_host`, `get_errno_value`, `resolve_hostname` |

## Usage

```pli
 main: procedure options(main);
 %include net;

   declare
     request  char(256) varying,
     response char(2048),
     host     char(256) varying init('example.com:80'),
     bytes    size_t,
     conn     like conncb;

   on condition(neterror) begin;
     display('Networking error, code = ' || oncode());
     goto cleanup;
   end;

   request =
       'GET / HTTP/1.1'    || LINE_END ||
       'Host: ' || host    || LINE_END ||
       'Connection: close' || LINE_END || LINE_END;
   
   call netdial(conn, host, AF.INET);

   call netwriteall(conn, request); 
   bytes = netreadall(conn, response);

   display('Response ' || substr(response, 1, bytes));
 
 cleanup:
   call netclose(conn); 
 end;
```

## Build & Install

Requires Iron Spring PL/I (`plic`) and `gcc` (32-bit).

```sh
make
sudo make install              # or: make install PREFIX=$HOME/.local
```

## Run an Example

After `make install`, compile and link against the installed library:

```sh
cd examples

plic -C -dELF readall_test.pli    \
  $(pkg-config --cflags net)      \  
  -o readall_test.o

gcc -m32 -no-pie -z muldefs        \   
  -o readall_test readall_test.o   \
  $(pkg-config --libs net)                 
```

**NOTE:** `pkg-config` handles the library paths only. The remaining flags are toolchain requirements (Iron Spring PL/I's 32-bit ELF target) and don't change between projects.

Or build with a script:

```sh
cd examples
./build.sh readall_test.pli
```

## License

Apache 2.0
