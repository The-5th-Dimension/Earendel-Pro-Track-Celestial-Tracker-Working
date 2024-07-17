package com.earendel.earendel

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.AdapterView
import android.widget.ArrayAdapter
import android.widget.ListView
import android.widget.Toast
import com.google.firebase.database.FirebaseDatabase

class PlanetActivity : AppCompatActivity() , AdapterView.OnItemClickListener {

    private val databaseReference = FirebaseDatabase.getInstance().reference
    private val planet = arrayOf("Sun", "Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune", "Moon")

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_planet)

        val listView: ListView = findViewById(R.id.planet_list)
        val arrayAdapter: ArrayAdapter<String> = ArrayAdapter(applicationContext,
            android.R.layout.simple_list_item_1, planet)

        listView.adapter = arrayAdapter
        listView.onItemClickListener = this

    }

    override fun onItemClick(parent: AdapterView<*>?, view: View?, position: Int, id: Long) {
        val options: String = parent?.getItemAtPosition(position) as String
        Toast.makeText(applicationContext, "$options is Selected",
            Toast.LENGTH_LONG).show()
        writeToFirebase(options)
    }

    private fun writeToFirebase(options: String) {
        val optionsRef = databaseReference.child("Planet")
        optionsRef.setValue(options)
    }
}