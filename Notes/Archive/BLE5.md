GATT :  Generic Attributes
RTLS : real-time locating systems
IPS : indoor positioning systems
IQ : In-Phase and Quadrature
HCI : Host Controller Interface
LL : link layer
CTE : Constant Tone Extension
PDU : Protocol Data Unit
CRC : cyclic redundancy check
ATT : Attribute Protocol
PAST : Periodic Advertising Sync Transfer
AFH (Adaptive Frequency Hopping

*********************************
*	DIRECTION FIDING	*
*********************************

***** AoA Method *****
- Angle of Arrival
- Array of antennae in receiver required


***** AoD Method *****
- Angle of Departure
- Array of antennae in transmitter required

*****************************************
*	GATT Caching Enhancements	*
*****************************************

***** GATT device *****
- Attribute table :
(always be the same in some devices)
	- services
	- characteristics
	- descriptors
(change)
	- value of these attributes above

- Service Discovery : a procedure that client performs to get information
about attribute table of Server

***** Change of attribute table *****
- server informs client by sending an ATT indication
- client replied with an ATT confirmation and performed service discovery

- Service Changed : a procedure that server performs to informs clients
about changes in the attribute table

***** Improved Caching Strategy
- Data Hash characteristic : allows the client to ask the server if anything has changed

- For the first connection, the server hashes the attribute table and send the hash code to client
- Client then stores that data and subsequently uses it to determine if there is any change in
attribute table of server (by comparing the hash value)
- If there is any changes, client perform a Service Discovery

***** Better State Management
- State machine : define whether or not the clien attribute table cache and the server attribute table
are in sync and decide if the client needs to perform service discovery.

- There are 2 states of client :
	- change-aware : 
	- change-unaware : server will ignore all ATT command from client
	
*****************************************
*	ADVERTISING ENHANCEMENT		*
*****************************************

***** RANDOMIZED ADVERTISING CHANNEL INDEXING *****
- Normally, when all three channels are in use, advertising uses channels in the sequence 
(par ex : 37->38->39)
- BLE5 stipulate that it's must have random delay (0-10ms) between advertising events to avoid collision data package

- Device in the advertising state can now select channels in the random order 
(39-38-37 38-37-39) - avoid collisions

***** Periodic Advertising Sync Transfer *****
- Normally, AUX_ADV_IND PDUs in advertising device contain SyncInfo field that has info about synchronize with the periodic advertising
- BENEFIT : more energy efficient, some cases require precise timing in the exchange of data.  	
- PROBLEM : some devices don't have enough energy or have limitations in duty cycle or scan time.

- New PAST feature allows another powerful device perform the synchronization and then pass the data to the less powerful device.
























































poulet legumes chat batterie sans-issue capitaine




























