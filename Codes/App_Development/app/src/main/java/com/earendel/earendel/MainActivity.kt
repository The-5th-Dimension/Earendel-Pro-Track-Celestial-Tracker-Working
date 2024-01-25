package com.earendel.earendel

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

            val starButton = findViewById<Button>(R.id.btnStar)
            val planetButton = findViewById<Button>(R.id.btnPlanet)

        starButton.setOnClickListener{
            val intent = Intent(this, StarActivity::class.java)
            startActivity(intent)
        }

        planetButton.setOnClickListener{
            val intent = Intent(this, PlanetActivity::class.java)
            startActivity(intent)
        }

    }
}