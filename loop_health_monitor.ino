Simple Loop-Rate Health Monitor Example (Arduino / ESP32)

/*
    Lightweight Loop-Rate Health Monitor
    ------------------------------------
    Basic concept demonstration.

    - Main loop increments a counter.
    - Supervisor checks loop rate every second.
    - If loop-rate drops below threshold:
        -> warning
        -> recovery attempt
        -> optional restart

    Compatible with Arduino / ESP32 style environments.
*/

volatile unsigned long loopCounter = 0;

unsigned long previousCounter = 0;
unsigned long lastCheck = 0;

const unsigned long checkInterval = 1000; // 1 second
const unsigned long threshold = 5000;     // minimum loops/sec

int warningLevel = 0;

void setup() {
    Serial.begin(115200);

    Serial.println("System started");
}

void loop() {

    // Main runtime heartbeat
    loopCounter++;

    // Supervisor timing
    if (millis() - lastCheck >= checkInterval) {

        unsigned long currentCounter = loopCounter;
        unsigned long delta = currentCounter - previousCounter;

        previousCounter = currentCounter;
        lastCheck = millis();

        Serial.print("Loops/sec: ");
        Serial.println(delta);

        // Threshold logic
        if (delta < threshold) {

            warningLevel++;

            Serial.println("WARNING: LOW LOOP RATE DETECTED");

            // Example recovery action
            recoverSubsystem();

            // Escalation
            if (warningLevel >= 3) {

                Serial.println("CRITICAL: SYSTEM RESTART");

                delay(1000);

                // ESP32 restart
                ESP.restart();

                // Arduino alternative:
                // NVIC_SystemReset();
            }

        } else {

            // Healthy system
            warningLevel = 0;
        }
    }

    // Simulated workload
    delayMicroseconds(50);
}


void recoverSubsystem() {

    Serial.println("Attempting subsystem recovery...");

    // Example actions:
    // reconnect WiFi
    // clear queues
    // restart sensor
    // flush buffers
}

Concept

This example demonstrates:

- loop-rate telemetry,
- lightweight runtime health monitoring,
- threshold-based state management,
- progressive recovery,
- and autonomous restart behavior.

The architecture can be expanded with:

- distributed telemetry,
- DDoS detection,
- router integration,
- safe-mode booting,
- diagnostics,
- and adaptive mitigation logic.
