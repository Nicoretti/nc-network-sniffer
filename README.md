# A simple network sniffer for Linux

## Build  
A Make and a Bake based build is suppored.

### Make based build
 * Run make based build
    `make`
 * executable can be found at /out/sniffer

### bake based build
 * Install the bake build tool 
    `gem install bake-toolkit`
 * Run bake based build in nc-network-sniffer directory
    `bake Debug -v2 -a black`
 * executable can be found at
      
## Usage
**Attention:** requires root privileges.
  `snf INTERFACE` 
  
Example (Sniff trafic on eth0): 
    `sniffer eth0`
  
For futher details see http://nicoretti.github.io/nc-network-sniffer/.
