# GPS
A library for reading NMEA data from a GPS module and producing Google search query URL for the coordinates 

This library was used in a car emergency system project where it read the navigational data from an attached GPS module and produced an SMS to be sent to emergency services via a GSM module. The result for the sample function creates a line of text with a Google search query URL mainly for testing, but can easily be manipulated. Communications between the GPS module and the central device (STM32 Nucleo-144 was used in this particular project) ran via a UART connection.

This GPS library can be used with any GPS module supporting the official NMEA standard for marine navigation.
