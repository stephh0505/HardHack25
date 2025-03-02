# Magiclick Pill Case

**MARKETING PITCH**

Introducing the MagiClick Pill Case – the smart, simple solution designed with seniors in mind. Never miss a dose again: set your personalized schedule and let the bright LED reminder guide you to the right compartment. Its intuitive analog design and expandable setup make managing multiple medications effortless. Enjoy peace of mind and stay independent with MagiClick. Developed by team CACKS.

### Table of Contents
1. **Background**
2. **Market Exploration**
3. **Design and Prototyping**
4. **Challenges**
6. **Feature Summary**

## Background
HardHack 2025 is a 36-hour hackathon that largely focuses on the development of hardware through Arduino and Raspberry Pi boards. HardHack offers three tracks: beginner - health devices, intermediate - smart devices, and advanced - sustainable devices. Our team chose the beginner track as it was our first hackathon, and we were relatively new to hardware design.

## Market Exploration
Before designing our product, our team spent several hours analyzing the medical device market for a niche that we could target. Eventually, we settled on assisting the elderly, especially those who are forgetful or have neurodegenerative diseases, be more independent. Since elderly people take lots of pills to maintain their health, we wanted to develop a pill case that was straightforward to use, didn't require digital technology, and easily expandable while maintaining compact.

## Design Iteration Process
Our initial design was a simple pill case with three sliding drawers. At the back of each drawer would be a button (connected to an arduino nano) that, when pressed, would begin a timer. Once the timer ends, a signal would be sent to the piezoelectric buzzers that would alert the user to take their pills. However, we noticed several issues with that design such as confusion on which pill to take, inflexible timers for pills, and limited quantity of pills.

Thus, we began to iteratively address each problem with new features: a t-shape groove on each sliding drawer that allows the pill case to be extended, different colored lights that indicates which pills should be taken, an LCD display that showed the time and what time each pill should be taken, and a keypad that allows users to change the date and pill times. Each feature was first tested before being added to the final product.

## Challenges
Our team faced a few challenges when it came to both hardware and software development. In hardware, everything went smoothly until it came time to solder the entire circuit onto a DigiKey solder board. Initially, the process was finished in under an hour, but would continuously error out when running software that worked on the pre-solder circuit. The debugging process would then go on to take well over three hours, with the issue mainly pertaining to wires touching multiple rails on the circuit board. 

In software, it was challenging to learn new libraries and the Arduino language. Furthermore, the buttons would sometimes not send a signal (or the signal would not be processed) when pressed, leading to the light/buzzer continuously buzzing, which would also take several hours to debug.

## Feature Summary
Here is a video that goes over the features of our prototype. 

[![Watch the video](https://i9.ytimg.com/vi_webp/CwNRd6YSiFY/mqdefault.webp?v=67c4405f&sqp=CIyAkb4G&rs=AOn4CLCaclyy-LqLTrT5V0faLmEKbebY6Q)](https://www.youtube.com/watch?v=CwNRd6YSiFY)


