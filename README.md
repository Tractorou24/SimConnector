<div align="center">
	<h1>SimConnector</h1>
	A SimConnect wrapper for unix systems.
</div>

## Home Cockpit Project Diagram

Basic overall diagram of the Home Cockpit project:
```
.----------.    Comm    .---------------.  SimConnect  .-----------.
|   Pi4    | <--------> | Sim Connector | <----------> | MSFS 2020 |
.----------.  protocol  .---------------.    LIB/DLL   .-----------.
```

## SimConnector

This project is a wrapper for SimConnect that allows it to be used on unix systems. It is designed to be used with a multiplatform communication system (like sockets/usbs).

- SimConnect is a DLL that is used to communicate with Microsoft Flight Simulator 2020. It is a Windows only library.
 
 Il also provides a useful API used in the Home Cockpit project. You can request, for example, all the date useful for the PFD, ND, or any other system and not une one single simvar.

## Design specifications

The SimConnector API is composed of (one or multiples):

Communication protocol:
- IConnection: The module responsible of sending/recieving data from ONE SINGLE source.
- IConnectionManager: The module responsible of handling multiple IConnection.
- IRequest: The module sent by the client to request data from SimConnector.
- IResponse: The module recieved by the client after sending a request.

SimVars:
- ISimVar: A SimConnect simvar
- ISimVarGroup: A group of SimConnect simvars

Requests/Responses:
- Requests can be of 2 types, SetRequest or ReadRequest.
- Same for Responses, SetResponse or ReadResponse.

It's possible to get/set a single simvar using ISimVar or multiple simvars using the ISimVarGroup interface.
