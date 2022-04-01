# Tello-C

Tello-C is a C client library for the Tello drone.

All movement commands are provided as API functions in order to provide
improved position tracking without using a mission pad. This position
is provided alongside the state information that the Tello itself
provides for ease of use.

## API

The API is a mixture of synchronous commands
and state retrieval functions.

While the functionality of the library utilizes threading to handle the
multiple connections to Tello, the API is not thread-safe and should
be mutex protected for each Tello instance.

### Memory Responsibility
In order to provide compatibility with other languages, any memory allocated
by the library must be freed by the library. This allows abstraction and
protection of internal data. This concept applies to the configuration
object, the library instance, and any replies from the drone. Each of these
objects has an associated free function in the API.

### Connecting

Connecting to a Tello drone is as simple as instantiation via the API.
Once instantiated successfully, all necessary connections to the drone
have been made.

#### Configuration

All configuration of the connection is done via the configuration API in
`api/telloc_config.h`. See below for a list of the configuration parameters
and what they control.

| Parameter              | Type         | Units        | Description                                                                                                                   |
| ---------------------- | ------------ | ------------ | ----------------------------------------------------------------------------------------------------------------------------- |
| ipAddress              | char*        | N/A          | IP address of the drone to connect to.                                                                                        |
| commandPort            | unsigned int | N/A          | UDP port to send commands to.                                                                                                 |
| statePort              | unsigned int | N/A          | UDP port that state updates should be received on.                                                                            |
| commandResponseTimeout | unsigned int | milliseconds | Amount of time that the library should wait between sending a command receiving the response before treating it as a failure. |
| stateTimeout           | unsigned int | milliseconds | Amount of time between state updates that the library should wait before throwing an exception.                               |

Note that upon instantiation of the library, the configuration structure can
be cleaned up using the provided function.

### Cleaning Up

The connection to the drone is cleaned up as part of freeing the library
instance. For more information, see "Memory Responsibility".

### Sending Commands

TBD

### Errors

TBD
