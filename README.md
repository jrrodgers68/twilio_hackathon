# twilio_hackathon

## Sparki meets Twilio

Welcome to the wonderful world of robotics!  And text messages!  2 of the world's greatest 
inventions combined into a single project - sliced bread doesn't stand a chance!

This project requires 2 pieces of hardware to make the magic happen:
  - [Arcbotics Sparki robot](http://arcbotics.com/products/sparki/)
  - [Particle Argon](https://store.particle.io/products/argon)
  
  The Particle Argon gives Sparki the commands it receives from its REST api.  Sparki does all the work.
  
  So to make this work, you'll need to upload the sparki control logic to the robot.  This happens over a USB 
  cable directly connected to Sparki.  After that, you'll need to obtain the Argon and follow the setup instructions
  to claim it into your account.  You can then either use the WebIde at particle.io or setup a local development 
  environment using Visual Studio Code and the Particle Workbench.  Flash your new device with the supplied code.
  
  Finally, you will need to go to Twilio.com and add a project.  Add a new phone number and configure the messaging 
  to forward SMS notifications to the python service.  Since you are likely behind a firewall at home, you can check
  out a great helper like [ngrok](https://ngrok.com/) to make life easier and safer getting to your locally running
  python service.
  
  Once all that is done, put Sparki on the floor after turning him on, put your feet and grab your phone, and start
  texting commands to your robot.  The currently supported commands are as follows:
                 f  ==  forward
                 b  ==  backward
                 l  ==  turn left 
                 r  ==  turn right
                 s  ==  stop moving
                 d  ==  do a little dance
                 n  ==  do a little nerd dance
                 
  What more could you ask for?
