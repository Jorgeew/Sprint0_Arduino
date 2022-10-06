// ----------------------------------------------------
// Ejemplo IBeaconBasico.ino
// Adaptado de https://learn.adafruit.com/bluefruit-nrf52-feather-learning-guide/adafruitbluefruit
// Jordi Bataller Mascarell
// Modificado: Jorge Larrosa Quesada
// ----------------------------------------------------
#include <bluefruit.h>
// ----------------------------------------------------
// setup
// ----------------------------------------------------
void setup() {
   //
   //
   Serial.begin(115200);
   
   Serial.println("-----------------------\n");
   Serial.println(" PRUEBAS iBeacon  ");
   Serial.println("-----------------------\n");

   //
   // Initialise the Bluefruit module
   //
   Serial.println("Initialise the Bluefruit nRF52 module");
   Bluefruit.begin();

   //
   // Set the advertised device name (keep it short!)
   //
   Serial.println("Setting Device Name to GTI-3A " );

   //Nombre del Beacon
   Bluefruit.setName("GTI-JDEC");
   Bluefruit.ScanResponse.addName();

   //
   //
   //
   Serial.println("\nAdvertising");

} // setup()
 

//Función srartAdvertising()

// ----------------------------------------------------
// ----------------------------------------------------
// R, R --> ()
void startAdvertising(int datos, int sensor) {
   //Se le pasan los datos del sensor y el número que representa al sensor
   Serial.println( " startAdvertising() " );

   Serial.println( " Bluefruit.Advertising.stop(); ");
   Bluefruit.Advertising.stop(); // ya lo enchufo luego

   //
   // Advertising packet
   //
   Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
   Bluefruit.Advertising.addTxPower();

   //
   //
   //


   // Include Name
   Serial.println( " Bluefruit.Advertising.addName(); " );
   Bluefruit.Advertising.addName();

   //
   //
   //
   Serial.println( " Bluefruit.Advertising.setBeacon( elBeacon ); ");

   uint8_t beaconUUID[16] = {
     'E', 'P', 'S', 'G', '-', 'G', 'T', 'I',
     '-', 'P', 'R', 'O', 'Y', '-', '3', 'A'
     };
   BLEBeacon elBeacon( beaconUUID, datos, sensor, 73 );
   elBeacon.setManufacturer( 0x004c ); // aple id
   Bluefruit.Advertising.setBeacon( elBeacon );

   //
   //
   //
   Bluefruit.Advertising.restartOnDisconnect(true);
   Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
   Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
   Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds

   Serial.println( " Bluefruit.Advertising.start(0);" );

} // startAdvertising ()
 

//Proceso loop()

// ----------------------------------------------------
// ----------------------------------------------------
namespace Loop {
   int cont = 0;
};
// ....................................................
void loop() {

   using namespace Loop;

   cont++;

   delay(1000);

   startAdvertising(cont,5);

   Serial.print( " ** loop cont=" );
   Serial.println( cont );
} // ()
// ----------------------------------------------------
// ----------------------------------------------------
// ----------------------------------------------------
// ----------------------------------------------------