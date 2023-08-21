# UDP Communication

This is a small example for a *client-server*-based UDP communication.


## Build and install

We use *Boost*'s [asio](https://www.boost.org/doc/libs/1_83_0/doc/html/boost_asio.html) libraries for UDP socket management.
You can install them with
```bash
sudo apt-get install libboost-all-dev
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
```bash
export PATH=$PATH:$HOME/install/bin
```
