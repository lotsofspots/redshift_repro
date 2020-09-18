# redshift_repro
Reproducer for a bug in the redshift driver on Linux - this was run on RHEL7.

Steps:
1. ./clean.sh - cleans up any existing build artifacts and driver files
2. ./setup.sh - downloads the 1.4.17.1000 driver, unpacks it and set up ini files
3. ./build.sh - builds the reproducer - a binary and a couple of libraries
4. Edit run.sh and fill in the necessary host and login credentials
5. ./run.sh - runs the reproducer
