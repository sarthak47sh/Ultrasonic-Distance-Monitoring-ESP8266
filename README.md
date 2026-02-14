<h1 align="center">Ultrasonic Distance Monitoring System (ESP8266)</h1>

<p align="center">
<b>Current Version:</b> 6<br>
<b>Status:</b> Completed
</p>

<hr>

<h2>Overview</h2>

<p>
This project implements an ultrasonic distance monitoring system using a 
<b>NodeMCU ESP8266</b> and an <b>HC-SR04 ultrasonic sensor</b>. 
The system measures distance in real time, provides LED-based proximity indication, 
and logs data to the cloud using ThingSpeak.
</p>

<p>
The project was developed incrementally, evolving from basic distance measurement 
into a modular, IoT-enabled embedded system with improved firmware architecture 
and system responsiveness.
</p>

<hr>

<h2>Key Features</h2>

<ul>
<li>Real-time distance measurement using ultrasonic time-of-flight</li>
<li>LED-based proximity indication (Green, Yellow, Red)</li>
<li>Cloud data logging using ThingSpeak IoT platform</li>
<li>Modular and maintainable firmware architecture</li>
<li>Non-blocking timing using <code>millis()</code></li>
<li>Safe hardware interfacing using voltage protection</li>
</ul>

<hr>

<h2>Project Objective</h2>

<p>
To design and implement a reliable embedded system for distance measurement while 
applying clean firmware design principles, hardware safety considerations, 
and IoT integration suitable for real-world embedded applications.
</p>

<hr>

<h2>Components Used</h2>

<ul>
<li>NodeMCU ESP8266</li>
<li>HC-SR04 Ultrasonic Sensor</li>
<li>Red LED</li>
<li>Yellow LED</li>
<li>Green LED</li>
<li>Current limiting resistors</li>
<li>Breadboard</li>
<li>Jumper wires</li>
</ul>

<hr>

<h2>Working Principle</h2>

<p>
The HC-SR04 ultrasonic sensor measures distance using the time-of-flight method:
</p>

<ol>
<li>ESP8266 sends a trigger pulse</li>
<li>Sensor emits ultrasonic wave</li>
<li>Wave reflects from object</li>
<li>Echo pin stays HIGH for round-trip time</li>
<li>Distance is calculated using timing measurement</li>
</ol>

<p><b>Formula:</b></p>

<pre>
Distance = (Time × Speed of Sound) / 2
</pre>

<hr>

<h2>Hardware Connections</h2>

<h3>Ultrasonic Sensor</h3>

<ul>
<li>VCC → Vin (5V)</li>
<li>GND → GND</li>
<li>TRIG → D6</li>
<li>ECHO → D5 (via voltage divider for 3.3V protection)</li>
</ul>

<h3>LED Connections</h3>

<ul>
<li>Green LED → D1</li>
<li>Yellow LED → D2</li>
<li>Red LED → D3</li>
</ul>

<hr>

<h2>System Architecture</h2>

<h3>Logical Flow</h3>

<pre>
Ultrasonic Sensor
      ↓
ESP8266
      ↓
Distance Calculation
      ↓
Decision Logic
      ↓
LED Indicators
      ↓
ThingSpeak Cloud
</pre>

<h3>System Description</h3>

<ul>
<li>ESP8266 measures echo timing</li>
<li>Distance is calculated using time-of-flight</li>
<li>Firmware compares distance with thresholds</li>
<li>LEDs indicate proximity locally</li>
<li>Data is uploaded to ThingSpeak cloud</li>
</ul>

<hr>

<h2>LED Indication Logic</h2>

<table border="1" cellpadding="8">
<tr>
<th>Distance (cm)</th>
<th>LED</th>
</tr>

<tr>
<td>&gt; 50</td>
<td>Green</td>
</tr>

<tr>
<td>20 – 50</td>
<td>Yellow</td>
</tr>

<tr>
<td>&lt; 20</td>
<td>Red</td>
</tr>

</table>

<hr>

<h2>Firmware Design Highlights</h2>

<ul>
<li>Modular functions for sensor reading and LED control</li>
<li>Use of named constants</li>
<li>Defensive checks for invalid readings</li>
<li>Clean and maintainable firmware structure</li>
<li>Non-blocking timing using <code>millis()</code></li>
</ul>

<hr>

<h2>IoT Integration</h2>

<p>
ESP8266 connects to WiFi and uploads distance data to ThingSpeak cloud, 
enabling remote monitoring and visualization.
</p>

<hr>

<h2>Performance Optimization</h2>

<h3>Problem</h3>

<p>
ThingSpeak requires a minimum 15-second update interval, causing slow system response.
</p>

<h3>Solution</h3>

<p>
Local sensor processing was separated from cloud upload timing using non-blocking scheduling 
with <code>millis()</code>, ensuring responsive system behavior.
</p>

<hr>

<h2>Version History</h2>

<h3>Version 1 – Basic Measurement</h3>
<ul>
<li>Sensor interfacing</li>
<li>Serial output</li>
</ul>

<h3>Version 2 – LED Indication</h3>
<ul>
<li>Added LEDs</li>
<li>Distance threshold logic</li>
</ul>

<h3>Version 3 – Code Refactoring</h3>
<ul>
<li>Modular firmware design</li>
</ul>

<h3>Version 4 – Documentation</h3>
<ul>
<li>Architecture documentation</li>
</ul>

<h3>Version 5 – IoT Integration</h3>
<ul>
<li>ThingSpeak connectivity</li>
</ul>

<h3>Version 6 – Optimization</h3>
<ul>
<li>Non-blocking timing</li>
<li>Improved responsiveness</li>
</ul>

<hr>

<h2>Skills Demonstrated</h2>

<ul>
<li>Embedded C/C++ programming</li>
<li>Sensor interfacing</li>
<li>GPIO control</li>
<li>Firmware architecture design</li>
<li>Non-blocking embedded timing</li>
<li>IoT integration</li>
<li>Hardware-software integration</li>
</ul>

<hr>

<h2>Future Improvements</h2>

<ul>
<li>Web dashboard</li>
<li>Sensor data filtering</li>
<li>Battery operation</li>
<li>Multi-sensor support</li>
</ul>

<hr>

<h2>Author</h2>

<p>
<b>Sarthak Sharma</b><br>
Electronics and Communication Engineering<br>
IIIT Bhopal
</p>
