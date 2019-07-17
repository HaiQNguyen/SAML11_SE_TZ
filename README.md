# TrustZone and Symmetric authentication Use case

## Overview

This use case explains how to use TrustZone on ARM Cortex-M33 for IP protection and ATECC508 for authentication.  

## Requirements

* SAML11 Xplained Pro
* ATECC508 with adapter board

![Use case setup](https://bitbucket.org/hainguyenprivaterepo/trustzone_atecc_usecase/raw/41799cedc73b426626c4b96c1c6c4739736b1f5a/Doc/Image/system_setup.jpg) 

## Description

![Authentication and TP protection](https://bitbucket.org/hainguyenprivaterepo/trustzone_atecc_usecase/raw/41799cedc73b426626c4b96c1c6c4739736b1f5a/Doc/Image/TrustZone_and_Authentication.png)

### Terminology

+ **Non-secure application** is supposed to be an application developed by third party.  This application is located in non-secure memory area ( non-TrustZone area). This application calls an API ( Sum function ) located in the TrustZone area through the Veneer Table. Before the calling happens, this application has to authenticate to the Secure application.
+ **Secure application** is located in the secure memory area (TrustZone area) . This application is responsible for hosting the API, which the non-secure application wants to call. It is also responsible for authenticating the non-secure application. 

### Scenario

* When the non-secure application tries to call the the API in TrustZone area, the secure application checks if the non-secure one is already authenticated and allows the API to run or showing error message. 
* The non-secure application can access to the API by first authenticating to the secure application. The secure application carries out the authentication process and return the status if authentication. Then the non-secure application is allowed to access the API.  

## Runinng the use case

* Download the project file and open it with Atmel Studio. 
* Start TeraTerm with the following setup: 
  * Baudrate 9600 
  * Data: 8
  * No parity
  * Stop bit: 1
* Compile and run the code, below is the result from console:

![Log from terminal](https://bitbucket.org/hainguyenprivaterepo/trustzone_atecc_usecase/raw/41799cedc73b426626c4b96c1c6c4739736b1f5a/Doc/Image/log.PNG)

## Release note

### Version 1.0

* Initialize version

### Version 1.1

* Modify secure API in TrustZone from a sum function to a random function to simulate the temperature data
* Modify 2-page brochure

## Contact 

Quang Hai Nguyen 

Arrow Central Europe GmbH 

qnguyen@arroweurope.com

