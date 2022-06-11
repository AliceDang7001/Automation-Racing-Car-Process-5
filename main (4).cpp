
#include "mbed.h"

// Assigning Pinouts for the Microcontroller //

// Motor Control //
PwmOut A(D6);
PwmOut B(D9);
PwmOut C(D10);
PwmOut D(D5);

// Servo Motors //
PwmOut scoop(A6);
PwmOut claw(A2);
PwmOut collector(A1);
PwmOut whiteBucket(A5);
PwmOut blackBucket(D3);

// Optosensor //
AnalogIn opto(A3);

// Button //
DigitalIn button(D2);

// ------------------------------------------------------------------------------------- //

// Movement Functions //

// Drive Forward //
void forward(float time1){
    A=1, B=0, C=1, D=0;
    wait(time1);
    A=0, B=0, C=0, D=0;
    }
    
// Drive Backwards //
void reverse(float time2){
    A=0, B=1, C=0, D=1;
    wait(time2);
    A=0, B=0, C=0, D=0;
    }
    
// Turn Left //
void right(float time3){
    A=1, B=0, C=0, D=1;
    wait(time3);
    A=0, B=0, C=0, D=0;
    }
    
// Turn Right //
void left(float time4){
    A=0, B=1, C=1, D=0;
    wait(time4);
    A=0, B=0, C=0, D=0;
    }
    
void shake(){
    A=1, B=0, C=1, D=0;
    wait(.2);
    A=0, B=0, C=0, D=0;
    wait(.2);
    A=0, B=1, C=0, D=1;
    wait(.2);
    A=0, B=0, C=0, D=0;
    }

// Setup Periods //
void period(){
    A.period(.01);
    B.period(.01);
    C.period(.01);
    D.period(.01);
    }
    
// ------------------------------------------------------------------------------------- //
    
// Main Code //
int main(){
    
    // Push to Start
    while(button == 0){
        
        }
    wait (1);
    
    // Set initial positions
    
    scoop.pulsewidth_us(2000);
    wait(1.5);
    collector.pulsewidth_us(1400);
    wait(1.5);
    claw.pulsewidth_us(1425);
    wait(1.5);
    whiteBucket.pulsewidth_us(1550);
    wait(1.5);
    blackBucket.pulsewidth_us(1550);
    wait(1.5);
    
    // Push to Start
    while(button == 0){
        
        }
    wait (1);
    
    // Set Periods //
    period();
    
    // Begin the journey of collecting, sorting, and delivering //
    
    // Get to the blocks in order to scoop them up
    forward(.75);
    
    wait(0.5);
    
    left(0.35);
    
    wait(0.5);
    
    forward(1.5);
    
    // Collect the blocks
    
    collector.pulsewidth_us(1400);
    wait(1);
    collector.pulsewidth_us(2000);
    
    // Lift the scoop upwards and reset scoop and collector to initial position
    
    scoop.pulsewidth_us(900);
    wait(2.5);
    scoop.pulsewidth_us(1500);
    wait(0.5);
    collector.pulsewidth_us(1400);
    
    // Sort and Shimmy 
        while(1){
            wait(2); 
            float analog = opto * 3.3;    
            int i = 0;
            float average = 0;
            
            shake();
            
            if(analog < 3.22){
                
                while(i <= 15){
                float analog = opto * 3.3; 
                average = average + analog;
                i++; 
                    
                }
                average = average / i; 
                claw.pulsewidth_us(1425);    
                wait(1); 
                
                
                //Black Block 
                if(average < 3.2 && average > 1.7){   
                wait(1);
                claw.pulsewidth_us(2400);
                wait(2);
                claw.pulsewidth_us(1425);    
                wait(1);
                 }
    
                if(average <= 1.5){                 
                //White Block
                wait(1);
                claw.pulsewidth_us(550);
                wait(2);
                claw.pulsewidth_us(1425);    
                wait(1);
            
                }
            
            }

        }
        
    // Deliver the White Blocks to the base
    
    while(button == 0){
        reverse(1);
        wait(0.01);
        }
        
    forward(0.2);
        
    right(0.5);
        
    while(button == 0){
        reverse(1);
        wait(0.01);
        }
        
    whiteBucket.pulsewidth_us(800);
    }

        

