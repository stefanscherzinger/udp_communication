# UDP Communication

This is a small example for a *client-server*-based UDP communication.


## Build and install

We use *Boost*'s [asio](https://www.boost.org/doc/libs/1_83_0/doc/html/boost_asio.html) libraries for UDP socket management.
You can install them with
```bash
sudo apt-get install libboost-system-dev
```

In a terminal, get the repo with
```bash
git clone https://github.com/stefanscherzinger/udp_communication.git
```

and inside that repo

```bash
mkdir build && cd build
cmake ..
make
cmake --install . --prefix $HOME/install
```

## Usage
In every new terminal, use
```bash
export PATH=$PATH:$HOME/install/bin
```
to make both the `server` and `client` binaries globally available.
You can then start them, e.g. with
```bash
server 9001
```
and
```bash
client 9001
```
and watch them communicate on `127.0.0.1` (localhost by default) on port `9001`.
