package com.myfirstapp.firebase_java_test;

public class Celestial {

    String CelestialBody;

    public Celestial() {
    }

    public Celestial(String celestialBody) {
        CelestialBody = celestialBody;
    }

    public String getCelestialBody() {
        return CelestialBody;
    }

    public void setCelestialBody(String celestialBody) {
        CelestialBody = celestialBody;
    }
}
