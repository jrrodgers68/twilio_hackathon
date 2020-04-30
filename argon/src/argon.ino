/*
 * Project argon
 * Description: Simple app to allow Argon to receive commands and forward them to Sparki
 * Author: John Rodgers
 * Date: 4/27/2020
 */

int sparkiCommand(String command);

// setup() runs once, when the device is first turned on.
void setup() {
    // Put initialization like pinMode and begin functions here.
    Serial.begin(9600);
    Serial1.begin(9600);  // we talk to Sparki over TX/RX

    // we're going to skip calling Particle.connect
    if(Particle.connected() == false)
    {
        WiFi.on();
        Particle.connect();
    }

    bool result = Particle.function("sparki", sparkiCommand);
    if(!result)
    {
        Serial.print("Failed to register our function!!");
    }

}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
    // The core of your code will likely live here.

}

int sparkiCommand(String command)
{
    // just send the command directly to Sparki
    //  these come from a controlled source
    Particle.publish("SPARKI_COMMAND", command.c_str(), 60, PRIVATE); 
    Serial1.print(command.c_str());
    Serial1.print("\n"); // end of command indicator to Sparki
    return 0;
}
