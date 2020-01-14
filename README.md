# FIT3143 Parallel Computing Assignment 2

## WSN Description
The wireless sensor network comprises 20 nodes and a base station. These nodes are arranged in a 4 x 5 (rectangular-shaped) grid.

Distance between the adjacent nodes is kept as such that these nodes can wirelessly communicate. The adjacent nodes can exchange data through unicast and broadcast modes of communications.

Communication between non-adjacent nodes is not possible.

Every node in the WSN can however independently exchange data with the base-station (e.g. through a satellite link). Base-station for this WSN is an additional computer node that is entrusted with the task of gathering data from all the 20 nodes in the WSN.

## Event Detection Criterion: 
In order for an event to be recorded by the WSN, at least three adjacent nodes, to a reference node, must simultaneously report their activations to the base-station (explanatory in Section III). The base station then collects all the event reports and writes these to its log file.

## Assignment Project: 
Develop a Message Passing Interface (MPI) C code that simulates the operation of this WSN including the base station in an efficient manner. The criterion for measuring efficiency in this exercise is in finding a communication scheme that minimises the messages to the base- station whilst satisfying the WSN’s event detection criterion (stated above). In addition, the events and/or messages sent between adjacent nodes and to the base station are to be encrypted. You can choose and implement any C based encryption algorithm. You are also allowed to use available encryption algorithms (in C programming language) provided you properly cite the owner of the algorithm (in your C source code and in your report). More importantly, you are required to demonstrate the use of Open Multi-processing (OpenMP) to improve the performance of the applied encryption algorithm.
Hints:
1. Assume that a set of MPI tasks (processes) represents the WSN and each MPI task can represent a WSN node.
2. In order to simulate random occurrences of events within the WSN, each WSN node may be provisioned with an independent random number generator with the condition that at least three adjacent nodes must produce the same random number, at the sampling time, to constitute an event.
3. Write the key performance metrics e.g. the simulation time, number of events detected, number of messages/event with senders’ adjacency information/addresses, total number of messages (for this simulation), to an output file. Doing so may assist in proving the correctness and efficiency of your implementation.
