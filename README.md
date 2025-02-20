<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>

<h1>🎮 Particle Collision Simulation using Raylib 🚀</h1>

<p>
    A simple physics engine built using <strong>C</strong> and <strong>Raylib</strong> to simulate the movement 
    and collision of particles under gravity. The simulation evolves through multiple versions, incorporating 
    friction, variable particle sizes, and alpha blending for enhanced realism.
</p>

<h2>📌 Features</h2>
<ul>
    <li>✔️ Basic <strong>particle movement</strong> under gravity</li>
    <li>✔️ <strong>Elastic collisions</strong> between particles</li>
    <li>✔️ <strong>Wall collisions</strong> with velocity damping</li>
    <li>✔️ <strong>Friction force</strong> to slow particles over time</li>
    <li>✔️ <strong>Variable particle sizes</strong> for more realistic dynamics</li>
    <li>✔️ <strong>Alpha blending</strong> to simulate fading effects</li>
</ul>

<h2>🔧 Installation & Setup</h2>

<h3>1️⃣ Install Raylib</h3>
<p>Ensure you have <strong>Raylib</strong> installed on your system:</p>

<h4>Windows (MSYS2)</h4>
<pre><code>pacman -S mingw-w64-x86_64-raylib</code></pre>

<h4>Linux (Ubuntu/Debian)</h4>
<pre><code>sudo apt install libraylib-dev</code></pre>

<h4>macOS (Homebrew)</h4>
<pre><code>brew install raylib</code></pre>

<h3>2️⃣ Clone the Repository</h3>
<pre><code>git clone https://github.com/Assem-ElQersh/Particle-Collision-Simulation.git
cd particle-simulation</code></pre>

<h3>3️⃣ Compile & Run</h3>
<pre><code>gcc main.c -o main -lraylib -lopengl32 -lgdi32 -lwinmm
./main</code></pre>
<p><em>(Replace <code>main.c</code> with any other version file if needed, I recommend trying <code>third version - support particles of different sizes.c</code> first)</em></p>

<h2>📂 Project Versions</h2>
<table border="1">
    <tr>
        <th>Version</th>
        <th>Features Added</th>
    </tr>
    <tr>
        <td><strong>main.c</strong></td>
        <td>Basic gravity & collisions</td>
    </tr>
    <tr>
        <td><strong>second version - added friction force.c</strong></td>
        <td>Introduced <strong>friction</strong> for damping</td>
    </tr>
    <tr>
        <td><strong>third version - support particles of different sizes.c</strong></td>
        <td>Added <strong>variable particle sizes</strong></td>
    </tr>
    <tr>
        <td><strong>fourth version - alpha blending.c</strong></td>
        <td>Implemented <strong>alpha transparency</strong> for fading effect</td>
    </tr>
</table>

<h2>🎯 Future Improvements</h2>
<ul>
    <li>✅ <strong>Optimize performance</strong> using <strong>QuadTree spatial partitioning</strong></li>
    <li>✅ Implement <strong>inelastic collisions</strong> for more realism</li>
    <li>✅ Introduce <strong>mouse interactions</strong> (dragging, repelling particles)</li>
    <li>✅ Use <strong>multithreading (OpenMP)</strong> to improve efficiency</li>
</ul>

<h2>📜 License</h2>
<p>
    This project is licensed under the <strong>MIT License</strong>. Feel free to use and modify it!
</p>

</body>
</html>
