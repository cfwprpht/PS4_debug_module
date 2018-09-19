
     ____  __________ __ ___    ___  ___ ___ ____ __ ____    ____
     || \\||   || ))| ||// \\   ||\\//||// \\|| \\|| ||||   ||   
     ||  ))|== ||=)|| |(( ___   || \/ |((   ))|  ))| ||||   ||== 
     ||_//||___||_))\_//\\_||   ||    ||\\_//||_//\\_//||__|||___
     
     
## What's this ?
     A driver for debugging reasons. Will jailbreak the process if needed so,
     that it hase access to fs and can write a file to usb.
     
## Does it need any special drivers to be loaded ?
     No. Only the system drivers which are automaticly loaded.
     The Fios2 should be initialized before you run this prx.
     
## How to use ?
     You need to add the PRX project to yours app one
     and set a depense from your project to the dll.
     Use "dinit()" and "dfinalize()" to initialize or finalize the driver.
     For a message just use "debug()".
     A log file is then written to the connected and first found
     usb device. The actual time will be used for the name.
     At last, don't forget to load the prx from your pkg installation
     before using it.
     
     
     -Have Fun- cfwprpht